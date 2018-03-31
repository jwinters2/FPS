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

  private:
    Vec3 pos;
    Renderable* model;
};
