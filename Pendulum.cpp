#include "Pendulum.h"
#include "dormand_prince.h"
#include <cmath>
#include <iostream>
#define g 9.81
using namespace std;
Math_Pendulum::Math_Pendulum(long double l, long double m, long double k,
                             long double theta) {
  n = 2;
  a = new long double[n];
  a[0] = theta;
  a[1] = 0;
  beta = k / m;
  alpha = sqrt(g / l);
}
void Math_Pendulum::function(long double *ind, long double *dep,
                             long double *step_result) {
  step_result[0] = dep[1];
  step_result[1] = -pow(alpha, 2) * dep[0] - 2 * beta * dep[1];
}
void Math_Pendulum::run(long double tk) {
  int size = (int)((tk) / 1e-2) + 1;
  result_list = new long double *[size];
  for (int i = 0; i < size; i++) {
    result_list[i] = new long double[n + 1];
  }
  Integrator_Dormand_Prince integrator(1e-8, 1e-8, 1e-8, 1e-8, n, 1e-2, size);
  long double *result = integrator.integration(0, tk, this);
  for (int i = 0; i < n; i++) {
    std::cout << result[i] << std::endl;
  }
  plotter(2, 0, size);
  integrator.~Integrator_Dormand_Prince();
}
