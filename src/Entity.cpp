#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity()
{
  x = rand()%100;   
};

Entity::~Entity(){};

void Entity::update()
{
  x++;
};

void Entity::draw() const
{
  std::cout << "x = " << x;
};
