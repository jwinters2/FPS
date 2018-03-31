#include "GraphicsManager.h"
#include "Statue.h"
#include "Math3d.h"
#include "component/renderable/Model.h"

Statue::Statue()
{
  model = new Model("assets/statue2.obj");
  model->setTransform(Mat4::Translate(pos));
}

Statue::~Statue()
{
  delete model;
}

void Statue::draw() const
{
  model->draw();
}
