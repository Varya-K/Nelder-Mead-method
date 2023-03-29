#include "Rosenbrock.h"
#include <iostream>

Rosenbrock::Rosenbrock() :Function(2) {}

double Rosenbrock::Calculate(Point p)
{
	double x = p[0];
	double y = p[1];
	return (pow(1-x, 2) + 100*pow(y-x*x, 2));
}
