#pragma once

#include "Renderable.h"

class WireframeBox: public Renderable
{
  public:
    WireframeBox(const Vec3&, const Vec3&);

    ~WireframeBox();

    void setDimensions(const Vec3&);
    void setColor(const Vec3&);

    void draw() const;

  private:
    Vec3 dimensions;
    Vec3 color;
};
