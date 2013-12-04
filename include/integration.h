#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "vector2d.h"

typedef struct s_state {
  vector2d position;
  vector2d speed;
  // Quick and dirty
  double mass;
  struct s_state* ps1;
  struct s_state* ps2;
  struct s_state* ps3;
} state;

//! Addition of two states for integration
state ss_add(state, state);

//! Multiplication of a state by a scalar for integration
state ss_multiply(double, state);

//! Euler method
void euler(state*, state(*)(state), double);

//! Runge-Kutta method
void rk4(state*, state(*)(state), double);

#endif // INTEGRATION_H

