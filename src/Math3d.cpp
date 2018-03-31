#include <iostream>

#include "Math3d.h"

// ----------------
// VEC3 DEFINITIONS
// ----------------

Vec3::Vec3(): x(0), y(0), z(0) {}
Vec3::Vec3(double d): x(d), y(d), z(d) {}
Vec3::Vec3(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
Vec3::Vec3(const Vec3& o): x(o.x), y(o.y), z(o.z) {}

std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
  out << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
  return out;
}

Vec3 operator+(const Vec3& a, const Vec3& b)
{
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator+=(Vec3& a, const Vec3& b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return Vec3(a);
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator-=(Vec3& a, const Vec3& b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return Vec3(a);
}

Vec3 operator*(const Vec3& a, double c)
{
  return Vec3(c * a.x, c * a.y, c * a.z);
}

Vec3 operator*(double c, Vec3& a)
{
  return Vec3(c * a.x, c * a.y, c * a.z);
}

Vec3 operator*=(Vec3& a, double c)
{
  a.x *= c;
  a.y *= c;
  a.z *= c;
  return Vec3(a);
}

Vec3 operator/(const Vec3& a, double c)
{
  return Vec3(a.x / c, a.y / c, a.z / c);
}

Vec3 operator/=(Vec3& a, double c)
{
  a.x /= c;
  a.y /= c;
  a.z /= c;
  return Vec3(a);
}

double operator*(Vec3& a, Vec3& b)
{
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// ----------------
// QUAT DEFINITIONS
// ----------------

Quat::Quat():x(0),y(0),z(0),w(0) {}

// ----------------
// MAT4 DEFINITIONS
// ----------------

/*
 *   [0][1][2][3]
 * x  .  .  .  .
 * y  .  .  .  .
 * z  .  .  .  .
 * w  .  .  .  .
 */

Mat4::Mat4():x{1.0,0.0,0.0,0.0} // apparently C++ initalizer lists don't need 
            ,y{0.0,1.0,0.0,0.0} // parens with array-bracket-lists
            ,z{0.0,0.0,1.0,0.0}
            ,w{0.0,0.0,0.0,1.0}
            {}

Mat4::Mat4(double d):x{  d,0.0,0.0,0.0}
                    ,y{0.0,  d,0.0,0.0}
                    ,z{0.0,0.0,  d,0.0}
                    ,w{0.0,0.0,0.0,  d}
                    {}

Mat4::Mat4(const Mat4& o):x{o.x[0], o.x[1], o.x[2], o.x[3],}
                         ,y{o.y[0], o.y[1], o.y[2], o.y[3],}
                         ,z{o.z[0], o.z[1], o.z[2], o.z[3],}
                         ,w{o.w[0], o.w[1], o.w[2], o.w[3],}
                         {}

Mat4 Mat4::Identity()
{
  /*
   * [ 1, 0, 0, 0 ]
   * [ 0, 1, 0, 0 ]
   * [ 0, 0, 1, 0 ]
   * [ 0, 0, 0, 1 ]
   */
  return Mat4();
}

Mat4 Mat4::Translate(const Vec3& v)
{
  /*
   * [ 1, 0, 0, x ]
   * [ 0, 1, 0, y ]
   * [ 0, 0, 1, z ]
   * [ 0, 0, 0, 1 ]
   */
  Mat4 retval;
  retval.x[3] = v.x;
  retval.y[3] = v.y;
  retval.z[3] = v.z;
  return retval;
}

Mat4 Mat4::Scale(const Vec3& v)
{
  /*
   * [ x, 0, 0, 0 ]
   * [ 0, y, 0, 0 ]
   * [ 0, 0, z, 0 ]
   * [ 0, 0, 0, 1 ]
   */
   Mat4 retval;
   retval.x[0] = v.x;
   retval.y[1] = v.y;
   retval.z[2] = v.z;
   return retval;
}
//static Mat4 Mat4::Rotate(const Quat&);

std::ostream& operator<<(std::ostream& out, const Mat4& m)
{
  out << "[ " << m.x[0] << ", " << m.x[1] << ", "
      <<         m.x[2] << ", " << m.x[3] << " ]" << std::endl

      << "[ " << m.y[0] << ", " << m.y[1] << ", "
      <<         m.y[2] << ", " << m.y[3] << " ]" << std::endl

      << "[ " << m.z[0] << ", " << m.z[1] << ", "
      <<         m.z[2] << ", " << m.z[3] << " ]" << std::endl

      << "[ " << m.w[0] << ", " << m.w[1] << ", "
      <<         m.w[2] << ", " << m.w[3] << " ]" << std::endl;
}


Mat4 operator*(const Mat4& A, const Mat4& B)
{
  Mat4 retval;

  retval.x[0] = ( A.x[0] * B.x[0] ) + ( A.x[1] * B.y[0] ) +
                ( A.x[2] * B.z[0] ) + ( A.x[3] * B.w[0] );
  retval.x[1] = ( A.x[0] * B.x[1] ) + ( A.x[1] * B.y[1] ) +
                ( A.x[2] * B.z[1] ) + ( A.x[3] * B.w[1] );
  retval.x[2] = ( A.x[0] * B.x[2] ) + ( A.x[1] * B.y[2] ) +
                ( A.x[2] * B.z[2] ) + ( A.x[3] * B.w[2] );
  retval.x[3] = ( A.x[0] * B.x[3] ) + ( A.x[1] * B.y[3] ) +
                ( A.x[2] * B.z[3] ) + ( A.x[3] * B.w[3] );

  retval.y[0] = ( A.y[0] * B.x[0] ) + ( A.y[1] * B.y[0] ) +
                ( A.y[2] * B.z[0] ) + ( A.y[3] * B.w[0] );
  retval.y[1] = ( A.y[0] * B.x[1] ) + ( A.y[1] * B.y[1] ) +
                ( A.y[2] * B.z[1] ) + ( A.y[3] * B.w[1] );
  retval.y[2] = ( A.y[0] * B.x[2] ) + ( A.y[1] * B.y[2] ) +
                ( A.y[2] * B.z[2] ) + ( A.y[3] * B.w[2] );
  retval.y[3] = ( A.y[0] * B.x[3] ) + ( A.y[1] * B.y[3] ) +
                ( A.y[2] * B.z[3] ) + ( A.y[3] * B.w[3] );

  retval.z[0] = ( A.z[0] * B.x[0] ) + ( A.z[1] * B.y[0] ) +
                ( A.z[2] * B.z[0] ) + ( A.z[3] * B.w[0] );
  retval.z[1] = ( A.z[0] * B.x[1] ) + ( A.z[1] * B.y[1] ) +
                ( A.z[2] * B.z[1] ) + ( A.z[3] * B.w[1] );
  retval.z[2] = ( A.z[0] * B.x[2] ) + ( A.z[1] * B.y[2] ) +
                ( A.z[2] * B.z[2] ) + ( A.z[3] * B.w[2] );
  retval.z[3] = ( A.z[0] * B.x[3] ) + ( A.z[1] * B.y[3] ) +
                ( A.z[2] * B.z[3] ) + ( A.z[3] * B.w[3] );

  retval.w[0] = ( A.w[0] * B.x[0] ) + ( A.w[1] * B.y[0] ) +
                ( A.w[2] * B.z[0] ) + ( A.w[3] * B.w[0] );
  retval.w[1] = ( A.w[0] * B.x[1] ) + ( A.w[1] * B.y[1] ) +
                ( A.w[2] * B.z[1] ) + ( A.w[3] * B.w[1] );
  retval.w[2] = ( A.w[0] * B.x[2] ) + ( A.w[1] * B.y[2] ) +
                ( A.w[2] * B.z[2] ) + ( A.w[3] * B.w[2] );
  retval.w[3] = ( A.w[0] * B.x[3] ) + ( A.w[1] * B.y[3] ) +
                ( A.w[2] * B.z[3] ) + ( A.w[3] * B.w[3] );

  return retval;
}

Mat4 operator*=(Mat4& A, const Mat4& B)
{ 
}

Vec3 operator*(const Mat4& A, const Vec3& v)
{
  Vec3 retval;
  retval.x = ( A.x[0] * v.x) + (A.x[1] * v.y) + (A.x[2] * v.z) + A.x[3];
  retval.y = ( A.y[0] * v.x) + (A.y[1] * v.y) + (A.y[2] * v.z) + A.y[3];
  retval.z = ( A.z[0] * v.x) + (A.z[1] * v.y) + (A.z[2] * v.z) + A.z[3];
  return retval;
}
