#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846

#include <math.h>
#include <string>
#include <stdio.h>


#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    Matrix4();
	Matrix4(double p[]);
    Matrix4& operator=(const Matrix4&);
	Matrix4 operator*(const Matrix4&);
	Vector4 operator*(const Vector4&);
    double* getPointer(); 
	double get(int);
    void identity();
    void transpose();
	void makeRotateX(double);
    void makeRotateY(double); 
	void makeRotateZ(double);
	void makeRotate(double angle, Vector3& axis);
	void makeScale(double, double, double);
	void makeTranslate(double, double, double);
	void print(std::string);
	void viewPortToWindowSize(double, double, double, double);
	void adjustProjection(double, double, double, double);
};

#endif