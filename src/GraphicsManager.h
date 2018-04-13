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
  GLuint normalBuffer;
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
    void drawWireframeBox(const Vec3&, const Vec3&, const Vec3&, const Mat4&);

    void render(const Entity&) const;

    bool loadModel(std::string);
    void unloadModel(std::string);

    // render a textureless model (use white texture)
    void renderModel(std::string);
    void renderModel(std::string, const Vec3&, const Vec3&, const Quat&);
    void renderModel(std::string, const Mat4&);

    // render a textured model
    void renderModel(std::string, std::string);
    void renderModel(std::string, std::string, 
                     const Vec3&, const Vec3&, const Quat&);
    void renderModel(std::string, std::string, const Mat4&);

    bool isModelLoaded(std::string) const;

    bool loadTexture(std::string);
    void unloadTexture(std::string);
    bool isTextureLoaded(std::string) const;

    void beginRender();
    void endRender() const;

    GLFWwindow* getWindow() const;

    static GraphicsManager* gm;
    static GraphicsManager& getReference();

    void setWindowSize(int,int);

    void setCamera(const Entity*);

  private:
    int width;
    int height;

    const Entity* camera;

    GLFWwindow* window;

    GLuint programID;
    GLuint vertexArrayID;
    GLuint textureSamplerID;
    GLuint matrixID;
    GLuint MVID;
    GLuint colorID;
    GLuint lightPositionID;
    GLuint ambientID;

    GLuint lineVertexBuffer;

    glm::mat4 CameraMatrix;
    glm::mat4 ProjectionMatrix;
    glm::mat4 MVPMatrix;
    glm::mat4 MVMatrix;

    std::map<std::string, ModelMapEntry>   modelMap;
    std::map<std::string, TextureMapEntry> textureMap;

    GLuint loadShaders(std::string, std::string) const;

    bool loadWhiteTexture();
    bool loadErrorModel();
    bool loadErrorTexture();

    static glm::mat4 toGlmMat4(const Mat4&);
    static bool isPowerOfTwo(unsigned int);
};
