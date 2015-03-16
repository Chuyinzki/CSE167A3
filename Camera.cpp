#include "Camera.h"


Camera::Camera()
{
	C.identity();
}

Camera::Camera(Vector3 ee, Vector3 dd, Vector3 upup){
	e = ee;
	d = dd;
	up = upup;
	deriveC(e, d, up);
}

void Camera::deriveC(Vector3 ee, Vector3 dd, Vector3 upup){
	Vector3 zaxis = (ee - dd);
	zaxis.normalize();
	//zaxis.print("Zaxis");

	Vector3 xaxis = upup.cross(upup, zaxis);
	xaxis.normalize();
	//xaxis.print("Xaxis");

	Vector3 yaxis = upup.cross(zaxis, xaxis);
	yaxis.normalize();
	//yaxis.print("Yxis");


	cArray[0] = xaxis.get(0);
	cArray[1] = xaxis.get(1);
	cArray[2] = xaxis.get(2);
	cArray[3] = 0.0;

	cArray[4] = yaxis.get(0);
	cArray[5] = yaxis.get(1);
	cArray[6] = yaxis.get(2);
	cArray[7] = 0.0;

	cArray[8] = zaxis.get(0);
	cArray[9] = zaxis.get(1);
	cArray[10] = zaxis.get(2);
	cArray[11] = 0.0;

	cArray[12] = 0;
	cArray[13] = 0;
	cArray[14] = 0;
	cArray[15] = 1.0;

	//Matrix4 is COLUMN MAJOR!
	C = Matrix4(cArray);

	C.transpose();

	

	Matrix4 trans;
	trans.makeTranslate(-ee.get(0), -ee.get(1), -ee.get(2));


	C = C * trans;

	//C.transpose();


}

GLdouble* Camera::getGLMatrix(){

	return C.getPointer();
}

Matrix4& Camera::getMatrix(){
	return C;
}