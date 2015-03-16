#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
}

Matrix4::Matrix4(double p[])
{
	//COLUMN MAJOR!!

	int g = 0;

	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			m[j][i] = p[g];
			g++;
		}
	}
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m2){
	double temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8,
		temp9, temp10, temp11, temp12, temp13, temp14, temp15;

	temp0 = (m[0][0] * m2.m[0][0]) + (m[0][1] * m2.m[1][0]) + (m[0][2] * m2.m[2][0]) + (m[0][3] * m2.m[3][0]);
	temp1 = (m[0][0] * m2.m[0][1]) + (m[0][1] * m2.m[1][1]) + (m[0][2] * m2.m[2][1]) + (m[0][3] * m2.m[3][1]);
	temp2 = (m[0][0] * m2.m[0][2]) + (m[0][1] * m2.m[1][2]) + (m[0][2] * m2.m[2][2]) + (m[0][3] * m2.m[3][2]);
	temp3 = (m[0][0] * m2.m[0][3]) + (m[0][1] * m2.m[1][3]) + (m[0][2] * m2.m[2][3]) + (m[0][3] * m2.m[3][3]);

	temp4 = (m[1][0] * m2.m[0][0]) + (m[1][1] * m2.m[1][0]) + (m[1][2] * m2.m[2][0]) + (m[1][3] * m2.m[3][0]);
	temp5 = (m[1][0] * m2.m[0][1]) + (m[1][1] * m2.m[1][1]) + (m[1][2] * m2.m[2][1]) + (m[1][3] * m2.m[3][1]);
	temp6 = (m[1][0] * m2.m[0][2]) + (m[1][1] * m2.m[1][2]) + (m[1][2] * m2.m[2][2]) + (m[1][3] * m2.m[3][2]);
	temp7 = (m[1][0] * m2.m[0][3]) + (m[1][1] * m2.m[1][3]) + (m[1][2] * m2.m[2][3]) + (m[1][3] * m2.m[3][3]);

	temp8 = (m[2][0] * m2.m[0][0]) + (m[2][1] * m2.m[1][0]) + (m[2][2] * m2.m[2][0]) + (m[2][3] * m2.m[3][0]);
	temp9 = (m[2][0] * m2.m[0][1]) + (m[2][1] * m2.m[1][1]) + (m[2][2] * m2.m[2][1]) + (m[2][3] * m2.m[3][1]);
	temp10 = (m[2][0] * m2.m[0][2]) + (m[2][1] * m2.m[1][2]) + (m[2][2] * m2.m[2][2]) + (m[2][3] * m2.m[3][2]);
	temp11 = (m[2][0] * m2.m[0][3]) + (m[2][1] * m2.m[1][3]) + (m[2][2] * m2.m[2][3]) + (m[2][3] * m2.m[3][3]);

	temp12 = (m[3][0] * m2.m[0][0]) + (m[3][1] * m2.m[1][0]) + (m[3][2] * m2.m[2][0]) + (m[3][3] * m2.m[3][0]);
	temp13 = (m[3][0] * m2.m[0][1]) + (m[3][1] * m2.m[1][1]) + (m[3][2] * m2.m[2][1]) + (m[3][3] * m2.m[3][1]);
	temp14 = (m[3][0] * m2.m[0][2]) + (m[3][1] * m2.m[1][2]) + (m[3][2] * m2.m[2][2]) + (m[3][3] * m2.m[3][2]);
	temp15 = (m[3][0] * m2.m[0][3]) + (m[3][1] * m2.m[1][3]) + (m[3][2] * m2.m[2][3]) + (m[3][3] * m2.m[3][3]);

	Matrix4 ret = Matrix4();
	ret.m[0][0] = temp0;
	ret.m[0][1] = temp1;
	ret.m[0][2] = temp2;
	ret.m[0][3] = temp3;

	ret.m[1][0] = temp4;
	ret.m[1][1] = temp5;
	ret.m[1][2] = temp6;
	ret.m[1][3] = temp7;

	ret.m[2][0] = temp8;
	ret.m[2][1] = temp9;
	ret.m[2][2] = temp10;
	ret.m[2][3] = temp11;

	ret.m[3][0] = temp12;
	ret.m[3][1] = temp13;
	ret.m[3][2] = temp14;
	ret.m[3][3] = temp15;

	return ret;
}

Vector4 Matrix4::operator*(const Vector4& vec){
	double temp0, temp1, temp2, temp3;
	double xvec, yvec, zvec, wvec;
	xvec = vec.get(0);
	yvec = vec.get(1);
	zvec = vec.get(2);
	wvec = vec.get(3);

	temp0 = (xvec * m[0][0]) + (yvec *m[0][1]) +
		(zvec * m[0][2]) + (wvec * m[0][3]);
	temp1 = (xvec * m[1][0]) + (yvec * m[1][1]) +
		(zvec * m[1][2]) + (wvec * m[1][3]);
	temp2 = (xvec * m[2][0]) + (yvec * m[2][1]) +
		(zvec * m[2][2]) + (wvec * m[2][3]);
	temp3 = (xvec * m[3][0]) + (yvec * m[3][1]) +
		(zvec * m[3][2]) + (wvec * m[3][3]);

	Vector4 ret(temp0, temp1, temp2, temp3);
	return ret;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

double Matrix4::get(int i){
	if (i == 0) return m[0][0];
	if (i == 1) return m[0][1];
	if (i == 2) return m[0][2];
	if (i == 3) return m[0][3];
	if (i == 4) return m[1][0];
	if (i == 5) return m[1][1];
	if (i == 6) return m[1][2];
	if (i == 7) return m[1][3];
	if (i == 8) return m[2][0];
	if (i == 9) return m[2][1];
	if (i == 10) return m[2][2];
	if (i == 11) return m[2][3];
	if (i == 12) return m[3][0];
	if (i == 13) return m[3][1];
	if (i == 14) return m[3][2];
	if (i == 15) return m[3][3];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

void Matrix4::makeRotateX(double angle){
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[1][1] = cos(angle);
	m[1][2] = sin(angle);
	m[2][1] = -sin(angle);
	m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeRotateZ(double angle){
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[1][0] = sin(angle);
	m[0][1] = -sin(angle);
	m[1][1] = cos(angle);
}

void Matrix4::makeRotate(double angle, Vector3& axis){
	identity();
	axis.normalize();
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians

	double x = axis.get(0);
	double y = axis.get(1);
	double z = axis.get(2);

	m[0][0] = cos(angle) + x*(1 - cos(angle));
	m[0][1] = x*y*(1 - cos(angle)) - z*sin(angle);
	m[0][2] = x*z*(1 - cos(angle)) + y*sin(angle);

	m[1][0] = y*x*(1 - cos(angle)) + z*sin(angle);
	m[1][1] = cos(angle) + y*(1 - cos(angle));
	m[1][2] = y*z*(1 - cos(angle)) - x*sin(angle);

	m[2][0] = z*x*(1 - cos(angle)) - y*sin(angle);
	m[2][1] = z*y*(1 - cos(angle)) + x*sin(angle);
	m[2][2] = cos(angle) + z*(1 - cos(angle));

}

void Matrix4::makeScale(double sx, double sy, double sz){
	identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
}

void Matrix4::makeTranslate(double tx, double ty, double tz){
	identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;

}

void Matrix4::print(string comment){
	cout << comment << endl;
	printf("%f %f %f %f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
	printf("%f %f %f %f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
	printf("%f %f %f %f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
	printf("%f %f %f %f\n\n", m[3][0], m[3][1], m[3][2], m[3][3]);

}

void Matrix4::viewPortToWindowSize(double x0, double x1, double y0, double y1){
	identity();
	m[0][0] = (x1 - x0) / 2;
	m[1][1] = (y1 - y0) / 2;
	m[2][2] = 1.0 / 2.0;
	m[3][3] = 1.0;

	m[0][3] = (x0 + x1) / 2;
	m[1][3] = (y0 + y1) / 2;
	m[2][3] = 1.0 / 2.0;
}

void Matrix4::adjustProjection(double FOV, double aspect, double near, double far){
	identity();
	FOV = FOV / 180.0 * M_PI;  // convert from degrees to radians

	m[0][0] = (1.0) / (aspect * tan(FOV/2));
	m[1][1] = (1.0) / tan(FOV / 2);
	m[2][2] = (near + far) / (near - far);
	m[3][3] = 0.0;

	m[3][2] = -1.0;
	m[2][3] = (2*near*far) / (near - far);
}