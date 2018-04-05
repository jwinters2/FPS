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

    double deltaTime;
    Vec3 gravity;

    bool insideWorldBounds(const RigidBody&, CollisionInfo&) const;
    bool boundingBoxCollision(const RigidBody&, const RigidBody&
                             ,CollisionInfo&) const;

    //GJK algorithm (with helper functions and minimumSeparation stuff)
    bool GJKAlgorithm(const RigidBody&, const RigidBody& ,CollisionInfo&) const;
    Vec3 GJKSupport(const RigidBody&, const Vec3&) const;
    bool GJKNearestSimplex(std::vector<Vec3>&, Vec3&) const;
    bool GJKNearestSimplexCase2(std::vector<Vec3>&, Vec3&) const;
    bool GJKNearestSimplexCase3(std::vector<Vec3>&, Vec3&) const;
    bool GJKNearestSimplexCase4(std::vector<Vec3>&, Vec3&) const;
    
    bool EPAAlgorithm(const RigidBody&, const RigidBody&,
                      std::vector<Vec3>&, CollisionInfo&) const;

    void checkCollisions() const;
};
