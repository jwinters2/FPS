#pragma once

#include "Entity.h"
#include "Math3d.h"

class RotationObject: public Entity
{
  public:
    RotationObject();
    ~RotationObject();

    void update();
    void draw() const;

  private:
    Vec3 axis;
};
