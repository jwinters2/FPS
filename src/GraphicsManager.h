#pragma once

#include "Entity.h"
#include "Model.h"

#include <GL/gl.h>

#include <map>

class GLFWwindow;

class GraphicsManager
{
  public:
    GraphicsManager(int,int,bool=false);
    ~GraphicsManager();

    void render(const Entity&);

    bool loadModel(std::string);
    void unloadModel(std::string);
    void renderModel(std::string) const;

  private:
    GLFWwindow* window;
    GLuint vertexArrayID;
    std::map<std::string, Model> modelMap;
    std::map<std::string, GLuint> vertexBufferMap;
};
