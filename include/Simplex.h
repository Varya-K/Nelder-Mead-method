#pragma once
#include "Point.h"
#include "Function.h"


class Simplex
{
public:
	Simplex(int count, int dimension); //создает симплекс размера count с случайными точками размерности dimension
	~Simplex();
	int Count() const;
	int Dimension() const;
	Point& operator[](int i);
	Point centroid(int ind_except);
	void sort_simplex(Function* f);
	double standard_deviation(Function* f);
private:
	int count;
	int dimension;
	Point* points;
};

