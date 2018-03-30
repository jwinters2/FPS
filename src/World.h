#pragma once

#include "Math3d.h"

class Entity;

class World
{
  public:
    World();
    World(double);
    World(double, double, double);
    World(const Vec3&);
    ~World();
    void update();
    void draw() const;

  private:
    Entity** entityList; 
    Vec3 dimensions;

    void init();
};
