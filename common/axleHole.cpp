/*************************************************/
/*                                               */
/*				   AXLEHOLE.CPP		             */
/*                                               */
/*************************************************/


#include "axleHole.h" //Vigilar con la "A"!!!!!
#include "conector.h"
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado
AxleHole& AxleHole::operator=(AxleHole &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Extreme::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}


/*************************************************/

FRAN_SEGMENTO AxleHole::obtenerSegmento(sirMat4d W2C)
{
	//W2C es la matriz del conector al espacio del cual yo quiero pasar el conector actual.

	FRAN_SEGMENTO AB;
	sirMat4d C2W,C2C;
	sirVector4d A(0,0,0,1),B(0,0,longitud,1); //SON PUNTOS Y NO VECTORES!!!

	C2W=obtenerC2W();
	C2C=W2C*C2W;

	A=C2C*A;
	B=C2C*B;

	AB.A=A[2];
	AB.B=B[2];

	return AB;
}

/*************************************************/

FRAN_SEGMENTO AxleHole::obtenerSegmento(void)
{
	FRAN_SEGMENTO AB;

	AB.A=0;
	AB.B=longitud;

	return AB;
}

