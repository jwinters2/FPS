#pragma once

#include "Math3d.h"
#include "component/renderable/Renderable.h"

class Entity
{
  public:
    Entity();
    ~Entity();

    virtual void update();
    virtual void draw() const;

    void setPosition(const Vec3&);

  protected:
    Transform transform;
    Renderable* model;
};
