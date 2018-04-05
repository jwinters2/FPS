#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

class Box: public Entity
{
  public:
    Box(PhysicsEngine*, const Vec3&, const Vec3&);
    ~Box();

    void enableKeyboardMovement();

    void update();
    void draw() const;

  private:
    bool keyboardMovement;
};
