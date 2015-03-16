#include "Vector3.h"

Vector3::Vector3(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3::Vector3(double x, double y, double z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;

}

Vector3 Vector3::operator+(const Vector3& vec){
	double tempx, tempy, tempz;
	if (this != &vec){
		tempx = x + vec.x;
		tempy = y + vec.y;
		tempz = z + vec.z;
	}
	Vector3 ret = Vector3(tempx, tempy, tempz);
	return ret;
}

Vector3 Vector3::operator-(const Vector3& vec){
	double tempx, tempy, tempz;
	if (this != &vec){
		tempx = x - vec.x;
		tempy = y - vec.y;
		tempz = z - vec.z;
	}
	Vector3 ret = Vector3(tempx, tempy, tempz);
	return ret;
}

double Vector3::get(int i){
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	else return NULL;
}

void Vector3::negate(){
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::scale(double s){
	x = s*x;
	y = s*y;
	z = s*z;
}

double Vector3::dot(const Vector3& a, const Vector3& b){
	//switch x y z to an array of doubles
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b){
	double newX = (a.y*b.z) - (a.z*b.y);
	double newY = (a.z*b.x) - (a.x*b.z);
	double newZ = (a.x*b.y) - (a.y*b.x);
	return Vector3(newX, newY, newZ); //potentially have to change
}

double Vector3::length(){
	return sqrt((x*x) + (y*y) + (z*z));
}

void Vector3::normalize(){
	double len = Vector3::length();
	if (len != 0){
		x = x / len;
		y = y / len;
		z = z / len;
	}
}


void Vector3::print(std::string comment){
	std::cout << comment << "x = " << x << ", y = " << y <<
		", z = "<< z << std::endl;
}