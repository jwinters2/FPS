#include <iostream>
#include <cstdlib>

#include "Entity.h"
#include "component/renderable/Model.h"

Entity::Entity()
{
  pos.x = rand()%20 - 10;
  pos.y = rand()%20 - 10;   
  pos.z = rand()%20 - 10;   

  //model = new Model("assets/statue.obj");
};

Entity::~Entity()
{
  //delete model;
};

void Entity::setPosition(const Vec3& p)
{
  pos = p; 
};

void Entity::update()
{
  //pos = pos + Vec3(0.0, 1.0, 0.0);
};

void Entity::draw() const
{
  //std::cout << "pos = " << pos;
  model->setTransform(Mat4::Translate(pos));
  model->draw();
};
