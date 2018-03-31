#pragma once

#include "Renderable.h"

#include <string>

class Model: public Renderable
{
  public:
    Model(std::string);
    ~Model();

    void draw() const;

  private:
    std::string modelName; 
};
