#include <cstdlib>
#include <ctime>
#include <chrono>

#include "Math3d.h"
#include "GraphicsManager.h"
#include "World.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  GraphicsManager gm(640,480,false);
  gm.loadModel("assets/statue.obj");

  /*
  for(int i=0; i<50; i++)
  {
    gm.beginRender();
    gm.renderModel("assets/statue.obj");
    gm.endRender();
    usleep(100 * 1000);
  }
  */

  std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
  std::chrono::time_point<std::chrono::high_resolution_clock> newTime;
  std::chrono::duration<double> elapsedTime;

  World world(10.0);
  while(true)
  {
    // this loop has all the timing and whatnot happening in it

    // get the current time
    currentTime = std::chrono::high_resolution_clock::now();

    world.update();
    world.draw();

    // get the current time again
    newTime = std::chrono::high_resolution_clock::now();
    // the elapsed time is the difference
    elapsedTime = newTime - currentTime;
    // the current time is now the new time
    currentTime = newTime;

    std::cout << "elapsed time: " << elapsedTime.count() << " " << std::endl;
    std::cout << "FPS:          " << 1/elapsedTime.count() << " " << std::endl;
  }

};
