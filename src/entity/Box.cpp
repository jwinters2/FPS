#include "Box.h"
#include "component/renderable/WireframeBox.h"
#include "PhysicsEngine.h"

Box::Box(PhysicsEngine* pe, const Vec3& pos, const Vec3& dim)
{
  transform.pos = pos;
  rigidBody = new RigidBody(this, dim, 1.0);
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
}
