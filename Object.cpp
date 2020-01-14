#include "Object.h"
#include "dormand_prince.h"
#include <iostream>
Object::Object(int n_, long double *start_conditions) {
  n = n_;
  a = new long double[n];
  for (int i = 0; i < n; i++) {
    a[i] = start_conditions[i];
  }
}
Object::~Object() = default;

void Object::run(long double t_start, long double t_finish) {

  int size = (int)((t_finish - t_start) / 1e-2) + 1;
  result_list = new long double *[size];
  for (int i = 0; i < size; i++) {
    result_list[i] = new long double[n + 1];
  }
  Integrator_Dormand_Prince integrator(1e-8, 1e-8, 1e-8, 1e-8, n, 1e-2, size);
  long double *result = integrator.integration(t_start, t_finish, this);
  for (int i = 0; i < n; i++) {
    std::cout << result[i] << std::endl;
  }
  plotter(0, 1, size);
  integrator.~Integrator_Dormand_Prince();
}
void Object::function(long double *ind, long double *dep,
                      long double *step_result) {

  step_result[0] =
      2.l + pow(a[0] + dep[0], 2) * (a[1] + dep[1]) - 9.533l * (a[0] + dep[0]);
  step_result[1] =
      8.533 * (a[0] + dep[0]) - pow(a[0] + dep[0], 2) * (a[1] + dep[1]);
}
void Object::SetA(long double *a_) {
  for (int i = 0; i < n; i++)
    a[i] = a_[i];
}
void Object::plotter(int k, int l, int size) {
  FILE *pipe = _popen("B:/gnuplot/bin/gnuplot.exe", "w");
  if (pipe != nullptr) {
    fprintf(pipe, "set term win\n");

    fprintf(pipe, "plot '-' with lines\n");
    for (int i = 0; i < size; i++)
      fprintf(pipe, "%lf %lf\n", (double)result_list[i][k],
              (double)result_list[i][l]);
    fprintf(pipe, "%s\n", "e");

    fflush(pipe);
  } else
    puts("Could not open the file\n");
  system("pause");
  if (pipe)
    _pclose(pipe);

  system("pause");
}
