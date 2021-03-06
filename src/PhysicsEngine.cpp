#include "PhysicsEngine.h"
#include "World.h"
#include "entity/Entity.h"

#include <vector>
#include <cmath>

double PhysicsEngine::maxImpulse = 0;
double PhysicsEngine::timeScale = 1;

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
    rb->applyImpulses();
    rb->position += rb->velocity * deltaTime * timeScale;
    
    if(rb->angularVelocity != Vec3(0))
    {
      rb->rotation.applyRotation(Quat(rb->angularVelocity.normal(),
                                     rb->angularVelocity.length()
                                     * deltaTime * timeScale
                                     * 180.0 / 3.14159263538));
    }
    
    // acceleration due to gravity
    if(rb->invMass != 0)
    {
      // objects with mass handle gravity just like any other force
      rb->addImpulse(gravity * deltaTime / rb->invMass);
    }

    /*
    if(!insideWorldBounds(*rb, ci))
    {
      rb->position -= ci.minimumSeparation;
      if(rb->invMass != 0)
      {
        rb->addImpulse(ci.impulse);
      }
      else
      {
        rb->velocity += ci.impulse;
      }
    }
    */
  }

  checkCollisions();

  for(unsigned int i=0; i<entityList.size(); i++)
  {
    rb = entityList[i]->rigidBody;

    //rb->applyImpulses();

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

  ci.pointOfContact = rb.position;

  return retval;
}

void PhysicsEngine::checkCollisions()
{
  CollisionInfo ci;
  for(unsigned int i = 0; i<entityList.size(); i++)
  {
    RigidBody* ar = entityList[i]->rigidBody;

    // check with bounds
    for(int j=0; j<6; j++)
    {
      if(GJKAlgorithm(*ar,world->getBound(j),ci))
      {
        if(ar->invMass != 0)
        {
          ar->collisionResolutionJump += ci.minimumSeparation;

          ar->addImpulse(ci.impulse);
          //if(ci.pointOfContact != Vec3(0))
          ar->addAngularImpulse((ci.pointOfContact - ar->position).cross
                                (ci.impulse * -0.9));

          if(ci.impulse.length() > maxImpulse)
          {
            maxImpulse = ci.impulse.length();
            std::cout << "Highest Impulse so far: " << maxImpulse << std::endl;
          }
        }

      }
    }

    for(unsigned int j = i + 1; j<entityList.size(); j++)
    {
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
          if(ar->simplifyMovement)
          {
            ar->position += ci.minimumSeparation;
            //ar->addImpulse(ci.impulse);
            ar->velocity -= (ar->velocity).proj(ci.minimumSeparation);
          }
          else
          {
            ar->collisionResolutionJump += ci.minimumSeparation 
                                         * (ar->invMass)/totalInvMass;

            ar->addImpulse(ci.impulse);
            //if(ci.pointOfContact != Vec3(0))
            ar->addAngularImpulse((ci.pointOfContact - ar->position).cross
                                  (ci.impulse * -0.9));
          }
        }

        if(br->invMass != 0)
        {
          if(br->simplifyMovement)
          {
            br->position -= ci.minimumSeparation;
            //br->addImpulse(ci.impulse * -1.0);
            br->velocity += (br->velocity).proj(ci.minimumSeparation);
          }
          else
          {
            br->collisionResolutionJump -= ci.minimumSeparation 
                                         * (br->invMass)/totalInvMass;

            br->addImpulse(ci.impulse * -1.0);
            //if(ci.pointOfContact != Vec3(0))
            br->addAngularImpulse((ci.pointOfContact - br->position).cross
                                  (ci.impulse * 0.9));
            // ci is calculated from the perspective of a hitting b
            // so invert it when b hitting a, because Newton's 3rd law
          }
        }

        entityList[i]->collide(*entityList[j], ci);
        entityList[j]->collide(*entityList[i], ci);

        if(ci.impulse.length() > maxImpulse)
        {
          maxImpulse = ci.impulse.length();
          //std::cout << "Highest Impulse so far: " << maxImpulse << std::endl;
        }
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
