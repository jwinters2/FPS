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
  Vec3 pointOfContact;
};

class PhysicsEngine
{
  public:
    PhysicsEngine(World*);
    ~PhysicsEngine();

    void performPhysics(double);

    void addObject(Entity*);

  private:
    static double maxImpulse;
    static double timeScale;

    struct SupportPoint
    {
      Vec3 v; // the point on the Minkowski difference
      Vec3 a; // the point on a that we used to get that point (we don't need b)

      SupportPoint();
      SupportPoint(const SupportPoint&);
    };

    struct Edge
    {
      SupportPoint v[2];
      Edge();
      Edge(const Edge&);
    };

    struct Triangle
    {
      SupportPoint v[3];
      Triangle();
      Triangle(const Triangle&);
    };

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
    std::vector<Vec3> GJKSupportSet(const RigidBody&, const Vec3&, double)const;

    bool GJKNearestSimplex(std::vector<SupportPoint>&, Vec3&) const;
    bool GJKNearestSimplexCase2(std::vector<SupportPoint>&, Vec3&) const;
    bool GJKNearestSimplexCase3(std::vector<SupportPoint>&, Vec3&) const;
    bool GJKNearestSimplexCase4(std::vector<SupportPoint>&, Vec3&) const;

    void RotateSort(std::vector<Vec3>&, const Vec3&) const;
    Vec3 GJKGetPointOfContact(std::vector<Vec3>&,std::vector<Vec3>&,
                             const Vec3&) const;
    
    bool EPAAlgorithm(const RigidBody&, const RigidBody&,
                      std::vector<SupportPoint>&, CollisionInfo&) const;

    void checkCollisions();
};
