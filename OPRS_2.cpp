// OPRS_2.cpp : Этот файл содержит функцию "main". Здесь начинается и
// заканчивается выполнение программы.
//

#include "Object.h"
#include "Pendulum.h"
#include "Spring.h"
#include "arenstorf.h"
#include <iostream>

int main() {
  long double *start = new long double[2];
  start[0] = 1.L;
  start[1] = 4.2665L;
  Object a(2, start);

  long double *start_conditions = new long double[4];
  start_conditions[0] = 0.994L;
  start_conditions[1] = 0.L;
  start_conditions[2] = 0.L;
  start_conditions[3] = -2.0317326295573368357302057924;

  Math_Pendulum b(0.3, 10, 1, 0.1);
  b.run(30);
  //  Model_Arenstorf *b = new Model_Arenstorf(4, start_conditions);
  //  b->run();
  //  Spring p(1, 1e-2, 10, 0.5, 0);
  //  p.run(10);
  //  Spring d(0, 1e-2, 10, 0.5, 0.3);
  //  d.run(10);
  //  Spring z(0, 1e-2, 10, 0.5, 0);
  //  z.run(10);
}
