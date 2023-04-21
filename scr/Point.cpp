#include "Point.h"
#include <iostream>



Point::Point() :dimension(0), coordinates(new double[0]) {};

Point::Point(int Dimension): dimension(Dimension){
	coordinates=new double[Dimension]();
	for (int i = 0; i < Dimension; i++) {
		coordinates[i] = pow(-1, rand() % 2) * ((float)rand() / (float)rand());
	}
}

Point::Point(int Dimension, double* Coordinates) : dimension(Dimension) 
												, coordinates(Coordinates)  {}

/*Point::~Point() {
	delete[] coordinates;
}*/

int Point::Dimension() const { return dimension; }

double Point::operator[](int i) const {
	return coordinates[i];
}

Point Point::operator+ (Point p) const {
	if (dimension == p.dimension) {
		double* coord = new double[dimension];
		for (int i = 0; i < dimension; i++) {
			coord[i] = coordinates[i] + p.coordinates[i];
		}
		Point p1(dimension, coord);
		return p1;


	}
	else return 0;
}

Point Point::operator- (Point p) const {
	if (dimension == p.dimension) {
		double* coord = new double[dimension];
		for (int i = 0; i < dimension; i++) {
			coord[i] = coordinates[i] - p.coordinates[i];
		}
		Point p1(dimension, coord);
		return p1;
	}
	else return 0;
}



Point Point::operator* (double a) const {
	double* coord = new double[dimension];
	for (int i = 0; i < dimension; i++) {
		coord[i] = coordinates[i] * a;
	}
	Point p1(dimension, coord);
	return p1;

}
Point Point::operator/ (double a)  const{
	double* coord = new double[dimension];
	for (int i = 0; i < dimension; i++) {
		coord[i] = coordinates[i] / a;
	}
	Point p1(dimension, coord);
	return p1;
}

Point operator* (double a, Point p) {
	double* coord = new double[p.Dimension()];
	for (int i = 0; i < p.Dimension(); i++) {
		coord[i] = p[i] * a;
	}
	Point p1(p.Dimension(), coord);
	return p1;
}

