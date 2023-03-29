
#include <iostream>
#include "Himmelblau.h"
#include "Nelder–Mead_method.h"
#include "Point.h"
#include "Rosenbrock.h"

int main()
{
	Himmelblau Hf;
	Function* Hfun=&Hf;
	Rosenbrock Rf;
	Function* Rfun = &Rf;
	double  ecceptable_error = 0.01;
	double reflection = 1;
	double expansion = 2;
	double contraction = 0.5;
	double shrink = 0.5;
	printf("\nHimmelblau\n");
	Point ResultH = NelderMead_method(Hfun, ecceptable_error);
	printf("\nRosenbrock\n");
	Point ResultR = NelderMead_method(Rfun, ecceptable_error);
	
}


