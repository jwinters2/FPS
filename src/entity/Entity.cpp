#include <iostream>
#include <cstdlib>

#include "Entity.h"
#include "component/renderable/Model.h"

Entity::Entity()
{
};

Entity::~Entity()
{
};

void Entity::setPosition(const Vec3& p)
{
  transform.pos = p; 
};

void Entity::update()
{
};

void Entity::draw() const
{
  //std::cout << "pos = " << pos;
  model->setTransform(transform.toMatrix());
  model->draw();
};
