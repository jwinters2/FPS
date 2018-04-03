#include <iostream>
#include <math.h>

#include "World.h"
#include "GraphicsManager.h"
#include "PhysicsEngine.h"

#include "entity/RotationObject.h"
#include "entity/Box.h"

World::World()
{
  dimension = Vec3(1.0);
  init();
}

World::World(double size)
{
  dimension = Vec3(size);
  init();
}

World::World(double x, double y, double z)
{
  dimension = Vec3(x,y,z);
  init();
}

World::World(const Vec3& dim)
{
  dimension = Vec3(dim);
  init();
}

void World::init()
{
  pe = new PhysicsEngine(this);
  //entityList.push_back(new RotationObject());
  //entityList.push_back(new Box(pe, Vec3(0, 3,0), Vec3(0.25)));
  //entityList.push_back(new Box(pe, Vec3(0, 1,0), Vec3(0.5, 0.25, 0.5)));
  //entityList.push_back(new Box(pe, Vec3(0,-1,0), Vec3(1, 0.5, 1)));

  Entity* e;
  for(int i=0; i<1; i++)
  {
    e= new Box(pe, Vec3(i-2,i-1.5,0), Vec3(0.4));
    e->setVelocity(Vec3(1,0,0));
    entityList.push_back(e);
  }

  e = new Box(pe, Vec3(0,-4.5,0), Vec3(3,0.5,3));
  e->setVelocity(Vec3(0,2,0));
  e->setMass(0);
  entityList.push_back(e);
};

World::~World()
{
  for(int i=0; i<entityList.size(); i++)
  {
    if(entityList[i] != nullptr)
    {
      delete entityList[i];
    }
  }

  delete pe;
};

void World::update(double dt)
{
  pe->performPhysics(dt);

  // this should use an octree
  for(int i=0; i<entityList.size(); i++)
  {
    if(entityList[i] != nullptr)
    {
      entityList[i]->update();
    }
  }
};

void World::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference(); 
  gm.beginRender();

  // draw the bounding box
  double x = dimension.x;
  double y = dimension.y;
  double z = dimension.z;

  Vec3 v[8];
  v[0] = Vec3(-1.0 * x, -1.0 * y, -1.0 * z);
  v[1] = Vec3( 1.0 * x, -1.0 * y, -1.0 * z);
  v[2] = Vec3( 1.0 * x, -1.0 * y,  1.0 * z);
  v[3] = Vec3(-1.0 * x, -1.0 * y,  1.0 * z);
  v[4] = Vec3(-1.0 * x,  1.0 * y, -1.0 * z);
  v[5] = Vec3( 1.0 * x,  1.0 * y, -1.0 * z);
  v[6] = Vec3( 1.0 * x,  1.0 * y,  1.0 * z);
  v[7] = Vec3(-1.0 * x,  1.0 * y,  1.0 * z);

  Vec3 color(1.0, 0.0, 0.0);

  // bottom square of box
  gm.drawLine(v[0], v[1], color);
  gm.drawLine(v[1], v[2], color);
  gm.drawLine(v[2], v[3], color);
  gm.drawLine(v[3], v[0], color);

  // top square of box
  gm.drawLine(v[4], v[5], color);
  gm.drawLine(v[5], v[6], color);
  gm.drawLine(v[6], v[7], color);
  gm.drawLine(v[7], v[4], color);

  // walls of the box
  gm.drawLine(v[0], v[4], color);
  gm.drawLine(v[1], v[5], color);
  gm.drawLine(v[2], v[6], color);
  gm.drawLine(v[3], v[7], color);

  // axis
  gm.drawLine(Vec3(0,0,0), Vec3(x,0,0), Vec3(1,0,0));
  gm.drawLine(Vec3(0,0,0), Vec3(0,y,0), Vec3(0,1,0));
  gm.drawLine(Vec3(0,0,0), Vec3(0,0,z), Vec3(0,0,1));

  // draw each entity
  for(int i=0; i<entityList.size(); i++)
  {
    if(entityList[i] != nullptr)
    {
      //std::cout << "entity " << i << " : ";
      entityList[i]->draw();
      //std::cout << std::endl;
    }
  }
  gm.endRender();
  //std::cout << std::endl;
}

Vec3 World::getDimension() const
{
  return dimension;
}
