#include "Box.h"
#include "component/renderable/WireframeBox.h"
#include "PhysicsEngine.h"
//#include "GraphicsManager.h"

Box::Box(PhysicsEngine* pe, const Vec3& pos, const Vec3& dim)
{
  transform.pos = pos;
  rigidBody = new RigidBody(this, dim, 1.0, 1.0);
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

void Box::update()
{
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
