#include "Box.h"
#include "component/renderable/WireframeBox.h"
#include "PhysicsEngine.h"

Box::Box(PhysicsEngine* pe)
{
  rigidBody = new RigidBody(this, Vec3(0.5), 1.0);
  model = new WireframeBox(Vec3(0.5), Vec3(1.0));
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
