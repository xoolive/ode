#include "integration.h"

vector2d gravity = {0., -9.81};
double cx = 0.5;
double sref = 0.1;
double rho = 1.184;

state ballistic_derivate(state s)
{
  state dt;
  dt.position = s.speed;
  dt.speed = gravity;
  return dt;
}
