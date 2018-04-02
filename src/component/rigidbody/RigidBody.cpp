#include "RigidBody.h"
#include "entity/Entity.h"
#include "GraphicsManager.h"

RigidBody::RigidBody(Entity* own, const Vec3& dim, double m):
                     owner(own), dimension(dim), mass(m)
{
  if(owner != nullptr)
  {
    position = own->transform.pos;
    rotation = own->transform.rot;
  }

  velocity = Vec3(0);
}

RigidBody::~RigidBody() {}

void RigidBody::update(double dt)
{
}

void RigidBody::updateOwner()
{
  if(owner != nullptr)
  {
    owner->transform.pos = position;
    owner->transform.rot = rotation;
  }
}
