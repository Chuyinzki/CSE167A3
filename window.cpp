#include <iostream>
#include "math.h"

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "House.h"
#include "Camera.h"
#include "FileObj.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
double spinner = 1.0;
double colour[3] = { 1.0, 1.0, 0 };
int type = 0;
double velocity1;
double velocity2;
Camera camera = Camera();
House house = House();

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	switch (type){
	case 0:{
			Globals::cube.spin(spinner);
			break;
		}
	case 1:{
			   translateBall();
			   break;
	}
	case 2:{
			   //House doesn't need an idle callback
			   break;
	}
	case 3:{
			   //Bunny doesn't need an idle callback
			   break;
	}
	case 4:{
			   //Dragon doesn't need an idle callback
			   break;
	}
	}

	displayCallback();         // call display routine to show the cube
}

void Window::translateBall(){
	Matrix4 temp = Globals::cube.getMatrix();
	Matrix4 trans = Matrix4();
	trans.makeTranslate(velocity1, velocity2, 0);
	Globals::cube.getMatrix() = trans*temp;

	int x, y;
	x = temp.get(3);
	y = temp.get(7);

	if (x > 10 && velocity1 > 0) velocity1 *= -1;
	if (y > 10 && velocity2 > 0) velocity2 *= -1;
	if (x < -10 && velocity1 <= 0) velocity1 *= -1;
	if (y < -10 && velocity2 <= 0) velocity2 *= -1;
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  glLoadMatrixd(camera.getGLMatrix());

  switch (type){
  case 0:{
	  // Tell OpenGL what ModelView matrix to use:
	  Matrix4 glmatrix;
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());

	  // Draw all six faces of the cube:
	  glBegin(GL_QUADS);
	  glColor3f(colour[0], colour[1], colour[2]);		// This makes the cube green; the parameters are for red, green and blue. 
	  // To change the color of the other faces you will need to repeat this call before each face is drawn.
	  // Draw front face:
	  glNormal3f(0.0, 0.0, 1.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw left side:
	  glNormal3f(-1.0, 0.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw right side:
	  glNormal3f(1.0, 0.0, 0.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);

	  // Draw back face:
	  glNormal3f(0.0, 0.0, -1.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);

	  // Draw top side:
	  glNormal3f(0.0, 1.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(-5.0, 5.0, -5.0);

	  // Draw bottom side:
	  glNormal3f(0.0, -1.0, 0.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);
	  glEnd();
	  break;
  }
  case 1:{
			 // Tell OpenGL what ModelView matrix to use:
			 Matrix4 glmatrix;
			 glmatrix = Globals::cube.getMatrix();
			 glmatrix.transpose();
			 glLoadMatrixd(glmatrix.getPointer());

			 glutSolidSphere(1, 50, 50);
			 break; }
  case 2:{
			 House::draw();
			 break; 
	}
  case 3:{	
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_POINT_SMOOTH);
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

			// Tell OpenGL what ModelView matrix to use:
			Matrix4 glmatrix;
			glmatrix = Globals::objB.getMatrix();
			glmatrix.transpose();
			glLoadMatrixd(glmatrix.getPointer());
			Globals::objB.draw();
			break;
  }
  case 4:{
			 glEnable(GL_BLEND);
			 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			 glEnable(GL_POINT_SMOOTH);
			 glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

			 // Tell OpenGL what ModelView matrix to use:
			 Matrix4 glmatrix;
			 glmatrix = Globals::objD.getMatrix();
			 glmatrix.transpose();
			 glLoadMatrixd(glmatrix.getPointer());
			 Globals::objD.draw();
			 break;
  }
  }
  
  glFlush();  
  glutSwapBuffers();
}

void Window::keyboardCallback(unsigned char key, int x, int y) {
	//std::cout << "key " << key << std::endl;
	//Esc key
	if (key == 27) exit(0);

	//y key
	if (key == 'y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, -3, 0);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, -3, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, -3, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}

	}

	//Y key
	if (key == 'Y'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 3, 0);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 3, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 3, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}
	}

	//x key
	if (key == 'x'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(-3, 0, 0);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(-3, 0, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(-3, 0, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}
	}

	//X key
	if (key == 'X'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(3, 0, 0);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(3, 0, 0);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(3, 0, 0);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}

	}

	//z key
	if (key == 'z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, 3);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, 3);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, 3);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}

	}

	//Z key
	if (key == 'Z'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, -3);
				   Globals::cube.getMatrix() = rotate*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, -3);
				   Globals::objB.getMatrix() = rotate*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeTranslate(0, 0, -3);
				   Globals::objD.getMatrix() = rotate*temp;
				   break;
		}
		}
	}

	//r key
	if (key == 'r'){
		Globals::cube.getMatrix().identity();
		colour[0] = 0;
		colour[1] = 1.0;
		colour[2] = 0;
	}

	//s key
	if (key == 's'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(1.1, 1.1, 1.1);
				   Globals::cube.getMatrix() = temp*scale;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(1.1, 1.1, 1.1);
				   Globals::objB.getMatrix() = temp*scale;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(1.1, 1.1, 1.1);
				   Globals::objD.getMatrix() = temp*scale;
				   break;
		}
		}
	}

	//S key
	if (key == 'S'){
		Matrix4 temp, scale;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(0.9, 0.9, 0.9);
				   Globals::cube.getMatrix() = temp*scale;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(0.9, 0.9, 0.9);
				   Globals::objB.getMatrix() = temp*scale;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   scale = Matrix4();
				   scale.makeScale(0.9, 0.9, 0.9);
				   Globals::objD.getMatrix() = temp*scale;
				   break;
		}
		}
	}

	//o key
	if (key == 'O'){

		Matrix4 temp, orbit;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(-10.0);
				   Globals::cube.getMatrix() = orbit*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(-10.0);
				   Globals::objB.getMatrix() = orbit*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(-10.0);
				   Globals::objD.getMatrix() = orbit*temp;
				   break;
		}
		}
	}

	//o key
	if (key == 'o'){
		Matrix4 temp, orbit;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(10.0);
				   Globals::cube.getMatrix() = orbit*temp;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(10.0);
				   Globals::objB.getMatrix() = orbit*temp;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   orbit = Matrix4();
				   orbit.makeRotateZ(10.0);
				   Globals::objD.getMatrix() = orbit*temp;
				   break;
		}
		}
	}

	//h key
	if (key == 'h'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//H key
	if (key == 'H'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(-10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateX(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//j key
	if (key == 'j'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//J key
	if (key == 'J'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(-10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateY(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//k key
	if (key == 'k'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//K key
	if (key == 'K'){
		Matrix4 temp, rotate;

		switch (type){
		case 0:{
				   //cubes and sphere
				   temp = Globals::cube.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(-10.0);
				   Globals::cube.getMatrix() = temp*rotate;
				   break;
		}

		case 3:{
				   //object Bunny
				   temp = Globals::objB.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(-10.0);
				   Globals::objB.getMatrix() = temp*rotate;
				   break;
		}

		case 4:{
				   //object Dragon
				   temp = Globals::objD.getMatrix();
				   rotate = Matrix4();
				   rotate.makeRotateZ(-10.0);
				   Globals::objD.getMatrix() = temp*rotate;
				   break;
		}
		}
	}

	//t key
	if (key == 't') spinner *= -1;

	//print Vector3 position
	/*Matrix4 temp = Globals::objB.getMatrix();
	Vector3(temp.get(3), temp.get(7), temp.get(11)).print("Position of Vector3 of Bunny: ");*/

	if (key == 'b'){
		type = ++type % 4;

		Globals::cube.getMatrix().identity();
		colour[0] = 0;
		colour[1] = 1.0;
		colour[2] = 0;

		velocity1 = (rand() % 3000 - 1000) / 1000.0;
		velocity2 = (rand() % 3000 - 1000) / 1000.0;
	}

}

void Window::keyboardCallbackSpecial(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_F1:{
						 //Cube
						 type = 0;
						 break;
	}

	case GLUT_KEY_F2:{
						 //House 1
						 type = 2;
						 camera = Camera(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
						 glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
						 glLoadMatrixd(camera.getGLMatrix());
						 break;
	}

	case GLUT_KEY_F3:{
						 //House 2
						 type = 2;
						 camera = Camera(Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5));
						 glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
						 glLoadMatrixd(camera.getGLMatrix());
						 break;
	}
	case GLUT_KEY_F4:{
						 //Bunny
						 type = 3;
						 printf("Max and Min vertices for Bunny\nMinX = %f   MaxX = %f\nMinY = %f   MaxY = %f\nMinZ = %f   MaxZ = %f\n\n",
							 Globals::objB.minX, Globals::objB.maxX, Globals::objB.minY, Globals::objB.maxY, Globals::objB.minZ, Globals::objB.maxZ);
						 printf("Adjusts for Bunny = \nAdjustX = %f\nAdjustY = %f\nAdjustZ = %f\n\n",
							 Globals::objB.adjustX, Globals::objB.adjustY, Globals::objB.adjustZ);
						 break;
	}

	case GLUT_KEY_F5:{
						 //Dragon
						 type = 4;
						 printf("Max and Min vertices for Dragon\nMinX = %f   MaxX = %f\nMinY = %f   MaxY = %f\nMinZ = %f   MaxZ = %f\n\n",
							 Globals::objD.minX, Globals::objD.maxX, Globals::objD.minY, Globals::objD.maxY, Globals::objD.minZ, Globals::objD.maxZ);
						 printf("Adjusts for Dragon = \nAdjustX = %f\nAdjustY = %f\nAdjustZ = %f\n\n",
							 Globals::objD.adjustX, Globals::objD.adjustY, Globals::objD.adjustZ);
						 break;
	}
	}
}