
#include <iostream>
#include "Himmelblau.h"
#include "Nelder–Mead_method.h"
#include "Point.h"
#include "Rosenbrock.h"

int main()
{
	Himmelblau Hf;
	Rosenbrock Rf;
	double  ecceptable_error = 0.01;
	double reflection = 1;
	double expansion = 2;
	double contraction = 0.5;
	double shrink = 0.5;
	printf("\nHimmelblau\n");
	NelderMead_method ResultH = NelderMead_method(&Hf, ecceptable_error);
	ResultH.Save("1.txt");
	printf("\nRosenbrock\n");
	NelderMead_method ResultR = NelderMead_method(&Rf, ecceptable_error, reflection, expansion, contraction, shrink);
	ResultR.Print();
	
}


