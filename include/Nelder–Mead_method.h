#pragma once
#include "Simplex.h"
#include "Point.h"
#include "Function.h"
#include <iostream>
#include <fstream>
#include <iomanip>


class NelderMead_method{
public:
	NelderMead_method(Function* F, double Ecceptable_error);
	NelderMead_method(Function* F, double Ecceptable_error, double Reflection, double Expansion, double Contraction, double Shrink);
	Point Min();
	void Print();
	void Save(const char* file_name);
private:
	Function* f;
	double ecceptable_error;
	double reflection = 1;
	double expansion = 2;
	double contraction = 0.5;
	double shrink = 0.5;
	bool should_be_printed = false;
	void Print_begin_end();
	void Print_middle(int step, Point Xl, Point Xg, Point Xh, Point Xr, Point Xe, Point Xc, double st_deviation);
};




