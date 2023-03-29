#pragma once
#include "Point.h"
class Function
{
protected:
	int dimensionality;
public:
	Function(int dimenionality);
	int Dimensionality() const;
	virtual double Calculate(Point p) = 0;
};

