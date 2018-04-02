#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

class Box: public Entity
{
  public:
    Box(PhysicsEngine*);
    ~Box();

    void update();
    void draw() const;
};
