#include <cstdlib>
#include <ctime>

#include "Math3d.h"
#include "GraphicsManager.h"
#include "World.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  GraphicsManager gm(1920,1080);
  gm.loadModel("assets/triangle.obj");
  gm.renderModel("assets/triangle.obj");
  
  World world;
  for(int i=0; i<10; i++)
  {
    world.update();
    world.draw();
  }

  while(true);
};
