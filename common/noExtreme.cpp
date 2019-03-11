/*************************************************/
/*                                               */
/*				   NOEXTREME.CPP	             */
/*                                               */
/*************************************************/


#include "noExtreme.h"
#include "piece.h"


/*************************************************/

//Operador de asignación sobrecargado no se hereda
NoExtreme& NoExtreme::operator=(NoExtreme &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}

/*************************************************/

bool NoExtreme::libre(void)
{
	if(conectados.NElementos()==0) return true;
	else return false; //==1-->Stud ocupado
}

/*************************************************/

bool NoExtreme::ocupado()
{
	return (!libre());
}

/*************************************************/

FRAN_SEGMENTO NoExtreme::obtenerSegmento(void)
{
	//YA TIENE LA Z PARA FUERA LOS NoExtreme!!!

	FRAN_SEGMENTO AB;

	AB.A=0;
	AB.B=(float)LONGITUD_STUD;

	return AB;
}

/*************************************************/

FRAN_SEGMENTO NoExtreme::obtenerSegmento(sirMat4d W2C)
{
	//YA TIENE LA Z PARA FUERA LOS NoExtreme!!!

	FRAN_SEGMENTO AB;
	sirMat4d C2W,C2C;
	sirVector4d A(0,0,0,1),B(0,0,LONGITUD_STUD,1); //SON PUNTOS NO VECTORES!!!

	C2W=obtenerC2W();
	C2C=W2C*C2W;

	A=C2C*A;
	B=C2C*B;

	AB.A=(float)A[2];
	AB.B=(float)B[2];

	return AB;
}

/*************************************************/

sirVector4d NoExtreme::obtenerPuntoInicial(void)
{
	sirMat4d C2W;
	sirVector4d v(0,0,0,1);

	C2W=obtenerC2W();

	v[0]=C2W[0][3];
	v[1]=C2W[1][3];
	v[2]=C2W[2][3];

	return v;
}

/*************************************************/

sirVector4d NoExtreme::obtenerPuntoFinal(void)
{
	sirMat4d C2W;
	sirVector4d v1(0,0,0,1),v2(0,0,LONGITUD_STUD,0);

	C2W=obtenerC2W();

	//v1->PUNTO!!!
	//v2->VECTOR TRASLACIÓN!!!

	v1[0]=C2W[0][3];
	v1[1]=C2W[1][3];
	v1[2]=C2W[2][3];

	v2=C2W*v2;

	v1[0]=v1[0]+v2[0];
	v1[1]=v1[1]+v2[1];
	v1[2]=v1[2]+v2[2];

	return v1;
}

