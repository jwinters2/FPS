#pragma once

#include "Renderable.h"

class BoundingBox: public Renderable
{
  public:
    BoundingBox(const Vec3&, const Vec3&);

    ~BoundingBox();

    void draw() const;

  private:
    Vec3 dimensions;
    Vec3 color;
};
