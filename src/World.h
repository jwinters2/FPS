#pragma once

class Entity;

class World
{
  public:
    World();
    ~World();
    void update();
    void draw() const;

  private:
    Entity** entityList; 
};
