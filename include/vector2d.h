#ifndef VECTOR2D_H
#define VECTOR2D_H

typedef struct s_vector2d {
  double x, z;
} vector2d ;

//! Addition of two vectors
vector2d dv2_add(vector2d, vector2d);

//! Multiplication of a vector by a scalar
vector2d dv2_multiply(double, vector2d);

//! Dot product of two vectors
double dv2_dot(vector2d, vector2d);

#endif // VECTOR2D_H

