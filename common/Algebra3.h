#ifndef ALGEBRA3_H
#define ALGEBRA3_H

#include <math.h>
#include <iostream.h>
/*********FRAN***********/
#include "matrix.h"
#include "object.h"
/*********FRAN***********/
//#include <algo.h>
//#include <kernel/defs.h>
//#include <kernel/error.h>

//COSECHA PROPIA
#define EPSILON 0.01

#define THRESHOLD_SIN_THETA 0.00000001

#ifdef WIN32

#define M_PI            3.14159265358979323846
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.70710678118654752440
#define MAXFLOAT        ((float)3.40282346638528860e+38)
#define MAXPATHLEN 1024

/*********FRAN***********/
#define DELTA_FRAN 0.05//0.002
#define DELTA_NEGATIVA -0.05
/*********FRAN***********/

extern double   DRAND48();
extern double   drand48();
extern void     srand48(long seedval);
extern double   rint(double x);
#endif

class sirVector4d;
class sirMat3d;
class sirMat4d;
class sirVector3d;
class sirVector3D;

class sirVector2d
{
protected:

  double vec[2];

public:

  // Constructors

  sirVector2d();
  sirVector2d(const double x, const double y);
  sirVector2d(const double d);
  sirVector2d(const sirVector2d& v);			// copy constructor
  sirVector2d(const sirVector3d& v);			// cast v3 to v2
  sirVector2d(const sirVector3d& v, int dropAxis);	// cast v3 to v2

  // Assignment operators

  sirVector2d& operator= ( const sirVector2d& v );	// assignment of a sirVector2d
  sirVector2d& operator+= ( const sirVector2d& v );	// incrementation by a sirVector2d
  sirVector2d& operator-= ( const sirVector2d& v );	// decrementation by a sirVector2d
  sirVector2d& operator*= ( const double d );	// multiplication by a constant
  sirVector2d& operator/= ( const double d );	// division by a constant
  double& operator[] ( int i);		// indexing
  double operator[] ( int i) const ;		// indexing
  double& X() { return vec[0]; }
  double& Y() { return vec[1]; }
  const double& X() const { return vec[0]; }
  const double& Y() const { return vec[1]; }

  // special functions

  double length();			// length of a sirVector2d
  double length2();			// squared length of a sirVector2d
  sirVector2d& normalize();			// normalize a sirVector2d


  // friends

  friend sirVector2d operator- (const sirVector2d& v);			    // -v1
  friend sirVector2d operator+ (const sirVector2d& a, const sirVector2d& b);	    // v1 + v2
  friend sirVector2d operator- (const sirVector2d& a, const sirVector2d& b);	    // v1 - v2
  friend sirVector2d operator* (const sirVector2d& a, const double d);	    // v1 * 3.0
  friend sirVector2d operator* (const double d, const sirVector2d& a);	    // 3.0 * v1
  friend sirVector2d operator* (const sirMat3d& a, const sirVector2d& v);	    // M . v
  friend sirVector2d operator* (const sirVector2d& v, sirMat3d& a);	    // v . M
  friend double operator* (const sirVector2d& a, const sirVector2d& b);    // dot product
  friend sirVector2d operator/ (const sirVector2d& a, const double d);	    // v1 / 3.0
  friend sirVector3d operator^ (const sirVector2d& a, const sirVector2d& b);	    // cross product
  friend int operator== (const sirVector2d& a, const sirVector2d& b);	    // v1 == v2 ?
  friend int operator!= (const sirVector2d& a, const sirVector2d& b);	    // v1 != v2 ?
  friend ostream& operator<< (ostream& s, const sirVector2d& v);	    // output to stream
  friend istream& operator>> (istream& s, sirVector2d& v);	    // input from strm.
  friend void swap(sirVector2d& a, sirVector2d& b);                 // swap v1 & v2
//#ifndef WIN32
//  friend sirVector2d min(const sirVector2d& a, const sirVector2d& b);		    // min(v1, v2)
//  friend sirVector2d max(const sirVector2d& a, const sirVector2d& b);		    // max(v1, v2)
//#else
//  friend const sirVector2d& min(const sirVector2d& a, const sirVector2d& b);		    // min(v1, v2)
//  friend const sirVector2d& max(const sirVector2d& a, const sirVector2d& b);		    // max(v1, v2)
//#endif
  friend sirVector2d prod(const sirVector2d& a, const sirVector2d& b);		    // term by term *

  // necessary friend declarations

  friend class sirVector3d;
};


//: 3d vector
class sirVector3d
{
  friend class sirMat3d;

protected:
  double vec[3];
public:
  sirVector3d()
  {
    vec[0] = 0.0;
    vec[1] = 0.0;
    vec[2] = 0.0;
  }
  //: Default constructor
  sirVector3d(const double x, const double y, const double z)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }
  sirVector3d(const double val)
  {
    vec[0] = val;
    vec[1] = val;
    vec[2] = val;
  }
  sirVector3d(const sirVector3D& v);
  sirVector3d(const sirVector4d& v);

  double& operator[](const int i) { return vec[i]; }
  double operator[](const int i) const { return vec[i]; }

  void ini(const double x, const double y, const double z)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }
  sirVector3d& operator=(const sirVector4d& v);
  sirVector3d& operator=(const sirVector3d& v) {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    return *this;
  }
  //:

  void ini(const sirVector3d& vector) { *this = vector; }
  double& X() { return vec[0] ; }
  double& Y() { return vec[1] ; }
  double& Z() { return vec[2] ; }
  const double& X() const { return vec[0] ; }
  const double& Y() const { return vec[1] ; }
  const double& Z() const { return vec[2] ; }
  double GetX() const { return vec[0]; }
  double GetY() const { return vec[1]; }
  double GetZ() const { return vec[2]; }
  void zero() {vec[0]=0.0; vec[1]=0.0; vec[2]=0.0;}
  double sum() const { return vec[0] + vec[1] + vec[2]; }
  double getAverage() const { return sum() / 3.; }
  //double max() const { return ::max(::max(vec[0], vec[1]), vec[2]); }
  // double min() const { return ::min(::min(vec[0], vec[1]), vec[2]); }

  sirVector3d operator+(const sirVector3d& v) const {
    return sirVector3d(vec[0]+v.GetX(), vec[1]+v.GetY(), vec[2]+v.GetZ());
  }
  sirVector3d operator-(const sirVector3d& v) const {
    return sirVector3d(vec[0]-v.GetX(), vec[1]-v.GetY(), vec[2]-v.GetZ());
  }
//  sirVector3d operator/(const double k) const {
//    return sirVector3d(vec[0]/k, vec[1]/k, vec[2]/k);
//  }
  sirVector3d operator+=(const sirVector3d& v) {
    vec[0] += v.GetX();
    vec[1] += v.GetY();
    vec[2] += v.GetZ();
    return *this;
  }
  sirVector3d operator-=(const sirVector3d& v) {
    vec[0] -= v.GetX();
    vec[1] -= v.GetY();
    vec[2] -= v.GetZ();
    return *this;
  }
  sirVector3d operator*=(const sirVector3d& v) {
    vec[0] *= v.GetX();
    vec[1] *= v.GetY();
    vec[2] *= v.GetZ();
    return *this;
  }
  void Escalar(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
  }
  sirVector3d operator/=(const double k) {
    vec[0] /= k;
    vec[1] /= k;
    vec[2] /= k;
    return *this;
  }
  sirVector3d operator*=(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
    return *this;
  }
  double operator*(const sirVector3d& v) const {
    //    return (double)vec[0]*(double)v.GetX() + (double)vec[1]*(double)v.GetY() + (double)vec[2]*(double)v.GetZ();
    return vec[0]*v[0] + vec[1]*v[1] + vec[2]*v[2];
  }
  sirVector3d operator^(const sirVector3d& rhs) const {
    return sirVector3d(vec[1]*rhs.vec[2]-vec[2]*rhs.vec[1],
		       rhs.vec[0]*vec[2]-vec[0]*rhs.vec[2],
		       vec[0]*rhs.vec[1]-vec[1]*rhs.vec[0]);
  }
  int operator==(const sirVector3d& v) const {
    return vec[0]==v.GetX() && vec[1]==v.GetY() && vec[2]==v.GetZ();
  }
  int operator<(const double f) const {
    return vec[0]<f || vec[1]<f || vec[2]<f;
  }
  /* -- fdpc: yet defined (in a different way) above!!!
  friend sirVector3d operator^(const sirVector3d& lhs,
			       const sirVector3d& rhs) {
    return sirVector3d(lhs.vec[1]*rhs.vec[2]-lhs.vec[2]*rhs.vec[1],
		       rhs.vec[0]*lhs.vec[2]-lhs.vec[0]*rhs.vec[2],
		       lhs.vec[0]*rhs.vec[1]-lhs.vec[1]*rhs.vec[0]);
  }
  */
  friend sirVector3d operator*(const sirVector3d& v, double k) {
    return sirVector3d(v.GetX()*k, v.GetY()*k, v.GetZ()*k);
  }
  friend sirVector3d operator*(double k, const sirVector3d& v) {
    return sirVector3d(v.GetX()*k, v.GetY()*k, v.GetZ()*k);
  }
  /*
    -- fdpc: we need a **single** operator like
             this one. otherwise, we can end up with compiler errors like:
               more than one operator "/" matches these operands:
                 function "operator/(const sirVector3d &, double)"
                 function "sirVector3d::operator/(float) const"
                 operand types are: const sirVector3d / int
		 */
  friend sirVector3d operator/(const sirVector3d& v, double k) {
    return sirVector3d(v.GetX()/k, v.GetY()/k, v.GetZ()/k);
  }
  friend sirVector3d operator/(double k, const sirVector3d& v) {
    return sirVector3d(k/v.X(), k/v.Y(), k/v.Z());
  }
  double Modulo2() const {
    return (double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2];
  }
  double Modulo() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  }
  double norm() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  }
  double norm2() const {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
  }
  double Normalizar() {
    double d = 1./sqrt((double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2]);
    vec[0] *= d; vec[1] *= d; vec[2] *= d;
    return d;
  }
  double normalize() {
    double d = sqrt((double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2]);
    vec[0] /= d; vec[1] /= d; vec[2] /= d;
    return d;
  }
  void Rot12(const double, const double, const double, const double);
  int Visible(sirVector3d&);
  void ExtractVerts(double&, double&, int) const;


  double computeAzimuthAngle() const
  {
    /* Precondition: v must be a normalized Vector3 */
    double sinTheta, phi, aux;

    sinTheta=sin(acos(vec[2]));
    if (fabs(sinTheta)<THRESHOLD_SIN_THETA)
    {
      return(0.); /* x = y = 0. */
    }
    else
    {
      aux=vec[0]/sinTheta; /* for avoiding precission problems */
      if (aux>1.) phi=0.;
      else if (aux<-1.) phi=M_PI;
      else phi=acos(aux);
      return((vec[1]<0.)?-phi:phi);
    }
    /*
     ** ** Equivalent code for this routine: **
     ** return(computeAngle(v.x,v.y));
     */
  }

  double computePolarAngle() const
  {
    /* Precondition: v must be a normalized Vector3 */
    return(acos(vec[2]));
    /*
     ** ** Equivalent code for this routine: **
     ** return(computeAngle(v.z,sqrt(v.x*v.x+v.y*v.y)));
     */
  }

  void print(unsigned n = 6) const;

  int compare(const sirVector3d& v) const {
    int code;

    code = 0;
    if (X() > v.X() + EPSILON) code += 1;
    if (Y() > v.Y() + EPSILON) code += 2;
    if (Z() > v.Y() + EPSILON) code += 4;
    if (code!=0)  /* x1 > x2 || y1 > y2 || z1 > z2 */
      return code;

    if (X() < v.X() - EPSILON ||
	Y() < v.Y() - EPSILON ||
	Z() < v.Z() - EPSILON)
      return code;        /* not the same vector */

    return 8;
  }
  sirVector3d& reduce(const sirVector4d& v);
  friend void swap(sirVector3d& a, sirVector3d& b);
  friend ostream& operator<< (ostream& s, const sirVector3d& v);
  friend istream& operator>> (istream& s, sirVector3d& v);
  friend sirVector3d operator- (const sirVector3d& v);
  //  friend sirVector3d operator* (const sirVector4d& v);

  // Conversion operators

  typedef double* floatPtr;
  operator floatPtr() { return vec; }
  operator sirVector4d();
};

ostream& operator<< (ostream& s, const sirVector3d& v);
double distance(const sirVector3d& v1, const sirVector3d& v2);

class sirVector4d
{
  friend class sirMat4d;

protected:
  double vec[4];
public:
  sirVector4d()
  {
    vec[0] = 0.0;
    vec[1] = 0.0;
    vec[2] = 0.0;
    //vec[3] = 0.0; //Es un vector
	/************FRAN**********/
	vec[3]=1.0; //Es un punto
	/************FRAN**********/
  }

  sirVector4d(const double x, const double y, const double z, const double w)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
  }
  sirVector4d(const double val)
  {
    vec[0] = val;
    vec[1] = val;
    vec[2] = val;
    vec[3] = val;
  }
  sirVector4d(const sirVector3d& v) {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = 1.;
  }
  void ini(const double x, const double y, const double z, const double w)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
  }
  double& operator[](int i) { return vec[i]; }
  double operator[](int i) const { return vec[i]; }
  sirVector4d& operator=(const sirVector3d& v) {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = 1.;
    return *this;
  }
  sirVector4d& operator=(const sirVector4d& v) {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = v[3];
    return *this;
  }

  void ini(sirVector4d v) { *this = v; }
  double& X() { return vec[0] ; }
  double& Y() { return vec[1] ; }
  double& Z() { return vec[2] ; }
  double& W() { return vec[3] ; }
  const double& X() const { return vec[0] ; }
  const double& Y() const { return vec[1] ; }
  const double& Z() const { return vec[2] ; }
  const double& W() const { return vec[3] ; }
  double GetX() const { return vec[0]; }
  double GetY() const { return vec[1]; }
  double GetZ() const { return vec[2]; }
  double GetW() const { return vec[3]; }
  void zero() { vec[0] = vec[1] = vec[2] = vec[3] = 0.0; }
  sirVector4d operator+(const sirVector4d& v) const {
    return sirVector4d(vec[0]+v.GetX(), vec[1]+v.GetY(), vec[2]+v.GetZ(), vec[3]+v.GetW());
  }
  sirVector4d operator-(const sirVector4d& v) const {
    return sirVector4d(vec[0]-v.GetX(), vec[1]-v.GetY(), vec[2]-v.GetZ(), vec[3]-v.GetW());
  }
//  sirVector4d operator/(const double k) const {
//    return sirVector4d(vec[0]/k, vec[1]/k, vec[2]/k, vec[3]/k);
//  }
  sirVector4d operator+=(const sirVector4d& v) {
    vec[0] += v.GetX();
    vec[1] += v.GetY();
    vec[2] += v.GetZ();
    vec[3] += v.GetW();
    return *this;
  }
  sirVector4d operator+=(const sirVector3d& v) {
    vec[0] += v.GetX();
    vec[1] += v.GetY();
    vec[2] += v.GetZ();
    return *this;
  }
  sirVector4d operator-=(const sirVector4d& v) {
    vec[0] -= v.GetX();
    vec[1] -= v.GetY();
    vec[2] -= v.GetZ();
    vec[3] -= v.GetW();
    return *this;
  }
  sirVector4d operator*=(const sirVector4d& v) {
    vec[0] *= v.GetX();
    vec[1] *= v.GetY();
    vec[2] *= v.GetZ();
    vec[3] *= v.GetW();
    return *this;
  }
  void Escalar(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
    vec[3] *= k;
  }
  sirVector4d operator/=(const double k) {
    vec[0] /= k;
    vec[1] /= k;
    vec[2] /= k;
    vec[3] /= k;
    return *this;
  }
  sirVector4d operator*=(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
    vec[3] *= k;
    return *this;
  }
  double operator*(const sirVector4d& v) const {
    return (double)vec[0]*(double)v.GetX() + (double)vec[1]*(double)v.GetY() + (double)vec[2]*(double)v.GetZ() + (double)vec[3]*(double)v.GetW();
  }

  int operator==(const sirVector4d& v) const {
    return vec[0]==v.GetX() && vec[1]==v.GetY() && vec[2]==v.GetZ() && vec[3]==v.GetW();
  }
  int operator<(const double f) const {
    return vec[0]<f || vec[1]<f || vec[2]<f || vec[3]<f;
  }
  friend sirVector4d operator*(const sirVector4d& v, double k) {
    return sirVector4d(v.GetX()*k, v.GetY()*k, v.GetZ()*k, v.GetW()*k);
  }
  friend sirVector4d operator*(double k, const sirVector4d& v) {
    return sirVector4d(v.GetX()*k, v.GetY()*k, v.GetZ()*k, v.GetW()*k);
  }
  friend sirVector4d operator/(const sirVector4d& v, double k) {
    return sirVector4d(v.GetX()/k, v.GetY()/k, v.GetZ()/k, v.GetW()/k);
  }
  friend sirVector4d operator/(double k, const sirVector4d& v) {
    return sirVector4d(v.GetX()/k, v.GetY()/k, v.GetZ()/k, v.GetW()/k);
  }
  double Modulo2() const {
    return (double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2] + (double)vec[3]*(double)vec[3];
  }
  double Modulo() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3]);
  }
  double norm() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3]);
  }
  double norm2() const {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] + vec[3]*vec[3];
  }
  double Normalizar() {
    double d = norm();
    vec[0] /= d; vec[1] /= d; vec[2] /= d; vec[3] /= d;
    return d;
  }
  double normalize() {
    double d = norm();
    vec[0] /= d; vec[1] /= d; vec[2] /= d; vec[3] /= d;
    return d;
  }
  void inversa(){
	  int i;
	  for (i=0;i<3;i++)
	  {
		  if(vec[i]<0) vec[i]*=(-1);
		  else if (vec[i]>0) vec[i]=0-vec[i];
	  }
  }


  friend void swap(sirVector4d& a, sirVector4d& b);
  friend sirVector4d operator- (const sirVector4d& v);
  friend ostream& operator<< (ostream& s, const sirVector4d& v);
  friend istream& operator>> (istream& s, sirVector4d& v);
};



class sirMat3d
{
protected:

  sirVector3d v[3];

public:

  // Constructors

  sirMat3d();
  sirMat3d(const sirVector3d& v0, const sirVector3d& v1, const sirVector3d& v2);
  sirMat3d(const double d);
  sirMat3d(const sirMat3d& m);

  // Assignment operators

  sirMat3d& operator	= ( const sirMat3d& m );	    // assignment of a sirMat3d
  sirMat3d& operator+= ( const sirMat3d& m );	    // incrementation by a sirMat3d
  sirMat3d& operator-= ( const sirMat3d& m );	    // decrementation by a sirMat3d
  sirMat3d& operator*= ( const double d );	    // multiplication by a constant
  sirMat3d& operator/= ( const double d );	    // division by a constant
  sirVector3d& operator[] ( int i);		    // indexing
  const sirVector3d& operator[] ( int i) const ;		    // indexing

  // special functions

  sirMat3d transpose();			    // transpose
  sirMat3d inverse();				    // inverse

  // friends

  friend sirMat3d operator- (const sirMat3d& a);			    // -m1
  friend sirMat3d operator+ (const sirMat3d& a, const sirMat3d& b);	    // m1 + m2
  friend sirMat3d operator- (const sirMat3d& a, const sirMat3d& b);	    // m1 - m2
  friend sirMat3d operator* (sirMat3d& a, sirMat3d& b);		    // m1 * m2
  friend sirMat3d operator* (const sirMat3d& a, const double d);	    // m1 * 3.0
  friend sirMat3d operator* (const double d, const sirMat3d& a);	    // 3.0 * m1
  friend sirMat3d operator/ (const sirMat3d& a, const double d);	    // m1 / 3.0
  friend int operator== (const sirMat3d& a, const sirMat3d& b);	    // m1 == m2 ?
  friend int operator!= (const sirMat3d& a, const sirMat3d& b);	    // m1 != m2 ?
  friend ostream& operator<< (ostream& s, const sirMat3d& m);	    // output to stream
  friend istream& operator>> (istream& s, sirMat3d& m);	    // input from strm.
  friend void swap(sirMat3d& a, sirMat3d& b);			    // swap m1 & m2

  // necessary friend declarations

  friend sirVector3d operator* (const sirMat3d& a, const sirVector3d& v);	    // linear transform
  friend sirVector2d operator* (const sirMat3d& a, const sirVector2d& v);	    // linear transform
};


/**
 * Clase sirMat4d.
 * Clase de matriz 4x4 (Coordenadas homogéneas).
 */

class sirMat4d
{
protected:

  sirVector4d v[4];

public:

  // Constructors

  sirMat4d();
  sirMat4d(const sirVector4d& v0, const sirVector4d& v1, const sirVector4d& v2, const sirVector4d& v3);
  sirMat4d(const double d);
  sirMat4d(const sirMat4d& m);

  // Assignment operators

  sirMat4d& operator	= ( const sirMat4d& m );	    // assignment of a sirMat4d
  sirMat4d& operator+= ( const sirMat4d& m );	    // incrementation by a sirMat4d
  sirMat4d& operator-= ( const sirMat4d& m );	    // decrementation by a sirMat4d
  sirMat4d& operator*= ( const double d );	    // multiplication by a constant
  sirMat4d& operator*= ( const sirMat4d& mat );	    // multiplication by a constant
  sirMat4d& operator/= ( const double d );	    // division by a constant
  sirVector4d& operator[] ( int i);		    // indexing
  const sirVector4d& operator[] ( int i) const ;		    // indexing

  // special functions

  sirMat4d transpose();			    // transpose
  sirMat4d inverse();				    // inverse
  void selfInverse();
  // friends

  friend sirMat4d operator- (const sirMat4d& a);			    // -m1
  friend sirMat4d operator+ (const sirMat4d& a, const sirMat4d& b);	    // m1 + m2
  friend sirMat4d operator- (const sirMat4d& a, const sirMat4d& b);	    // m1 - m2
  friend sirMat4d operator* (sirMat4d& a, sirMat4d& b);		    // m1 * m2
  friend sirMat4d operator* (const sirMat4d& a, const double d);	    // m1 * 4.0
  friend sirMat4d operator* (const double d, const sirMat4d& a);	    // 4.0 * m1
  friend sirMat4d operator/ (const sirMat4d& a, const double d);	    // m1 / 3.0
  friend int operator== (const sirMat4d& a, const sirMat4d& b);	    // m1 == m2 ?
  friend int operator!= (const sirMat4d& a, const sirMat4d& b);	    // m1 != m2 ?
  friend ostream& operator<< (ostream& s, const sirMat4d& m);	    // output to stream
  friend istream& operator>> (istream& s, sirMat4d& m);	    // input from strm.
  friend void swap(sirMat4d& a, sirMat4d& b);			    // swap m1 & m2

  /*********************FRAN*********************/

  /**
   * Función que permite realizar un canvio de sistema de referencia.
   * M=M*matriz donde M es la matriz del objeto que llama a este método.
   * @param matriz es la matriz del canvio de sistema de referencia que queremos aplicar.
  */
  void canvioSR(sirMat4d matriz);

  /**
   * Aplica una translación sobre la matriz que invocó este método.
   * Esta transformación solo afectará a las coordenadas: [0][3]=Cx, [1][3]=Cy, [2][3]=Cz.
   * @param vector vector translación.
  */
  void translacion(sirVector3d vector);

  /**
   * Crea la matriz de transformación 3D, a partir de la normal,el centro y dirección.
   * @param normal la normal del conector
   * @param centro el centro del conector
   * @param dir la dirección del conector
  */
  void crearRotacion(sirVector3d up,sirVector3d dir);

  /**
   * Crea una matriz 4x4 a partir de un puntero a un vector de 16 floats.
   * @param m el puntero al primer a los elementos que formarán la matriz
  */
  void introducir(float *m);

  /**
   * Función que transforma una matriz en coordenadas LDraw a coordenadas de LeoCAD.
  */
  void transformacionLeoCAD(void);

  void obtenerMatriz(double *m);
  sirMat4d rotarX(double angulo);
  sirMat4d rotarY(double angulo);
  sirMat4d rotarZ(double angulo);

  void trasladar(sirVector3d v);

  /*********************FRAN*********************/

  // necessary friend declarations

  friend sirVector4d operator* (const sirMat4d& a, const sirVector4d& v);	    // linear transform
  friend sirVector3d operator* (const sirMat4d& a, const sirVector3d& v);	    // linear transform
  // friend sirVector3d operator* (const sirMat4d& a, const sirVector3d& v);	    // linear transform
};

/****************************************************************
*								*
*	       2D functions and 3D functions			*
*								*
****************************************************************/

sirMat3d identity2D();				    // identity 2D
sirMat3d translation2D(sirVector2d& v);				    // translation 2D
sirMat3d rotation2D(sirVector2d& Center, const double angleDeg);	    // rotation 2D
sirMat3d scaling2D(sirVector2d& scaleVector);			    // scaling 2D
sirMat4d identity3D();					    // identity 3D
sirMat4d translation3D(sirVector3d& v);				    // translation 3D
void translation3D(sirMat4d& mat, const sirVector3d& v);				    // translation 3D
sirMat4d rotation3D(sirVector3d& Axis, const double angleDeg);	    // rotation 3D
void rotationX3D(sirMat4d& mat, const double angleDeg);	    // rotation 3D
void rotationY3D(sirMat4d& mat, const double angleDeg);	    // rotation 3D
void rotationZ3D(sirMat4d& mat, const double angleDeg);	    // rotation 3D
sirMat4d scaling3D(sirVector3d& scaleVector);			    // scaling 3D
void scaling3D(sirMat4d& mat, const sirVector3d& scaleVector);			    // scaling 3D
sirMat4d perspective3D(const double d);			    // perspective 3D
/*********************FRAN*********************/

/**
 *
 *
 */
sirVector3d obtenerTranslacion(sirMat4d final,sirMat4d inicial);

/**
 *
 *
 */
sirVector3d obtenerTranslacion(sirVector3d final,sirMat4d inicial);
/**
 *
 *
 */
sirVector3d obtenerTranslacion(sirMat4d final,sirVector3d inicial);

/**
 *
 *
 */
sirVector3d obtenerinterseccion(sirMat4d final,sirMat4d inicial);

/**
 *
 *
 */
sirVector3d obtenerinterseccionradio(sirMat4d final,sirMat4d inicial,double restatico,double rdinamico);

/**
 *
 *
 */
sirVector3d obtenerinterseccionradio90(sirMat4d final,sirMat4d inicial,double restatico,double rdinamico);

/**
 *
 *
 */
double transformacionLeoCAD(double numero);

/**
 * Cálculo de la distancia al cuadrado entre un punto "p" y una recta "linea".
 * Se calcula la distancia al cuadrado para evitar realizar la raiz cuadrada, ya que este método será llamado muchas veces.
 * @param px coordenada x del punto p.
 * @param py coordenada y del punto p.
 * @param pz coordenada z del punto p.
 * @param linea estructura con información sobre la línea.
 */
double distanciaPuntoRecta(double px,double py,double pz,LC_CLICKLINE linea);

/**
 * Función que determina si dos puntos se encuentran en la misma posición.
 * Los dos puntos estarán en la misma posición si |(x1,y1,z1)-(x2,y2,z2)|<Valor.
 * @param x1 componente x del primer punto.
 * @param y1 componente y del primer punto.
 * @param z1 componente z del primer punto.
 * @param x2 componente x del segundo punto.
 * @param y2 componente y del segundo punto.
 * @param z2 componente z del segundo punto.
 */
bool iguales(double x1,double y1,double z1,double x2,double y2,double z2);

/**
 * Función que determina si dos puntos se encuentran en la misma posición.
 * Los dos puntos estarán en la misma posición si |(x1,y1)-(x2,y2)|<Valor.
 * @param x1 componente x del primer punto.
 * @param x2 componente x del segundo punto.
 */
bool iguales(double x1,double x2);

/**
 * Calcula la distancia mínima entre distMin los dos puntos.
 * @param xi componente x del primer punto.
 * @param yi componente y del primer punto.
 * @param zi componente z del primer punto.
 * @param xf componente x del segundo punto.
 * @param yf componente y del segundo punto.
 * @param zf componente z del segundo punto.
 */
double distanciaPuntos(double xi,double yi,double zi,double xf,double yf,double zf);

/**
 * Calcula la distancia mínima entre A-B1 y A-B2.
 * @param A primer punto.
 * @param B1 segundo puntol
 * @param B2 tercer punto.
 */
double distanciaMinimaPuntoPuntos(sirVector4d A,sirVector4d B1,sirVector4d B2);

/*********************FRAN*********************/

class sirVector3D
{
protected:
  double vec[3];
public:
  sirVector3D()
  {
    vec[0] = 0.0;
    vec[1] = 0.0;
    vec[2] = 0.0;
  }
  //: Default constructor
  sirVector3D(const double x, const double y, const double z)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }
  sirVector3D(const double val)
  {
    vec[0] = val;
    vec[1] = val;
    vec[2] = val;
  }
  sirVector3D(const sirVector4d& v);

  double& operator[](const int i) { return vec[i]; }
  double operator[](const int i) const { return vec[i]; }

  void ini(const double x, const double y, const double z)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }
  sirVector3D& operator= (const sirVector4d& v);
  sirVector3D& operator=(const sirVector3D& v) {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    return *this;
  }
  //:

  void ini(sirVector3D v) { *this = v; }
  double& X() { return vec[0] ; }
  double& Y() { return vec[1] ; }
  double& Z() { return vec[2] ; }
  const double& X() const { return vec[0] ; }
  const double& Y() const { return vec[1] ; }
  const double& Z() const { return vec[2] ; }
  double GetX() const { return vec[0]; }
  double GetY() const { return vec[1]; }
  double GetZ() const { return vec[2]; }
  void zero() {vec[0]=0.0; vec[1]=0.0; vec[2]=0.0;}
  double sum() const { return vec[0] + vec[1] + vec[2]; }
  double getAverage() const { return sum() / 3.; }
  //double max() const { return ::max(::max(vec[0], vec[1]), vec[2]); }
  //double min() const { return ::min(::min(vec[0], vec[1]), vec[2]); }

  sirVector3D operator+(const sirVector3D& v) const {
    return sirVector3D(vec[0]+v.GetX(), vec[1]+v.GetY(), vec[2]+v.GetZ());
  }
  sirVector3D operator-(const sirVector3D& v) const {
    return sirVector3D(vec[0]-v.GetX(), vec[1]-v.GetY(), vec[2]-v.GetZ());
  }
  //  sirVector3D operator/(const double k) const {
  //    return sirVector3D(vec[0]/k, vec[1]/k, vec[2]/k);
  //  }
  sirVector3D operator+=(const sirVector3D& v) {
    vec[0] += v.GetX();
    vec[1] += v.GetY();
    vec[2] += v.GetZ();
    return *this;
  }
  sirVector3D operator-=(const sirVector3D& v) {
    vec[0] -= v.GetX();
    vec[1] -= v.GetY();
    vec[2] -= v.GetZ();
    return *this;
  }
  sirVector3D operator*=(const sirVector3D& v) {
    vec[0] *= v.GetX();
    vec[1] *= v.GetY();
    vec[2] *= v.GetZ();
    return *this;
  }
  void Escalar(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
  }
  sirVector3D operator/=(const double k) {
    vec[0] /= k;
    vec[1] /= k;
    vec[2] /= k;
    return *this;
  }
  sirVector3D operator*=(const double k) {
    vec[0] *= k;
    vec[1] *= k;
    vec[2] *= k;
    return *this;
  }
  double operator*(const sirVector3D& v) const {
    return (double)vec[0]*(double)v.GetX() + (double)vec[1]*(double)v.GetY() + (double)vec[2]*(double)v.GetZ();
  }
  sirVector3D operator^(const sirVector3D& v) const {
    return sirVector3D(vec[1]*v.GetZ()-vec[2]*v.GetY(),
		       v.GetX()*vec[2]-vec[0]*v.GetZ(),
		       vec[0]*v.GetY()-vec[1]*v.GetX());
  }
  int operator==(const sirVector3D& v) const {
    return vec[0]==v.GetX() && vec[1]==v.GetY() && vec[2]==v.GetZ();
  }
  int operator<(const double f) const {
    return vec[0]<f || vec[1]<f || vec[2]<f;
  }
  friend sirVector3D operator^(const sirVector3D& v1, const sirVector3D& v2) {
    return sirVector3D(v1[1]*v2.GetZ()-v1[2]*v2.GetY(),
		       v2.GetX()*v1[2]-v1[0]*v2.GetZ(),
		       v1[0]*v2.GetY()-v1[1]*v2.GetX());
  }
  friend sirVector3D operator*(const sirVector3D& v, double k) {
    return sirVector3D(v.GetX()*k, v.GetY()*k, v.GetZ()*k);
  }
  friend sirVector3D operator*(double k, const sirVector3D& v) {
    return sirVector3D(v.GetX()*k, v.GetY()*k, v.GetZ()*k);
  }
  friend sirVector3D operator/(const sirVector3D& v, double k) {
    return sirVector3D(v.GetX()/k, v.GetY()/k, v.GetZ()/k);
  }
  friend sirVector3D operator/(double k, const sirVector3D& v) {
    return sirVector3D(v.GetX()/k, v.GetY()/k, v.GetZ()/k);
  }
  double Modulo2() const {
    return (double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2];
  }
  double Modulo() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  }
  double norm() const {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
  }
  double norm2() const {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
  }
  double Normalizar() {
    double d = sqrt((double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2]);
    vec[0] /= d; vec[1] /= d; vec[2] /= d;
    return d;
  }
  double normalize() {
    double d = sqrt((double)vec[0]*(double)vec[0] + (double)vec[1]*(double)vec[1] + (double)vec[2]*(double)vec[2]);
    vec[0] /= d; vec[1] /= d; vec[2] /= d;
    return d;
  }
  void Rot12(const double, const double, const double, const double);
  int Visible(sirVector3D&);
  void ExtractVerts(double&, double&, int) const;


  double computeAzimuthAngle() const
  {
    /* Precondition: v must be a normalized Vector3 */
    double sinTheta, phi, aux;

    sinTheta=sin(acos(vec[2]));
    if (fabs(sinTheta)<THRESHOLD_SIN_THETA)
    {
      return(0.); /* x = y = 0. */
    }
    else
    {
      aux=vec[0]/sinTheta; /* for avoiding precission problems */
      if (aux>1.) phi=0.;
      else if (aux<-1.) phi=M_PI;
      else phi=acos(aux);
      return((vec[1]<0.)?-phi:phi);
    }
    /*
     ** ** Equivalent code for this routine: **
     ** return(computeAngle(v.x,v.y));
     */
  }

  double computePolarAngle() const
  {
    /* Precondition: v must be a normalized Vector3 */
    return(acos(vec[2]));
    /*
     ** ** Equivalent code for this routine: **
     ** return(computeAngle(v.z,sqrt(v.x*v.x+v.y*v.y)));
     */
  }

  void print(unsigned n = 6) const;

  int compare(const sirVector3D& v) const {
    int code;

    code = 0;
    if (X() > v.X() + EPSILON) code += 1;
    if (Y() > v.Y() + EPSILON) code += 2;
    if (Z() > v.Y() + EPSILON) code += 4;
    if (code!=0)  /* x1 > x2 || y1 > y2 || z1 > z2 */
      return code;

    if (X() < v.X() - EPSILON ||
	Y() < v.Y() - EPSILON ||
	Z() < v.Z() - EPSILON)
      return code;        /* not the same vector */

    return 8;
  }
  sirVector3D& reduce(const sirVector4d& v);
  friend void swap(sirVector3D& a, sirVector3D& b);
  friend ostream& operator<< (ostream& s, const sirVector3D& v);
  friend istream& operator>> (istream& s, sirVector3D& v);
  friend sirVector3D operator- (const sirVector3D& v);

  // Conversion operators

  typedef double* doublePtr;
  operator doublePtr() { return vec; }
  operator sirVector4d();
  sirVector3D& operator = (const sirVector3d& v);
};


#endif

