#pragma once

#include "entity/Entity.h"
#include "Model.h"
#include "Math3d.h"

#include <GL/gl.h>

#include <map>

class GLFWwindow;

class GraphicsManager
{
  public:
    GraphicsManager(int,int,bool);
    ~GraphicsManager();

    void drawLine(const Vec3&,const Vec3&,const Vec3&);

    void render(const Entity&) const;

    bool loadModel(std::string);
    void unloadModel(std::string);
    void renderModel(std::string);

    void beginRender() const;
    void endRender() const;

    GLFWwindow* getWindow() const;

    static GraphicsManager* gm;
    static GraphicsManager& getReference();

    void setWindowSize(int,int);

  private:
    int width;
    int height;

    GLFWwindow* window;

    GLuint programID;
    GLuint vertexArrayID;
    GLuint lineVertexBuffer;

    glm::mat4 CameraMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 MVPMatrix;
    GLuint matrixID;

    std::map<std::string, Model> modelMap;

    GLuint loadShaders(std::string, std::string) const;
};
