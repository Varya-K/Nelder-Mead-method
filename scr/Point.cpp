#include "Point.h"
#include <iostream>


Point::Point() : dimensionality(0)
				, coordinates{}
{}

Point::Point(int dimensionality) {
	this->dimensionality = dimensionality;
	coordinates=new double[dimensionality]();
}

Point::Point(int dimensionality, double* coordinates) : Point(dimensionality) {
	this->coordinates = coordinates;
}

double* Point::Coordinates() const { return coordinates; }
void Point::Coordinates(double* coord) { coordinates = coord; }
int Point::Dimensionality() const { return dimensionality; }

void Point::rand_coordinates() {
	for (int i = 0; i < dimensionality; i++) {
		coordinates[i] = pow(-1, rand() % 2) * ((float)rand()/(float)rand());
	}
}

double& Point::operator[] (int i) {
	if (i < dimensionality && i >= 0) {
		return coordinates[i];
	}

}

Point Point::operator+ (Point p) {
	Point p1(dimensionality);
	if (dimensionality == p.dimensionality) {
		for (int i = 0; i < dimensionality; i++) {
			p1[i] = coordinates[i] + p[i];
		}
		return p1;
	}
	else return p1;
}
Point Point::operator- (Point p) {
	Point p1(dimensionality);
	if (dimensionality == p.Dimensionality()) {
		for (int i = 0; i < dimensionality; i++) {
			p1[i] = coordinates[i] - p[i];
		}
		return p1;
	}
	else return p1;
}
Point Point::operator* (double a) {
	Point p1(dimensionality);
	for (int i = 0; i < dimensionality; i++) {
		p1[i] = coordinates[i] * a;
	}
	return p1;

}
Point Point::operator/ (double a) {
	Point p1(dimensionality);
	for (int i = 0; i < dimensionality; i++) {
		p1[i] = coordinates[i] / a;
	}
	return p1;
}

Point operator* (double a, Point p) {
	Point p1(p.Dimensionality());
	for (int i = 0; i < p.Dimensionality(); i++) {
		p1[i] = p[i] * a;
	}
	return p1;
}

