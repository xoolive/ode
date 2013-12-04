#include "vector2d.h"

//! Addition of two vectors
vector2d dv2_add(vector2d v1, vector2d v2)
{
  vector2d result = { v1.x + v2.x, v1.z + v2.z };
  return result;
}

//! Multiplication of a vector by a scalar
vector2d dv2_multiply(double d, vector2d v)
{
  vector2d result = { d*v.x, d*v.z };
  return result;
}

//! Dot product of two vectors
double dv2_dot(vector2d v1, vector2d v2)
{
  return (v1.x*v2.x + v1.z*v2.z);
}

