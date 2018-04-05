#include "PhysicsEngine.h"
#include "World.h"
#include "entity/Entity.h"

#include <vector>
#include <cmath>

PhysicsEngine::PhysicsEngine(World* w):world(w),gravity(Vec3(0.0,-1.0,0.0))
{ }

PhysicsEngine::~PhysicsEngine() { }

void PhysicsEngine::performPhysics(double dt)
{
  deltaTime = dt;
  
  RigidBody* rb;
  CollisionInfo ci;

  for(unsigned int i=0; i<entityList.size(); i++)
  {
    rb = entityList[i]->rigidBody;
    rb->position += rb->velocity * deltaTime;
    
    // acceleration due to gravity
    if(rb->invMass != 0)
    {
      // objects with mass handle gravity just like any other force
      rb->addImpulse(gravity * deltaTime / rb->invMass);
    }

    if(!insideWorldBounds(*rb, ci))
    {
      rb->position -= ci.minimumSeparation;
      //rb->velocity += ci.impulse * rb->invMass;
      if(rb->invMass != 0)
      {
        rb->addImpulse(ci.impulse);
      }
      else
      {
        rb->velocity += ci.impulse;
      }
    }
  }

  checkCollisions();

  for(unsigned int i=0; i<entityList.size(); i++)
  {
    rb = entityList[i]->rigidBody;

    rb->applyImpulses();

    // acceleration due to gravity (disabled for massless objects)
    if(rb->invMass == 0)
    {
      // massless objects just add gravity to its velocity
      //rb->velocity += gravity * deltaTime;
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
  ci.minimumSeparation = Vec3(0);
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
  if(!retval && rb.invMass != 0)// && ci.minimumSeparation != Vec3(0) )
  {
    ci.impulse = -1 * ci.minimumSeparation.normal()
               * (ci.minimumSeparation.normal() * rb.velocity) 
               * (1 + rb.restitution)
               / rb.invMass;
  }
  else
  {
    ci.impulse = -1 * ci.minimumSeparation.normal()
               * (ci.minimumSeparation.normal() * rb.velocity) 
               * (1 + rb.restitution);
  }

  return retval;
}

void PhysicsEngine::checkCollisions() const
{
  CollisionInfo ci;
  for(unsigned int i = 0; i<entityList.size(); i++)
  {
    for(unsigned int j = i + 1; j<entityList.size(); j++)
    {
      RigidBody* ar = entityList[i]->rigidBody;
      RigidBody* br = entityList[j]->rigidBody;

      //if(boundingBoxCollision(*ar,*br,ci))
      if(GJKAlgorithm(*ar,*br,ci))
      {
        // calcualte the total inverted mass for separation (with a buffer)
        double totalInvMass = ar->invMass + br->invMass;

        // if one of them has infinite mass, 
        // only the finite mass one should move out of the way,
        // otherwise move in porportion to m1/(m1+m2)
        if(ar->invMass != 0)
        {
          ar->position += ci.minimumSeparation * (ar->invMass)/totalInvMass;
          ar->addImpulse(ci.impulse);
        }
        if(br->invMass != 0)
        {
          br->position -= ci.minimumSeparation * (br->invMass)/totalInvMass;
          br->addImpulse(ci.impulse * -1.0);
          // ci is calculated from the perspective of a hitting b
          // so invert it when b hitting a, because Newton's 3rd law
        }

        std::cout << "colliding" << std::endl;
      }
      else
      {
        std::cout << std::endl;
      }
    }
  }
}

bool PhysicsEngine::boundingBoxCollision(const RigidBody& a, const RigidBody& b
                                        ,CollisionInfo& ci) const
{
  Vec3 aMin = a.position - a.dimension;
  Vec3 aMax = a.position + a.dimension;
  Vec3 bMin = b.position - b.dimension;
  Vec3 bMax = b.position + b.dimension;
  Vec3 overlap(0);

  bool retval = true;

  if(retval && aMax.x > bMin.x && aMin.x < bMax.x)
  {
    // a and b are intersecting on the x axis 
    overlap.x = (aMax.x - bMin.x < bMax.x - aMin.x ? bMin.x - aMax.x
                                                   : bMax.x - aMin.x);
  }
  else
  {
    retval = false;
  }

  if(retval && aMax.y > bMin.y && aMin.y < bMax.y)
  {
    // a and b are intersecting on the y axis 
    //overlap.y = fmin(aMax.y - bMin.y, bMax.y - aMin.y);
    overlap.y = (aMax.y - bMin.y < bMax.y - aMin.y ? bMin.y - aMax.y
                                                   : bMax.y - aMin.y);
  }
  else
  {
    retval = false;
  }

  if(retval && aMax.z > bMin.z && aMin.z < bMax.z)
  {
    // a and b are intersecting on the z axis 
    overlap.z = (aMax.z - bMin.z < bMax.z - aMin.z ? bMin.z - aMax.z
                                                   : bMax.z - aMin.z);
  }
  else
  {
    retval = false;
  }

  if(retval)
  {
    // minimumSeparation, is just the smallest axis
    if(std::abs(overlap.x) < std::abs(overlap.y)
    && std::abs(overlap.x) < std::abs(overlap.z))
    {
      ci.minimumSeparation = Vec3(overlap.x,0,0);
    }
    else
    {
      // smallest axis is either y or z
      if(std::abs(overlap.y) < std::abs(overlap.z))
      {
        ci.minimumSeparation = Vec3(0,overlap.y,0);
      }
      else
      {
        ci.minimumSeparation = Vec3(0,0,overlap.z);
      }
    }

    // restitution is the maximum of each object's restitution
    double rest = (a.restitution > b.restitution ? a.restitution
                                                 : b.restitution);

    Vec3 displacement = ci.minimumSeparation; //a.position - b.position;

    /* if one of them has infinite mass, the equation changes a bit
     *
     * the general equation is I = (2 Ma Mb)/(Ma + Mb) * (deltaV)
     * but if one mass is infinite, the limit approaches (2 M),
     * where M is the finite mass
     *
     * also 2 is replaced with (1 + restitution)
     */
    double massComponent;

    if(a.invMass == 0)
    {
      massComponent = b.invMass;
    }
    else if(b.invMass == 0)
    {
      massComponent = a.invMass;
    }
    else
    {
      double Am = 1.0 / a.invMass;
      double Bm = 1.0 / b.invMass;
      massComponent = (Am + Bm) * a.invMass * b.invMass;
    }

    ci.impulse = -1 * displacement.normal()
               * (displacement.normal() * (a.velocity - b.velocity))
               * (1 + rest) / massComponent;
  }
  else
  {
    ci.minimumSeparation = Vec3(0);
    ci.impulse = Vec3(0);
  }

  ci.areColliding = retval;
  return retval;
}
