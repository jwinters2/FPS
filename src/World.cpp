#include <iostream>

#include "GraphicsManager.h"
#include "World.h"
#include "Entity.h"

World::World()
{
  entityList = new Entity*[2];
  for(int i=0; i<2; i++)
  {
    entityList[i] = new Entity();
  }
};

World::~World()
{
  for(int i=0; i<2; i++)
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
  for(int i=0; i<2; i++)
  {
    if(entityList[i] != nullptr)
    {
      entityList[i]->update();
    }
  }
};

void World::draw() const
{
  const GraphicsManager& gm = GraphicsManager::getReference(); 
  gm.beginRender();
  for(int i=0; i<2; i++)
  {
    if(entityList[i] != nullptr)
    {
      std::cout << "entity " << i << " : ";
      entityList[i]->draw();
      std::cout << std::endl;
    }
  }
  gm.endRender();
  std::cout << std::endl;
}
