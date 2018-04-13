#include "entity/Player.h"
#include "InputManager.h"

Player::Player(World* w,const Vec3& pos)
{
  rigidBody = new RigidBody(this, 0, 0);
  rigidBody->setPosition(pos);
  rigidBody->makeBoxHitbox(Vec3(1));

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
  rigidBody->setRotation(rot);

  if(im.getKeyPressed(KeyCodes::W))
  {
    rigidBody->addPosition(rot.toMatrix() * Vec3( 0.1,0,0));
  }
  if(im.getKeyPressed(KeyCodes::S))
  {
    rigidBody->addPosition(rot.toMatrix() * Vec3(-0.1,0,0));
  }
  if(im.getKeyPressed(KeyCodes::A))
  {
    rigidBody->addPosition(rot.toMatrix() * Vec3(0,0,-0.1));
  }
  if(im.getKeyPressed(KeyCodes::D))
  {
    rigidBody->addPosition(rot.toMatrix() * Vec3(0,0, 0.1));
  }
  if(im.getKeyPressed(KeyCodes::SPACE))
  {
    rigidBody->addVelocity(Vec3(0,3,0));
  }
}

void Player::draw() const
{
}
