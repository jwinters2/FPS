#include <iostream>
#include <cstdlib>

#include "Entity.h"
#include "component/renderable/Model.h"

Entity::Entity():model(nullptr),rigidBody(nullptr)
{
};

Entity::~Entity()
{
  if(rigidBody != nullptr)
  {
    delete rigidBody;
  }
  if(model != nullptr)
  {
    delete model;
  }
};

void Entity::collide(Entity& e, const CollisionInfo& ci) {}

Transform Entity::getTransform() const
{
  return transform;
}

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

double Entity::getMass() const
{
  if(rigidBody != nullptr)
  {
    return rigidBody->getMass();
  }
  return 0;
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
