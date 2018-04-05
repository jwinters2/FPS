#include "PhysicsEngine.h"

//#define GJK_DEBUG

#include <vector>

bool PhysicsEngine::GJKAlgorithm(const RigidBody& a, const RigidBody& b, 
                                 CollisionInfo& ci) const
{
  // return false if one rigidbody doesn't have a hitbox (it's empty)
  if(a.hitbox.empty() || b.hitbox.empty())
  {
    return false;
  }

  #ifdef GJK_DEBUG
  Mat4 Ta = a.getTransform().toMatrix();
  for(unsigned int i = 0; i < a.hitbox.size(); i++)
  {
    std::cout << (i==0 ? "A = " : "    ") << Ta * a.hitbox[i] << std::endl;
  }
  std::cout << std::endl;
  Mat4 Tb = b.getTransform().toMatrix();
  for(unsigned int i = 0; i < b.hitbox.size(); i++)
  {
    std::cout << (i==0 ? "B = " : "    ") << Tb * b.hitbox[i] << std::endl;
  }
  std::cout << std::endl;
  #endif

  Vec3 direction(1,0,0);
  Vec3 nextPoint = GJKSupport(a,direction) - GJKSupport(b,-direction);
  std::vector<Vec3> simplex;
  simplex.push_back(nextPoint);
  direction = -nextPoint;
  bool retval;

  while(true)
  {
    // (debugging) print simplex and direction
    /*
    for(unsigned int i=0; i<simplex.size(); i++)
    {
      std::cout << (i==0 ? "simplex   = " :
                           "            ")
                << simplex[i] << std::endl;
    }
    std::cout << "direction = " << direction << std::endl;
    // */

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

    /*
    std::cout << "nextPoint = " << nextPoint << std::endl;
    std::cout << "nextPoint * direction = "
              << nextPoint * direction << std::endl;
    // */

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
  
    /*
    std::cout << std::endl;
    // */
  }

  if(retval)
  {
    EPAAlgorithm(a,b,simplex,ci);
  }

  return retval;
}

Vec3 PhysicsEngine::GJKSupport(const RigidBody& r, const Vec3& v) const
{
  // get the point in r's hitbox with the highest dot produc with v
  Mat4 t = r.getTransform().toMatrix();
  double currentMax = (t * r.hitbox[0]) * v;
  Vec3 retval = (t * r.hitbox[0]);

  for(unsigned int i=1; i<r.hitbox.size(); i++)
  {
    double current = (t * r.hitbox[i]) * v;
    if(current > currentMax)
    {
      currentMax = current;
      retval = (t * r.hitbox[i]);
    }
  }

  /*
  std::cout << "support: "<< retval << std::endl;
  // */
  return retval;
}

bool PhysicsEngine::GJKNearestSimplex(std::vector<Vec3>& simplex, 
                                      Vec3& direction) const
{
  switch(simplex.size())
  {
    case 2: return GJKNearestSimplexCase2(simplex, direction);
    case 3: return GJKNearestSimplexCase3(simplex, direction);
    case 4: return GJKNearestSimplexCase4(simplex, direction);
  }

  // we shouldn't hit a case other than 2,3 or 4 vertices
  // if we do we (I) made a mistake somewhere
  std::cout << "ERROR: GJK simplex vertex-count is outside range [2,4]"
            << std::endl;
  return false;
}

/*
 * our simplex is a line (2 points)
 *
 * it looks something like:
 *
 * [3] |    [1]     |  [2]
 *     |            |
 *   b *------------* a
 *     |            |
 *     |            |
 *
 *
 * where a is the new point
 *
 * the origin can't exist in [3] or a would be in that general direction
 * (a is the point we just found), so we just need to check if the origin is in 
 * [1] or [2]
 *
 * if ab . ao > 0 (a to b is roughly in the direction of a to the origin)
 *   [1]: s = [b,a], d = ab x ao x ab
 * else
 *   [2]: s = [a], d = ao
 */
bool PhysicsEngine::GJKNearestSimplexCase2(std::vector<Vec3>& simplex, 
                                      Vec3& direction) const
{
  Vec3 ao = -simplex[1];
  Vec3 ab = simplex[0] - simplex[1];

  if(ab * ao > 0)
  {
    // don't need to change the simplex
    direction = ab.cross(ao.cross(ab));
    //std::cout << "Case 2 region [1] (no removal)" << std::endl;
  }
  else
  {
    // [b,a] -> [a]
    simplex.erase(simplex.begin());
    direction = ao;
    //std::cout << "Case 2 region [2] (removal" << std::endl;
  }

  return false;
}

/*
 * our simplex is a triangle (3 points)
 *
 * it looks something like:
 *
 *
 *    c * 
 *      |  -       [1]
 *      |     -           /
 *      |        -       /
 *      |           -   /
 *      |  [4]         * a  [2]
 *      |  [5]       -  \
 *      |          -      \
 *      |        -          \
 *      |      -
 *      |     -   [3]
 *      |   -
 *      | -
 *    b *
 *
 *
 * if (abc x ac) . ao > 0  (abc = ab x ac)
 *   [1, 2 or 3]
 *   if ac . ao > 0
 *     [1]: s = [c,a], d = ac x ao x ac
 *   else
 *     [2 or 3]
 *     Case 2: s = [b,a], d = ba
 * else
 *   [2, 3, 4 or 5]
 *   if (abc x ab) . ao > 0
 *     [2 or 3]
 *     Case 2: s = [b,a], d = ba
 *   else
 *     [4 or 5]
 *     if abc . ao > 0
 *       [4]: s = [c,b,a], d = abc
 *     else
 *       [5]: s = [b,c,a], d = -abc
 *    
 */
bool PhysicsEngine::GJKNearestSimplexCase3(std::vector<Vec3>& simplex, 
                                           Vec3& direction) const
{
  Vec3 ao = -simplex[2];
  Vec3 ab = simplex[1] - simplex[2];
  Vec3 ac = simplex[0] - simplex[2];

  Vec3 abc = ab.cross(ac);

  if(abc.cross(ac) * ao > 0)
  {
    if(ac * ao > 0)
    {
      // region 1
      // [c,b,a] -> [c,a]
      simplex.erase(simplex.begin() + 1);
      direction = ac.cross(ao.cross(ac));
      //std::cout << "Case 3 region 1 (removal)" << std::endl;
    }
    else
    {
      // this is identical to a simplex [b] that just added a
      // [c,b,a] -> [b,a]
      simplex.erase(simplex.begin());
      //std::cout << "Case 3 region 2,3 (removal)" << std::endl;
      GJKNearestSimplexCase2(simplex,direction);
    }
  }
  else
  {
    if(-(abc.cross(ab)) * ao > 0)
    {
      // this is identical to a simplex [b] that just added a
      // [c,b,a] -> [b,a]
      simplex.erase(simplex.begin());
      //std::cout << "Case 3 region 2,3 (removal) (second)" << std::endl;
      GJKNearestSimplexCase2(simplex,direction);
    }
    else
    {
      if(abc * ao > 0)
      {
        // region 4 (we don't need to change the simplex)
        //std::cout << "Case 3 region 4" << std::endl;
        direction = abc;
      }
      else
      {
        // region 5 (swap b and c to keep the triangle anti-clockwise)
        //std::cout << "Case 3 region 5 (swap)" << std::endl;
        Vec3 temp = simplex[0];
        simplex[0] = simplex[1];
        simplex[1] = temp;
        direction = -abc;
      }
    }
  }

  return false;
}

bool PhysicsEngine::GJKNearestSimplexCase4(std::vector<Vec3>& simplex, 
                                           Vec3& direction) const
{
  Vec3 ao = -simplex[3]; 
  Vec3 ab = simplex[2] - simplex[3]; 
  Vec3 ac = simplex[1] - simplex[3]; 
  Vec3 ad = simplex[0] - simplex[3]; 

  Vec3 abc = ab.cross(ac);
  Vec3 acd = ac.cross(ad);
  Vec3 adb = ad.cross(ab);

  if(abc * ao > 0)
  {
    if(acd * ao > 0)
    {
      // the nearest simplex is the ac edge, pretend we just added a
      // [d,c,b,a] -> [c,a]
      simplex.erase(simplex.begin());
      simplex.erase(simplex.begin() + 2);
      GJKNearestSimplexCase2(simplex,direction);
    }
    else
    {
      if(adb * ao > 0)
      {
        // the nearest simplex is the ab edge, pretend we just added a
        // [d,c,b,a] -> [b,a]
        simplex.erase(simplex.begin());
        simplex.erase(simplex.begin() + 1);
        GJKNearestSimplexCase2(simplex,direction);
      }
      else
      {
        // the nearest simplex is the abc triangle, pretend we just added a
        // [d,c,b,a] -> [c,b,a]
        simplex.erase(simplex.begin());
        GJKNearestSimplexCase3(simplex,direction);
      }
    }
  }
  else
  {
    if(acd * ao > 0)
    {
      if(adb * ao > 0)
      {
        // the nearest simplex is the ad edge, pretend we just added a
        // [d,c,b,a] -> [d,a]
        simplex.erase(simplex.begin() + 1);
        simplex.erase(simplex.begin() + 2);
        GJKNearestSimplexCase2(simplex,direction);
      }
      else
      {
        // the nearest simplex is the acd triangle, pretend we just added a
        // [d,c,b,a] -> [d,c,a]
        simplex.erase(simplex.begin() + 2);
        GJKNearestSimplexCase3(simplex,direction);
      }
    }
    else
    {
      if(adb * ao > 0)
      {
        // the nearest simplex is the adb triangle, pretend we just added a
        // [d,c,b,a] -> [b,d,a]
        simplex.erase(simplex.begin() + 1);
        Vec3 temp = simplex[0];
        simplex[0] = simplex[1];
        simplex[1] = temp;
        GJKNearestSimplexCase3(simplex,direction);
      }
      else
      {
        // we enclse the origin
        return true;
      }
    }
  }

  return false;
}

bool PhysicsEngine::EPAAlgorithm(const RigidBody& a, const RigidBody& b, 
                                 std::vector<Vec3>& simplex, CollisionInfo& ci)
const
{
  std::vector<std::vector<Vec3>> facesList;
  std::vector<std::vector<Vec3>> edgesList;

  // add abc face
  facesList.push_back(std::vector<Vec3>());
  facesList.back().push_back(simplex[3]);
  facesList.back().push_back(simplex[2]);
  facesList.back().push_back(simplex[1]);
  // add acd face
  facesList.push_back(std::vector<Vec3>());
  facesList.back().push_back(simplex[3]);
  facesList.back().push_back(simplex[1]);
  facesList.back().push_back(simplex[0]);
  // add adb face
  facesList.push_back(std::vector<Vec3>());
  facesList.back().push_back(simplex[3]);
  facesList.back().push_back(simplex[0]);
  facesList.back().push_back(simplex[2]);
  // add cbd face
  facesList.push_back(std::vector<Vec3>());
  facesList.back().push_back(simplex[1]);
  facesList.back().push_back(simplex[2]);
  facesList.back().push_back(simplex[0]);

  while(true)
  {
    #ifdef GJK_DEBUG
    for(unsigned int i=0; i<facesList.size(); i++)
    {
      std::cout << (i==0 ? "facesList = ":
                           "            ")
                << facesList[i][0] << " "
                << facesList[i][1] << " "
                << facesList[i][2] << std::endl;
    }
    #endif

    // find the face closest to the origin (the projection of the origin onto
    // the face has the shortest length)
    Vec3 abc = (facesList[0][1] - facesList[0][0]).cross     // ab x ac
               (facesList[0][2] - facesList[0][0]).normal(); // (b-a) x (c-a)
    double currentMinDist  = -facesList[0][0] * abc;
    Vec3   searchDirection = abc;// * currentMinDist;

    for(unsigned int i=1; i<facesList.size(); i++)
    {
      abc = (facesList[i][1] - facesList[i][0]).cross     // ab x ac
            (facesList[i][2] - facesList[i][0]).normal(); // (b-a) x (c-a)
      if(std::abs(currentMinDist) > std::abs(-facesList[i][0] * abc))
      {
        currentMinDist  = -facesList[i][0] * abc;
        searchDirection = abc;// * currentMinDist;
      }
    }

    // get the furthest point in that distance
    Vec3 expansionPoint = GJKSupport(a, searchDirection)
                        - GJKSupport(b,-searchDirection);

    // if we didn't get any new distance we're done
    // (the new point is co-planar with the closest face)
    #ifdef GJK_DEBUG
    std::cout << "expansionPoint       = " << expansionPoint << std::endl;
    std::cout << "                 searchDirection = "
              << searchDirection << std::endl;
    std::cout << "expansionPoint * searchDirection = " 
              << expansionPoint * searchDirection << std::endl;
    std::cout << "currentMinDist       = " << currentMinDist << std::endl;
    #endif
    if(std::abs((searchDirection * expansionPoint)
               - std::abs(currentMinDist)) < 0.02)
    {
      ci.areColliding = true;

      if(searchDirection != Vec3(0))
      {
        ci.minimumSeparation = searchDirection * currentMinDist;
        double massComponent;
        double rest = (a.restitution > b.restitution ? a.restitution
                                                     : b.restitution);

        if(a.invMass == 0)
        {
          massComponent = b.invMass;
        }
        else if(b.invMass == 0)
        {
          massComponent = a.invMass;
        }
        else
        {
          double Am = 1.0 / a.invMass;
          double Bm = 1.0 / b.invMass;
          massComponent = (Am + Bm) * a.invMass * b.invMass;
        }

        ci.impulse = -1 * ci.minimumSeparation.normal()
                   * (ci.minimumSeparation.normal() * (a.velocity - b.velocity))
                   * (1 + rest) / massComponent;
      }
      else
      {
        ci.impulse = Vec3(0);
      }

      return true;
    }

    // add edges of faces that face in the same general way
    for(unsigned int i=0; i<facesList.size(); i++)
    {
      abc = (facesList[i][1] - facesList[i][0]).cross     // ab x ac
            (facesList[i][2] - facesList[i][0]).normal(); // (b-a) x (c-a)
      if(abc * expansionPoint > 0)
      {
        // add this face's edges to the edge list (remove if their reverse is
        // in the list)

        for(int j=0; j<3; j++)
        {
          Vec3 pointA;
          Vec3 pointB;

          // get the points of the edge
          switch(j)
          {
            case 0: pointA = facesList[i][1]; pointB = facesList[i][2]; break;
            case 1: pointA = facesList[i][2]; pointB = facesList[i][0]; break;
            case 2: pointA = facesList[i][0]; pointB = facesList[i][1]; break;
          }

          // determine if the edge is already in the edge list (reversed,
          // since it would have belonged to another triangle
          bool isInEdgeList = false;
          for(unsigned int k = 0; k < edgesList.size(); k++)
          {
            if(edgesList[k][0] == pointB && edgesList[k][1] == pointA)
            {
              isInEdgeList = true;
              // remove it if it's there
              edgesList.erase(edgesList.begin() + k);
              break;
            }
          }

          // add it to the edges list otherwise
          if(!isInEdgeList)
          {
            edgesList.push_back(std::vector<Vec3>());
            edgesList.back().push_back(pointA);
            edgesList.back().push_back(pointB);
          }
        }

        // remove the face from the faces list
        facesList.erase(facesList.begin() + i);
        i--;
      }
    }

    for(unsigned int i=0; i < edgesList.size(); i++)
    {
      // make a new triangle from each edge and the new point and add it
      facesList.push_back(std::vector<Vec3>());
      facesList.back().push_back(edgesList[i][0]);
      facesList.back().push_back(edgesList[i][1]);
      facesList.back().push_back(expansionPoint);
    }

    // clear the edge list (we don't need to keep edges between iterations)
    edgesList.clear();
  }
}
