#include <cstdlib>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "GraphicsManager.h"

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
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::render(const Entity& e)
{
}
