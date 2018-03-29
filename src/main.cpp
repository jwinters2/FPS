#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Math3d.h"
#include "GraphicsManager.h"
#include "World.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  GraphicsManager gm(640,480);
  gm.loadModel("assets/statue.obj");
  gm.loadModel("assets/triangle.obj");

  for(int i=0; i<50; i++)
  {
    gm.beginRender();
    gm.renderModel("assets/statue.obj");
    //gm.renderModel("assets/triangle.obj");
    gm.endRender();
    usleep(100 * 1000);
  }
  
  /*
  World world;
  for(int i=0; i<50; i++)
  {
    world.update();
    world.draw();
    usleep(100 * 1000);
  }
  */

};
