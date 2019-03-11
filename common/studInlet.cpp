/*************************************************/
/*                                               */
/*				STUDINLET.CPP		             */
/*                                               */
/*************************************************/


#include "studInlet.h"
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado
StudInlet& StudInlet::operator=(StudInlet &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}




