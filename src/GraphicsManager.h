#pragma once

#include "Entity.h"

class GLFWwindow;

class GraphicsManager
{
  public:
    GraphicsManager(int,int,bool=false);
    ~GraphicsManager();

    void render(const Entity&);

  private:
    GLFWwindow* window;
};
