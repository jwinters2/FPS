#pragma once

#include "Math3d.h"

class Renderable
{
  public:
    Renderable();
    virtual ~Renderable();

    virtual void draw() const = 0;

    void setTransform(const Mat4&);

  protected:
    Mat4 transform;
};
