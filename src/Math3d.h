#include <iostream>
#pragma once

int randInt(int);
int randInt(int, int);
double randDouble();
double randDouble(double);
double randDouble(double, double);

// quaternion needs to know what this is
struct Mat4;

/*
 * Vec3
 *
 * a vector with 3 elements
 * used for positions, directions, and scaling
 */
struct Vec3
{
  double x;
  double y;
  double z;

  Vec3();
  Vec3(double);
  Vec3(double,double,double);
  Vec3(const Vec3&);

  double length() const;
  Vec3 normal() const;
  Vec3 normalize();

  Vec3 operator-() const;

  Vec3 cross(const Vec3&) const;
};

std::ostream& operator<<(std::ostream&, const Vec3&);
Vec3 operator+(const Vec3&, const Vec3&);
Vec3 operator+=(Vec3&, const Vec3&);
Vec3 operator-(const Vec3&, const Vec3&);
Vec3 operator-=(Vec3&, const Vec3&);
Vec3 operator*(double, const Vec3&);
Vec3 operator*(const Vec3&, double);
Vec3 operator*=(Vec3&, double);
Vec3 operator/(const Vec3&, double);
Vec3 operator/=(Vec3&, double);
Vec3 operator*(double, Vec3&);
double operator*(const Vec3&, const Vec3&);
bool operator==(const Vec3&, const Vec3&);
bool operator!=(const Vec3&, const Vec3&);

/*

 * Quat
 *
 * a vector with 4 elements
 * used for rotations (which are quaternions)
 */

struct Quat
{
 double x;
 double y;
 double z;
 double s;

 Quat();
 Quat(const Vec3&, double);

 Mat4 toMatrix() const;

 void applyRotation(const Quat&);

 static Quat slerp(const Quat&,const Quat&,double);
 double dot(const Quat&) const;
 Quat normal() const;
};

std::ostream& operator<<(std::ostream&, const Quat&);
Quat operator*(const Quat&, const Quat&);
Quat operator*(const Quat&, double);
Quat operator+(const Quat&, const Quat&);
Quat operator-(const Quat&, const Quat&);

/*
 * Mat3
 *
 * a 3x3 matrix
 * used for moments of inertia
 */

struct Mat3
{
  double x[3];
  double y[3];
  double z[3];

  Mat3();
  Mat3(double);
  Mat3(const Mat3&);

  Mat3 invert() const;
};

std::ostream& operator<<(std::ostream&, const Mat3&);
Vec3 operator*(const Mat3&, const Vec3&);

/*
 * Mat4
 *
 * a 4x4 matrix
 * used for transformations
 */

struct Mat4
{
  double x[4];
  double y[4];
  double z[4];
  double w[4];

  Mat4();
  Mat4(double);
  Mat4(const Mat4&);

  static Mat4 Identity();
  static Mat4 Translate(const Vec3&);
  static Mat4 Scale(const Vec3&);
  static Mat4 Rotate(const Quat&);
};

std::ostream& operator<<(std::ostream&, const Mat4&);
Mat4 operator*(const Mat4&, const Mat4&);
Mat4 operator*=(Mat4&, const Mat4&);
Vec3 operator*(const Mat4&, const Vec3&);

struct Transform
{
  Vec3 pos;
  Vec3 scale;
  Quat rot;

  Transform();

  Mat4 toMatrix() const;
};

std::ostream& operator<<(std::ostream&, const Transform);
