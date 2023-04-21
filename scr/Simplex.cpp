#include "Simplex.h"
#include <iostream>


Simplex::Simplex(int count, int dimension) {
	this->count = count;
	this->dimension = dimension;
	points = new Point[count];
	for (int i = 0; i < count; i++) {
		points[i] = Point(dimension);
	}
}

Simplex::~Simplex() {
	delete[] points;
}

int Simplex::Count() const { return count; }
int Simplex::Dimension() const { return dimension; }

Point& Simplex::operator[](int i) {
	if (i >= 0 && i < count) {
		return points[i];
	}
}


Point Simplex::centroid(int ind_except) {
	Point sum(dimension, new double[dimension]());
	for (int i = 0; i < count; i++) {
		if (i != ind_except) {
			sum = sum + points[i];
		}
	}
	if (ind_except >= 0 && ind_except < count) return sum / (double)(count-1);
	else return sum / count;
}

void Simplex::sort_simplex(Function* f) {
	for (int i = 1; i < count; i++) {
		for (int j = 0; j < count-i; j++) {
			if (f->Calculate(points[j]) > f->Calculate(points[j + 1])){
				Point t = points[j];
				points[j] = points[j + 1];
				points[j + 1] = t;
			}
		}
	}
}

double Simplex::standard_deviation(Function* f) {
	double sum=0;
	for (int i = 0; i < count; i++) {
		sum = sum + f->Calculate(points[i]);
	}
	double avarage = sum / count;
	sum = 0;
	for (int i = 0; i < count; i++) {
		sum = sum + (f->Calculate(points[i])-avarage)*(f->Calculate(points[i]) - avarage);
	}
	return pow(sum/count,0.5);
}

