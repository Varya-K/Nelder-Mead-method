#pragma once
#include "Point.h"
class Function
{
protected:
	int dimension;
public:
	Function(int dimention);
	int Dimension() const;
	virtual double Calculate(Point p) = 0;
};

