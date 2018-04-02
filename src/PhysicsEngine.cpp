#include "PhysicsEngine.h"
#include "World.h"
#include "entity/Entity.h"

#include <vector>

PhysicsEngine::PhysicsEngine(World* w):world(w),gravity(Vec3(0.0,-3.0,0.0))
{ }

PhysicsEngine::~PhysicsEngine() { }

void PhysicsEngine::performPhysics(double dt)
{
  RigidBody* rb;

  for(int i=0; i<entityList.size(); i++)
  {
    rb = entityList[i]->rigidBody;
    
    // acceleration due to gravity
    rb->velocity += gravity * dt;

    rb->position += rb->velocity * dt;

    if(!insideWorldBounds(*rb))
    {
      rb->position -= rb->velocity * dt;
      rb->velocity.y *= -0.2;
    }

    rb->updateOwner();
  }
}

void PhysicsEngine::addObject(Entity* e)
{
  entityList.push_back(e);
}

bool PhysicsEngine::insideWorldBounds(const RigidBody& rb) const
{
  if(world == nullptr)
  {
    return true;
  }
  Vec3 dimension = world->getDimension();

  return !(rb.position.x - rb.dimension.x < -dimension.x
        || rb.position.x + rb.dimension.x >  dimension.x
        || rb.position.y - rb.dimension.y < -dimension.y
        || rb.position.y + rb.dimension.y >  dimension.y
        || rb.position.z - rb.dimension.z < -dimension.z
        || rb.position.z + rb.dimension.z >  dimension.z);
}
