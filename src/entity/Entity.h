#pragma once

#include "Math3d.h"
#include "PhysicsEngine.h"
#include "component/renderable/Renderable.h"
#include "component/rigidbody/RigidBody.h"

class Entity
{
  public:
    Entity();
    virtual ~Entity();

    virtual void update();
    virtual void draw() const;

    virtual void collide(Entity&, const CollisionInfo&);

    Transform getTransform() const;

    void setPosition(const Vec3&);
    void addPosition(const Vec3&);

    void setVelocity(const Vec3&);
    void addVelocity(const Vec3&);

    void setMass(double);
    double getMass() const;

  protected:
    Transform transform;
    Renderable* model;
    RigidBody* rigidBody;

  friend class World;
  friend class PhysicsEngine;
  friend class RigidBody;
};
