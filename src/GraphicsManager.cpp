#include <cstdlib>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"

GraphicsManager* GraphicsManager::gm = nullptr;

static const GLfloat lineData[] =
{
  0.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 1.0f
};

// -------------------
// INITALIZE / CLEANUP
// -------------------

GraphicsManager::GraphicsManager(int width, int height, bool fullscreen)
                                :camera(nullptr)
{
  // set a reference for the singleton instance
  if(gm == nullptr)
  {
    gm = this;
  }

  // initialize GLFW (the window manager)
  if(!glfwInit())
  {
    std::cerr << "Error: GLFW could not be initialized" << std::endl;
    exit(EXIT_FAILURE);
  }

  // set some flags (hints, I guess) for the window
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // apparently this is only needed for macs
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the actual window
  if(fullscreen)
  {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    std::cout << "starting in fullscreen mode with dimensions " << 
      mode->width << "x" << mode->height << std::endl;

    window = glfwCreateWindow(mode->width, mode->height, 
                              "FPS Game", monitor, NULL);

    width = mode->width;
    height = mode->height;
  }
  else
  {
    std::cout << "starting in windowed mode with dimensions " 
              << width << "x" << height << std::endl;
    window = glfwCreateWindow(width, height, "FPS Game", NULL, NULL);
  }

  if(window == NULL)
  {
    std::cerr << "Error: window could not be created" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if(glewInit() != GLEW_OK)
  {
    std::cerr << "Error: GLEW could not be initialized" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // set the background color and depth options
  glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // generate the vertex array
  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);

  // load, compile and link the shaders
  programID = loadShaders("shaders/VertexShader.glsl",
                          "shaders/FragmentShader.glsl");

  // check for errors
  if(programID == 0)
  {
    std::cerr << "Error: OpenGL program could not be created" << std::endl;
    exit(EXIT_FAILURE);
  }


  // setup a vertexbuffer for a single line
  glGenBuffers(1, &lineVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lineData), lineData, GL_STATIC_DRAW);

  // setup MVP matrix (this will be done on the fly later)
  CameraMatrix = glm::lookAt(
    glm::vec3(0,0,0),
    glm::vec3(1,0,0),
    glm::vec3(0,1,0)
  );

  ProjectionMatrix = glm::perspective(
    glm::radians(45.0f),
    (float)width/(float)height,
    0.1f,
    100.0f
  );

  MVPMatrix = ProjectionMatrix * CameraMatrix;

  // get a reference to the matrix and texure sampler in the shaders
  textureSamplerID = glGetUniformLocation(programID, "texSampler");
  matrixID         = glGetUniformLocation(programID, "MVP");
  MVID             = glGetUniformLocation(programID, "MV");
  colorID          = glGetUniformLocation(programID, "shading");
  lightPositionID  = glGetUniformLocation(programID, "lightPosition");
  ambientID        = glGetUniformLocation(programID, "ambient");

  // load error texture
  loadErrorModel();

  // "load" white and error textures
  loadWhiteTexture();
  loadErrorTexture();
}

GraphicsManager::~GraphicsManager()
{
  std::cout << "shutting down graphics manager" << std::endl;

  // free model buffers
  for(auto i = modelMap.begin(); i != modelMap.end(); ++i)
  {
    glDeleteBuffers(1, &(i->second.vertexBuffer));
    glDeleteBuffers(1, &(i->second.uvBuffer));
    glDeleteBuffers(1, &(i->second.normalBuffer));
  }

  glDeleteBuffers(1, &lineVertexBuffer);
  glDeleteProgram(programID);

  // free texture buffers
  for(auto i = textureMap.begin(); i != textureMap.end(); ++i)
  {
    glDeleteTextures(1, &(i->second.textureBuffer));
  }

  glDeleteVertexArrays(1, &vertexArrayID);

  glfwDestroyWindow(window);
  glfwTerminate();
}

// --------------------------
// SINGLETON REFERENCE GETTER
// --------------------------

GraphicsManager& GraphicsManager::getReference()
{
  return *gm;
}

// ------------------------
// ETC. GETTERS AND SETTERS
// ------------------------

GLFWwindow* GraphicsManager::getWindow() const
{
  return window;
}

void GraphicsManager::setWindowSize(int w, int h)
{
  if(w != width || height != h)
  {
    width = w;
    height = h;

    ProjectionMatrix = glm::perspective(
      glm::radians(45.0f),
      (float)width/(float)height,
      0.1f,
      100.0f
    );
  
    MVPMatrix = ProjectionMatrix * CameraMatrix;

    glViewport(0,0,width,height);
  }
}

void GraphicsManager::unloadModel(std::string path) {}

bool GraphicsManager::isModelLoaded(std::string path) const
{
  return modelMap.find(path) != modelMap.end();
}

void GraphicsManager::unloadTexture(std::string path) {}

bool GraphicsManager::isTextureLoaded(std::string path) const
{
  return textureMap.find(path) != textureMap.end();
}

// ---------------
// MODEL RENDERING
// ---------------

void GraphicsManager::beginRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(programID);

  if(camera != nullptr)
  {
    Mat4 rot     = camera->getTransform().rot.toMatrix();
    Vec3 pos     = camera->getTransform().pos;

    Vec3 forward = rot * Vec3(1,0,0);
    Vec3 upward  = rot * Vec3(0,1,0);

    CameraMatrix = glm::lookAt(
      glm::vec3(pos.x, pos.y, pos.z),
      glm::vec3(pos.x + forward.x, pos.y + forward.y, pos.z + forward.z),
      glm::vec3(upward.x, upward.y, upward.z)
    );
  }
  else
  {
    CameraMatrix = glm::lookAt(
      glm::vec3(0,0,0),
      glm::vec3(1,0,0),
      glm::vec3(0,1,0)
    );
  }
}

void GraphicsManager::endRender() const
{
  glfwSwapBuffers(window);
}

void GraphicsManager::renderModel(std::string modelPath)
{
  renderModel(modelPath, "TEX_WHITE");
}

void GraphicsManager::renderModel(std::string modelPath, const Vec3& position,
                                  const Vec3& scale, const Quat& rotation)
{
  renderModel(modelPath, "TEX_WHITE", position, scale, rotation);
}

void GraphicsManager::renderModel(std::string modelPath, const Mat4& transform)
{
  renderModel(modelPath, "TEX_WHITE", transform);
}

void GraphicsManager::renderModel(std::string modelPath, std::string texPath)
{
  renderModel(modelPath, texPath, Mat4::Identity());
}

void GraphicsManager::renderModel(std::string modelPath, std::string texPath,
                                  const Vec3& position, const Vec3& scale, 
                                  const Quat& rotation)
{
  Transform t;
  t.pos = position;
  t.scale = scale;
  t.rot = rotation;
  renderModel(modelPath, texPath, t.toMatrix());
}

void GraphicsManager::renderModel(std::string modelPath, std::string texPath,
                                  const Mat4& transform)
{
  ModelMapEntry model;
  TextureMapEntry texture;

  if(modelMap.find(modelPath) == modelMap.end())
  {
    //std::cout << "WARNING: cannot render model: model " << modelPath 
    //          << ": does not exist" << std::endl;
    model = modelMap.at("MODEL_ERROR");
  }
  else
  {
    model = modelMap.at(modelPath);
  }

  if(textureMap.find(texPath) == textureMap.end())
  {
    //std::cout << "WARNING: cannot render model: texture " << texPath 
    //          << ": does not exist" << std::endl;
    texture = textureMap.at("TEX_ERROR");
  }
  else
  {
    texture = textureMap.at(texPath);
  }

  //std::cout << "vertexBuffer  = " << model.vertexBuffer << std::endl;
  //std::cout << "textureBuffer = " << texture.textureBuffer << std::endl;
  //std::cout << "uvBuffer      = " << model.uvBuffer << std::endl;

  glUniform3f(lightPositionID, 30.0f, 30.0f, 30.0f);
  glUniform3f(ambientID, 0.2f, 0.2f, 0.2f);

  // set the color to white
  glUniform3f(colorID, 1.0f, 1.0f, 1.0f);

  // reset the MVP matrix
  MVMatrix  = CameraMatrix * toGlmMat4(transform);
  MVPMatrix = ProjectionMatrix * MVMatrix;
  glUniformMatrix4fv(MVID, 1, GL_FALSE, &MVMatrix[0][0]);
  glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

  // bind the texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture.textureBuffer);
  glUniform1i(textureSamplerID, 0);

  glEnableVertexAttribArray(0);

  // bind the model
  glBindBuffer(GL_ARRAY_BUFFER, model.vertexBuffer);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glEnableVertexAttribArray(1);

  // bind the uvs
  glBindBuffer(GL_ARRAY_BUFFER, model.uvBuffer);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glEnableVertexAttribArray(2);

  // bind the uvs
  glBindBuffer(GL_ARRAY_BUFFER, model.normalBuffer);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glDrawArrays(GL_TRIANGLES, 0, 3 * model.triangleCount);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
    
void GraphicsManager::drawLine(const Vec3& a,const Vec3& b,const Vec3& color)
{
  glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(a.x, a.y, a.z));
  glm::mat4 scale = glm::scale(glm::mat4(), 
                               glm::vec3(b.x - a.x, b.y - a.y, b.z - a.z));

  // light (ambient is 1, so everything's always fully lit)
  glUniform3f(ambientID, 1.0f, 1.0f, 1.0f);

  // color
  glUniform3f(colorID, color.x, color.y, color.z);
  MVPMatrix = ProjectionMatrix * CameraMatrix * translate * scale;
  glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

  // bind the texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureMap.at("TEX_WHITE").textureBuffer);
  glUniform1i(textureSamplerID, 0);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );
  
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, textureMap.at("TEX_WHITE").textureBuffer);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glDrawArrays(GL_LINES, 0, 2);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void GraphicsManager::drawWireframeBox(const Vec3& center
                                      ,const Vec3& dimension
                                      ,const Vec3& color
                                      ,const Mat4& transform)
{
  Vec3 v[8];
  v[0] = center + Vec3(-dimension.x, -dimension.y, -dimension.z)/2;
  v[1] = center + Vec3( dimension.x, -dimension.y, -dimension.z)/2;
  v[2] = center + Vec3(-dimension.x,  dimension.y, -dimension.z)/2;
  v[3] = center + Vec3( dimension.x,  dimension.y, -dimension.z)/2;
  v[4] = center + Vec3(-dimension.x, -dimension.y,  dimension.z)/2;
  v[5] = center + Vec3( dimension.x, -dimension.y,  dimension.z)/2;
  v[6] = center + Vec3(-dimension.x,  dimension.y,  dimension.z)/2;
  v[7] = center + Vec3( dimension.x,  dimension.y,  dimension.z)/2;

  // bottom square
  drawLine(transform * v[0], transform * v[1], color);
  drawLine(transform * v[1], transform * v[3], color);
  drawLine(transform * v[3], transform * v[2], color);
  drawLine(transform * v[2], transform * v[0], color);

  // top square
  drawLine(transform * v[4], transform * v[5], color);
  drawLine(transform * v[5], transform * v[7], color);
  drawLine(transform * v[7], transform * v[6], color);
  drawLine(transform * v[6], transform * v[4], color);

  // walls
  drawLine(transform * v[0], transform * v[4], color);
  drawLine(transform * v[1], transform * v[5], color);
  drawLine(transform * v[2], transform * v[6], color);
  drawLine(transform * v[3], transform * v[7], color);
}

void GraphicsManager::setCamera(const Entity* e)
{
  camera = e;
}

glm::mat4 GraphicsManager::toGlmMat4(const Mat4& m)
{
  glm::mat4 retval;

  retval[0][0] = m.x[0];
  retval[1][0] = m.x[1];
  retval[2][0] = m.x[2];
  retval[3][0] = m.x[3];

  retval[0][1] = m.y[0];
  retval[1][1] = m.y[1];
  retval[2][1] = m.y[2];
  retval[3][1] = m.y[3];

  retval[0][2] = m.z[0];
  retval[1][2] = m.z[1];
  retval[2][2] = m.z[2];
  retval[3][2] = m.z[3];

  retval[0][3] = m.w[0];
  retval[1][3] = m.w[1];
  retval[2][3] = m.w[2];
  retval[3][3] = m.w[3];

  return retval;
}

bool GraphicsManager::isPowerOfTwo(unsigned int x)
{
  unsigned int a = 1;
  while (a<x)
  {
    a *= 2;
  }
  return (a==x);
}
