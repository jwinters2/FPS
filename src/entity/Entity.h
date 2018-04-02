#pragma once

#include "Math3d.h"
#include "component/renderable/Renderable.h"
#include "component/rigidbody/RigidBody.h"

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
    RigidBody* rigidBody;

  friend class PhysicsEngine;
  friend class RigidBody;
};
