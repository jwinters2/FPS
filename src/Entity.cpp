#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity()
{
  pos.x = rand()%100;   
  pos.y = rand()%100;   
  pos.z = rand()%100;   
};

Entity::~Entity(){};

void Entity::update()
{
  pos = pos + Vec3(0.0, 1.0, 0.0);
};

void Entity::draw() const
{
  std::cout << "pos = " << pos;
};
