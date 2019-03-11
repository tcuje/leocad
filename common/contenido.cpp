/*************************************************/
/*                                               */
/*				  CONTENIDO.CPP                  */
/*                                               */
/*************************************************/

#include "contenido.h"

/*************************************************/

//Constructor por defecto
Contenido::Contenido(void)
{
	contenido=new char[1];
	strcpy(contenido,"");
}

/*************************************************/

//Constructor con parámetros
Contenido::Contenido(char *c)
{
	contenido=new char[strlen(c)+1];
	strcpy(contenido,c);
}

/*************************************************/

//Constructor de copia
Contenido::Contenido(Contenido &c)
{
	contenido=new char[strlen(c.contenido)+1];
	strcpy(contenido,c.contenido);
}

/*************************************************/

//Destructor de la clase
Contenido::~Contenido(void)
{
	delete [] contenido;
}

/*************************************************/

//Operador de assignación
Contenido& Contenido::operator =(Contenido &c)
{
	if(*this!=c)
	{
		delete [] contenido;
		contenido=new char[strlen(c.contenido)+1];
		strcpy(contenido,c.contenido);
	}
	return *this;
}

/*************************************************/

//Sobrecarga de operadores
bool Contenido::operator ==(Contenido c)
{
	if(!strcmp(contenido,c.contenido)) return true;
	else return false;
}

/*************************************************/

bool Contenido::operator !=(Contenido c)
{
	if(!strcmp(contenido,c.contenido)) return false;
	else return true;
}

/*************************************************/

void Contenido::introducirContenido(char *c)
{
	delete [] contenido;
	contenido=new char[strlen(c)+1];
	strcpy(contenido,c);
}

