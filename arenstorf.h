#pragma once
#include "Object.h"
class Model_Arenstorf : protected Object {
public:
  Model_Arenstorf(int n_, long double *start_conditions)
      : Object(4, start_conditions){};
  ~Model_Arenstorf() = default;
  virtual void function(long double *ind, long double *dep,
                        long double *step_result) override;
  virtual long double *GetA() override { return a; }
  virtual long double GetA_I(int i) override { return a[i]; }
  virtual void run();
};
