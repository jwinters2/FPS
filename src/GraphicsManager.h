#pragma once

#include "entity/Entity.h"
#include "Math3d.h"

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <map>

class GLFWwindow;

struct ModelMapEntry
{
  GLuint vertexBuffer;
  GLuint uvBuffer;
  unsigned int triangleCount;
};

struct TextureMapEntry
{
  GLuint textureBuffer;
};

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
    void renderModel(std::string, const Vec3&, const Vec3&, const Quat&);
    void renderModel(std::string, const Mat4&);
    bool isModelLoaded(std::string) const;

    bool loadTexture(std::string);
    void unloadTexture(std::string);
    bool isTextureLoaded(std::string) const;

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
    GLuint textureSamplerID;
    GLuint lineVertexBuffer;

    glm::mat4 CameraMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 MVPMatrix;
    GLuint matrixID;

    std::map<std::string, ModelMapEntry>   modelMap;
    std::map<std::string, TextureMapEntry> textureMap;

    GLuint loadShaders(std::string, std::string) const;

    static glm::mat4 toGlmMat4(const Mat4&);
    static bool isPowerOfTwo(unsigned int);
};
