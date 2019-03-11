//
// 4x4 Matrix1 class
//

#include <memory.h>
#include <math.h>
#include <string.h>
#include "Matrix1.h"
#include "file.h"
#include "defines.h"
/**********FRAN*********/
#include "utilidades.h"
#include <stdlib.h>
#include <afxwin.h>
#include "globals.h"
/**********FRAN*********/


// =============================================================================
// static functions

static double Identity[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

// Perform a 4x4 Matrix1 multiplication  (product = a x b).
// WARNING: (product != b) assumed
static void matmul (double *product, const double *a, const double *b)
{
  int i;

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

  for (i = 0; i < 4; i++)
  {
    double ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
    P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
    P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
    P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
    P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
  }

#undef A
#undef B
#undef P
}

// Generate a 4x4 transformation Matrix1 from rotation parameters.
static void rotation_Matrix1 (double angle, double x, double y, double z, double m[] )
{
  double s, c, mag, xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

  s = sin (angle * DTOR);
  c = cos (angle * DTOR);
  mag = sqrt(x*x + y*y + z*z);

  if (mag == 0)
  {
    // generate an identity Matrix1 and return
    memcpy (m, Identity, sizeof(double[16]));
    return;
  }

  x /= mag;
  y /= mag;
  z /= mag;

  xx = x * x;
  yy = y * y;
  zz = z * z;
  xy = x * y;
  yz = y * z;
  zx = z * x;
  xs = x * s;
  ys = y * s;
  zs = z * s;
  one_c = 1.0f - c;

  m[0] = (one_c * xx) + c;
  m[4] = (one_c * xy) - zs;
  m[8] = (one_c * zx) + ys;
  m[12]= 0;

  m[1] = (one_c * xy) + zs;
  m[5] = (one_c * yy) + c;
  m[9] = (one_c * yz) - xs;
  m[13]= 0;

  m[2] = (one_c * zx) - ys;
  m[6] = (one_c * yz) + xs;
  m[10]= (one_c * zz) + c;
  m[14]= 0;

  m[3] = 0;
  m[7] = 0;
  m[11]= 0;
  m[15]= 1;
}

// =============================================================================
// Matrix1 class

Matrix1::Matrix1 ()
{
  LoadIdentity();
}

Matrix1::Matrix1 (const double* mat)
{
  memcpy (&m[0], mat, sizeof(double[16]));
}

/*Matrix1::Matrix1 (const double *mat)
{
  for (int i = 0; i < 16; i++)
    m[i] = (double)mat[i];
}
*/
// Create a Matrix1 from axis-angle and a point
Matrix1::Matrix1 (const double *rot, const double *pos)
{
	double tmp[4] = { rot[0], rot[1], rot[2], rot[3]*DTOR };
	double q[4];
	double length, cosA, sinA;
	length = sqrt(tmp[0]*tmp[0] + tmp[1]*tmp[1] + tmp[2]*tmp[2]);

	// if zero vector passed in, just return identity quaternion
	if (length < 1E-5)
	{
		q[0] = 0;
		q[1] = 0;
		q[2] = 0;
		q[3] = 1;
		return;
	}

	tmp[0] /= length;
	tmp[1] /= length;
	tmp[2] /= length;

	cosA = cos(tmp[3] / 2.0f);
	sinA = sin(tmp[3] / 2.0f);

	q[3] = cosA;
	q[0] = sinA * tmp[0];
	q[1] = sinA * tmp[1];
	q[2] = sinA * tmp[2];

	// Now calculate the Matrix1
	double s,xs,ys,zs,wx,wy,wz,xx,xy,xz,yy,yz,zz;

	s = 2.0f / (q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);

	xs = q[0] * s;   ys = q[1] * s;   zs = q[2] * s;
	wx = q[3] * xs;  wy = q[3] * ys;  wz = q[3] * zs;
	xx = q[0] * xs;  xy = q[0] * ys;  xz = q[0] * zs;
	yy = q[1] * ys;  yz = q[1] * zs;  zz = q[2] * zs;

	m[0] = 1.0f - (yy + zz);
	m[4] = xy - wz;
	m[8] = xz + wy;
	m[12]= pos[0];

	m[1] = xy + wz;
	m[5] = 1.0f - (xx + zz);
	m[9] = yz - wx;
	m[13]= pos[1];

	m[2] = xz - wy;
	m[6] = yz + wx;
	m[10]= 1.0f - (xx + yy);
	m[14]= pos[2];

	m[3] = 0.0f;
	m[7] = 0.0f;
	m[11] = 0.0f;
	m[15] = 1.0f;
}

Matrix1::~Matrix1()
{
}

// Expand from the .bin file
void Matrix1::FromPacked (const double *mat)
{

  m[0] = mat[0];
  m[1] = mat[1];
  m[2] = mat[2];
  m[3] = 0.0f;
  m[4] = mat[3];
  m[5] = mat[4];
  m[6] = mat[5];
  m[7] = 0.0f;
  m[8] = mat[6];
  m[9] = mat[7];
  m[10] = mat[8];
  m[11] = 0.0f;
  m[12] = mat[9];
  m[13] = mat[10];
  m[14] = mat[11];
  m[15] = 0.0f;
}

void Matrix1::FromFloat (const double* mat)
{
  memcpy (&m[0], mat, sizeof(double[16]));
}

void Matrix1::LoadIdentity ()
{
  memcpy (&m[0], &Identity, sizeof(double[16]));
}

void Matrix1::Multiply (Matrix1& m1, Matrix1& m2)
{
  matmul (m, m1.m, m2.m);
}

void Matrix1::Rotate (double angle, double x, double y, double z)
{
  double rm[16];


  if (angle == 0.0)
    return;

  rotation_Matrix1(angle, x, y, z, rm);
  matmul(rm, rm, m);
  memcpy (&m[0], &rm[0], sizeof(rm));

  for (int i = 0; i < 12; i++)
    if (fabs (m[i]) < .001f)
      m[i] = 0;
}

void Matrix1::RotateCenter (double angle, double x, double y, double z, double px, double py, double pz)
{
  m[12] -= px;
  m[13] -= py;
  m[14] -= pz;

  Rotate (angle, x, y, z);

  m[12] += px;
  m[13] += py;
  m[14] += pz;
}

void Matrix1::Translate (double x, double y, double z)
{

  m[12] = m[0] * x + m[4] * y + m[8]  * z + m[12];
  m[13] = m[1] * x + m[5] * y + m[9]  * z + m[13];
  m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
  m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
}

void Matrix1::SetTranslation (double x, double y, double z)
{
  m[12] = x;
  m[13] = y;
  m[14] = z;
  m[15] = 1;
}

void Matrix1::GetTranslation (double* x, double* y, double* z)
{
  *x = m[12];
  *y = m[13];
  *z = m[14];
}

void Matrix1::GetTranslation (double pos[3])
{
  pos[0] = m[12];
  pos[1] = m[13];
  pos[2] = m[14];
}

void Matrix1::SetTranslation (double pos[3])
{
  m[12] = pos[0];
  m[13] = pos[1];
  m[14] = pos[2];
  m[15] = 1;
}

void Matrix1::Create(double mx, double my, double mz, double rx, double ry, double rz)
{
	LoadIdentity();
	Translate(mx, my, mz);
	Rotate(rx, 1, 0, 0);
	Rotate(ry, 0, 1, 0);
	Rotate(rz, 0, 0, 1);
}

void Matrix1::CreateOld(double mx, double my, double mz, double rx, double ry, double rz)
{
	LoadIdentity();
	Translate(mx, my, mz);

	double rm[16];
	rotation_Matrix1(rx, 1, 0, 0, rm);
	matmul(m, m, rm);
	rotation_Matrix1(ry, 0, 1, 0, rm);
	matmul(m, m, rm);
	rotation_Matrix1(rz, 0, 0, 1, rm);
	matmul(m, m, rm);
}

// Transform a point by a 4x4 Matrix1. out = m * in
void Matrix1::TransformPoint(double out[], const double in[3])
{
	out[0] = m[0]*in[0] + m[4]*in[1] + m[8]*in[2] + m[12];
	out[1] = m[1]*in[0] + m[5]*in[1] + m[9]*in[2] + m[13];
	out[2] = m[2]*in[0] + m[6]*in[1] + m[10]*in[2] + m[14];
}

void Matrix1::TransformPoints (double p[], int n)
{
	for (int i = 0; i < n*3; i += 3)
	{
		double tmp[3] = { p[i], p[i+1], p[i+2] };
		TransformPoint (&p[i], tmp);
	}
}

void Matrix1::FromLDraw (const double *f)
{

  double trans[16] = { 1,0,0,0, 0,0,-1,0, 0,1,0,0, 0,0,0,1 };
  double t[16] = { 1,0,0,0, 0,0,1,0, 0,-1,0,0, 0,0,0,1 };

  m[0] = f[3];    m[1] = f[6];    m[2] = f[9];
  m[4] = f[4];    m[5] = f[7];    m[6] = f[10];
  m[8] = f[5];    m[9] = f[8];    m[10]= f[11];
  m[12]= f[0]/25; m[13]= f[1]/25; m[14]= f[2]/25;

  matmul (m, m, t);
  matmul (trans, trans, m);
  memcpy (&m[0], &trans[0], sizeof(m));
}

void Matrix1::ToLDraw (double *f) const
{
  double trans[16] = { 1,0,0,0, 0,0,-1,0, 0,1,0,0, 0,0,0,1 };
  double tmp[16] = { 1,0,0,0, 0,0,1,0, 0,-1,0,0, 0,0,0,1 };

  matmul(tmp, tmp, m);
  matmul (tmp, tmp, trans);

  f[0] = m[12]*25; f[1] = -m[14]*25; f[2] = m[13]*25;
  f[3] = tmp[0];   f[4] = tmp[4];    f[5] = tmp[8];
  f[6] = tmp[1];   f[7] = tmp[5];    f[8] = tmp[9];
  f[9] = tmp[2];   f[10]= tmp[6];    f[11]= tmp[10];
}

void Matrix1::FileLoad (File& file)
{
  double tmp[12];

  file.ReadLong (&tmp, 12);

  m[0] = tmp[0]; m[1] = tmp[1];  m[2] = tmp[2];  m[3] = 0.0f;
  m[4] = tmp[3]; m[5] = tmp[4];  m[6] = tmp[5];  m[7] = 0.0f;
  m[8] = tmp[6]; m[9] = tmp[7];  m[10]= tmp[8];  m[11]= 0.0f;
  m[12]= tmp[9]; m[13]= tmp[10]; m[14]= tmp[11]; m[15]= 1.0f;
}

void Matrix1::FileSave (File& file) const
{
  double tmp[12];

  tmp[0] = m[0];  tmp[1] = m[1];  tmp[2] = m[2];
  tmp[3] = m[4];  tmp[4] = m[5];  tmp[5] = m[6];
  tmp[6] = m[8];  tmp[7] = m[9];  tmp[8] = m[10];
  tmp[9] = m[12]; tmp[10]= m[13]; tmp[11]= m[14];

  file.WriteLong (&tmp, 12);
}

void Matrix1::ToEulerAngles (double *rot) const
{
  double sinPitch, cosPitch, sinRoll, cosRoll, sinYaw, cosYaw;
  double colMatrix1[4][4];

  colMatrix1[0][0] = m[0];
  colMatrix1[0][1] = m[4];
  colMatrix1[0][2] = m[8];
  colMatrix1[0][3] = m[12];

  colMatrix1[1][0] = m[1];
  colMatrix1[1][1] = m[5];
  colMatrix1[1][2] = m[9];
  colMatrix1[1][3] = m[13];

  colMatrix1[2][0] = m[2];
  colMatrix1[2][1] = m[6];
  colMatrix1[2][2] = m[10];
  colMatrix1[2][3] = m[14];

  colMatrix1[3][0] = 0.0f;
  colMatrix1[3][1] = 0.0f;
  colMatrix1[3][2] = 0.0f;
  colMatrix1[3][3] = 1.0f;

  sinPitch = -colMatrix1[2][0];
  cosPitch = sqrt(1 - sinPitch*sinPitch);

  if (fabs(cosPitch) > 0.0005)
  {
    sinRoll = colMatrix1[2][1] / cosPitch;
    cosRoll = colMatrix1[2][2] / cosPitch;
    sinYaw = colMatrix1[1][0] / cosPitch;
    cosYaw = colMatrix1[0][0] / cosPitch;
  }
  else
  {
    sinRoll = -colMatrix1[1][2];
    cosRoll = colMatrix1[1][1];
    sinYaw = 0;
    cosYaw = 1;
  }

  rot[2] = (RTOD*atan2 (sinYaw, cosYaw));
  rot[1] = (RTOD*atan2 (sinPitch, cosPitch));
  rot[0] = (RTOD*atan2 (sinRoll, cosRoll));

  if (rot[2] < 0) rot[2] += 360;
  if (rot[1] < 0) rot[1] += 360;
  if (rot[0] < 0) rot[0] += 360;
}

void Matrix1::ToAxisAngle (double *rot) const
{
  double fTrace = m[0] + m[5] + m[10];
  double inv, fCos = 0.5f * (fTrace - 1.0f);
  rot[3] = acos (fCos);  // in [0,PI]

//  if(puedo)
//	imprimirFloat(rot[3]);

  /**********FRAN*********/
  //if(rot[3]<(-1.0)) rot[3]=-1.0;
  //double fran=rot[3];
  /**********FRAN*********/

  if (rot[3] > 0.01f)
  {
    if (fabs (M_PI - rot[3]) > 0.01f)
    {
      rot[0] = m[6] - m[9];
      rot[1] = m[8] - m[2];
      rot[2] = m[1] - m[4];


	  /**********FRAN*********/
      //inv = 1.0f / (float)sqrt (rot[0]*rot[0] + rot[1]*rot[1] + rot[2]*rot[2]);
	  inv = 1.0f / sqrt (rot[0]*rot[0] + rot[1]*rot[1] + rot[2]*rot[2]);

	  rot[0] *= inv;
      rot[1] *= inv;
      rot[2] *= inv;
      /*rot[0] *= inv;
      rot[1] *= inv;
      rot[2] *= inv;*/
	  /**********FRAN*********/
    }
    else
    {
      // angle is PI
      double fHalfInverse;
      if (m[0] >= m[5])
      {
        // r00 >= r11
        if (m[0] >= m[10])
        {
          // r00 is maximum diagonal term
          rot[0] = (0.5 * sqrt (m[0] - m[5] - m[10] + 1.0));
          fHalfInverse = 0.5f / rot[0];
          rot[1] = fHalfInverse * m[4];
          rot[2] = fHalfInverse * m[8];
        }
        else
        {
          // r22 is maximum diagonal term
          rot[2] = (0.5 * sqrt (m[10] - m[0] - m[5] + 1.0));
          fHalfInverse = 0.5f / rot[2];
          rot[0] = fHalfInverse * m[8];
          rot[1] = fHalfInverse * m[9];
        }
      }
      else
      {
        // r11 > r00
        if (m[5] >= m[10])
        {
          // r11 is maximum diagonal term
          rot[1] = (0.5 * sqrt (m[5] - m[0] - m[10] + 1.0));
          fHalfInverse  = 0.5f / rot[1];
          rot[0] = fHalfInverse * m[4];
          rot[2] = fHalfInverse * m[9];
        }
        else
        {
          // r22 is maximum diagonal term
          rot[2] = (0.5 * sqrt (m[10] - m[0] - m[5] + 1.0));
          fHalfInverse = 0.5f / rot[2];
          rot[0] = fHalfInverse * m[8];
          rot[1] = fHalfInverse * m[9];
        }
      }
    }
  }
  else
  {
    // The angle is 0 and the Matrix1 is the identity.  Any axis will
    // work, so just use the x-axis.
    rot[0] = 0.0;
    rot[1] = 0.0;
    rot[2] = 1.0;
  }


  rot[3] *= RTOD;


  /**********FRAN*********/
  //fran=rot[3];
  /**********FRAN*********/

  /**********FRAN*********/
  //if(rot[3]>0 && rot[3]<0.03) rot[3]=0;
  /**********FRAN*********/
}

void Matrix1::FromEulerAngles (double roll, double pitch, double yaw)
{
	double  cosYaw, sinYaw, cosPitch, sinPitch, cosRoll, sinRoll;

	cosYaw = cos(yaw*DTOR);
	sinYaw = sin(yaw*DTOR);
	cosPitch = cos(pitch*DTOR);
	sinPitch = sin(pitch*DTOR);
	cosRoll = cos(roll*DTOR);
	sinRoll = sin(roll*DTOR);

	m[0] = cosYaw * cosPitch;
	m[4] = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll;
	m[8] = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;
	m[12] = 0.0f;

	m[1] = sinYaw * cosPitch;
	m[5] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
	m[9] = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;
	m[13] = 0.0f;

	m[2] = -sinPitch;
	m[6] = cosPitch * sinRoll;
	m[10] = cosPitch * cosRoll;
	m[14] = 0.0f;

	m[3] = 0.0f;
	m[7] = 0.0f;
	m[11] = 0.0f;
	m[15] = 1.0f;
}

// Create a rotation Matrix1 (angle is in degrees)
void Matrix1::FromAxisAngle (const double *axis, double angle)
{
  if (angle == 0.0f)
    return;
  rotation_Matrix1 (angle, axis[0], axis[1], axis[2], m);
}

bool Matrix1::FromInverse(double* src)
{
/*
// This code is better !
	double det_1, pos, neg, temp;

#define ACCUMULATE	  \
	if (temp >= 0.0)  \
		pos += temp;  \
	else			  \
		neg += temp;

#define PRECISION_LIMIT (1.0e-15)

	// Calculate the determinant of subMatrix1 A and determine if the
	// the Matrix1 is singular as limited by the double precision
	// double ing-point data representation.
	pos = neg = 0.0f;
	temp =	src[0] * src[5] * src[10];
	ACCUMULATE
	temp =	src[1] * src[6] * src[8];
	ACCUMULATE
	temp =	src[2] * src[4] * src[9];
	ACCUMULATE
	temp = -src[2] * src[5] * src[8];
	ACCUMULATE
	temp = -src[1] * src[4] * src[10];
	ACCUMULATE
	temp = -src[0] * src[6] * src[9];
	ACCUMULATE
	det_1 = pos + neg;
#define ABS(a) (a < 0) ? -a : a
	// Is the subMatrix1 A singular ?
	if ((det_1 == 0.0) || (ABS(det_1 / (pos - neg)) < PRECISION_LIMIT))
		return false;

	// Calculate inverse(A) = adj(A) / det(A)
	det_1 = 1.0f / det_1;
	inverse[0] =  (src[5]*src[10] - src[6]*src[9])*det_1;
	inverse[4] = -(src[4]*src[10] - src[6]*src[8])*det_1;
	inverse[8] =  (src[4]*src[9]  - src[5]*src[8])*det_1;
	inverse[1] = -(src[1]*src[10] - src[2]*src[9])*det_1;
	inverse[5] =  (src[0]*src[10] - src[2]*src[8])*det_1;
	inverse[9] = -(src[0]*src[9]  - src[1]*src[8])*det_1;
	inverse[2] =  (src[1]*src[6]  - src[2]*src[5])*det_1;
	inverse[6] = -(src[0]*src[6]  - src[2]*src[4])*det_1;
	inverse[10] = (src[0]*src[5]  - src[1]*src[4])*det_1;

	// Calculate -C * inverse(A)
	inverse[12] = -(src[12]*inverse[0] + src[13]*inverse[4] + src[14]*inverse[8]);
	inverse[13] = -(src[12]*inverse[1] + src[13]*inverse[5] + src[14]*inverse[9]);
	inverse[14] = -(src[12]*inverse[2] + src[13]*inverse[6] + src[14]*inverse[10]);

	// Fill in last column
	inverse[3] = inverse[7] = inverse[11] = 0.0f;
	inverse[15] = 1.0f;

	return true;
*/
	double t;
	int i, j, k, swap;
	double tmp[4][4];

	for (i = 0; i < 16; i++)
		m[i] = 0.0;
	m[0] = m[5] = m[10] = m[15] = 1.0;

	for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
		tmp[i][j] = src[i*4+j];

	for (i = 0; i < 4; i++)
	{
		// look for largest element in column.
		swap = i;
		for (j = i + 1; j < 4; j++)
			if (fabs(tmp[j][i]) > fabs(tmp[i][i]))
				swap = j;

		if (swap != i)
		{
			// swap rows.
			for (k = 0; k < 4; k++)
			{
				t = tmp[i][k];
				tmp[i][k] = tmp[swap][k];
				tmp[swap][k] = t;

				t = m[i*4+k];
				m[i*4+k] = m[swap*4+k];
				m[swap*4+k] = t;
			}
		}

		if (tmp[i][i] == 0)
		{
			// The Matrix1 is singular, which shouldn't happen.
			return false;
		}

		t = tmp[i][i];
		for (k = 0; k < 4; k++)
		{
			tmp[i][k] /= t;
			m[i*4+k] /= t;
		}
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				t = tmp[j][i];
				for (k = 0; k < 4; k++)
				{
					tmp[j][k] -= tmp[i][k]*t;
					m[j*4+k] -= m[i*4+k]*t;
				}
			}
		}
	}

	return true;
}

bool Matrix1::Invert ()
{
  double t, inverse[16];
  int i, j, k, swap;
  double tmp[4][4];

  for (i = 0; i < 16; i++)
    inverse[i] = 0.0;
  inverse[0] = inverse[5] = inverse[10] = inverse[15] = 1.0;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      tmp[i][j] = m[i*4+j];

  for (i = 0; i < 4; i++)
  {
    // look for largest element in column.
    swap = i;
    for (j = i + 1; j < 4; j++)
      if (fabs(tmp[j][i]) > fabs(tmp[i][i]))
	swap = j;

    if (swap != i)
    {
      // swap rows.
      for (k = 0; k < 4; k++)
      {
	t = tmp[i][k];
	tmp[i][k] = tmp[swap][k];
	tmp[swap][k] = t;

	t = inverse[i*4+k];
	inverse[i*4+k] = inverse[swap*4+k];
	inverse[swap*4+k] = t;
      }
    }

    if (tmp[i][i] == 0)
    {
      // The Matrix1 is singular, which shouldn't happen.
      return false;
    }

    t = tmp[i][i];
    for (k = 0; k < 4; k++)
    {
      tmp[i][k] /= t;
      inverse[i*4+k] /= t;
    }

    for (j = 0; j < 4; j++)
    {
      if (j != i)
      {
	t = tmp[j][i];
	for (k = 0; k < 4; k++)
	{
	  tmp[j][k] -= tmp[i][k]*t;
	  inverse[j*4+k] -= inverse[i*4+k]*t;
	}
      }
    }
  }

  for (i = 0; i < 16; i++)
    m[i] = inverse[i];

  return true;
}

void Matrix1::CreatePerspective (double fovy, double aspect, double nearval, double farval)
{
  double left, right, bottom, top;
  double x, y, a, b, c, d;

  LoadIdentity ();

  top = nearval * tan (fovy * M_PI / 360.0);
  bottom = -top;

  left = bottom * aspect;
  right = top * aspect;

  if ((nearval<=0.0 || farval<=0.0) || (nearval == farval) || (left == right) || (top == bottom))
    return;

  x = (2.0f*nearval) / (right-left);
  y = (2.0f*nearval) / (top-bottom);
  a = (right+left) / (right-left);
  b = (top+bottom) / (top-bottom);
  c = -(farval+nearval) / ( farval-nearval);
  d = -(2.0f*farval*nearval) / (farval-nearval);

#define M(row,col)  m[col*4+row]
  M(0,0) = x;     M(0,1) = 0.0F;  M(0,2) = a;      M(0,3) = 0.0F;
  M(1,0) = 0.0F;  M(1,1) = y;     M(1,2) = b;      M(1,3) = 0.0F;
  M(2,0) = 0.0F;  M(2,1) = 0.0F;  M(2,2) = c;      M(2,3) = d;
  M(3,0) = 0.0F;  M(3,1) = 0.0F;  M(3,2) = -1.0F;  M(3,3) = 0.0F;
#undef M
}

void Matrix1::CreateLookat (const double *eye, const double *target, const double *up)
{
  double x[3], y[3], z[3];
  double mag;

  z[0] = eye[0] - target[0];
  z[1] = eye[1] - target[1];
  z[2] = eye[2] - target[2];
  mag = sqrt (z[0]*z[0] + z[1]*z[1] + z[2]*z[2]);
  if (mag)
  {
    z[0] /= mag;
    z[1] /= mag;
    z[2] /= mag;
  }

  y[0] = up[0];
  y[1] = up[1];
  y[2] = up[2];

  // X vector = Y cross Z
  x[0] =  y[1]*z[2] - y[2]*z[1];
  x[1] = -y[0]*z[2] + y[2]*z[0];
  x[2] =  y[0]*z[1] - y[1]*z[0];

  // Recompute Y = Z cross X
  y[0] =  z[1]*x[2] - z[2]*x[1];
  y[1] = -z[0]*x[2] + z[2]*x[0];
  y[2] =  z[0]*x[1] - z[1]*x[0];

  mag = sqrt (x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
  if (mag)
  {
    x[0] /= mag;
    x[1] /= mag;
    x[2] /= mag;
  }

  mag = sqrt (y[0]*y[0] + y[1]*y[1] + y[2]*y[2]);
  if (mag)
  {
    y[0] /= mag;
    y[1] /= mag;
    y[2] /= mag;
  }

#define M(row,col)  m[col*4+row]
  M(0,0) = x[0];  M(0,1) = x[1];  M(0,2) = x[2];  M(0,3) = 0.0;
  M(1,0) = y[0];  M(1,1) = y[1];  M(1,2) = y[2];  M(1,3) = 0.0;
  M(2,0) = z[0];  M(2,1) = z[1];  M(2,2) = z[2];  M(2,3) = 0.0;
  M(3,0) = 0.0;   M(3,1) = 0.0;   M(3,2) = 0.0;   M(3,3) = 1.0;
#undef M

  // Translate Eye to Origin
  m[12] = m[0] * -eye[0] + m[4] * -eye[1] + m[8]  * -eye[2] + m[12];
  m[13] = m[1] * -eye[0] + m[5] * -eye[1] + m[9]  * -eye[2] + m[13];
  m[14] = m[2] * -eye[0] + m[6] * -eye[1] + m[10] * -eye[2] + m[14];
  m[15] = m[3] * -eye[0] + m[7] * -eye[1] + m[11] * -eye[2] + m[15];
}

/*************************FRAN********************************/

/*void Matrix1::crear(sirMat4d matriz)
{
	//Primer vector columna
	m[0]=matriz[0][0];
	m[1]=matriz[1][0];
	m[2]=matriz[2][0];
	m[3]=matriz[3][0];

	//Segundo vector columna
	m[4]=matriz[0][1];
	m[5]=matriz[1][1];
	m[6]=matriz[2][1];
	m[7]=matriz[3][1];

	//Tercer vector columna
	m[8]=matriz[0][2];
	m[9]=matriz[1][2];
	m[10]=matriz[2][2];
	m[11]=matriz[3][2];

	//Cuarto vector columna
	m[12]=matriz[0][3];
	m[13]=matriz[1][3];
	m[14]=matriz[2][3];
	m[15]=matriz[3][3];
}*/

void Matrix1::crear(double *matriz)
{
	//Primer vector columna
	m[0]=matriz[0];
	m[1]=matriz[1];
	m[2]=matriz[2];
	m[3]=matriz[3];

	//Segundo vector columna
	m[4]=matriz[4];
	m[5]=matriz[5];
	m[6]=matriz[6];
	m[7]=matriz[7];

	//Tercer vector columna
	m[8]=matriz[8];
	m[9]=matriz[9];
	m[10]=matriz[10];
	m[11]=matriz[11];

	//Cuarto vector columna
	m[12]=matriz[12];
	m[13]=matriz[13];
	m[14]=matriz[14];
	m[15]=matriz[15];
}

/*************************************************************/

void Matrix1::crearx(double *matriz)
{
	//Primer vector columna
	m[12]=matriz[0];
	m[13]=matriz[1];
	m[14]=matriz[2];
	m[15]=matriz[3];

	//Segundo vector columna
	m[4]=matriz[4];
	m[5]=matriz[5];
	m[6]=matriz[6];
	m[7]=matriz[7];

	//Tercer vector columna
	m[8]=matriz[8];
	m[9]=matriz[9];
	m[10]=matriz[10];
	m[11]=matriz[11];

	//Cuarto vector columna
	m[0]=matriz[12];
	m[1]=matriz[13];
	m[2]=matriz[14];
	m[3]=matriz[15];
}

/*************************************************************/

void Matrix1::modificarmat()
{
	//Primer vector columna
	m[12]=-1;
	m[13]=0;
	m[14]=0;
	m[15]=0;

	//Segundo vector columna
	m[4]=0;
	m[5]=-1;
	m[6]=0;
	m[7]=0;

	//Tercer vector columna
	m[8]=0;
	m[9]=0;
	m[10]=1;
	m[11]=0;

	//Cuarto vector columna
	m[0]=0.9;
	m[1]=0;
	m[2]=0;
	m[3]=1;
}