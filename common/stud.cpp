/*************************************************/
/*                                               */
/*					STUD.CPP		             */
/*                                               */
/*************************************************/


#include "stud.h"
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado (No se hereda!!!)
Stud& Stud::operator=(Stud &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}


/*************************************************/

//Redefinimos el método rotarConector de la clase conector para el Stud.
void Stud::rotarConector(sirMat4d r,bool sobreZ/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	//Si rotamos respecto al eje Z del CH entonces no lo propagamos a los conectados del CylindricalHole!!!
	//Si rotamos respecto a otro eje, entonces llamamos al rotar del conector.

	Conector *actual;

	if(obligatorio) NoExtreme::rotarConector(r,sobreZ);
	else
	{
		conectados.Primero();
		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			actual->mensajeDeStud();
			actual->rotar(r,sobreZ);
			conectados.Siguiente();
		}
	}

	actual=NULL;
}

/*************************************************/

void Stud::moverConector(sirVector3d t)
{
	Conector *actual;

	/******************************/
	recalcularConexiones=true;
	/******************************/

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		actual->mensajeDeStud();
		actual->mover(t);
		conectados.Siguiente();
	}
}