#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>
#include <stdio.h>
#include <iostream>

class Vector3
{
protected:
	double x,y,z;

public:
	Vector3();
	Vector3(double x, double y, double z);
	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	void negate();
	void scale(double s);
	double Vector3::get(int i);
	double dot(const Vector3&, const Vector3&);
	static Vector3 cross(const Vector3&, const Vector3&);
	double length();
	void normalize();
	void print(std::string);
};

#endif