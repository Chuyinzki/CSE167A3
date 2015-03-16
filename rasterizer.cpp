#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <array>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Camera.h"
#include "Matrix4.h"
#include "FileObj.h"
#include "Vector4.h"

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static double* zBuffer = new double[window_width * window_height];

int type = 0;
int shading = 0;
int zBuff = 0;
int pScale = 0;
double minZ = 1;
double maxZ = 0;

Camera cam;
Matrix4 P;
Matrix4 D;
FileObj *curObj;



using namespace std;

namespace Globals
{
	FileObj objB("C:\\Users\\Chuyinzkiz\\Documents\\UCSD 2014\\CSE 167\\Project3_Jesus Villegas\\bunny.xyz");
	Matrix4 originalBunnyMatrix = objB.getMatrix();
	FileObj objD("C:\\Users\\Chuyinzkiz\\Documents\\UCSD 2014\\CSE 167\\Project3_Jesus Villegas\\dragon.xyz");
	Matrix4 originalDragonMatrix = objD.getMatrix();
};

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

Color lightColor = { 0.5, 1.0, 0.5 };
double brightness = 50.0;
Vector3 pointLight(-15,15,15);
Color objColor = { 1.0, 1.0, 1.0 };
int pointSize;

double rounded(double g)
{
	return floor(g);
}

void loadData()
{
	// point cloud parser goes here
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
		zBuffer[i] = 1;
	}

}


// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b, int pSize){
	int offset = y*window_width * 3 + x * 3;

	for (int i = 0; i < pSize; i++){
		for (int j = 0; j < pSize; j++){

			offset = (y + i)*window_width * 3 + (x+j) * 3;

			if (offset >= 0 && offset < window_width * window_height * 3) pixels[offset] = r;
			if (offset >= 0 && offset < (window_width * window_height * 3) + 1) pixels[offset + 1] = g;
			if (offset >= 0 && offset < (window_width * window_height * 3) + 2) pixels[offset + 2] = b;
		}
	}
}

void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	double x;
	double y;
	double z;
	double w;
	Vector3 L;
	Vector4 nTemp;
	double d;
	double cf;
	int inty;
	int into;
	Color final;
	int draw = 0;
	double yRound = 0;
	double xRound = 0;

	Vector4 p(0, 1, 2, 3);
	Vector4 ps(0,1,2,3);
	int vecSize = curObj->getVecSize();

	for (int i = 0; i < vecSize; i += 3){
		ps.set(curObj->getVec(i), curObj->getVec(i+1), curObj->getVec(i+2), 1.0);
		nTemp.set(curObj->getNorms(i), curObj->getNorms(i + 1), curObj->getNorms(i + 2), 1.0);

		p = curObj->getMatrix() * ps;
		nTemp = curObj->getMatrix()*nTemp;

		if (shading){
			Vector3 pr(p.get(0),p.get(1),p.get(2));
			Vector3 N(nTemp.get(0), nTemp.get(1), nTemp.get(2));
			L = pointLight - pr;
			d = L.length();

			N.normalize();

			cf = ((N.dot(N, L)*brightness) / (d*d * M_PI));

			final.r = (lightColor.r * objColor.r)*cf;
			final.g = (lightColor.g * objColor.g)*cf;
			final.b = (lightColor.b * objColor.b)*cf;


		}

		p = cam.getMatrix()*p;

		p = P * p;

		p.dehomogenize();


		x = p.get(0);
		y = p.get(1);
		z = p.get(2);



		if (x < 1.0 && x > -1.0 && y < 1.0 && y > -1.0 && z < 1.0 && z > 0.0){
			p = D*p;

			if (minZ > z) minZ = z;
			if (maxZ < z) maxZ = z;

			x = p.get(0);
			y = p.get(1);
			z = p.get(2);


			if (pScale){
				//cout << (maxZ + minZ) / 2 << endl;
				//while (1);
				if (z < (maxZ + minZ) / 2) pointSize = 3;
				else pointSize = 2;
				//pointSize = 5;
				
			}
			else{
				pointSize = 1;
			}

			if (zBuff){
				yRound = rounded(y);
				xRound = rounded(x);
				inty = (int)yRound * (int)window_width + (int)xRound;

				if (inty > 0 && inty < window_height*window_width && zBuffer[inty] > z){
						zBuffer[inty] = z;
					draw = 1;
				}
			}

			else{
				draw = 1;
			}

			if (shading && draw){
				drawPoint(x, y, final.r, final.g, final.b, pointSize);
			}
			else if (draw){
				drawPoint(x, y, objColor.r, objColor.g, objColor.b, pointSize);
			}
		}
		draw = 0;
		
	}
}

void displayCallback()
{
	clearBuffer();
	//cout << "beginning Rasterize\n" << endl;
	rasterize();
	//cout << "Rasterize has ended\n" << endl;

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
	glutSwapBuffers();
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	delete[] zBuffer;
	pixels = new float[window_width * window_height * 3];
	zBuffer = new double[window_width*window_height];
	P.adjustProjection(60.0, (double)window_width / (double) window_height, 1.0, 1000.0);
	D.viewPortToWindowSize(0, window_width, 0, window_height);
	displayCallback();

}

void keyboardCallback(unsigned char key, int, int)
{
	//Esc key
	if (key == 27) exit(0);

	//1 key
	if (key == 49) {
		shading = 0;
		cout << "Shading OFF!" << endl;
		displayCallback();
	}

	//2 key
	if (key == 50) {
		shading = 1;
		cout << "Shading ON!" << endl;
		displayCallback();
	}

	//3 key
	if (key == 51) {
		if (zBuff){
			zBuff = 0;
			cout << "Z-Buffer OFF!" << endl;
		}
		else{
			zBuff = 1;
			cout << "Z-Buffer ON!" << endl;
		}
		displayCallback();
	}

	//4 key
	if (key == 52){
		if (pScale){
			pScale = 0;
			cout << "Point Sizing OFF!" << endl;
		}
		else{
			pScale = 1;
			cout << "Point Sizing ON!" << endl;
		}
		displayCallback();
	}

	//r for reset
	if (key == 'r'){
		switch (type){
		case 0:{
				   //object Bunny
				   Globals::objB.getMatrix() = Globals::originalBunnyMatrix;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   Globals::objD.getMatrix() = Globals::originalDragonMatrix;
				   displayCallback();
				   break;
		}
		}
	}

	//y key
	if (key == 'y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, -3, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, -3, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}

	}

	//Y key
	if (key == 'Y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 3, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 3, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}
	}

	//x key
	if (key == 'x'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(-3, 0, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(-3, 0, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}
	}

	//X key
	if (key == 'X'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(3, 0, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(3, 0, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}

	}

	//z key
	if (key == 'z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, 3);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, 3);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}

	}

	//Z key
	if (key == 'Z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, -3);
				   Globals::objB.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, -3);
				   Globals::objD.getMatrix() = rotate*temp;
				   displayCallback();
				   break;
		}
		}
	}

	//s key
	if (key == 's'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(1.1, 1.1, 1.1);
				   Globals::objB.getMatrix() = temp*scale;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(1.1, 1.1, 1.1);
				   Globals::objD.getMatrix() = temp*scale;
				   displayCallback();
				   break;
		}
		}
	}

	//S key
	if (key == 'S'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(0.9, 0.9, 0.9);
				   Globals::objB.getMatrix() = temp*scale;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(0.9, 0.9, 0.9);
				   Globals::objD.getMatrix() = temp*scale;
				   displayCallback();
				   break;
		}
		}
	}

	//o key
	if (key == 'O'){

		Matrix4 temp, orbit;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(-10.0);
				   Globals::objB.getMatrix() = orbit*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(-10.0);
				   Globals::objD.getMatrix() = orbit*temp;
				   displayCallback();
				   break;
		}
		}
	}

	//o key
	if (key == 'o'){
		Matrix4 temp, orbit;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(10.0);
				   Globals::objB.getMatrix() = orbit*temp;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(10.0);
				   Globals::objD.getMatrix() = orbit*temp;
				   displayCallback();
				   break;
		}
		}
	}

	//h key
	if (key == 'h'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}

	//H key
	if (key == 'H'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}

	//j key
	if (key == 'j'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}

	//J key
	if (key == 'J'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}

	//k key
	if (key == 'k'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}

	//K key
	if (key == 'K'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}

		case 1:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   displayCallback();
				   break;
		}
		}
	}
}


void keyboardCallbackSpecial(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_F1:{
						 type = 0;
						 printf("BUNNYYYYY!!!!!\n");
						 curObj = &Globals::objB;
						 displayCallback();
						 break;
	}

	case GLUT_KEY_F2:{
						 type = 1;
						 printf("DRAGOOOOON!!!!!\n");
						 curObj = &Globals::objD;
						 displayCallback();
						 break;
	}
	}
}




int main(int argc, char** argv) {
	curObj = &Globals::objB;
	cam = Camera(Vector3(0,0,50), Vector3(0,0,0), Vector3(0,1,0));
	pointLight = Vector3();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer de Jesus Villegas");

	//loadData();

	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(keyboardCallbackSpecial);

	glutMainLoop();
	return 0;
}