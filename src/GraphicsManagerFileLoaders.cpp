#include <cstdlib>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"

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

// -------------
// MODEL LOADING
// -------------

bool GraphicsManager::loadModel(std::string path)
{
  if(modelMap.find(path) != modelMap.end())
  {
    // if the model already exists, don't load it, we're done
    std::cout << "WARNING: model " << path 
              << " already exists, not loading again" << std::endl;
    return true;
  }

  std::cout << "loading model " << path << std::endl;
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

  GLuint uvBuffer;
  glGenBuffers(1, &uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, final_uvs.size() * sizeof(glm::vec2), 
               &final_uvs[0], GL_STATIC_DRAW);

  // make a new model to load the data into
  ModelMapEntry newModel;
  newModel.vertexBuffer = vertexBuffer;
  newModel.uvBuffer = uvBuffer;
  newModel.triangleCount = final_vertices.size()/3;

  modelMap[path] = newModel;
  //std::cout << "vertexBuffer  = " << newModel.vertexBuffer  << std::endl;
  //std::cout << "    uvBuffer  = " << newModel.uvBuffer      << std::endl;
  //std::cout << "triangleCount = " << newModel.triangleCount << std::endl;
}

// ---------------
// TEXTURE LOADING
// ---------------

bool GraphicsManager::loadTexture(std::string path)
{
  if(isTextureLoaded(path))
  {
    // if the texture already exists, don't load it, we're done
    std::cout << "WARNING: texture " << path 
              << " already exists, not loading again" << std::endl;
    return true;
  }

  std::cout << "loading texture " << path << std::endl;

  // declare some variables
  const int HEADER_SIZE = 54; // .bmp files have a header of 54 bits
  char header[HEADER_SIZE];   // where the actual data will go
  unsigned int dataPos;       // where the actual data starts
  unsigned int width;         // dimensions of the image
  unsigned int height;
  unsigned int imageSize;     // width * height * 3 (bytes per pixel, RGB)
  char* data;        // the actual contents of the file

  // (try to) open the file
  std::ifstream file("./" + path);
  if(!file.is_open())
  {
    std::cerr << "file " << path << " failed to open" << std::endl;
    return false;
  }

  // read the header into header
  file.read(header,HEADER_SIZE);
  if( !(file.rdstate() == std::ios::goodbit
     && header[0] == 'B' && header[1] == 'M') )
  {
    std::cerr << "file " << path << " is not a valid .bmp file" << std::endl;
    return false;
  }

  // read the metadata from the header
  // first we get the pointers (to chars), then cast them to int pointers
  // then dereference them to get the data as an int
  dataPos   = *(unsigned int*)&(header[0x0A]); // data pos is stored at 0x0A
  imageSize = *(unsigned int*)&(header[0x22]);
  width     = *(unsigned int*)&(header[0x12]);
  height    = *(unsigned int*)&(header[0x16]);

  std::cout << "dataPos   = " << dataPos << std::endl;
  std::cout << "imageSize = " << imageSize << std::endl;
  std::cout << "width     = " << width << std::endl;
  std::cout << "height    = " << height << std::endl;

  // if the file is not formatted correctly, fill in the missing info
  if(dataPos   == 0) dataPos = 54;
  if(imageSize == 0) imageSize = width * height * 3;

  std::cout << "real dataPos   = " << dataPos << std::endl;
  std::cout << "real imageSize = " << imageSize << std::endl;

  // dimensions must be powers of 2 (and probably should be the same)

  if(! (isPowerOfTwo(width) && isPowerOfTwo(height)) )
  {
    std::cerr << "dimensions " << width << "x" << height 
              << " are not powers of 2" << std::endl;
    return false;
  }

  if(width != height)
  {
    std::cout << "WARNING: dimensions " << width << "x" << height 
              << " are not equal" << std::endl;
  }

  // transfer the entire rest of the file into a buffer
  data = new char[imageSize];
  file.read(data,imageSize);
  file.close();

  GLuint textureBuffer;
  glGenTextures(1, &textureBuffer);
  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
               GL_BGR, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                  GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  TextureMapEntry newTexture;
  newTexture.textureBuffer = textureBuffer;

  //std::cout << "new textureBuffer = " << textureBuffer << std::endl;

  textureMap[path] = newTexture;

  delete [] data;
}

bool GraphicsManager::loadWhiteTexture()
{
  unsigned int imageSize = 2 * 2 * 3;
  char data[imageSize];

  for(int i=0; i<imageSize; i++)
  {
    data[i] = 0xFF; // for white
  }

  GLuint textureBuffer;
  glGenTextures(1, &textureBuffer);
  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, 
               GL_BGR, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                  GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  TextureMapEntry newTexture;
  newTexture.textureBuffer = textureBuffer;

  //std::cout << "new textureBuffer = " << textureBuffer << std::endl;

  textureMap["TEX_WHITE"] = newTexture;
}

bool GraphicsManager::loadErrorTexture()
{
  // the "error texture" is a pink and black texture we use to draw if
  // the correct texture couldn't be loaded

  unsigned int imageSize = 32 * 32 * 3;
  char data[imageSize];

  for(int i=0; i<imageSize; i+=3)
  {
    if(i%2 == 0)
    {
      data[i  ] = 0xFF; // even-numbered pixels are pink
      data[i+1] = 0x80;
      data[i+2] = 0x80;
    }
    else
    {
      data[i  ] = 0x00; // odd-numbered pixels are black
      data[i+1] = 0x00;
      data[i+2] = 0x00;
    }
  }

  GLuint textureBuffer;
  glGenTextures(1, &textureBuffer);
  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, 
               GL_BGR, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                  GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  TextureMapEntry newTexture;
  newTexture.textureBuffer = textureBuffer;

  //std::cout << "new textureBuffer = " << textureBuffer << std::endl;

  textureMap["TEX_ERROR"] = newTexture;
}
