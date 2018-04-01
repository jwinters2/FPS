#include <iostream>
#include <math.h>

#include "GraphicsManager.h"
#include "World.h"
#include "entity/Entity.h"
#include "entity/Statue.h"

const int ENTITY_COUNT = 3;

World::World()
{
  dimensions = Vec3(1.0);
  init();
}

World::World(double size)
{
  dimensions = Vec3(size);
  init();
}

World::World(double x, double y, double z)
{
  dimensions = Vec3(x,y,z);
  init();
}

World::World(const Vec3& dim)
{
  dimensions = Vec3(dim);
  init();
}

void World::init()
{
  entityList = new Entity*[ENTITY_COUNT];

  for(int i=0; i<ENTITY_COUNT; i++)
  {
    entityList[i] = new Statue();
  }
};

World::~World()
{
  for(int i=0; i<ENTITY_COUNT; i++)
  {
    if(entityList[i] != nullptr)
    {
      delete entityList[i];
    }
  }
  delete [] entityList;
};

void World::update()
{
  // this should use an octree
  for(int i=0; i<ENTITY_COUNT; i++)
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
  double x = dimensions.x/2.0;
  double y = dimensions.y/2.0;
  double z = dimensions.z/2.0;

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

  //gm.renderModel("assets/statue.obj");

  // draw each entity
  for(int i=0; i<ENTITY_COUNT; i++)
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
