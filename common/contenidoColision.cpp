/*************************************************/
/*                                               */
/*			  CONTENIDOCOLISION.CPP              */
/*                                               */
/*************************************************/

#include "contenidoColision.h"
#include "conector.h"

/*************************************************/

//Constructor por defecto
ContenidoColision::ContenidoColision(void)
{
	pCon=NULL; //No hay que guardar espacio porque nos darán una referencia a un conector con espacio ya reservado.
	final=false; //Por defecto conectores con hermanos.
}

/*************************************************/

//Constructor con parámetros
ContenidoColision::ContenidoColision(Conector *con,bool fin)
{
	pCon=con;
	final=fin;
}

/*************************************************/

//Constructor de copia
ContenidoColision::ContenidoColision(ContenidoColision &c)
{
	Conector *con;

	con=c.obtenerConector();
	pCon=con->nuevoClon(); //Poner bién el NUEVO CLON en CONECTORE..etc.

	final=c.final;
}

/*************************************************/

//Destructor de la clase
ContenidoColision::~ContenidoColision(void)
{
	pCon=NULL; //No puedo hacer un delete porque borraria un conector que me han pasado y que se puede seguir utilizando.
}

/*************************************************/

//Operador de assignación
ContenidoColision& ContenidoColision::operator =(ContenidoColision &c)
{
	Conector *con;

	if(*this!=c)
	{
		pCon=NULL;
		con=c.obtenerConector();
		pCon=con->nuevoClon();
		final=c.final;
	}
	return *this;
}

/*************************************************/

//Sobrecarga de operadores
bool ContenidoColision::operator ==(ContenidoColision c)
{
	Conector *con;

	con=c.obtenerConector();
	if(pCon==con && final==c.final) return true;
	else return false;
}

/*************************************************/

bool ContenidoColision::operator !=(ContenidoColision c)
{
	if((*this)==c) return false;
	else return true;
}

