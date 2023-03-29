#pragma once

class Point
{
private:
	int dimensionality; //размерность пространства
	double* coordinates;

public:
	Point();
	Point(int dimensoinality);
	Point(int dimensionality, double* coordinates);
	double* Coordinates() const;
	void Coordinates(double* coord);
	int Dimensionality() const;
	void rand_coordinates();
	double& operator[] (int i);
	Point operator+ (Point p);
	Point operator- (Point p);
	Point operator* (double a);
	Point operator/ (double a);

};

Point operator*(double a, Point p);


