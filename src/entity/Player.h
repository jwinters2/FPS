#pragma once

#include "entity/Entity.h"
#include "World.h"

class Player: public Entity
{
  public:
    Player(World*, const Vec3&);
    ~Player();
    
    void update();
    void draw() const;
    void collide(Entity&, const CollisionInfo&);

  private:
    Vec3 floorNormal;
};
