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

  SupportPoint nextPoint;
  nextPoint.a = GJKSupport(a,direction);
  nextPoint.v = nextPoint.a - GJKSupport(b,-direction);

  std::vector<SupportPoint> simplex;
  simplex.push_back(nextPoint);

  direction = -nextPoint.v;
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
    nextPoint.a = GJKSupport(a,direction);
    nextPoint.v = nextPoint.a - GJKSupport(b,-direction);
    
    // if the next point is not in the same direction (roughly) as the direction
    // then we've gone as far as we can in that direction and it wasn't enough
    // to enclose the origin, return false
    if(nextPoint.v * direction < 0)
    {
      retval = false;
      break;
    }

    #ifdef GJK_DEBUG
    std::cout << "nextPoint = " << nextPoint.v << std::endl;
    std::cout << "direction = " << direction << std::endl;
    std::cout << "nextPoint * direction = "
              << nextPoint.v * direction << std::endl;
    #endif
     

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

bool PhysicsEngine::GJKNearestSimplex(std::vector<SupportPoint>& simplex, 
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
bool PhysicsEngine::GJKNearestSimplexCase2(std::vector<SupportPoint>& simplex, 
                                      Vec3& direction) const
{
  Vec3 ao = -simplex[1].v;
  Vec3 ab =  simplex[0].v - simplex[1].v;

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

  #ifdef GJK_DEBUG
  for(unsigned int i=0; i<simplex.size(); i++)
  {
    std::cout << (i==0?"CASE 2: ":"        ") << simplex[i].v << std::endl;
  }
  std::cout << "       ab = " << ab << std::endl;
  std::cout << "       ao = " << ao << std::endl;
  std::cout << "      dir = " << direction << std::endl;
  #endif


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
bool PhysicsEngine::GJKNearestSimplexCase3(std::vector<SupportPoint>& simplex, 
                                           Vec3& direction) const
{
  Vec3 ao = -simplex[2].v;
  Vec3 ab =  simplex[1].v - simplex[2].v;
  Vec3 ac =  simplex[0].v - simplex[2].v;

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
        SupportPoint temp = simplex[0];
        simplex[0] = simplex[1];
        simplex[1] = temp;
        direction = -abc;
      }
    }
  }

  #ifdef GJK_DEBUG
  for(unsigned int i=0; i<simplex.size(); i++)
  {
    std::cout << (i==0?"CASE 3: ":"        ") << simplex[i].v << std::endl;
  }
  std::cout << "       ab = " << ab << std::endl;
  std::cout << "       ac = " << ac << std::endl;
  std::cout << "       ao = " << ao << std::endl;
  std::cout << "      abc = " << abc << std::endl;
  std::cout << "      dir = " << direction << std::endl;
  #endif

  return false;
}

bool PhysicsEngine::GJKNearestSimplexCase4(std::vector<SupportPoint>& simplex, 
                                           Vec3& direction) const
{
  Vec3 ao = -simplex[3].v; 
  Vec3 ab =  simplex[2].v - simplex[3].v; 
  Vec3 ac =  simplex[1].v - simplex[3].v; 
  Vec3 ad =  simplex[0].v - simplex[3].v; 

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
        SupportPoint temp = simplex[0];
        simplex[0] = simplex[1];
        simplex[1] = temp;
        GJKNearestSimplexCase3(simplex,direction);
      }
      else
      {
        // we enclose the origin
        #ifdef GJK_DEBUG
        for(unsigned int i=0; i<simplex.size(); i++)
        {
          std::cout << (i==0?"CASE 4: ":"        ") << simplex[i].v << std::endl;
        }
        std::cout << "       ab = " << ab << std::endl;
        std::cout << "       ac = " << ac << std::endl;
        std::cout << "       ad = " << ad << std::endl;
        std::cout << "       ao = " << ao << std::endl;
        std::cout << "      abc = " << abc << std::endl;
        std::cout << "      acd = " << acd << std::endl;
        std::cout << "      adb = " << adb << std::endl;
        std::cout << "      dir = " << direction << std::endl;
        #endif
        return true;
      }
    }
  }

  #ifdef GJK_DEBUG
  for(unsigned int i=0; i<simplex.size(); i++)
  {
    std::cout << (i==0?"CASE 4: ":"        ") << simplex[i].v << std::endl;
  }
  std::cout << "       ab = " << ab << std::endl;
  std::cout << "       ac = " << ac << std::endl;
  std::cout << "       ad = " << ad << std::endl;
  std::cout << "       ao = " << ao << std::endl;
  std::cout << "      abc = " << abc << std::endl;
  std::cout << "      acd = " << acd << std::endl;
  std::cout << "      adb = " << adb << std::endl;
  std::cout << "      dir = " << direction << std::endl;
  #endif

  return false;
}

bool PhysicsEngine::EPAAlgorithm(const RigidBody& a, const RigidBody& b, 
                                 std::vector<SupportPoint>& simplex, 
                                 CollisionInfo& ci) const
{
  std::vector<Triangle> facesList;
  std::vector<Edge> edgesList;

  // add abc face
  facesList.push_back(Triangle());
  facesList.back().v[0] = simplex[3];
  facesList.back().v[1] = simplex[2];
  facesList.back().v[2] = simplex[1];
  // add acd face
  facesList.push_back(Triangle());
  facesList.back().v[0] = simplex[3];
  facesList.back().v[1] = simplex[1];
  facesList.back().v[2] = simplex[0];
  // add adb face
  facesList.push_back(Triangle());
  facesList.back().v[0] = simplex[3];
  facesList.back().v[1] = simplex[0];
  facesList.back().v[2] = simplex[2];
  // add cbd face
  facesList.push_back(Triangle());
  facesList.back().v[0] = simplex[1];
  facesList.back().v[1] = simplex[2];
  facesList.back().v[2] = simplex[0];

  while(true)
  {
    #ifdef GJK_DEBUG
    for(unsigned int i=0; i<facesList.size(); i++)
    {
      std::cout << (i==0 ? "facesList = ":
                           "            ")
                << facesList[i].v[0].v << " "
                << facesList[i].v[1].v << " "
                << facesList[i].v[2].v << std::endl;
      Vec3 abc = (facesList[i].v[1].v - facesList[i].v[0].v).cross     // ab x ac
                 (facesList[i].v[2].v - facesList[i].v[0].v).normal();
      std::cout << "        n = " << abc << " (l=" << abc.length() << ")" << std::endl;
      if(facesList[i].v[0].v * abc < 0)
      {
        std::cout << "NORMAL POINTS TOWARDS THE ORIGIN" << std::endl;
      }
    }
    #endif

    // find the face closest to the origin (the projection of the origin onto
    // the face has the shortest length)
    Vec3 abc = (facesList[0].v[1].v - facesList[0].v[0].v).cross     // ab x ac
               (facesList[0].v[2].v - facesList[0].v[0].v).normal();
    double currentMinDist  = std::abs(facesList[0].v[0].v * abc);
    Vec3   searchDirection = abc;
    Triangle currentFace = facesList[0];

    for(unsigned int i=1; i<facesList.size(); i++)
    {
      abc = (facesList[i].v[1].v - facesList[i].v[0].v).cross     // ab x ac
            (facesList[i].v[2].v - facesList[i].v[0].v).normal();
      if(currentMinDist > std::abs(facesList[i].v[0].v * abc))
      {
        currentMinDist  = std::abs(facesList[i].v[0].v * abc);
        searchDirection = abc;
        currentFace = facesList[i];
      }
    }

    // get the furthest point in that distance
    SupportPoint expansionPoint;
    expansionPoint.a = GJKSupport(a, searchDirection);
    expansionPoint.v = expansionPoint.a - GJKSupport(b,-searchDirection);

    #ifdef GJK_DEBUG
    std::cout << currentFace.v[0].v << " ";
    std::cout << currentFace.v[1].v << " ";
    std::cout << currentFace.v[2].v << std::endl;
    std::cout << "expansionPoint       = " << expansionPoint.v << std::endl;
    std::cout << "                 searchDirection = "
              << searchDirection << std::endl;
    std::cout << "expansionPoint * searchDirection = " 
              << expansionPoint.v * searchDirection << std::endl;
    std::cout << "currentMinDist       = " << currentMinDist << std::endl;
    #endif

    // if we didn't get any new distance we're done
    // (the new point is co-planar with the closest face)
    //if(std::abs((searchDirection * expansionPoint.v)
    //           - std::abs(currentMinDist)) < 0.02)
    if((searchDirection * expansionPoint.v) - currentMinDist < 0.02)
    {
      ci.areColliding = true;

      // calculate barycentric weights for our triangle

      // projection of the origin onto the closest face
      Vec3 tp = currentFace.v[0].v *
               (currentFace.v[0].v * searchDirection.normal());

      Vec3 ta = currentFace.v[0].v;  // the vertices of the triangle
      Vec3 tb = currentFace.v[1].v;
      Vec3 tc = currentFace.v[2].v;

      // the area of the main triangle
      // (we're getting ratios, so we ignore the /2)
      double abcArea = ((tb-ta).cross(tc-ta)).length();

      // the areas of each sub-triangle (p with 2 other vertices)
      //double abpArea = ((a-p).cross(b-p)).length(); // we don't need this one
      double bcpArea = ((tb-tp).cross(tc-tp)).length();
      double acpArea = ((ta-tp).cross(tc-tp)).length();

      double u = bcpArea / abcArea;
      double v = acpArea / abcArea;
      double w = 1.0 - u - v; // they always sum to 1

      // get the same point using the original a's vertices
      ci.pointOfContact = currentFace.v[0].a * u
                        + currentFace.v[1].a * v
                        + currentFace.v[2].a * w;

      // calculate the minimum separation
      ci.minimumSeparation = searchDirection * currentMinDist;

      // calculate the impulse
      if(searchDirection * currentMinDist != Vec3(0))
      {
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

        // velocities of the points of contact
        // (center of mass velocity plus tangental velocity (omega x r)
        Vec3 avel = a.velocity + a.angularVelocity.cross
                                 (ci.pointOfContact - a.position);
        Vec3 bvel = b.velocity + b.angularVelocity.cross
                                 (ci.pointOfContact - b.position);

        ci.impulse = -1 * ci.minimumSeparation.normal()
                   * (ci.minimumSeparation.normal() * (avel - bvel))
                   * (1 + rest) / massComponent;
      }
      else
      {
        ci.impulse = Vec3(0);
      }
      return true;
    }

    // clear the edge list (we don't need to keep edges between iterations)
    edgesList.clear();

    // add edges of faces that face in the same general way
    for(unsigned int i=0; i<facesList.size(); i++)
    {
      abc = (facesList[i].v[1].v - facesList[i].v[0].v).cross     // ab x ac
            (facesList[i].v[2].v - facesList[i].v[0].v).normal();
      if(abc * (expansionPoint.v - facesList[i].v[0].v) > 0)
      {
        // add this face's edges to the edge list (remove if their reverse is
        // in the list)

        for(int j=0; j<3; j++)
        {
          SupportPoint pointA;
          SupportPoint pointB;

          // get the points of the edge
          switch(j)
          {
            case 0:
              pointA = facesList[i].v[1];
              pointB = facesList[i].v[2];
              break;
            case 1: 
              pointA = facesList[i].v[2];
              pointB = facesList[i].v[0];
              break;
            case 2:
              pointA = facesList[i].v[0];
              pointB = facesList[i].v[1];
              break;
          }

          // determine if the edge is already in the edge list (reversed,
          // since it would have belonged to another triangle
          bool isInEdgeList = false;
          for(unsigned int k = 0; k < edgesList.size(); k++)
          {
            if(edgesList[k].v[0].v == pointB.v 
            && edgesList[k].v[1].v == pointA.v)
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
            edgesList.push_back(Edge());
            edgesList.back().v[0] = pointA;
            edgesList.back().v[1] = pointB;
          }
        }

        // remove the face from the faces list
        facesList.erase(facesList.begin() + i);
        i--;
      }
    }

    for(unsigned int j=0; j < edgesList.size(); j++)
    {
      // make a new triangle from each edge and the new point and add it
      facesList.push_back(Triangle());
      facesList.back().v[0] = edgesList[j].v[0];
      facesList.back().v[1] = edgesList[j].v[1];
      facesList.back().v[2] = expansionPoint;
    }
  }
}

// constructors for helper structs
PhysicsEngine::Triangle::Triangle()
{
  v[0] = SupportPoint();
  v[1] = SupportPoint();
  v[2] = SupportPoint();
}

PhysicsEngine::Triangle::Triangle(const Triangle& t)
{
  v[0] = t.v[0];
  v[1] = t.v[1];
  v[2] = t.v[2];
}

PhysicsEngine::Edge::Edge()
{
  v[0] = SupportPoint();
  v[1] = SupportPoint();
}

PhysicsEngine::Edge::Edge(const Edge& e)
{
  v[0] = e.v[0];
  v[1] = e.v[1];
}

PhysicsEngine::SupportPoint::SupportPoint()
{
  v = Vec3();
  a = Vec3();
}

PhysicsEngine::SupportPoint::SupportPoint(const SupportPoint& s)
{
  v = s.v;
  a = s.a;
}
