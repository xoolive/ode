#include "integration.h"

state ss_add(state s1, state s2)
{
  state s = {{s1.position.x + s2.position.x, s1.position.z + s2.position.z},
             {s1.speed.x + s2.speed.x, s1.speed.z + s2.speed.z} };
  // quick and dirty
  s.mass = s1.mass;
  s.ps1 = s1.ps1;
  s.ps2 = s1.ps2;
  s.ps3 = s1.ps3;
  return s;
}

state ss_multiply(double d, state s)
{
  state r = {{d * s.position.x, d * s.position.z},
             {d * s.speed.x, d * s.speed.z}};
  // quick and dirty
  r.mass = s.mass;
  r.ps1 = s.ps1;
  r.ps2 = s.ps2;
  r.ps3 = s.ps3;
  return r;
}

void euler(state* cur, state(*derivate)(state), double dt)
{
  *cur = ss_add(*cur, ss_multiply(dt, derivate(*cur)));
}

void rk4(state* cur, state(*derivate)(state), double dt)
{

}
