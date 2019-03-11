/*************************************************/
/*                                               */
/*                  PASOS.CPP                    */
/*                                               */
/*************************************************/


#include "pasos.h"
#include <string.h>
#include <afxwin.h>
#include "lista.h"


/*************************************************/
//Constructor por defecto
Pasos::Pasos(void)
{
	pas=new Listapasos();
	pasv=new Listapasos();
}

/*************************************************/
Pasos::~Pasos(void)
{
	pas=NULL;
	pasv=NULL;
}


/*************************************************/
void Pasos::IntroducirConectores(char conA[],char conB[],char tipo)
{
	strcpy(conectorA,conA);
	strcpy(conectorB,conB);
	tipoconexion=tipo;
}

/*************************************************/
void Pasos::IntroducirConectores(char conA[],char conB[])
{
	strcpy(conectorA,conA);
	strcpy(conectorB,conB);
}

/*************************************************/
//Sobrecarga de operadores

bool Pasos::operator==(Pasos c)
{
	return (strcmp(conectorA,c.conectorA)==0 && strcmp(conectorB,c.conectorB)==0 && tipoconexion==c.tipoconexion);

}

/*************************************************/

bool Pasos::operator!=(Pasos c)
{
	return (strcmp(conectorA,c.conectorA)!=0 && strcmp(conectorB,c.conectorB)!=0);
}

/*************************************************/
void Pasos::obtenerconectorA(char a[])
{
	strcpy(a,conectorA);

}

/*************************************************/
void Pasos::obtenerconectorB(char a[])
{
	strcpy(a,conectorB);
}

/*************************************************/
char Pasos::obtenertipoconexion()
{
	return tipoconexion;
}


/*************************************************/
void Pasos::IntroducirPasos(char paso)
{
	pas->Introducir(paso);
}

/*************************************************/
void Pasos::IntroducirPasosV(char paso)
{
	pasv->Introducir(paso);
}

/*************************************************/
char Pasos::obtenerPasos(void)
{
	return pas->Actual();
}

/*************************************************/
void Pasos::PrimerPasos()
{
	pas->Primero();
}

/*************************************************/
void Pasos::SiguientePasos()
{
	pas->Siguiente();
}

/*************************************************/
bool Pasos::FinPasos()
{
	return pas->Fin();
}

/*************************************************/
void Pasos::EliminarPasos()
{
	pas->borrartodo();
	delete pas;
}

/*************************************************/
char Pasos::obtenerPasosV(void)
{
	return pasv->Actual();
}

/*************************************************/
void Pasos::PrimerPasosV()
{
	pasv->Primero();
}

/*************************************************/
void Pasos::SiguientePasosV()
{
	pasv->Siguiente();
}

/*************************************************/
bool Pasos::FinPasosV()
{
	return pasv->Fin();
}

/*************************************************/
void Pasos::EliminarPasosV()
{
	pasv->borrartodo();
	delete pasv;
}

/*************************************************/
//Operador de asignación sobrecargado
Pasos& Pasos::operator=(Pasos &p)
{

	//Si los objectos son diferentes...
	if(*this!=p)
	{
		strcpy(conectorA,p.conectorA);
		strcpy(conectorB,p.conectorB);
		tipoconexion=p.tipoconexion;
		pas=p.pas;
		pasv=p.pasv;

	}
	return *this;
}


