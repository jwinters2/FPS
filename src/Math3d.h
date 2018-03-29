#include <iostream>
#pragma once

struct Vec3
{
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double);
  Vec3(double,double,double);
  Vec3(const Vec3&);
};

std::ostream& operator<<(std::ostream&, const Vec3&);
Vec3 operator+(const Vec3&, const Vec3&);
Vec3 operator+=(Vec3&, const Vec3&);
Vec3 operator-(const Vec3&, const Vec3&);
Vec3 operator-=(Vec3&, const Vec3&);
Vec3 operator*(const Vec3&, double);
Vec3 operator*=(Vec3&, double);
Vec3 operator/(const Vec3&, double);
Vec3 operator/=(Vec3&, double);
Vec3 operator*(double, Vec3&);
double operator*(Vec3&, Vec3&);
