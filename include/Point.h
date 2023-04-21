#pragma once

class Point
{

public:
	Point();
	Point(int dimensoin);
	Point(int dimension, double* coordinates);
	//~Point();
	int Dimension() const;
	double operator[](int i) const;
	Point operator+ (Point p) const;
	Point operator- (Point p) const;
	Point operator* (double a) const;
	Point operator/ (double a) const;

private:
	int dimension; //размерность пространства
	double* coordinates;
};

Point operator*(double a, Point p);


