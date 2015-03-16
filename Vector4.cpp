#include <string>
#include "Vector4.h"

using namespace std;

Vector4::Vector4(){
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(double xx, double yy, double zz, double ww){
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}

Vector4 Vector4::operator+(const Vector4& vec){
	//check for fourth component && arrays instead of vars
	double tempx, tempy, tempz, tempw;
	if (this != &vec){
		tempx = x + vec.x;
		tempy = y + vec.y;
		tempz = z + vec.z;
		tempw = w + vec.w;
	}
	Vector4 *ret = new Vector4(tempx, tempy, tempz, tempw);
	return *ret;
}

Vector4 Vector4::operator-(const Vector4& vec){
	double tempx, tempy, tempz, tempw;
	if (this != &vec){
		tempx = x - vec.x;
		tempy = y - vec.y;
		tempz = z - vec.z;
		tempw = w - vec.w;
	}
	Vector4 *ret = new Vector4(tempx, tempy, tempz, tempw);
	return *ret;
}

double Vector4::get(int i) const {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	if (i == 3) return w;
	else return NULL;
}

void Vector4::set(double xx, double yy, double zz, double ww){
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}

void Vector4::dehomogenize(){
	if (w == 0){
		printf("Fourth component is zero, cannot dehomogenize...\n exiting...\n");
		exit(1);
	}
	x = x / w;
	y = y / w;
	z = z / w;
	w = 1;
}

void Vector4::print(string comment){
	cout << comment << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}