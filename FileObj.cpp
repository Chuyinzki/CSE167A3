#include "FileObj.h"


FileObj::FileObj(char* fileName)
{
	FILE *file = fopen(fileName, "r");
	parse(file);

	model2world.identity();

	Matrix4 temp;
	temp.makeTranslate(-adjustX, -adjustY, -adjustZ);
	//temp.makeTranslate(5, -5, -5);
	temp.print("Translation Matrix:\n");

	model2world = model2world * temp;
	float angle1 = 30 / 180.0 * M_PI;
	float angle2 = 180 / 180.0 * M_PI;
	float final3 = angle1 / angle2;

	float scale = ((40 * tan(final3*3.14))/(maxX - minX))*2;

	temp.makeScale(scale, scale, scale);
	temp.print("Scaling Matrix:\n");

	model2world = temp * model2world;
}


FileObj::~FileObj()
{
}

void FileObj::draw(){

	Matrix4 glMatrix;
	glMatrix = model2world;
	glMatrix.transpose();
	glLoadMatrixd(glMatrix.getPointer());

	//model2world.print("");

	glPointSize(1);

	glBegin(GL_POINTS);
	for (int i = 0; i < vecs.size(); i += 3)
	{
		glNormal3d(norms[i], norms[i + 1], norms[i + 2]);
		glVertex3d(vecs[i], vecs[i + 1], vecs[i + 2]);
	}
	glEnd();

}

void FileObj::parse(FILE * pFile){

	float x, y, z, nx, ny, nz;
	Vector3 temp;
	while (6 == fscanf(pFile,"%f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz))
	{
		vecs.push_back(x);
		vecs.push_back(y);
		vecs.push_back(z);

		temp = Vector3(nx,ny,nz);
		temp.normalize();

		norms.push_back(temp.get(0));
		norms.push_back(temp.get(1));
		norms.push_back(temp.get(2));
	}
	fclose(pFile);
	findMax();

	adjustX = (maxX + minX) / 2.0;
	adjustY = (maxY + minY) / 2.0;
	adjustZ = (maxZ + minZ) / 2.0;
}

float FileObj::getVec(int i){
	return vecs[i];
}

float FileObj::getNorms(int i){
	return norms[i];
}

int FileObj::getVecSize(){
	return vecs.size();
}

Matrix4& FileObj::getMatrix()
{
	return model2world;
}

void FileObj::findMax(){
	for (int i = 0; i < vecs.size(); i+=3){
		if (vecs[i] > maxX) maxX = vecs[i];
		if (vecs[i] < minX) minX = vecs[i];
	}

	for (int i = 1; i < vecs.size(); i += 3){
		if (vecs[i] > maxY) maxY = vecs[i];
		if (vecs[i] < minY) minY = vecs[i];
	}

	for (int i = 2; i < vecs.size(); i += 3){
		if (vecs[i] > maxZ) maxZ = vecs[i];
		if (vecs[i] < minZ) minZ = vecs[i];
	}
}

