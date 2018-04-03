#pragma once

#include "Math3d.h"

class Entity;

class RigidBody
{
  public:
    RigidBody(Entity*, const Vec3&, double, double);
    ~RigidBody();

    void updateOwner();

    void setPosition(const Vec3&);
    void addPosition(const Vec3&);

    void setVelocity(const Vec3&);
    void addVelocity(const Vec3&);

    void setMass(double);

  private:
    Entity* owner;

    // position, and velocity
    Vec3 position;
    Vec3 velocity;

    // bounding box
    Vec3 dimension;

    // rotation
    Quat rotation;
    Quat angular_vel;

    // inverted mass, restitution and moment of inertia
    double invMass;
    double restitution;

  friend class PhysicsEngine;
};
