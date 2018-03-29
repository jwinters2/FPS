#include <cstdlib>
#include <ctime>

#include "Math3d.h"
#include "GraphicsManager.h"
#include "World.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  GraphicsManager gm(1920,1080);
  
  /*
  World world;
  for(int i=0; i<10; i++)
  {
    world.update();
    world.draw();
  }
  */

  Vec3 a(1);
  Vec3 b(2,3,4);

  std::cout << "a    = " << a << std::endl;
  std::cout << "b    = " << b << std::endl;
  std::cout << std::endl;
  Vec3 c(a);
  b += (c *= 5.0);
  std::cout << std::endl;
  std::cout << "a    = " << a << std::endl;
  std::cout << "b    = " << b << std::endl;
  std::cout << "c    = " << c << std::endl;

  while(true);
};
