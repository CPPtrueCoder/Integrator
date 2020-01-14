#pragma once
#include "Object.h"
class Math_Pendulum : protected Object {
private:
  double alpha;
  double beta;

public:
  Math_Pendulum(long double l, long double m, long double k, long double theta);
  virtual void function(long double *ind, long double *dep,
                        long double *step_result) override;
  virtual void run(long double tk);
  // long double** result_list = 0;
};
