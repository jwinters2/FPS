#include "RigidBody.h"
#include "entity/Entity.h"
#include "GraphicsManager.h"

#include <fstream>

RigidBody::RigidBody(Entity* own, double m, double r):
                     owner(own), invMass((m==0?0:1/m)),
                     restitution(r),simplifyMovement(false)
{
  if(owner != nullptr)
  {
    position = own->transform.pos;
    rotation = own->transform.rot;
  }

  velocity        = Vec3(0);
  angularVelocity = Vec3(0);
  impulse         = Vec3(0);
  angularImpulse  = Vec3(0);
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

void RigidBody::makeBoxHitbox(const Vec3& dim)
{
  for(int i=-1; i<=1; i+=2)
  {
    for(int j=-1; j<=1; j+=2)
    {
      for(int k=-1; k<=1; k+=2)
      {
        hitbox.push_back(Vec3(dim.x * i, dim.y * j, dim.x * k));
      }
    }
  }

  invMOI = Mat3(0);                                   // normally 12
  invMOI.x[0] = ((dim.y * dim.y) + (dim.z * dim.z)) / 3;
  invMOI.y[1] = ((dim.x * dim.x) + (dim.z * dim.z)) / 3;
  invMOI.z[2] = ((dim.x * dim.x) + (dim.y * dim.y)) / 3;
                                       // but dim are half the lengths, so 3

  invMOI = invMOI.invert();
}

void RigidBody::makePlaneHitbox(const Vec3& dim)
{
  if(dim.x == 0)
  {
    hitbox.push_back(Vec3(0, dim.y, dim.z));
    hitbox.push_back(Vec3(0, dim.y,-dim.z));
    hitbox.push_back(Vec3(0,-dim.y, dim.z));
    hitbox.push_back(Vec3(0,-dim.y,-dim.z));
  }
  else if(dim.y == 0)
  {
    hitbox.push_back(Vec3( dim.x,0, dim.z));
    hitbox.push_back(Vec3(-dim.x,0,-dim.z));
    hitbox.push_back(Vec3( dim.x,0, dim.z));
    hitbox.push_back(Vec3(-dim.x,0,-dim.z));
  }
  else if(dim.z == 0)
  {
    hitbox.push_back(Vec3( dim.x, dim.y,0));
    hitbox.push_back(Vec3(-dim.x,-dim.y,0));
    hitbox.push_back(Vec3( dim.x, dim.y,0));
    hitbox.push_back(Vec3(-dim.x,-dim.y,0));
  }

  invMOI = Mat3(0);                                   // normally 12
  invMOI.x[0] = ((dim.y * dim.y) + (dim.z * dim.z)) / 3;
  invMOI.y[1] = ((dim.x * dim.x) + (dim.z * dim.z)) / 3;
  invMOI.z[2] = ((dim.x * dim.x) + (dim.y * dim.y)) / 3;
                                       // but dim are half the lengths, so 3

  invMOI = invMOI.invert();
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

void RigidBody::setRotation(const Quat& q)
{
  rotation = q;
}

void RigidBody::addRotation(const Quat& q)
{
  rotation.applyRotation(q);
}

void RigidBody::setAngularVelocity(const Vec3& omega)
{
  angularVelocity = omega;
}

void RigidBody::addAngularVelocity(const Vec3& omega)
{
  angularVelocity += omega;
}

void RigidBody::addImpulse(const Vec3& i)
{
  impulse += i;
}

void RigidBody::addAngularImpulse(const Vec3& i)
{
  if(i.length() * invMass > 0.01)
  angularImpulse += i;
}

void RigidBody::applyImpulses()
{
  velocity += impulse * invMass;

  Mat3 R(rotation.toMatrix());
  angularVelocity += (R * (invMOI * (R.invert() * angularImpulse))) * invMass;
  //angularVelocity += (invMOI *  angularImpulse) * invMass;

  position += collisionResolutionJump;

  impulse = Vec3(0);
  angularImpulse = Vec3(0);
  collisionResolutionJump = Vec3(0);
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

double RigidBody::getMass() const
{
  if(invMass == 0)
  {
    return 0;
  }
  return 1/invMass;
}

void RigidBody::setSimplifiedMovement(bool sm)
{
  simplifyMovement = sm;
}

Transform RigidBody::getTransform() const
{
  Transform retval;
  retval.pos   = position;
  retval.scale = Vec3(1);
  retval.rot   = rotation;
  return retval;
}

void RigidBody::updateOwner()
{
  if(owner != nullptr)
  {
    owner->transform.pos = position;
    owner->transform.rot = rotation;
  }
}
