#include <stdio.h> // use of printf
#include <stdlib.h> // use of EXIT_SUCCESS, atoi, atof
#include <string.h>

#include "vector2d.h"
#include "integration.h"

state ballistic_derivate(state s);
state twobody_derivate(state s);
state fourbody_derivate(state s);

enum PROBLEM { BALLISTIC, TWOBODY, FOURBODY };

int main(int argc, char* argv[])
{
  double dt = 0.001;
  unsigned int nb_iter = 1e5;
  void (*integration)(state*, state(*)(state), double) ;
  integration = euler;
  enum PROBLEM problem = BALLISTIC;
  char* filename = "output.txt";

  size_t idx = 0;
  while ( ++idx < argc )
  {
    if (strcmp(argv[idx], "--help") == 0)
    {
      printf("--help         displays this help\n");
      printf("--integration  choose integration method, euler (default) or rk4\n");
      printf("--iter         choose number of iteration, default 100000\n");
      printf("--output       output file name, default 'output.txt'\n");
      printf("--problem      choose problem, ballistic (default), twobody or fourbody\n");
      printf("--step         choose integration step, default 0.001\n");

      return EXIT_SUCCESS;
    }
    if (strcmp(argv[idx], "--integration") == 0)
    {
      if (++idx < argc)
      {
        if (strcmp(argv[idx], "euler") == 0)
        {
          printf ("Integrate with Euler\n");
          integration = euler ;
          continue;
        }
        if (strcmp(argv[idx], "rk4") == 0)
        {
          printf ("Integrate with RK4\n");
          integration = rk4 ;
          continue;
        }
        printf ("Syntax: '--integration euler' or '--integration rk4'\n");
        return 4;
      }
    }

    if (strcmp(argv[idx], "--problem") == 0)
    {
      if (++idx < argc)
      {
        if (strcmp(argv[idx], "ballistic") == 0)
        {
          printf ("Ballistic problem\n");
          problem = BALLISTIC ;
          continue;
        }
        if (strcmp(argv[idx], "twobody") == 0)
        {
          printf ("Two body problem\n");
          problem = TWOBODY ;
          continue;
        }
        if (strcmp(argv[idx], "fourbody") == 0)
        {
          printf ("Four body problem\n");
          problem = FOURBODY ;
          continue;
        }
        printf ("Syntax: '--problem ballistic' or '--problem twobody'\n");
        printf ("     or '--problem fourbody'\n");
        return 4;
      }
    }

    if (strcmp(argv[idx], "--step") == 0)
    {
      if (++idx < argc)
      {
        dt = atof(argv[idx]);
        printf( "Integration step: %lf\n", dt );
        continue;
        if (dt < 1e-19)
        {
          printf ("Syntax: '--step 0.001' (positive floating point value)\n");
          return 4;
        }
      }
    }

    if (strcmp(argv[idx], "--iter") == 0)
    {
      if (++idx < argc)
      {
        nb_iter = atoi(argv[idx]);
        printf( "Number of iterations: %d\n", nb_iter );
        continue;
        if (nb_iter < 1)
        {
          printf ("Syntax: '--iter 1e6' (positive integer value)\n");
          return 4;
        }
      }
    }

    if (strcmp(argv[idx], "--output") == 0)
      if (++idx < argc)
      {
        filename = argv[idx];
        continue;
      }
  }

  FILE* f = fopen (filename, "w");
  printf ("Output file: %s\n", filename);

  if (problem == BALLISTIC)
  {
    state current = { {0., 100.}, {100., 100.}, 2. };

    while (current.position.z >= 0.)
    {
      fprintf(f, "%lf %lf\n", current.position.x, current.position.z);
      integration (&current, ballistic_derivate, dt);
    }
    fclose(f);
    return EXIT_SUCCESS;
  }

  if (problem == TWOBODY)
  {
    state s1 = { {10., 0.}, {0., -1.}, 8e11};
    state s2 = { {-8., 0.}, {0., .8}, 1e12 };

    s1.ps1 = &s2;
    s2.ps1 = &s1;

    size_t i = 0;
    while (++i < nb_iter)
    {
      fprintf(f, "%lf %lf %lf %lf\n",
              s1.position.x, s1.position.z,
              s2.position.x, s2.position.z);
      integration (&s1, twobody_derivate, dt);
      integration (&s2, twobody_derivate, dt);
    }
    fclose(f);
    return EXIT_SUCCESS;
  }

  if (problem == FOURBODY)
  {
    state b1 = { {10., 0.},  {0., -1.}, 1e11 };
    state b2 = { {-10., 0.},  {0., 1.}, 1e11 };
    state b3 = { {0., 10.},  {1., 0.},  1e11 };
    state b4 = { {0., -10.}, {-1., 0.}, 1e11 };

    b1.ps1 = &b2; b1.ps2 = &b3; b1.ps3 = &b4;
    b2.ps1 = &b1; b2.ps2 = &b3; b2.ps3 = &b4;
    b3.ps1 = &b1; b3.ps2 = &b2; b3.ps3 = &b4;
    b4.ps1 = &b1; b4.ps2 = &b2; b4.ps3 = &b3;

    size_t i = 0;
    while (++i < nb_iter)
    {

      fprintf(f, "%lf %lf %lf %lf %lf %lf %lf %lf\n",
              b1.position.x, b1.position.z,
              b2.position.x, b2.position.z,
              b3.position.x, b3.position.z,
              b4.position.x, b4.position.z);

      integration (&b1, fourbody_derivate, dt);
      integration (&b2, fourbody_derivate, dt);
      integration (&b3, fourbody_derivate, dt);
      integration (&b4, fourbody_derivate, dt);
    }

    fclose(f);
    return EXIT_SUCCESS;
  }
}
