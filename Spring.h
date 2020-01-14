#pragma once
#include "Object.h"
class Spring : protected Object {
private:
  double alpha;
  double beta;
  double mu;

public:
  Spring(long double beta_, long double m, long double k, long double theta,
         long double mu_);
  virtual void function(long double *ind, long double *dep,
                        long double *step_result) override;
  virtual void run(long double tk);
  // long double **result_list = 0;
};
