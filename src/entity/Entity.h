#pragma once

#include "Math3d.h"

class Entity
{
  public:
    Entity();
    ~Entity();

    void update();
    void draw() const;

  private:
    Vec3 pos;
};
