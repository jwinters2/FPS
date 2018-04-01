#pragma once

#include "entity/Entity.h"
#include <vector>

class PhysicsEngine
{
  public:
    PhysicsEngine();
    ~PhysicsEngine();

    void performPhysics();

    void addObject(Entity*);

  private:
    std::vector<Entity*> entityList;

    Vec3 gravity;
};
