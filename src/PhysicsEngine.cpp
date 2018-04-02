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
  CollisionInfo ci;

  for(int i=0; i<entityList.size(); i++)
  {
    rb = entityList[i]->rigidBody;
    
    // acceleration due to gravity
    rb->velocity += gravity * dt;

    rb->position += rb->velocity * dt;

    if(!insideWorldBounds(*rb, ci))
    {
      rb->position -= rb->velocity * dt;
      rb->velocity += ci.impulse * rb->invMass;
    }

    rb->updateOwner();
  }
}

void PhysicsEngine::addObject(Entity* e)
{
  entityList.push_back(e);
}

bool PhysicsEngine::insideWorldBounds(const RigidBody& rb, CollisionInfo& ci)
const
{
  if(world == nullptr)
  {
    return true;
  }

  Vec3 dimension = world->getDimension();
  ci.minimumSeparation = Vec3(0,0,0);
  ci.impulse = Vec3(0,0,0);
  bool retval = true;

  if(rb.position.x - rb.dimension.x < -dimension.x)
  {
    ci.minimumSeparation.x += rb.position.x - rb.dimension.x + dimension.x;
    retval = false; 
  }
  if(rb.position.x + rb.dimension.x > dimension.x)
  {
    ci.minimumSeparation.x += rb.position.x + rb.dimension.x - dimension.x;
    retval = false; 
  }

  if(rb.position.y - rb.dimension.y < -dimension.y)
  {
    ci.minimumSeparation.y += rb.position.y - rb.dimension.y + dimension.y;
    retval = false; 
  }
  if(rb.position.y + rb.dimension.y > dimension.y)
  {
    ci.minimumSeparation.y += rb.position.y + rb.dimension.y - dimension.y;
    retval = false; 
  }

  if(rb.position.z - rb.dimension.z < -dimension.z)
  {
    ci.minimumSeparation.z += rb.position.z - rb.dimension.z + dimension.z;
    retval = false; 
  }
  if(rb.position.z + rb.dimension.z > dimension.z)
  {
    ci.minimumSeparation.z += rb.position.z + rb.dimension.z - dimension.z;
    retval = false; 
  }

  ci.areColliding = !retval;
  if(rb.invMass != 0 && ci.minimumSeparation != Vec3(0,0,0) )
  {
    ci.impulse -= ci.minimumSeparation.normal()
                * (ci.minimumSeparation.normal() * rb.velocity) 
                * (1 + rb.restitution)
                / rb.invMass;
  }

  return retval;
}
