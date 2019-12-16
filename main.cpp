#include "Object.h"
#include "dormand_prince.h"
#include <iostream>
using namespace std;

int main() {
  long double *start = new long double[2];
  start[0] = 1.L;
  start[1] = 4.2665L;
  Object a(2, start);
  a.run(0., 500);
}
