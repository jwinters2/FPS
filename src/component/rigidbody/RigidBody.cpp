#include "RigidBody.h"
#include "entity/Entity.h"
#include "GraphicsManager.h"

RigidBody::RigidBody(Entity* own, const Vec3& dim, double m, double r):
                     owner(own), dimension(dim), invMass((m==0?0:1/m)),
                     restitution(r)
{
  if(owner != nullptr)
  {
    position = own->transform.pos;
    rotation = own->transform.rot;
  }

  velocity = Vec3(0);
}

RigidBody::~RigidBody() {}

void RigidBody::setPosition(const Vec3& p)
{
  position = p;
}

void RigidBody::addPosition(const Vec3& p)
{
  position += p;
}

void RigidBody::setVelocity(const Vec3& v)
{
  velocity = v;
}

void RigidBody::addVelocity(const Vec3& v)
{
  velocity += v;
}

void RigidBody::setMass(double m)
{
  if(m <= 0)
  {
    invMass = 0;
  }
  else
  {
    invMass = 1/m;
  }
}

void RigidBody::updateOwner()
{
  if(owner != nullptr)
  {
    owner->transform.pos = position;
    owner->transform.rot = rotation;
  }
}
