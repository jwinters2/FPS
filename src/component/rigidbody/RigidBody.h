#pragma once

#include "Math3d.h"

#include <vector>

class Entity;

class RigidBody
{
  public:
    RigidBody(Entity*, const Vec3&, double, double);
    ~RigidBody();

    Transform getTransform() const;

    void loadHitbox(std::string);
    void makeBoxHitbox(const Vec3&);

    void updateOwner();

    void setPosition(const Vec3&);
    void addPosition(const Vec3&);

    void setVelocity(const Vec3&);
    void addVelocity(const Vec3&);

    void setRotation(const Quat&);
    void addRotation(const Quat&);

    void setAngularVelocity(const Vec3&);
    void addAngularVelocity(const Vec3&);

    void addImpulse(const Vec3&);
    void addAngularImpulse(const Vec3&);
    void applyImpulses();

    void setMass(double);

  private:
    Entity* owner;

    // hitbox shape (it's convex, so just a list of vertices is sufficient)
    std::vector<Vec3> hitbox;

    // position, velocity and impulse
    Vec3 position;
    Vec3 velocity;
    Vec3 impulse;

    // bounding box
    Vec3 dimension;

    // rotation
    Quat rotation;
    Vec3 angularVelocity;
    Vec3 angularImpulse;

    // inverted mass, restitution and interted moment of inertia
    double invMass;
    Mat3 invMOI;

    double restitution;

  friend class PhysicsEngine;
};
