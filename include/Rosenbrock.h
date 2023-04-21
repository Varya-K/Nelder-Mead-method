#pragma once
#include "Function.h"
class Rosenbrock: public Function
{
public:
	Rosenbrock();
	double Calculate(Point p);
};

