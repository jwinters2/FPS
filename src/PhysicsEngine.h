#pragma once

//#include "entity/Entity.h"
#include "Math3d.h"
#include "component/rigidbody/RigidBody.h"
#include <vector>

class World;
class Entity;

struct CollisionInfo
{
  bool areColliding;
  Vec3 minimumSeparation;
  Vec3 impulse;
};

class PhysicsEngine
{
  public:
    PhysicsEngine(World*);
    ~PhysicsEngine();

    void performPhysics(double);

    void addObject(Entity*);

  private:
    World* world;

    std::vector<Entity*> entityList;

    Vec3 gravity;

    bool insideWorldBounds(const RigidBody&, CollisionInfo&) const;
};
