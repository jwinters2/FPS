#include "Box.h"
#include "component/renderable/WireframeBox.h"
#include "PhysicsEngine.h"
#include "InputManager.h"

Box::Box(PhysicsEngine* pe, const Vec3& pos, const Vec3& dim):
         keyboardMovement(false)
{
  transform.pos = pos;
  rigidBody = new RigidBody(this, 1.0, 0);

  rigidBody->makeBoxHitbox(dim);
  rigidBody->setRotation(Quat(Vec3(1,0,0),0));

  model = new WireframeBox(dim, Vec3(1.0));
  if(pe != nullptr)
  {
    pe->addObject(this);
  }
}

Box::~Box()
{
  delete rigidBody;
  delete model;
}

void Box::enableKeyboardMovement()
{
  keyboardMovement = true;
}

void Box::update()
{
  if(keyboardMovement && rigidBody != nullptr)
  {
    InputManager& im = InputManager::getReference();
    if(im.getKeyPressed(KeyCodes::W))
      rigidBody->addPosition(Vec3(-0.1,   0,   0));
    if(im.getKeyPressed(KeyCodes::S))
      rigidBody->addPosition(Vec3( 0.1,   0,   0));

    if(im.getKeyPressed(KeyCodes::A))
      rigidBody->addPosition(Vec3(   0,   0, 0.1));
    if(im.getKeyPressed(KeyCodes::D))
      rigidBody->addPosition(Vec3(   0,   0,-0.1));

    if(im.getKeyPressed(KeyCodes::Z))
      rigidBody->addPosition(Vec3(   0, 0.1,   0));
    if(im.getKeyPressed(KeyCodes::X))
      rigidBody->addPosition(Vec3(   0,-0.1,   0));
  }

  model->setTransform(transform.toMatrix());
}

void Box::draw() const
{
  model->draw();

  /*
  GraphicsManager& gm = GraphicsManager::getReference();
  gm.drawLine(Vec3(-5,transform.pos.y,transform.pos.z),
              Vec3( 5,transform.pos.y,transform.pos.z),
              Vec3(1,0,0));
  gm.drawLine(Vec3(transform.pos.x,-5,transform.pos.z),
              Vec3(transform.pos.x, 5,transform.pos.z),
              Vec3(0,1,0));
  gm.drawLine(Vec3(transform.pos.x,transform.pos.y,-5),
              Vec3(transform.pos.x,transform.pos.y, 5),
              Vec3(0,0,1));
  */
}
