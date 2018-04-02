#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

class Box: public Entity
{
  public:
    Box(PhysicsEngine*, const Vec3&, const Vec3&);
    ~Box();

    void update();
    void draw() const;
};
