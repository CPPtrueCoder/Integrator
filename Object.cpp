#include "Object.h"
#include "dormand_prince.h"
#include <cmath>
#include <iostream>
Object::Object(int n_, long double *start_conditions) {
  n = n_;
  a = new long double[n];
  for (int i = 0; i < n; i++) {
    a[i] = start_conditions[i];
    // std::cout << a[i] << std::endl;
    // printf_s("%.16lf\n", a[i]);
  }
}
Object::~Object() = default;

void Object::run(long double t_start, long double t_finish) {
  /*long double h = 1e-2;
  long double t = t_start;
  long double* ind = new long double[n];
  long double* dep = new long double[n];
  for (int i = 0; i < n; i++)
  {
          ind[i] = t;
          dep[i] = a[i];
  }
  while (t <= t_finish)
  {
          long double* result = function(ind, dep);
          t += h;
          for (int i = 0; i < n; i++)
          {
                  a[i] += result[i];
                  ind[i] = t;
          }
  }*/
  int size = (int)((t_finish - t_start) / 1e-2) + 1;
  dormand_prince integrator(1e-8, 1e-8, 1e-8, 1e-8, n, 1e-2, size);
  long double *result = integrator.integration(t_start, t_finish, this);
  for (int i = 0; i < n; i++) {
    std::cout << result[i] << std::endl;
  }
  integrator.plotter(0, 1, size);
  integrator.~dormand_prince();
}
void Object::function(long double *ind, long double *dep,
                      long double *step_result) {

  step_result[0] = 2.l + pow(dep[0], 2) * (dep[1]) - 9.533l * (dep[0]);
  step_result[1] = 8.533 * (dep[0]) - pow(dep[0], 2) * (dep[1]);
}
void Object::SetA(long double *a_) {
  for (int i = 0; i < n; i++)
    a[i] = a_[i];
}
