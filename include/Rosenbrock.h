#pragma once
#include "Function.h"
class Rosenbrock: public Function
{
public:
	Rosenbrock();
	int Dimensionality() const;
	double Calculate(Point p);
};

