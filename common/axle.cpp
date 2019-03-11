/*************************************************/
/*                                               */
/*					AXLE.CPP		             */
/*                                               */
/*************************************************/


#include "axle.h" //Vigilar con la "A"!!!!!
#include "conector.h" //No se si hace falta!!!
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado
Axle& Axle::operator=(Axle &c)
{

	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Extreme::operator =(c); //Operador de asignación sobrecargado de la clase Extreme
	}
	return *this;
}

/*************************************************/


FRAN_SEGMENTO Axle::obtenerSegmento(sirMat4d W2C)
{
	//W2C es la matriz del conector al espacio del cual yo quiero pasar el conector actual.

	//-LONGITUD

	FRAN_SEGMENTO AB;
	sirMat4d C2W,C2C;
	sirVector4d A(0,0,0,1),B(0,0,-longitud,1); //SON PUNTOS Y NO VECTORES!!!

	C2W=obtenerC2W();
	C2C=W2C*C2W;

	A=C2C*A;
	B=C2C*B;

	AB.A=A[2];
	AB.B=B[2];

	return AB;
}

/*************************************************/

FRAN_SEGMENTO Axle::obtenerSegmento(void)
{
	FRAN_SEGMENTO AB;

	//-LONGITUD

	AB.A=0;
	AB.B=-longitud;

	return AB;
}

/*************************************************/

sirVector4d Axle::obtenerTraslacionLongitud(void)
{
	sirMat4d C2W;
	sirVector4d L(0,0,-longitud,0); //-LONGITUD!!!!!!!!!!

	C2W=obtenerC2W();
	L=C2W*L;

	return L;
}

