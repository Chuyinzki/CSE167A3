#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <GL/glut.h>

class Camera
{
protected:
	Vector3 e;
	Vector3 d;
	Vector3 up;

	Matrix4 C;

	double cArray[16];
	

public:
	Camera();
	Camera(Vector3, Vector3, Vector3);
	void deriveC(Vector3, Vector3, Vector3);
	GLdouble* getGLMatrix();
	Matrix4& getMatrix();
};

