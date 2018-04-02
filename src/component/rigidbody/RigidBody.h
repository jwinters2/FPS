#pragma once

#include "Math3d.h"

class Entity;

class RigidBody
{
  public:
    RigidBody(Entity*, const Vec3&, double);
    ~RigidBody();

    void update(double);
    void updateOwner();

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

    // mass and moment of inertia
    double mass;

  friend class PhysicsEngine;
};
