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

    void beginRender() const;
    void endRender() const;

    static GraphicsManager* gm;
    static GraphicsManager& getReference();

  private:
    GLFWwindow* window;

    GLuint programID;
    GLuint vertexArrayID;
    GLuint vertex_buffer_test;

    glm::mat4 CameraMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 MVPMatrix;
    GLuint matrixID;

    std::map<std::string, Model> modelMap;

    GLuint loadShaders(std::string, std::string) const;
};
