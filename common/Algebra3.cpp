// algebra3.cc

#include <stdio.h>
//#include <algobase.h> // max...

//#include <kernel/algebra3.h>
#include "Algebra3.h"
#include <ctype.h>
#include "utilidades.h"


#define VX 0
#define VY 1
#define VZ 2
#define VW 3
//#define RAND_MAX 1

/*
#ifdef WIN32
//WIN32 compatibility functions
double DRAND48()
{
  return drand48();
}

double drand48()
{
  double r1=rand();
  if (r1 == 0.0)
    r1 = rand();
  double r2=r1/(double)RAND_MAX;
  if (r2<0 || r2>1) {
    cerr << "WRONG RANDOM NUMBER!\n";
    r2 = 0.5;
  }
  return (r2);
}

void srand48(long seedval)
{
  srand((unsigned int)seedval);
}
*/
double rint(double x)
{
  return (fabs(x-floor(x))>0.5)?ceil(x):floor(x);
}
//#endif


/****************************************************************
*								*
*		    sirVector2d Member functions		*
*								*
****************************************************************/

// CONSTRUCTORS

sirVector2d::sirVector2d() {}

sirVector2d::sirVector2d(const double x, const double y)
{ vec[VX] = x; vec[VY] = y; }

sirVector2d::sirVector2d(const double d)
{ vec[VX] = vec[VY] = d; }

sirVector2d::sirVector2d(const sirVector2d& v)
{ vec[VX] = v.X(); vec[VY] = v.Y(); }

sirVector2d::sirVector2d(const sirVector3d& v) {
  // it is up to caller to avoid divide-by-zero
  vec[VX] = v.X()/v.Z(); vec[VY] = v.Y()/v.Z();
}

sirVector2d::sirVector2d(const sirVector3d& v, int dropAxis) {
    switch (dropAxis) {
	case VX: vec[VX] = v.Y(); vec[VY] = v.Z(); break;
	case VY: vec[VX] = v.X(); vec[VY] = v.Z(); break;
	default: vec[VX] = v.X(); vec[VY] = v.Y(); break;
    }
}


// ASSIGNMENT OPERATORS

sirVector2d& sirVector2d::operator = (const sirVector2d& v)
{ vec[VX] = v.X(); vec[VY] = v.Y(); return *this; }

sirVector2d& sirVector2d::operator += ( const sirVector2d& v )
{ vec[VX] += v.X(); vec[VY] += v.Y(); return *this; }

sirVector2d& sirVector2d::operator -= ( const sirVector2d& v )
{ vec[VX] -= v.X(); vec[VY] -= v.Y(); return *this; }

sirVector2d& sirVector2d::operator *= ( const double d )
{ vec[VX] *= d; vec[VY] *= d; return *this; }

sirVector2d& sirVector2d::operator /= ( const double d )
{ double d_inv = 1./d; vec[VX] *= d_inv; vec[VY] *= d_inv; return *this; }

double& sirVector2d::operator [] ( int i) {
    return vec[i];
}

double sirVector2d::operator [] ( int i) const {
    return vec[i];
}


// SPECIAL FUNCTIONS

double sirVector2d::length()
{ return sqrt(length2()); }

double sirVector2d::length2()
{ return vec[VX]*vec[VX] + vec[VY]*vec[VY]; }

sirVector2d& sirVector2d::normalize() // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }



// FRIENDS

sirVector2d operator - (const sirVector2d& a)
{ return sirVector2d(-a.vec[VX],-a.vec[VY]); }

sirVector2d operator + (const sirVector2d& a, const sirVector2d& b)
{ return sirVector2d(a.vec[VX]+ b.vec[VX], a.vec[VY] + b.vec[VY]); }

sirVector2d operator - (const sirVector2d& a, const sirVector2d& b)
{ return sirVector2d(a.vec[VX]-b.vec[VX], a.vec[VY]-b.vec[VY]); }

sirVector2d operator * (const sirVector2d& a, const double d)
{ return sirVector2d(d*a.vec[VX], d*a.vec[VY]); }

sirVector2d operator * (const double d, const sirVector2d& a)
{ return a*d; }

sirVector2d operator * (const sirMat3d& a, const sirVector2d& v) {
    sirVector3d av;

    av.X() = a.v[0].X()*v.X() + a.v[0].Y()*v.Y() + a.v[0].Z();
    av.Y() = a.v[1].X()*v.X() + a.v[1].Y()*v.Y() + a.v[1].Z();
    av.Z() = a.v[2].X()*v.X() + a.v[2].Y()*v.Y() + a.v[2].Z();
    return av;
}

sirVector2d operator * (const sirVector2d& v, sirMat3d& a)
{ return a.transpose() * v; }

double operator * (const sirVector2d& a, const sirVector2d& b)
{ return (a.X()*b.X() + a.Y()*b.Y()); }

sirVector2d operator / (const sirVector2d& a, const double d)
{ double d_inv = 1./d; return sirVector2d(a.X()*d_inv, a.Y()*d_inv); }

sirVector3d operator ^ (const sirVector2d& a, const sirVector2d& b)
{ return sirVector3d(0.0, 0.0, a.X() * b.Y() - b.X() * a.Y()); }

int operator == (const sirVector2d& a, const sirVector2d& b)
{ return (a.X() == b.X()) && (a.Y() == b.Y()); }

int operator != (const sirVector2d& a, const sirVector2d& b)
{ return !(a == b); }

ostream& operator << (ostream& s, const sirVector2d& v)
{ return s << "| " << v.X() << ' ' << v.Y() << " |"; }

istream& operator >> (istream& s, sirVector2d& v) {
  /*
    sirVector2d	v_tmp;
    char	c = ' ';

    while (isspace(c))
	s >> c;
    // The vectors can be formatted either as x y or | x y |
    if (c == '|') {
	s >> v_tmp[VX] >> v_tmp[VY];
	while (s >> c && isspace(c)) ;
	if (c != '|')
	    s.set(_bad);
	}
    else {
	s.putback(c);
	s >> v_tmp[VX] >> v_tmp[VY];
	}
    if (s)
	v = v_tmp;
	*/
    return s;
}

void swap(sirVector2d& a, sirVector2d& b)
{ sirVector2d tmp(a); a = b; b = tmp; }

//#ifndef WIN32
//sirVector2d min(const sirVector2d& a, const sirVector2d& b)
//#else
//const sirVector2d& min(const sirVector2d& a, const sirVector2d& b)
//#endif
//{ return sirVector2d(min(a.X(), b.X()), min(a.Y(), b.Y())); }

//#ifndef WIN32
//sirVector2d max(const sirVector2d& a, const sirVector2d& b)
//#else
//const sirVector2d& max(const sirVector2d& a, const sirVector2d& b)
//#endif
//{ return sirVector2d(max(a.X(), b.X()), max(a.Y(), b.Y())); }

sirVector2d prod(const sirVector2d& a, const sirVector2d& b)
{ return sirVector2d(a.X() * b.X(), a.Y() * b.Y()); }

sirVector3d&
sirVector3d::reduce(const sirVector4d& v)
{
  vec[0] = v[0];
  vec[1] = v[1];
  vec[2] = v[2];
  return *this;
}

sirVector3d::sirVector3d(const sirVector3D& v)
{
  vec[0] = v[0];
  vec[1] = v[1];
  vec[2] = v[2];
}

sirVector3d::sirVector3d(const sirVector4d& v)
{
  vec[0] = v[0]/v[3];
  vec[1] = v[1]/v[3];
  vec[2] = v[2]/v[3];
}

sirVector3d&
sirVector3d::operator = (const sirVector4d& v)
{
  vec[0] = v[0]/v[3];
  vec[1] = v[1]/v[3];
  vec[2] = v[2]/v[3];
  return *this;
}

void
sirVector3d::ExtractVerts(double& px, double& py, int which) const
{
  switch (which) {
  case 0:
    px = vec[1];
    py = vec[2];
    break;
  case 1:
    px = vec[0];
    py = vec[2];
    break;
  case 2:
    px = vec[0];
    py = vec[1];
    break;
  }
}

void
sirVector3d::print(unsigned n) const
{
  double base = pow(10, n);
  printf("(%f, %f, %f)", rint(vec[0]*base)/base, rint(vec[1]*base)/base, rint(vec[2]*base)/base);
}

sirVector3d::operator sirVector4d()
{
  return sirVector4d(*this);
}

double
distance(const sirVector3d& v1, const sirVector3d& v2)
{
  double dx = v2[0] - v1[0];
  double dy = v2[1] - v1[1];
  double dz = v2[2] - v1[2];
  return sqrt(dx*dx + dy*dy + dz*dz);
}

void
swap(sirVector3d& a, sirVector3d& b)
{ sirVector3d tmp(a); a = b; b = tmp; }

ostream&
operator << (ostream& s, const sirVector3d& v)
{ return s << "| " << v.X() << ' ' << v.Y() << ' ' << v.Z() << " |"; }

istream&
operator >> (istream& s, sirVector3d& v) {
  /*
    sirVector3d	v_tmp;
    char	c = ' ';

    while (isspace(c))
	s >> c;
    // The vectors can be formatted either as x y or | x y |
    if (c == '|') {
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
      while (s >> c && isspace(c)) ;
      if (c != '|')
	s.set(_bad);
    }
    else {
      s.putback(c);
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
	}
    if (s)
      v = v_tmp;
      */
    return s;
}

sirVector3d
operator - (const sirVector3d& a)
{ return sirVector3d(-a.vec[VX],-a.vec[VY],-a.vec[VZ]); }

/*
  sirVector3d
  operator * (const sirVector4d& a)
  { return sirVector3d(-a.X(),-a.Y(),-a.Z()); }
*/


//
// sirVector4d functions
//


void
swap(sirVector4d& a, sirVector4d& b)
{ sirVector4d tmp(a); a = b; b = tmp; }

sirVector4d
operator - (const sirVector4d& a)
{ return sirVector4d(-a.vec[VX],-a.vec[VY],-a.vec[VZ],-a.vec[VW]); }

ostream&
operator << (ostream& s, const sirVector4d& v)
{ return s << "| " << v.X() << ' ' << v.Y() << ' ' << v.Z() << ' ' << v.W() << " |"; }

istream&
operator >> (istream& s, sirVector4d& v) {
  /*
    sirVector4d	v_tmp;
    char	c = ' ';

    while (isspace(c))
	s >> c;
    // The vectors can be formatted either as x y or | x y |
    if (c == '|') {
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
      while (s >> c && isspace(c)) ;
      if (c != '|')
	s.set(_bad);
    }
    else {
      s.putback(c);
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
	}
    if (s)
      v = v_tmp;
      */
    return s;
}


/****************************************************************
*								*
*		    sirMat3d member functions			*
*								*
****************************************************************/

// CONSTRUCTORS

sirMat3d::sirMat3d() {}

sirMat3d::sirMat3d(const sirVector3d& v0, const sirVector3d& v1, const sirVector3d& v2)
{ v[0] = v0; v[1] = v1; v[2] = v2; }

sirMat3d::sirMat3d(const double d)
{ v[0] = v[1] = v[2] = sirVector3d(d); }

sirMat3d::sirMat3d(const sirMat3d& m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; }


// ASSIGNMENT OPERATORS

sirMat3d& sirMat3d::operator = ( const sirMat3d& m )
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; return *this; }

sirMat3d& sirMat3d::operator += ( const sirMat3d& m )
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; return *this; }

sirMat3d& sirMat3d::operator -= ( const sirMat3d& m )
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; return *this; }

sirMat3d& sirMat3d::operator *= ( const double d )
{ v[0] *= d; v[1] *= d; v[2] *= d; return *this; }

sirMat3d& sirMat3d::operator /= ( const double d )
{ v[0] /= d; v[1] /= d; v[2] /= d; return *this; }

sirVector3d& sirMat3d::operator [] ( int i) {
    return v[i];
}

const sirVector3d& sirMat3d::operator [] ( int i) const {
    return v[i];
}


// SPECIAL FUNCTIONS

sirMat3d sirMat3d::transpose() {
    return sirMat3d(sirVector3d(v[0][0], v[1][0], v[2][0]),
		sirVector3d(v[0][1], v[1][1], v[2][1]),
		sirVector3d(v[0][2], v[1][2], v[2][2]));
}

sirMat3d sirMat3d::inverse()	    // Gauss-Jordan elimination with partial pivoting
    {
    sirMat3d a(*this),	    // As a evolves from original mat into identity
	 b(identity2D());   // b evolves from identity into inverse(a)
    int	 i, j, i1;

    // Loop over cols of a from left to right, eliminating above and below diag
    for (j=0; j<3; j++) {   // Find largest pivot in column j among rows j..2
    i1 = j;		    // Row with largest pivot candidate
    for (i=j+1; i<3; i++)
	if (fabs(a.v[i].vec[j]) > fabs(a.v[i1].vec[j]))
	    i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    swap(a.v[i1], a.v[j]);
    swap(b.v[i1], b.v[j]);

    // Scale row j to have a unit diagonal
    if (a.v[j].vec[j]==0.);
      //error(SIRERR_MAT3SING);
    b.v[j] /= a.v[j].vec[j];
    a.v[j] /= a.v[j].vec[j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<3; i++)
	if (i!=j) {
	b.v[i] -= a.v[i].vec[j]*b.v[j];
	a.v[i] -= a.v[i].vec[j]*a.v[j];
	}
    }
    return b;
}

// FRIENDS

sirMat3d operator - (const sirMat3d& a)
{ return sirMat3d(-a.v[0], -a.v[1], -a.v[2]); }

sirMat3d operator + (const sirMat3d& a, const sirMat3d& b)
{ return sirMat3d(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); }

sirMat3d operator - (const sirMat3d& a, const sirMat3d& b)
{ return sirMat3d(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); }

sirMat3d operator * (sirMat3d& a, sirMat3d& b) {
    #define ROWCOL(i, j) \
    a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]
    return sirMat3d(sirVector3d(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
		sirVector3d(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
		sirVector3d(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
    #undef ROWCOL(i, j)
}

sirMat3d operator * (const sirMat3d& a, const double d)
{ return sirMat3d(a[0] * d, a[1] * d, a[2] * d); }

sirMat3d operator * (const double d, const sirMat3d& a)
{ return a*d; }

sirMat3d operator / (const sirMat3d& a, const double d)
{ return sirMat3d(a[0] / d, a[1] / d, a[2] / d); }

int operator == (const sirMat3d& a, const sirMat3d& b)
{ return (a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]); }

int operator != (const sirMat3d& a, const sirMat3d& b)
{ return !(a == b); }

ostream& operator << (ostream& s, const sirMat3d& m)
{ return s << m[VX] << '\n' << m[VY] << '\n' << m[VZ]; }

istream& operator >> (istream& s, sirMat3d& m) {
    sirMat3d    m_tmp;

    s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ];
    if (s)
	m = m_tmp;
    return s;
}

void swap(sirMat3d& a, sirMat3d& b)
{ sirMat3d tmp(a); a = b; b = tmp; }


/****************************************************************
*								*
*		    sirMat4d member functions			*
*								*
****************************************************************/

// CONSTRUCTORS

sirMat4d::sirMat4d()
{
	/*********FRAN********/
	//Antes no había nada!!!!!

	v[0][0]=1; v[0][1]=0; v[0][2]=0; v[0][3]=0;
	v[1][0]=0; v[1][1]=1; v[1][2]=0; v[1][3]=0;
	v[2][0]=0; v[2][1]=0; v[2][2]=1; v[2][3]=0;
	v[3][0]=0; v[3][1]=0; v[3][2]=0; v[3][3]=1;

	/*********FRAN********/
}

sirMat4d::sirMat4d(const sirVector4d& v0, const sirVector4d& v1, const sirVector4d& v2, const sirVector4d& v3)
{ v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3; }

sirMat4d::sirMat4d(const double d)
{ v[0] = v[1] = v[2] = v[3] = sirVector4d(d); }

sirMat4d::sirMat4d(const sirMat4d& m)
{ v[0] = m[0]; v[1] = m[1]; v[2] = m[2]; v[3] = m[3]; }


// ASSIGNMENT OPERATORS

sirMat4d& sirMat4d::operator = ( const sirMat4d& m )
{ v[0] = m[0]; v[1] = m[1]; v[2] = m[2]; v[3] = m[3];
return *this; }

sirMat4d& sirMat4d::operator += ( const sirMat4d& m )
{ v[0] += m[0]; v[1] += m[1]; v[2] += m[2]; v[3] += m[3];
return *this; }

sirMat4d& sirMat4d::operator -= ( const sirMat4d& m )
{ v[0] -= m[0]; v[1] -= m[1]; v[2] -= m[2]; v[3] -= m[3];
return *this; }

sirMat4d& sirMat4d::operator *= ( const double d )
{ v[0] *= d; v[1] *= d; v[2] *= d; v[3] *= d; return *this; }

sirMat4d& sirMat4d::operator /= ( const double d )
{ v[0] /= d; v[1] /= d; v[2] /= d; v[3] /= d; return *this; }

sirVector4d& sirMat4d::operator [] ( int i) {
    return v[i];
}

const sirVector4d& sirMat4d::operator [] ( int i) const {
    return v[i];
}

// SPECIAL FUNCTIONS;

sirMat4d sirMat4d::transpose() {
    return sirMat4d(sirVector4d(v[0][0], v[1][0], v[2][0], v[3][0]),
		sirVector4d(v[0][1], v[1][1], v[2][1], v[3][1]),
		sirVector4d(v[0][2], v[1][2], v[2][2], v[3][2]),
		sirVector4d(v[0][3], v[1][3], v[2][3], v[3][3]));
}

sirMat4d sirMat4d::inverse()	    // Gauss-Jordan elimination with partial pivoting
{
    sirMat4d a(*this),	    // As a evolves from original mat into identity
	 b(identity3D());   // b evolves from identity into inverse(a)
    int i, j, i1;

    // Loop over cols of a from left to right, eliminating above and below diag
    for (j=0; j<4; j++) {   // Find largest pivot in column j among rows j..3
    i1 = j;		    // Row with largest pivot candidate
    for (i=j+1; i<4; i++)
	if (fabs(a[i][j]) > fabs(a.v[i1][j]))
	i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    swap(a.v[i1], a[j]);
    swap(b.v[i1], b[j]);

    // Scale row j to have a unit diagonal
    if (a[j][j]==0.);
      //error(SIRERR_MAT4SING);
    b[j] /= a[j][j];
    a[j] /= a[j][j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<4; i++)
	if (i!=j) {
	b[i] -= a[i][j]*b[j];
	a[i] -= a[i][j]*a[j];
	}
    }
    return b;
}


void
sirMat4d::selfInverse()	    // Gauss-Jordan elimination with partial pivoting
{
    sirMat4d a(*this);	    // As a evolves from original mat into identity
    *this = identity3D();
    int i, j, i1;

    // Loop over cols of a from left to right, eliminating above and below diag
    for (j=0; j<4; j++) {   // Find largest pivot in column j among rows j..3
    i1 = j;		    // Row with largest pivot candidate
    for (i=j+1; i<4; i++)
	if (fabs(a[i][j]) > fabs(a.v[i1][j]))
	i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    swap(a.v[i1], a[j]);
    swap(v[i1], v[j]);

    // Scale row j to have a unit diagonal
    if (a[j][j]==0.);
      //error(SIRERR_MAT4SING);
    v[j] /= a[j][j];
    a[j] /= a[j][j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<4; i++)
	if (i!=j) {
	v[i] -= a[i][j]*v[j];
	a[i] -= a[i][j]*a[j];
	}
    }
}

/*********************FRAN*********************/

void sirMat4d::canvioSR(sirMat4d matriz)
{
	//es simplemente un producto de matrices
	(*this)=(*this)*matriz; //M=M*matriz

}

void sirMat4d::crearRotacion(sirVector3d up,sirVector3d dir)
{

	//CUIDADO NO SE SI LO DEL VECTOR COLUMNA ESTÁ BIÉN!!!!!!!

	sirVector3d rx,ry,rz;

	//rz==dir/||dir||
	rz[0]=dir[0];
	rz[1]=dir[1];
	rz[2]=dir[2];
	rz.normalize(); //Normalizar vector rz-->Dividir por la norma del vector

	//rx==normal x rz
	rx=up^rz;
	rx.normalize(); //Normalizar vector rx-->Dividir por la norma del vector

	//ry==rz x rx
	ry=rz^rx; //ry-->ya es un vector normalitzado

	//MAL-->SON V[i] VECTORES FILA!!!!!!!

	//Primer vector columna de la matriz
	v[0][0]=rx.GetX();
	v[1][0]=rx.GetY();
	v[2][0]=rx.GetZ();
	v[3][0]=0;

	//Segundo vector columna de la matriz
	v[0][1]=ry.GetX();
	v[1][1]=ry.GetY();
	v[2][1]=ry.GetZ();
	v[3][1]=0;

	//Tercer vector columna de la matriz
	v[0][2]=rz.GetX();
	v[1][2]=rz.GetY();
	v[2][2]=rz.GetZ();
	v[3][2]=0;

	//Cuarto vector columna de la matriz
	v[0][3]=0;
	v[1][3]=0;
	v[2][3]=0;
	v[3][3]=1;
}

void sirMat4d::translacion(sirVector3d vector)
{
	sirMat4d aux;

	//aux es la matriz de translación
	aux=translation3D(vector);
	(*this)=aux*(*this); //TRANS*MAT
}

void sirMat4d::introducir(float *m)
{
	//Primer vector columna de la matriz
	v[0][0]=m[0];
	v[1][0]=m[1];
	v[2][0]=m[2];
	v[3][0]=m[3];

	//Segundo vector columna de la matriz
	v[0][1]=m[4];
	v[1][1]=m[5];
	v[2][1]=m[6];
	v[3][1]=m[7];

	//Tercer vector columna de la matriz
	v[0][2]=m[8];
	v[1][2]=m[9];
	v[2][2]=m[10];
	v[3][2]=m[11];

	//Cuarto vector columna de la matriz
	v[0][3]=m[12];
	v[1][3]=m[13];
	v[2][3]=m[14];
	v[3][3]=m[15];

}

void sirMat4d::transformacionLeoCAD(void)
{
	float aux[12];
	Matrix auxMat;

	//Hay que pasarle orden-->Centro+matriz(fila)-->Como en LDraw

	//Primera tres componentes el centro
	aux[0]=v[0][3];
	aux[1]=v[1][3];
	aux[2]=v[2][3];

	/***************************************/

	//Los 3 vectores de rotación-->Tienen que estar en filas como en LDraw!!!!!!
	aux[3]=v[0][0];
	aux[4]=v[0][1];
	aux[5]=v[0][2];

	aux[6]=v[1][0];
	aux[7]=v[1][1];
	aux[8]=v[1][2];

	aux[9]=v[2][0];
	aux[10]=v[2][1];
	aux[11]=v[2][2];

	/*aux[3]=v[0][0];
	aux[4]=v[1][0];
	aux[5]=v[2][0];

	aux[6]=v[0][1];
	aux[7]=v[1][1];
	aux[8]=v[2][1];

	aux[9]=v[0][2];
	aux[10]=v[1][2];
	aux[11]=v[2][2];*/

	/***************************************/

	auxMat.FromLDraw(aux);

	v[0][0]=auxMat.m[0]; v[0][1]=auxMat.m[4]; v[0][2]=auxMat.m[8]; v[0][3]=auxMat.m[12];
	v[1][0]=auxMat.m[1]; v[1][1]=auxMat.m[5]; v[1][2]=auxMat.m[9]; v[1][3]=auxMat.m[13];
	v[2][0]=auxMat.m[2]; v[2][1]=auxMat.m[6]; v[2][2]=auxMat.m[10]; v[2][3]=auxMat.m[14];
	v[3][0]=auxMat.m[3]; v[3][1]=auxMat.m[7]; v[3][2]=auxMat.m[11]; v[3][3]=auxMat.m[15];
}


void sirMat4d::obtenerMatriz(double *m)
{
	m[0]=v[0][0];
	m[1]=v[1][0];
	m[2]=v[2][0];
	m[3]=v[3][0];

	m[4]=v[0][1];
	m[5]=v[1][1];
	m[6]=v[2][1];
	m[7]=v[3][1];

	m[8]=v[0][2];
	m[9]=v[1][2];
	m[10]=v[2][2];
	m[11]=v[3][2];

	m[12]=v[0][3];
	m[13]=v[1][3];
	m[14]=v[2][3];
	m[15]=v[3][3];
}

/*float *sirMat4d::obtenerMatriz(void)
{
	float aux[16];

	aux[0]=v[0][0];
	aux[1]=v[1][0];
	aux[2]=v[2][0];
	aux[3]=v[3][0];

	aux[4]=v[0][1];
	aux[5]=v[1][1];
	aux[6]=v[2][1];
	aux[7]=v[3][1];

	aux[8]=v[0][2];
	aux[9]=v[1][2];
	aux[10]=v[2][2];
	aux[11]=v[3][2];

	aux[12]=v[0][3];
	aux[13]=v[1][3];
	aux[14]=v[2][3];
	aux[15]=v[3][3];

	return aux;
}*/

sirMat4d sirMat4d::rotarX(double angulo)
{
	sirMat4d m;

	m[0][0]=1;  m[0][1]=0;			  m[0][2]=0;			m[0][3]=0;
	m[1][0]=0;  m[1][1]=cos(angulo);  m[1][2]=-sin(angulo);	m[1][3]=0;
	m[2][0]=0;	m[2][1]=sin(angulo);  m[2][2]=cos(angulo);	m[2][3]=0;
	m[3][0]=0;	m[3][1]=0;			  m[3][2]=0;			m[3][3]=1;

	return m*(*this);
}

sirMat4d sirMat4d::rotarY(double angulo)
{
	sirMat4d m;

	m[0][0]=cos(angulo);  m[0][1]=0;  m[0][2]=sin(angulo);  m[0][3]=0;
	m[1][0]=0;			  m[1][1]=1;  m[1][2]=0;			m[1][3]=0;
	m[2][0]=-sin(angulo); m[2][1]=0;  m[2][2]=cos(angulo);  m[2][3]=0;
	m[3][0]=0;			  m[3][1]=0;  m[3][2]=0;			m[3][3]=1;

	return m*(*this);
}

sirMat4d sirMat4d::rotarZ(double angulo)
{
	sirMat4d m;

	m[0][0]=cos(angulo); m[0][1]=-sin(angulo); m[0][2]=0;  m[0][3]=0;
	m[1][0]=sin(angulo); m[1][1]=cos(angulo);  m[1][2]=0;  m[1][3]=0;
	m[2][0]=0;			 m[2][1]=0;			   m[2][2]=1;  m[2][3]=0;
	m[3][0]=0;			 m[3][1]=0;			   m[3][2]=0;  m[3][3]=1;

	return m*(*this);
}

void sirMat4d::trasladar(sirVector3d vec)
{

	v[0][3]+=vec[0];
	v[1][3]+=vec[1];
	v[2][3]+=vec[2];
	v[3][3]=1;

}


/*********************FRAN*********************/

sirMat4d&
sirMat4d::operator *= (const sirMat4d& mat)
{
  #define ROWCOL(i, j) this->operator[](i)[0]*mat[0][j] + this->operator[](i)[1]*mat[1][j] + this->operator[](i)[2]*mat[2][j] + this->operator[](i)[3]*mat[3][j]

  this->operator[](0)[0] = ROWCOL(0,0);
  this->operator[](0)[1] = ROWCOL(0,1);
  this->operator[](0)[2] = ROWCOL(0,2);
  this->operator[](0)[3] = ROWCOL(0,3);
  this->operator[](1)[0] = ROWCOL(1,0);
  this->operator[](1)[1] = ROWCOL(1,1);
  this->operator[](1)[2] = ROWCOL(1,2);
  this->operator[](1)[3] = ROWCOL(1,3);
  this->operator[](2)[0] = ROWCOL(2,0);
  this->operator[](2)[1] = ROWCOL(2,1);
  this->operator[](2)[2] = ROWCOL(2,2);
  this->operator[](2)[3] = ROWCOL(2,3);
  this->operator[](3)[0] = ROWCOL(3,0);
  this->operator[](3)[1] = ROWCOL(3,1);
  this->operator[](3)[2] = ROWCOL(3,2);
  this->operator[](3)[3] = ROWCOL(3,3);

  #undef ROWCOL(i)

  return *this;
}

// FRIENDS

sirMat4d operator - (const sirMat4d& a)
{ return sirMat4d(-a[0], -a[1], -a[2], -a[3]); }

sirMat4d operator + (const sirMat4d& a, const sirMat4d& b)
{ return sirMat4d(a[0] + b[0], a[1] + b[1], a[2] + b[2],
  a[3] + b[3]);
}

sirMat4d operator - (const sirMat4d& a, const sirMat4d& b)
{ return sirMat4d(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]); }

sirMat4d operator * (sirMat4d& a, sirMat4d& b) {
    #define ROWCOL(i, j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + \
    a[i][2]*b[2][j] + a[i][3]*b[3][j]
    return sirMat4d(
    sirVector4d(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
    sirVector4d(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
    sirVector4d(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
    sirVector4d(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3))
    );
    #undef ROWCOL(i)
}

sirMat4d operator * (const sirMat4d& a, const double d)
{ return sirMat4d(a[0] * d, a[1] * d, a[2] * d, a[3] * d); }

sirMat4d operator * (const double d, const sirMat4d& a)
{ return a*d; }

sirMat4d operator / (const sirMat4d& a, const double d)
{ return sirMat4d(a[0] / d, a[1] / d, a[2] / d, a[3] / d); }

int operator == (const sirMat4d& a, const sirMat4d& b)
{ return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) &&
  (a[3] == b[3])); }

int operator != (const sirMat4d& a, const sirMat4d& b)
{ return !(a == b); }

ostream& operator << (ostream& s, const sirMat4d& m)
{ return s << m[VX] << '\n' << m[VY] << '\n' << m[VZ] << '\n' << m[VW]; }

istream& operator >> (istream& s, sirMat4d& m)
{
    sirMat4d    m_tmp;

    s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ] >> m_tmp[VW];
    if (s)
	m = m_tmp;
    return s;
}

void swap(sirMat4d& a, sirMat4d& b)
{ sirMat4d tmp(a); a = b; b = tmp; }


// Necessary friends

sirVector4d operator * (const sirMat4d& a, const sirVector4d& v) {
    #define ROWCOL(i) a[i][0]*v[VX] + a[i][1]*v[VY] \
    + a[i][2]*v[VZ] + a[i][3]*v[VW]
    return sirVector4d(ROWCOL(0), ROWCOL(1), ROWCOL(2), ROWCOL(3));
    #undef ROWCOL(i)
}

sirVector3d operator * (const sirMat4d& a, const sirVector3d& v) {
    #define ROWCOL(i) a[i][0]*v[VX] + a[i][1]*v[VY] \
    + a[i][2]*v[VZ] + a[i][3]
    double w = ROWCOL(3);
    return sirVector3d(ROWCOL(0)/w, ROWCOL(1)/w, ROWCOL(2)/w);
    #undef ROWCOL(i)
}



/****************************************************************
*								*
*	       2D functions and 3D functions			*
*								*
****************************************************************/



/******************************FRAN******************************/

sirVector3d obtenerTranslacion(sirMat4d final,sirMat4d inicial)
{
	sirVector3d trans;

	trans[0]=final[0][3]-inicial[0][3];
	trans[1]=final[1][3]-inicial[1][3];
	trans[2]=final[2][3]-inicial[2][3];

	return trans;
}

sirVector3d obtenerTranslacion(sirVector3d final,sirMat4d inicial)
{
	sirVector3d trans;

	trans[0]=final[0]-inicial[0][3];
	trans[1]=final[1]-inicial[1][3];
	trans[2]=final[2]-inicial[2][3];

	return trans;
}

sirVector3d obtenerTranslacion(sirMat4d final,sirVector3d inicial)
{
	sirVector3d trans;

	trans[0]=final[0][3]-inicial[0];
	trans[1]=final[1][3]-inicial[1];
	trans[2]=final[2][3]-inicial[2];

	return trans;
}

sirVector3d obtenerinterseccion(sirMat4d final,sirMat4d inicial)
{
	sirVector3d trans;

	trans[0]=0;
	trans[1]=final[1][3]-inicial[1][3];
	trans[2]=0;//final[2][3]-inicial[2][3];

	return trans;
}

sirVector3d obtenerinterseccionradio(sirMat4d final,sirMat4d inicial,double restatico,double rdinamico)
{
	sirVector3d trans (0,0,0),aux;

	imprimirMatriz(final);
	imprimirMatriz(inicial);

	trans[0]=final[0][3]-inicial[0][3];
	trans[1]=final[1][3]-inicial[1][3];
	trans[2]=final[2][3]-inicial[2][3];

	aux=trans/trans.norm();

	trans=aux*(trans.norm()-restatico-rdinamico);
	return trans;
}

sirVector3d obtenerinterseccionradio90(sirMat4d final,sirMat4d inicial,double restatico,double rdinamico)
{
	sirVector3d trans;

	if (final[0][3]<inicial[0][3])
	{
		trans[0]=final[0][3]-inicial[0][3]+restatico;
	}
	else
	{
		trans[0]=final[0][3]-inicial[0][3]-restatico;
	}
	trans[1]=rdinamico;
	trans[2]=0;

	return trans;
}

double transformacionLeoCAD(double numero)
{
	//Regla de tres-->CUTRE!!!
	return ((numero*0.96)/24);
}


double distanciaPuntoRecta(double px,double py,double pz,LC_CLICKLINE linea)
{
	//Calculo de la distancia al cuadrado entre un punto y una recta-->Nos ahorramos de hacer la raiz cuadrada
	//Más eficiente que calcular la distancia normal de un punto a una recta, ya que habría que hacer una raiz cuadrada

	//   |PA x dir|     |(vx,vy,vz)|          (vx^2)+(vy^2)+(vz^2)
	// d=---------- --> ------------ --> d^2=----------------------
	//     |dir|        |(dx,dy,dz)|          (dx^2)+(dy^2)+(dz^2)

	double vx,vy,vz; //componentes del producto vectorial
	double dx,dy,dz; //vector director de la recta

	//vector director de la recta!!!!!!!
	dx=linea.a2-linea.a1; //a2-a1;
	dy=linea.b2-linea.b1; //b2-b1;
	dz=linea.c2-linea.c1; //c2-c1;

	vx=((linea.b1-py)*dz)-((linea.c1-pz)*dy);
	vy=((linea.a1-px)*dz)-((linea.c1-pz)*dx);
	vz=((linea.a1-px)*dy)-((linea.b1-py)*dx);

	return ((vx*vx)+(vy*vy)+(vz*vz))/((dx*dx)+(dy*dy)+(dz*dz));
}

bool iguales(double x1,double y1,double z1,double x2,double y2,double z2)
{
	double vx,vy,vz,distancia;

	vx=x1-x2;
	vy=y1-y2;
	vz=z1-z2;

	distancia=(vx*vx)+(vy*vy)+(vz*vz);
	distancia=sqrt(distancia);
	if(distancia<=DELTA_FRAN) return true;
	else return false;
}

bool iguales(double x1,double x2)
{
	double distancia;

	distancia=x1-x2;

	if(distancia<0) distancia=-distancia;

	if(distancia<=DELTA_FRAN) return true;
	else return false;
}

double distanciaPuntos(double xi,double yi,double zi,double xf,double yf,double zf)
{
	sirVector3d v;

	v[0]=xf-xi;
	v[1]=yf-yi;
	v[2]=zf-zi;

	return v.norm();
}


double distanciaMinimaPuntoPuntos(sirVector4d A,sirVector4d B1,sirVector4d B2)
{
	//Podría utilizar la distancia al cuadrado!!!!!!
	double d1,d2;

	d1=distanciaPuntos(A[0],A[1],A[2],B1[0],B1[1],B1[2]);
	d2=distanciaPuntos(A[0],A[1],A[2],B2[0],B2[1],B2[2]);

	if(d1<=d2) return d1;
	else return d2;
}

/******************************FRAN******************************/

sirMat3d identity2D()
{   return sirMat3d(sirVector3d(1.0, 0.0, 0.0),
		sirVector3d(0.0, 1.0, 0.0),
		sirVector3d(0.0, 0.0, 1.0)); }

sirMat3d translation2D(sirVector2d& v)
{   return sirMat3d(sirVector3d(1.0, 0.0, v[VX]),
		sirVector3d(0.0, 1.0, v[VY]),
		sirVector3d(0.0, 0.0, 1.0)); }

sirMat3d rotation2D(sirVector2d& Center, const double angleDeg) {
    double  angleRad = angleDeg * M_PI / 180.0,
	    c = cos(angleRad),
	    s = sin(angleRad);

    return sirMat3d(sirVector3d(c, -s, Center[VX] * (1.0-c) + Center[VY] * s),
		sirVector3d(s, c, Center[VY] * (1.0-c) - Center[VX] * s),
		sirVector3d(0.0, 0.0, 1.0));
}

sirMat3d scaling2D(sirVector2d& scaleVector)
{   return sirMat3d(sirVector3d(scaleVector[VX], 0.0, 0.0),
		sirVector3d(0.0, scaleVector[VY], 0.0),
		sirVector3d(0.0, 0.0, 1.0)); }

sirMat4d identity3D()
{   return sirMat4d(sirVector4d(1.0, 0.0, 0.0, 0.0),
		sirVector4d(0.0, 1.0, 0.0, 0.0),
		sirVector4d(0.0, 0.0, 1.0, 0.0),
		sirVector4d(0.0, 0.0, 0.0, 1.0)); }

sirMat4d translation3D(sirVector3d& v)
{   return sirMat4d(sirVector4d(1.0, 0.0, 0.0, v[VX]),
		sirVector4d(0.0, 1.0, 0.0, v[VY]),
		sirVector4d(0.0, 0.0, 1.0, v[VZ]),
		sirVector4d(0.0, 0.0, 0.0, 1.0)); }

void
translation3D(sirMat4d& mat,  const sirVector3d& v)
{
  mat[0][0] = 1.0;
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = v[VX];
  mat[1][0] = 0.0;
  mat[1][1] = 1.0;
  mat[1][2] = 0.0;
  mat[1][3] = v[VY];
  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = 1.0;
  mat[2][3] = v[VZ];
  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}

sirMat4d rotation3D(sirVector3d& Axis, const double angleDeg) {
    double  angleRad = angleDeg * M_PI / 180.0,
	    c = cos(angleRad),
	    s = sin(angleRad),
	    t = 1.0 - c;

    Axis.normalize();
    return sirMat4d(sirVector4d(t * Axis[VX] * Axis[VX] + c,
		     t * Axis[VX] * Axis[VY] - s * Axis[VZ],
		     t * Axis[VX] * Axis[VZ] + s * Axis[VY],
		     0.0),
		sirVector4d(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
		     t * Axis[VY] * Axis[VY] + c,
		     t * Axis[VY] * Axis[VZ] - s * Axis[VX],
		     0.0),
		sirVector4d(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
		     t * Axis[VY] * Axis[VZ] + s * Axis[VX],
		     t * Axis[VZ] * Axis[VZ] + c,
		     0.0),
		sirVector4d(0.0, 0.0, 0.0, 1.0));
}

void
rotationX3D(sirMat4d& mat, const double angleDeg)
{
  double  angleRad = angleDeg * M_PI / 180.0,
    c = cos(angleRad),
    s = sin(angleRad),
    t = 1.0 - c;

  mat[0][0] = t + c;
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;

  mat[1][0] = 0.0;
  mat[1][1] = c;
  mat[1][2] = -s;
  mat[1][3] = 0.0;

  mat[2][0] = 0.0;
  mat[2][1] = s;
  mat[2][2] = c;
  mat[2][3] = 0.0;

  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}

void
rotationY3D(sirMat4d& mat, const double angleDeg)
{
  double  angleRad = angleDeg * M_PI / 180.0,
    c = cos(angleRad),
    s = sin(angleRad),
    t = 1.0 - c;

  mat[0][0] = c;
  mat[0][1] = 0.0;
  mat[0][2] = s;
  mat[0][3] = 0.0;

  mat[1][0] = 0.0;
  mat[1][1] = t + c;
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;

  mat[2][0] = -s;
  mat[2][1] = 0.0;
  mat[2][2] = c;
  mat[2][3] = 0.0;

  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}

void
rotationZ3D(sirMat4d& mat, const double angleDeg)
{
  double  angleRad = angleDeg * M_PI / 180.0,
    c = cos(angleRad),
    s = sin(angleRad),
    t = 1.0 - c;

  mat[0][0] = c;
  mat[0][1] = -s;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;

  mat[1][0] = s;
  mat[1][1] = c;
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;

  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = t + c;
  mat[2][3] = 0.0;

  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}

sirMat4d scaling3D(sirVector3d& scaleVector)
{   return sirMat4d(sirVector4d(scaleVector[VX], 0.0, 0.0, 0.0),
		sirVector4d(0.0, scaleVector[VY], 0.0, 0.0),
		sirVector4d(0.0, 0.0, scaleVector[VZ], 0.0),
		sirVector4d(0.0, 0.0, 0.0, 1.0)); }

void
scaling3D(sirMat4d& mat, const sirVector3d& v)
{
  mat[0][0] = v[VX];
  mat[0][1] = 0.0;
  mat[0][2] = 0.0;
  mat[0][3] = 0.0;

  mat[1][0] = 0.0;
  mat[1][1] = v[VY];
  mat[1][2] = 0.0;
  mat[1][3] = 0.0;

  mat[2][0] = 0.0;
  mat[2][1] = 0.0;
  mat[2][2] = v[VZ];
  mat[2][3] = 0.0;

  mat[3][0] = 0.0;
  mat[3][1] = 0.0;
  mat[3][2] = 0.0;
  mat[3][3] = 1.0;
}


sirMat4d perspective3D(const double d)
{   return sirMat4d(sirVector4d(1.0, 0.0, 0.0, 0.0),
		sirVector4d(0.0, 1.0, 0.0, 0.0),
		sirVector4d(0.0, 0.0, 1.0, 0.0),
		sirVector4d(0.0, 0.0, 1.0/d, 0.0)); }


// Double versions

sirVector3D&
sirVector3D::reduce(const sirVector4d& v)
{
  vec[0] = v[0];
  vec[1] = v[1];
  vec[2] = v[2];
  return *this;
}

sirVector3D::sirVector3D(const sirVector4d& v)
{
  vec[0] = v[0]/v[3];
  vec[1] = v[1]/v[3];
  vec[2] = v[2]/v[3];
}

sirVector3D&
sirVector3D::operator = (const sirVector4d& v)
{
  vec[0] = v[0]/v[3];
  vec[1] = v[1]/v[3];
  vec[2] = v[2]/v[3];
  return *this;
}

void
sirVector3D::ExtractVerts(double& px, double& py, int which) const
{
  switch (which) {
  case 0:
    px = vec[1];
    py = vec[2];
    break;
  case 1:
    px = vec[0];
    py = vec[2];
    break;
  case 2:
    px = vec[0];
    py = vec[1];
    break;
  }
}

void
sirVector3D::print(unsigned n) const
{
  double base = pow(10, n);
  printf("(%f, %f, %f)", rint(vec[0]*base)/base, rint(vec[1]*base)/base, rint(vec[2]*base)/base);
}

sirVector3D::operator sirVector4d()
{
  return sirVector4d(vec[0], vec[1], vec[2], 1.);
}


void
swap(sirVector3D& a, sirVector3D& b)
{ sirVector3D tmp(a); a = b; b = tmp; }

ostream&
operator << (ostream& s, const sirVector3D& v)
{ return s << "| " << v.X() << ' ' << v.Y() << ' ' << v.Z() << " |"; }

istream&
operator >> (istream& s, sirVector3D& v) {
  /*
    sirVector3D	v_tmp;
    char	c = ' ';

    while (isspace(c))
	s >> c;
    // The vectors can be formatted either as x y or | x y |
    if (c == '|') {
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
      while (s >> c && isspace(c)) ;
      if (c != '|')
	s.set(_bad);
    }
    else {
      s.putback(c);
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
	}
    if (s)
      v = v_tmp;
      */
    return s;
}

sirVector3D
operator - (const sirVector3D& a)
{ return sirVector3D(-a.vec[VX],-a.vec[VY],-a.vec[VZ]); }


sirVector3D&
sirVector3D::operator = (const sirVector3d& v)
{
  vec[0] = v[0];
  vec[1] = v[1];
  vec[2] = v[2];
  return *this;
}

