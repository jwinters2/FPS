#include "GraphicsManager.h"
#include "Statue.h"
#include "Math3d.h"
#include "component/renderable/Model.h"

Statue::Statue()
{
  model = new Model("assets/statue2.obj","TEX_ERROR");
}

Statue::~Statue()
{
  delete model;
}

void Statue::update()
{
  model->setTransform(transform.toMatrix());
}

void Statue::draw() const
{
  model->draw();
}
