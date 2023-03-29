#pragma once
#include "Simplex.h"
#include "Point.h"
#include "Function.h"


Point NelderMead_method(Function* f, double ecceptable_error,
	double reflection = 1, double expansion = 2,
	double contraction = 0.5, double shrink = 0.5);



