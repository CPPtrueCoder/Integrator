#pragma once
class Object
{
protected :
	long double* a;
	int n;
public:
	Object() = default;
	Object(int n_, long double* start_conditions);
	~Object();
	virtual void run(long double t_start, long double t_finish);
	virtual void function(long double* ind, long double* dep, long double* step_result);
	virtual long double* GetA() { return a; }
	virtual void SetA(long double* a_);
	virtual long double GetA_I(int i) { return a[i]; }
};

