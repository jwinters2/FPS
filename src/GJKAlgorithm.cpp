#include "PhysicsEngine.h"

#include <vector>

bool PhysicsEngine::GJKAlgorithm(const RigidBody& a, const RigidBody& b, 
                                 CollisionInfo&) const
{
  // return false if one rigidbody doesn't have a hitbox (it's empty)
  if(a.hitbox.empty() || b.hitbox.empty())
  {
    return false;
  }

  Vec3 direction(1,0,0);
  Vec3 nextPoint = GJKSupport(a,direction) - GJKSupport(b,-direction);
  std::vector<Vec3> simplex;
  simplex.push_back(firstPoint);
  direction = -firstPoint;
  bool retval;

  while(true)
  {
    // calculate the next point
    nextPoint = GJKSupport(a,direction) - GJKSupport(b,-direction);
    
    // if the next point is not in the same direction (roughly) as the direction
    // then we've gone as far as we can in that direction and it wasn't enough
    // to enclose the origin, return false
    if(nextPoint * direction < 0)
    {
      retval = false;
      break;
    }

    // add the next point to the simplex
    simplex.push_back(nextPoint);

    // GJKNearestSimplex modifies the simplex and direction, and returns whether
    // or not the origin is in the simplex (and therefore the Minkowski
    // difference and the shapes intersect)
    if(GJKNearestSimplex(simplex, direction))
    {
      retval = true;
      break;
    }
  }

  return retval;
}

Vec3 PhysicsEngine::GJKSupport(const RigidBody& r, const Vec3& v) const
{
  // get the point in r's hitbox with the highest dot produc with v
  double currentMax = r.hitbox[0] * v;
  Vec3 retval = r.hitbox[0];

  for(unsigned int i=1; i<r.hitbox.size(); i++)
  {
    double current = r.hitbox[i] * v;
    if(current > currentMax)
    {
      currentMax = current;
      retval = r.hitbox[i];
    }
  }

  return retval;
}

bool PhysicsEngine::GJKNearestSimplex(std::vector<Vec3>& simplex, 
                                      Vec3& direction) const
{
}
