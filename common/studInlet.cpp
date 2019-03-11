/*************************************************/
/*                                               */
/*				STUDINLET.CPP		             */
/*                                               */
/*************************************************/


#include "studInlet.h"
#include "piece.h"

/*************************************************/

//Operador de asignaci�n sobrecargado
StudInlet& StudInlet::operator=(StudInlet &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignaci�n sobrecargado de la clase Conector
	}
	return *this;
}




