#pragma once

class Renderable
{
  public:
    Renderable();
    ~Renderable();

    virtual void draw() const = 0;
};
