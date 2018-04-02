#include "WireframeBox.h"
#include "GraphicsManager.h"

WireframeBox::WireframeBox(const Vec3& dim,const Vec3& col):dimensions(dim)
                                                         ,color(col)
{}

WireframeBox::~WireframeBox() {}

void WireframeBox::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference();

  double x = dimensions.x;
  double y = dimensions.y;
  double z = dimensions.z;

  // bottom square
  gm.drawLine(transform * Vec3(-x,-y,-z), transform * Vec3( x,-y,-z), color);
  gm.drawLine(transform * Vec3( x,-y,-z), transform * Vec3( x, y,-z), color);
  gm.drawLine(transform * Vec3( x, y,-z), transform * Vec3(-x, y,-z), color);
  gm.drawLine(transform * Vec3(-x, y,-z), transform * Vec3(-x,-y,-z), color);

  // top square
  gm.drawLine(transform * Vec3(-x,-y, z), transform * Vec3( x,-y, z), color);
  gm.drawLine(transform * Vec3( x,-y, z), transform * Vec3( x, y, z), color);
  gm.drawLine(transform * Vec3( x, y, z), transform * Vec3(-x, y, z), color);
  gm.drawLine(transform * Vec3(-x, y, z), transform * Vec3(-x,-y, z), color);

  // sides
  gm.drawLine(transform * Vec3(-x,-y,-z), transform * Vec3(-x,-y, z), color);
  gm.drawLine(transform * Vec3( x,-y,-z), transform * Vec3( x,-y, z), color);
  gm.drawLine(transform * Vec3(-x, y,-z), transform * Vec3(-x, y, z), color);
  gm.drawLine(transform * Vec3( x, y,-z), transform * Vec3( x, y, z), color);
}
