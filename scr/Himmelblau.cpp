#include "Himmelblau.h"
#include <iostream>

Himmelblau::Himmelblau() :Function(2){}

double Himmelblau::Calculate(Point p)
{
	double x = p[0];
	double y = p[1];
	return (pow(x * x + y - 11, 2) + pow(x + y * y - 7, 2));
}
