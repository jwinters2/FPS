#include <cstdlib>
#include <ctime>

#include "World.h"

int main(int argc, char** argv)
{
  srand(time(NULL));

  World world;
  for(int i=0; i<10; i++)
  {
    world.update();
    world.draw();
  }
};
