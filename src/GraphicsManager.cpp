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


  // setup a vertexbuffer for a single line
  glGenBuffers(1, &lineVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lineData), lineData, GL_STATIC_DRAW);

  // setup MVP matrix (this will be done on the fly later)
  CameraMatrix = glm::lookAt(
    glm::vec3(20,10,18),
    glm::vec3(0,0,0),
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
  colorID          = glGetUniformLocation(programID, "shading");

  // "load" white and error textures
  loadWhiteTexture();
  loadErrorTexture();
}

GraphicsManager::~GraphicsManager()
{
  std::cout << "shutting down graphics manager" << std::endl;
  glDeleteBuffers(1, &lineVertexBuffer);
  glDeleteVertexArrays(1, &vertexArrayID);
  glDeleteProgram(programID);

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

void GraphicsManager::beginRender() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(programID);
}

void GraphicsManager::endRender() const
{
  glfwSwapBuffers(window);
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
  if(modelMap.find(modelPath) != modelMap.end()
  && textureMap.find(texPath) != textureMap.end())
  {
    ModelMapEntry   model   = modelMap.at(modelPath);
    TextureMapEntry texture = textureMap.at(texPath);

    //std::cout << "vertexBuffer  = " << model.vertexBuffer << std::endl;
    //std::cout << "textureBuffer = " << texture.textureBuffer << std::endl;
    //std::cout << "uvBuffer      = " << model.uvBuffer << std::endl;

    // set the color to white
    glUniform3f(colorID, 1.0f, 1.0f, 1.0f);

    // reset the MVP matrix
    MVPMatrix = ProjectionMatrix * CameraMatrix * toGlmMat4(transform);
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

    glDrawArrays(GL_TRIANGLES, 0, 3 * model.triangleCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  }
  else
  {
    if(modelMap.find(modelPath) == modelMap.end())
    {
      std::cerr << "cannot render model: model " << modelPath 
                << ": does not exist" << std::endl;
    }
    if(textureMap.find(texPath) == textureMap.end())
    {
      std::cerr << "cannot render model: texture " << texPath 
                << ": does not exist" << std::endl;
    }

  }
}
    
void GraphicsManager::drawLine(const Vec3& a,const Vec3& b,const Vec3& color)
{
  glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(a.x, a.y, a.z));
  glm::mat4 scale = glm::scale(glm::mat4(), 
                               glm::vec3(b.x - a.x, b.y - a.y, b.z - a.z));

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
