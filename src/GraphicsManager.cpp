#include <cstdlib>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GraphicsManager.h"

// -------------------
// INITALIZE / CLEANUP
// -------------------

GraphicsManager::GraphicsManager(int width, int height, bool fullscreen)
{
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
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // apparently this is only needed for macs
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the actual window
  if(fullscreen)
  {
    window = glfwCreateWindow(width, height, "FPS Game", NULL, NULL);
  }
  else
  {
    window = glfwCreateWindow(width, height, "FPS Game", glfwGetPrimaryMonitor(), NULL);
  }

  if(window == NULL)
  {
    std::cerr << "Error: window could not be created" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glewExperimental = true;
  if(glewInit() != GLEW_OK)
  {
    std::cerr << "Error: GLEW could not be initialized" << std::endl;
    exit(EXIT_FAILURE);
  }

  glGenVertexArrays(1, &vertexArrayID);
  glBindVertexArray(vertexArrayID);
}

GraphicsManager::~GraphicsManager()
{
}

// -------------------------
// MODEL LOADING / UNLOADING
// -------------------------

bool GraphicsManager::loadModel(std::string path)
{
  if(modelMap.find(path) != modelMap.end())
  {
    // if the model already exists, don't load it, we're done
    std::cout << "WARNING: model " << path << "already exists, not loading again" << std::endl;
    return true;
  }

  // make a new model to load the data into
  Model newModel;

  // initialize some vectors for temporary storage
  std::vector<unsigned int> v_indices, uv_indices, n_indices; // indices for vertices, uv values and normals
  std::vector<glm::vec3> verts, norms;  // vertices and normal vectors
  std::vector<glm::vec2> uvs;           // uv values

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

        while(cursor < current_vertex.size() && current_vertex[cursor] != '/')
        {
          // add to vi until we hit a /
          vi = (10 * vi) + (current_vertex[cursor] - '0');
          cursor++;
        }

        // skip the / we just hit
        cursor++;

        while(cursor < current_vertex.size() && current_vertex[cursor] != '/')
        {
          // add to uvi until we hit a /
          uvi = (10 * uvi) + (current_vertex[cursor] - '0');
          cursor++;
        }

        // skip the / we just hit
        cursor++;

        while(cursor < current_vertex.size() && current_vertex[cursor] != '/')
        {
          // add to n until we hit a / (or the end of the word)
          ni = (10 * ni) + (current_vertex[cursor] - '0');
          cursor++;
        }

        if(vi != 0)  v_indices .push_back(vi);  // add the values of the word into the indexes
        if(uvi != 0) uv_indices.push_back(uvi); // (don't add 0s)
        if(ni != 0)  n_indices .push_back(ni);
      }
    }
    else if(header.compare("o") == 0)
    {
      // we hit the end of a shape, add what we have and clear the temp stuff
      for(unsigned int i = 0; i<v_indices.size(); i++)
      {
        glm::vec3 temp = verts[v_indices[i] - 1]; // obj files start indexing at 1, not 0
        newModel.vertices.push_back(temp);
      }

      for(unsigned int i = 0; i<uv_indices.size(); i++)
      {
        glm::vec2 temp = uvs[uv_indices[i] - 1]; // obj files start indexing at 1, not 0
        newModel.uvs.push_back(temp);
      }
      
      for(unsigned int i = 0; i<n_indices.size(); i++)
      {
        glm::vec3 temp = norms[n_indices[i] - 1]; // obj files start indexing at 1, not 0
        newModel.normals.push_back(temp);
      }

      // clear the temp stuff
      verts.clear();
      uvs.clear();
      norms.clear();

      v_indices.clear();
      uv_indices.clear();
      n_indices.clear();
    }
  }

  // we hit the end of a shape, add what we have and clear the temp stuff
  for(unsigned int i = 0; i<v_indices.size(); i++)
  {
    glm::vec3 temp = verts[v_indices[i] - 1]; // obj files start indexing at 1, not 0
    newModel.vertices.push_back(temp);
  }

  for(unsigned int i = 0; i<uv_indices.size(); i++)
  {
    glm::vec2 temp = uvs[uv_indices[i] - 1]; // obj files start indexing at 1, not 0
    newModel.uvs.push_back(temp);
  }
  
  for(unsigned int i = 0; i<n_indices.size(); i++)
  {
    glm::vec3 temp = norms[n_indices[i] - 1]; // obj files start indexing at 1, not 0
    newModel.normals.push_back(temp);
  }

  for(int i=0; i<newModel.vertices.size(); i++)
  {
    std::cout << newModel.vertices[i][0] << "," << newModel.vertices[i][1] << ",";
    std::cout << newModel.vertices[i][2] << std::endl;
  }

  modelMap[path] = newModel;

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, newModel.vertices.size() * sizeof(glm::vec3), 
               &newModel.vertices[0], GL_STATIC_DRAW);

  vertexBufferMap[path] = vertexBuffer;
  std::cout << "vertexBuffer = " << vertexBuffer << std::endl;
}

void GraphicsManager::unloadModel(std::string path) {}

void GraphicsManager::renderModel(std::string path) const
{
  if(vertexBufferMap.find(path) != vertexBufferMap.end())
  {
    glEnableVertexAttribArray(0);
    std::cout << "vertexBuffer = " << vertexBufferMap.at(path) << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferMap.at(path));
    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
  }
  else
  {
    std::cerr << "cannot render model " << path << ": does not exist" << std::endl;
  }
}

void GraphicsManager::render(const Entity& e)
{
}
