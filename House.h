#pragma once
#include <GL/glut.h>
class House
{
protected:
	int nVerts = 42;    // your vertex array needs to have this many entries
public:
	House();
	~House();

	static void draw();
};

