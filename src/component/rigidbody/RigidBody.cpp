#include "RigidBody.h"
#include "entity/Entity.h"
#include "GraphicsManager.h"

#include <fstream>

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
  impulse  = Vec3(0);
}

RigidBody::~RigidBody() {}

void RigidBody::loadHitbox(std::string filename)
{
  std::ifstream file("./" + filename);
  if(!file.is_open())
  {
    std::cerr << "Error: hitbox file " << filename << "could not be loaded"
              << std::endl;
    return;
  }

  std::string header;
  while(file >> header)
  {
    if(header.compare("v") == 0)
    {
      // this line is a vertex
      Vec3 v;
      file >> v.x >> v.y >> v.z;
      hitbox.push_back(v);
    }
    else
    {
      // ignore all other lines
      file.ignore(1,'\n');
    }
  }
}

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

void RigidBody::addImpulse(const Vec3& i)
{
  impulse += i;
}

void RigidBody::applyImpulses()
{
  velocity += impulse * invMass;
  impulse = Vec3(0);
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
