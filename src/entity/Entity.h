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
    void addPosition(const Vec3&);

    void setVelocity(const Vec3&);
    void addVelocity(const Vec3&);

    void setMass(double);

  protected:
    Transform transform;
    Renderable* model;
    RigidBody* rigidBody;

  friend class PhysicsEngine;
  friend class RigidBody;
};
