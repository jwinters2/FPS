#include "RotationObject.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "component/renderable/Model.h"

RotationObject::RotationObject()
{
  model = new Model("assets/rotationModel.0obj","assets/rotationTex.bmp");
  transform.scale = Vec3(2,1,1);
}

RotationObject::~RotationObject()
{
  delete model;
}

void RotationObject::update()
{
  InputManager& im = InputManager::getReference();

  if(im.getKeyClicked(KeyCodes::R))
  {
    axis = Vec3(0,0,0);
    if(im.getKeyPressed(KeyCodes::LSHIFT))
    {
      transform.rot = Quat();
    }
  }

  int dir = ( im.getKeyPressed(KeyCodes::LSHIFT) ? -1 : 1);

  if(im.getKeyClicked(KeyCodes::X))
  {
    axis += Vec3(dir,0,0);
  }
  if(im.getKeyClicked(KeyCodes::Y))
  {
    axis += Vec3(0,dir,0);
  }
  if(im.getKeyClicked(KeyCodes::Z))
  {
    axis += Vec3(0,0,dir);
  }

  if(axis != Vec3(0,0,0) && im.getKeyPressed(KeyCodes::UP))
  {
    transform.rot.applyRotation(Quat(axis.normal(), 1));
  }

  if(axis != Vec3(0,0,0) && im.getKeyPressed(KeyCodes::DOWN))
  {
    transform.rot.applyRotation(Quat(axis.normal(), -1));
  }

  model->setTransform(transform.toMatrix());
}

void RotationObject::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference();
  gm.drawLine(Vec3(0,0,0), 10 * axis.normal(), Vec3(1,1,1));

  model->draw();
}
