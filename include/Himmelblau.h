#pragma once
#include "Function.h"
class Himmelblau: public Function
{
public:
	Himmelblau();
	int Dimensionality() const;
	double Calculate(Point p);
};

