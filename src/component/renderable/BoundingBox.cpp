#include "BoundingBox.h"
#include "GraphicsManager.h"

BoundingBox::BoundingBox(const Vec3& dim,const Vec3& col):dimensions(dim)
                                                         ,color(col)
{}

BoundingBox::~BoundingBox() {}

void BoundingBox::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference();

  double x = dimensions.x/2;
  double y = dimensions.y/2;
  double z = dimensions.z/2;

  // bottom square
  gm.drawLine(Vec3(-x,-y,-z), Vec3( x,-y,-z), color);
  gm.drawLine(Vec3( x,-y,-z), Vec3( x, y,-z), color);
  gm.drawLine(Vec3( x, y,-z), Vec3(-x, y,-z), color);
  gm.drawLine(Vec3(-x, y,-z), Vec3(-x,-y,-z), color);

  // top square
  gm.drawLine(Vec3(-x,-y, z), Vec3( x,-y, z), color);
  gm.drawLine(Vec3( x,-y, z), Vec3( x, y, z), color);
  gm.drawLine(Vec3( x, y, z), Vec3(-x, y, z), color);
  gm.drawLine(Vec3(-x, y, z), Vec3(-x,-y, z), color);

  // sides
  gm.drawLine(Vec3(-x,-y,-z), Vec3(-x,-y, z), color);
  gm.drawLine(Vec3( x,-y,-z), Vec3( x,-y, z), color);
  gm.drawLine(Vec3(-x, y,-z), Vec3(-x, y, z), color);
  gm.drawLine(Vec3( x, y,-z), Vec3( x, y, z), color);
}
