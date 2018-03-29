#pragma once

#include "Entity.h"

class Statue: public Entity
{
  public:
    Statue();
    ~Statue();

    void draw() const;

  private:
    const std::string modelPath;
};
