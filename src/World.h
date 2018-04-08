#pragma once

#include "Math3d.h"
#include "component/rigidbody/RigidBody.h"
#include "PhysicsEngine.h"

#include <vector>

class Entity;

class World
{
  public:
    World();
    World(double);
    World(double, double, double);
    World(const Vec3&);
    ~World();
    void update(double);
    void draw() const;

    Vec3 getDimension() const;

    void addObject(Entity*);

  private:
    std::vector<Entity*> entityList; 
    PhysicsEngine* pe;
    Vec3 dimension;

    void init();
};
