#pragma once

#include "Entity.h"

class Statue: public Entity
{
  public:
    Statue();
    ~Statue();

    void update();
    void draw() const;

  private:
};
