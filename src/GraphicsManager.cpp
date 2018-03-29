#include <cstdlib>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"

GraphicsManager* GraphicsManager::gm = nullptr;

static const GLfloat g_vertex_buffer_data[] =
{
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f
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

  glClearColor(0.3f, 0.3f, 1.0f, 0.0f);

  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);

  programID = loadShaders("shaders/VertexShader.glsl",
                          "shaders/FragmentShader.glsl");

  // setup MVP matrix (this will be done on the fly later)
  CameraMatrix = glm::lookAt(
    glm::vec3(0,0,20),
    glm::vec3(0,0,0),
    glm::vec3(0,1,0)
  );

  ProjectionMatrix = glm::perspective(
    glm::radians(45.0f),
    (float)height/(float)width,
    0.1f,
    100.0f
  );

  MVPMatrix = ProjectionMatrix * CameraMatrix;

  matrixID = glGetUniformLocation(programID, "MVP");
}

GraphicsManager::~GraphicsManager()
{
  std::cout << "shutting down graphics manager" << std::endl;
  glDeleteBuffers(1, &vertex_buffer_test);
  glDeleteVertexArrays(1, &vertexArrayID);
  glDeleteProgram(programID);

  glfwTerminate();
}

// --------------------------
// SINGLETON REFERENCE GETTER
// --------------------------

GraphicsManager& GraphicsManager::getReference()
{
  return *gm;
}

// --------------------------
// SHADER LOADING / COMPILING
// --------------------------

GLuint GraphicsManager::loadShaders(std::string vertPath, std::string fragPath)
const
{
  // make the shaders
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // read vertex shader from file
  std::string vertexCode;
  std::string currentLine;
  std::ifstream vertexFile("./" + vertPath);
  if(vertexFile.is_open())
  {
    while(std::getline(vertexFile,currentLine))
    {
      vertexCode += currentLine + "\n";
    }
  }
  else
  {
    std::cerr << "cannot open vertex shader file \"" 
              << vertPath << "\"" << std::endl;
    return 0;
  }
  
  // read fragment shader from file
  std::string fragmentCode;
  std::ifstream fragmentFile("./" + fragPath);
  if(vertexFile.is_open())
  {
    while(std::getline(fragmentFile,currentLine))
    {
      fragmentCode += currentLine + "\n";
    }
  }
  else
  {
    std::cerr << "cannot open fragment shader file \"" 
              << fragPath << "\"" << std::endl;
    return 0;
  }

  // for checking for compilation errors
  GLint result = GL_FALSE;
  int infoLogLength;

  // compile vertex shader
  std::cout << "compiling vertex shader " << vertPath << ":" << std::endl;
  char const* vertexCodePointer = vertexCode.c_str();
  glShaderSource(vertexShaderID, 1, &vertexCodePointer, NULL);
  glCompileShader(vertexShaderID);

  // check that the vertex shader compiled successfully
  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if(infoLogLength > 0)
  {
    // there was some sort of error
    std::vector<char> errorMessage(infoLogLength + 1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &errorMessage[0]);
    std::cerr << &errorMessage[0] << std::endl;
    return 0;
  }


  // compile fragment shader
  std::cout << "compiling fragment shader " << fragPath << ":" << std::endl;
  char const* fragmentCodePointer = fragmentCode.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentCodePointer, NULL);
  glCompileShader(fragmentShaderID);

  // check that the vertex shader compiled successfully
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if(infoLogLength > 0)
  {
    // there was some sort of error
    std::vector<char> errorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &errorMessage[0]);
    std::cerr << &errorMessage[0] << std::endl;
    return 0;
  }

  // link the program
  std::cout << "linking shaders to program" << std::endl;
  GLuint programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  // check if the program linked correctly
  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if(infoLogLength > 0)
  {
    // there was some sort of error
    std::vector<char> errorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &errorMessage[0]);
    std::cerr << &errorMessage[0] << std::endl;
    return 0;
  }

  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  return programID;
}

// -------------------------
// MODEL LOADING / UNLOADING
// -------------------------

bool GraphicsManager::loadModel(std::string path)
{
  if(modelMap.find(path) != modelMap.end())
  {
    // if the model already exists, don't load it, we're done
    std::cout << "WARNING: model " << path 
              << "already exists, not loading again" << std::endl;
    return true;
  }

  // initialize some vectors for temporary storage

  // indices for vertices, uv values and normals
  std::vector<unsigned int> v_indices, uv_indices, n_indices;
  std::vector<glm::vec3> verts, norms;  // vertices and normal vectors
  std::vector<glm::vec2> uvs;           // uv values

  // for loading into the actual GPU
  std::vector<glm::vec3> final_vertices, final_normals;
  std::vector<glm::vec2> final_uvs;

  // (try to) open the file
  std::ifstream file("./" + path); 
  if(!file.is_open())
  {
    std::cerr << "file " << path << " failed to open" << std::endl;
    return false;
  }

  // read the first word of each line
  std::string header;
  while(file >> header)
  {
    if(header.compare("v") == 0)
    {
      // it's a v (vertex), push it to vertices
      glm::vec3 vertex;
      file >> vertex.x >> vertex.y >> vertex.z;
      verts.push_back(vertex);
    }
    else if(header.compare("vt") == 0)
    {
      // it's a vt (texture coordinate), push it to uvs
      glm::vec2 vertex;
      file >> vertex.x >> vertex.y;
      uvs.push_back(vertex);
    }
    else if(header.compare("vn") == 0)
    {
      // it's a vn (normal vector), push it to normals
      glm::vec3 vertex;
      file >> vertex.x >> vertex.y >> vertex.z;
      norms.push_back(vertex);
    }
    else if(header.compare("f") == 0)
    {
      // it's a face, add values to the _indices vectors 
      for(int i=0; i<3; i++)
      {
        unsigned int vi  = 0;
        unsigned int uvi = 0;
        unsigned int ni  = 0;

        std::string current_vertex;
        file >> current_vertex;

        // start at the beginning of the word ("##/##/##")
        int cursor=0;

        while(cursor < current_vertex.size()
           && current_vertex[cursor] != '/')
        {
          // add to vi until we hit a /
          vi = (10 * vi) + (current_vertex[cursor] - '0');
          cursor++;
        }

        // skip the / we just hit
        cursor++;

        while(cursor < current_vertex.size()
           && current_vertex[cursor] != '/')
        {
          // add to uvi until we hit a /
          uvi = (10 * uvi) + (current_vertex[cursor] - '0');
          cursor++;
        }

        // skip the / we just hit
        cursor++;

        while(cursor < current_vertex.size()
           && current_vertex[cursor] != '/')
        {
          // add to n until we hit a / (or the end of the word)
          ni = (10 * ni) + (current_vertex[cursor] - '0');
          cursor++;
        }

        // add the values of the word into the indexes (don't add 0s)
        if(vi != 0)  v_indices .push_back(vi);
        if(uvi != 0) uv_indices.push_back(uvi);
        if(ni != 0)  n_indices .push_back(ni);
      }
    }
  }

  // end of the file, un-compress the data
  for(unsigned int i = 0; i<v_indices.size(); i++)
  {
    // obj files start indexing at 1, not 0
    glm::vec3 temp = verts[v_indices[i] - 1];
    final_vertices.push_back(temp);
  }

  for(unsigned int i = 0; i<uv_indices.size(); i++)
  {
    // obj files start indexing at 1, not 0
    glm::vec2 temp = uvs[uv_indices[i] - 1];
    final_uvs.push_back(temp);
  }
  
  for(unsigned int i = 0; i<n_indices.size(); i++)
  {
    // obj files start indexing at 1, not 0
    glm::vec3 temp = norms[n_indices[i] - 1];
    final_normals.push_back(temp);
  }

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, final_vertices.size() * sizeof(glm::vec3), 
               &final_vertices[0], GL_STATIC_DRAW);

  // make a new model to load the data into
  Model newModel;
  newModel.vertexBuffer = vertexBuffer;
  newModel.triangleCount = final_vertices.size()/3;

  modelMap[path] = newModel;
  std::cout << "vertexBuffer  = " << newModel.vertexBuffer  << std::endl;
  std::cout << "triangleCount = " << newModel.triangleCount << std::endl;
}
  

void GraphicsManager::unloadModel(std::string path) {}

// ---------------
// MODEL RENDERING
// ---------------

void GraphicsManager::beginRender() const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(programID);
}

void GraphicsManager::endRender() const
{
  glfwSwapBuffers(window);
}

void GraphicsManager::renderModel(std::string path) const
{
  if(modelMap.find(path) != modelMap.end())
  {
    Model model = modelMap.at(path);
    
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVPMatrix[0][0]);

    glEnableVertexAttribArray(0);
    //std::cout << "vertexBuffer = " << vertexBufferMap.at(path) << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, model.vertexBuffer);
    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );
    glDrawArrays(GL_TRIANGLES, 0, 3 * model.triangleCount);
    glDisableVertexAttribArray(0);
  }
  else
  {
    std::cerr << "cannot render model " << path 
              << ": does not exist" << std::endl;
  }
}

void GraphicsManager::render(const Entity& e)
{
}
