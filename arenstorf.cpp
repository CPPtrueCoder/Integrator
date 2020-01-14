#include "arenstorf.h"
#include "dormand_prince.h"
#include <iostream>
#include <time.h>

void Model_Arenstorf::run() {
  long double t_start = 0;

  long double period = 11.124340337266085134999734047;
  long double t_finish = 4 * period;
  long double delta = 1e-2;
  long double time;
  int size = (int)((t_finish - t_start) / delta) + 1;
  result_list = new long double *[size];
  for (int i = 0; i < size; i++) {
    result_list[i] = new long double[n + 1];
  }
  Integrator_Dormand_Prince integrator(1e-16, 1e-16, 1e-16, 1e-16, n, 1, size);
  time = clock();
  long double *result = integrator.integration(t_start, t_finish, this);
  time = (clock() - time) / CLOCKS_PER_SEC;
  std::cout << "time elapsed " << time << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << result[i] << std::endl;
  }
  plotter(0, 2, size);
  integrator.~Integrator_Dormand_Prince();
}
void Model_Arenstorf::function(long double *ind, long double *dep,
                               long double *step_result) {
  long double d1;
  long double d2;
  long double M = 0.012277471L;
  long double m = 1.l - M;
  d1 = (pow(pow(dep[0] + M, 2) + pow(dep[2], 2), 1.5));
  d2 = (pow(pow(dep[0] - m, 2) + pow(dep[2], 2), 1.5));
  step_result[1] = dep[0] + 2.l * (dep[3]) - (m * (dep[0] + M) / d1) -
                   (M * (dep[0] - m) / d2);
  step_result[3] =
      dep[2] - 2.l * (dep[1]) - (m * (dep[2]) / d1) - (M * (dep[2]) / d2);
  step_result[0] = dep[1];
  step_result[2] = dep[3];
}
