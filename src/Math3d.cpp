#include <iostream>

#include "Math3d.h"

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
