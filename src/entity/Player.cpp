#include "entity/Player.h"
#include "InputManager.h"

Player::Player(World* w,const Vec3& pos):floorNormal(Vec3(0))
{
  rigidBody = new RigidBody(this, 0, 0);
  rigidBody->setPosition(pos);
  rigidBody->makeBoxHitbox(Vec3(1));
  rigidBody->setSimplifiedMovement(true);

  if(w != nullptr)
  {
    w->addObject(this);
  }
}

Player::~Player()
{
}

void Player::update()
{
  static InputManager& im = InputManager::getReference();

  double yaw   = im.getMouseX();
  double pitch = im.getMouseY();
  Quat rot = Quat(Vec3(0,0,1),pitch/10);
  rot.applyRotation(Quat(Vec3(0,1,0),yaw/10));
  rigidBody->setRotation(Quat(Vec3(0,1,0),yaw/10));

  if(floorNormal != Vec3(0))
  {
    Vec3 w = rot.toMatrix() * Vec3( 0.1,0,   0);
    Vec3 s = rot.toMatrix() * Vec3(-0.1,0,   0);
    Vec3 a = rot.toMatrix() * Vec3(   0,0,-0.1);
    Vec3 d = rot.toMatrix() * Vec3(   0,0, 0.1);

    if(im.getKeyPressed(KeyCodes::W))
    {
      rigidBody->addPosition(w - w.proj(floorNormal));
    }
    if(im.getKeyPressed(KeyCodes::S))
    {
      rigidBody->addPosition(s - s.proj(floorNormal));
    }
    if(im.getKeyPressed(KeyCodes::A))
    {
      rigidBody->addPosition(a - a.proj(floorNormal));
    }
    if(im.getKeyPressed(KeyCodes::D))
    {
      rigidBody->addPosition(d - d.proj(floorNormal));
    }
    if(im.getKeyPressed(KeyCodes::SPACE))
    {
      rigidBody->addVelocity(Vec3(0,3,0));
    }
  }

  floorNormal = Vec3(0);
}

void Player::collide(Entity& e, const CollisionInfo& ci)
{
  if(e.getMass() == 0
  && floorNormal.y < ci.minimumSeparation.normal().y)
  {
    floorNormal = ci.minimumSeparation.normal();
  }
}

void Player::draw() const
{
}
