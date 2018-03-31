#include "Renderable.h"

Renderable::Renderable(){}
Renderable::~Renderable(){}

void Renderable::setTransform(const Mat4& t)
{
  transform = t;
}
