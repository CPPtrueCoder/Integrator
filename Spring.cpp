#include "Spring.h"
#include "dormand_prince.h"
#include <cmath>
#include <iostream>
#define g 9.81
using namespace std;
Spring::Spring(long double beta_, long double m, long double k,
               long double theta, long double mu_) {
  n = 2;
  a = new long double[n];
  a[0] = theta;
  a[1] = 0;
  beta = beta_;
  alpha = k / m;
  mu = mu_;
}
void Spring::function(long double *ind, long double *dep,
                      long double *step_result) {

  step_result[0] = dep[1];
  if (fabs(dep[1]) < 1e-16) {
    step_result[1] = -alpha * dep[0];
  } else if (dep[1] > 0) {
    step_result[1] = -alpha * dep[0] - beta * dep[1] - mu * g;
  } else if (dep[1] < 0) {
    step_result[1] = -alpha * dep[0] - beta * dep[1] + mu * g;
  }
}
void Spring::run(long double tk) {
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
