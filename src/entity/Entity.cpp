#include <iostream>
#include <cstdlib>

#include "Entity.h"
#include "component/renderable/Model.h"

Entity::Entity():rigidBody(nullptr),model(nullptr)
{
};

Entity::~Entity()
{
};

void Entity::setPosition(const Vec3& p)
{
  if(rigidBody != nullptr)
  {
    // the rigid body will take care of it for us (if there is one)
    rigidBody->setPosition(p);
  }
  else
  {
    transform.pos = p; 
  }
};

void Entity::addPosition(const Vec3& p)
{
  if(rigidBody != nullptr)
  {
    // the rigid body will take care of it for us (if there is one)
    rigidBody->addPosition(p);
  }
  else
  {
    transform.pos += p; 
  }
}

void Entity::setVelocity(const Vec3& v)
{
  if(rigidBody != nullptr)
  {
    rigidBody->setVelocity(v);
  }
}

void Entity::addVelocity(const Vec3& v)
{
  if(rigidBody != nullptr)
  {
    rigidBody->addVelocity(v);
  }
}

void Entity::setMass(double m)
{
  if(rigidBody != nullptr)
  {
    rigidBody->setMass(m);
  }
}

void Entity::update()
{
};

void Entity::draw() const
{
  //std::cout << "pos = " << pos;
  model->setTransform(transform.toMatrix());
  model->draw();
};
