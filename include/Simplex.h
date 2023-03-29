#pragma once
#include "Point.h"
#include "Function.h"


class Simplex
{
private:
	int count;
	int dimensionality;
	Point* points;
public:
	Simplex(int count, int dimensoinality);
	Simplex(int count, int dimensionality, Point* pionts);
	int Count() const;
	int Dimensionality() const;
	Point* Points() const;
	void Points(Point* s);
	Point& operator[](int i);
	void rand_points();
	Point centroid(int ind_except);
	void sort_simplex(Function* f);
	double standard_deviation(Function* f);
};

