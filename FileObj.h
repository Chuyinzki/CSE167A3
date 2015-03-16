#pragma once

#include <cstdio>
#include <stdio.h>
#include <vector>
#include "Vector3.h"
#include <GL/glut.h>
#include "Matrix4.h"

class FileObj
{
protected:

	Matrix4 model2world;
	std::vector <float> vecs;
	std::vector <float> norms;

public:
	FileObj(char *);
	~FileObj();
	void parse(FILE * stream);
	void draw();
	Matrix4& getMatrix();
	void findMax();
	float getVec(int);
	float getNorms(int);
	int getVecSize();


	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float adjustX, adjustY, adjustZ;

};

