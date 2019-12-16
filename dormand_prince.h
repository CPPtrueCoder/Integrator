#pragma once
#include "Object.h"
#include <vector>
class dormand_prince
{
private:
	int n;
	int size;
	long double eps;
	long double eps_max;
	long double h;
	long double new_h;
	long double delta;
	long double** k;
	
	long double** b;
	
	long double** result_list;
	
public:
	dormand_prince(long double eps_, long double eps_max_, long double h_, long double new_h_, int n_, long double delta_,int size_);
	~dormand_prince() = default;
	long double eps_(long  double* a1, long double* a4, long  double* a5);
	long double h_new(long double eps);
	long double* integration(long  double t_start, long  double t_finish,Object* example);
	void plotter(int k, int l,int size);
};
const long  double c[7] = { 0.L, 0.2L, 0.3L, 0.8L, 8.L / 9.L, 1.L, 1.L };
const long  double a[7][6] = {
	{ 0.L },
	{ 1.L / 5.L },
	{ 3.L / 40.L, 9.L / 40.L },
	{ 44.l / 45.l, -56.l / 15.l, 32.l / 9.l },
	{ 19372.l / 6561.l, -25360.l / 2187.l, 64448.l / 6561.l, -212.l / 729.l },
	{ 9017.l / 3168.l, -355.l / 33.l, 46732.l / 5247.l, 49.l / 176.l, -5103.l / 18656.l },
	{ 35.l / 384.l, 0.l, 500.l / 1113.l, 125.l / 192.l, -2187.l / 6784.l, 11.l / 84.l }
};
const long double b1[7] = { 35.l / 384.l, 0.l, 500.l / 1113.l, 125.l / 192.l, -2187.l / 6784.l, 11.l / 84.l, 0.l };
const long double b2[7] = { 5179.l / 57600.l, 0.l, 7571.l / 16695.l, 393.l / 640.l, -92097.l / 339200.l, 187.l / 2100.l, 1.l / 40.l };
const long double d[7] = { -12715105075.l / 11282082432.l,0.l,87487479700.l / 32700410799.l,-10690763975.l / 1880347072.l,701980252875.l / 199316789632.l,-1453857185.l / 822651844.l,69997945.l / 29380423.l };
const long double e[7] = { 71.l / 57600.l,0,-71.l / 16695.l,71.l / 1920.l,-17253.l / 339200.l,22.l / 525.l,-1.l / 40.l };
