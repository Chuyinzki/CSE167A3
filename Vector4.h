#pragma once
#include <iostream>

using namespace std;

class Vector4
{
protected:
	double x, y, z, w;

public:
	Vector4();
	Vector4(double x, double y, double z, double w);
	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
	double get(int) const;
	void set(double, double, double, double);
	void dehomogenize();
	void print(string comment);
};

