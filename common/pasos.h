/*************************************************/
/*                                               */
/*                   PASOS.H                     */
/*                                               */
/*************************************************/


#ifndef PASOS_H
#define PASOS_H

#include "listapasos.h"

class Pasos

{
private:
	char conectorA[20];
	char conectorB[20];

	Listapasos *pasv;

	char tipoconexion;

	Listapasos *pas;

public:
	 //Constructor por defecto
	  Pasos();

	 //Destructor por defecto
	  ~Pasos();

	 /**
	  * Sobrecarga del operador de igualdad.
	  * @param c pasos a asignar.
	  */
	  bool operator==(Pasos c);

	 /**
	  * Sobrecarga del operador de desigualdad.
	  * @param c pasos a comparar.
	  */
	  bool operator!=(Pasos c);

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * @param c pasos a asignar.
	  */
	  Pasos& operator=(Pasos &p);

	 /**
	  * M�todo que obtendremos el nombre del conector A.
	  * @param a cadena que obtine el nombre del conectorA.
	  */
	  void obtenerconectorA(char a[]);

	 /**
	  * M�todo que obtendremos el nombre del conector B.
	  * @param a cadena que obtine el nombre del conectorB.
	  */
	  void obtenerconectorB(char a[]);

	 /**
	  * Funci�n que devuelve si los pasos son de tipo c=conexion o v=verificaci�n.
	  */
	  char obtenertipoconexion();

	 /**
	  * Funci�n que obtendremos el paso actual de la lista de pasos.
	  */
	  char obtenerPasos();

	 /**
	  * M�todo que se coloca en el primer elemento de la lista de pasos.
	  */
	  void PrimerPasos();

	 /**
	  * M�todo que va al siguiente pasos de la lista.
	  */
	  void SiguientePasos();

	 /**
	  * Funci�n que devulve cierto si no existen mas pasos en esta lista.
	  */
	  bool FinPasos();

	 /**
	  * M�todo que eliminara todos los pasos de la lista.
	  */
	  void EliminarPasos();

	 /**
	  * M�todo que introducira un paso a la lista.
	  * @param paso es el paso a realizar el assembling.
	  */
	  void IntroducirPasos(char paso);

	  	 /**
	  * Funci�n que obtendremos el paso actual de la lista de pasos.
	  */
	  char obtenerPasosV();

	 /**
	  * M�todo que se coloca en el primer elemento de la lista de pasos.
	  */
	  void PrimerPasosV();

	 /**
	  * M�todo que va al siguiente pasos de la lista.
	  */
	  void SiguientePasosV();

	 /**
	  * Funci�n que devulve cierto si no existen mas pasos en esta lista.
	  */
	  bool FinPasosV();

	 /**
	  * M�todo que eliminara todos los pasos de la lista.
	  */
	  void EliminarPasosV();


	 /**
	  * M�todo que introducira un paso a la lista.
	  * @param paso es el paso a realizar para verificar.
	  */
	  void IntroducirPasosV(char paso);

	 /**
	  * M�todo que introduce la infomarcion en los valores de la clase pasos.
	  * @param conA cadena donde contendra el conectorA.
	  * @param conB cadena donde contendra el conectorB.
	  * @param tipo es el caracter para saber si es de tipo conexion o verificaci�n.
	  */
	  void IntroducirConectores(char conA[],char conB[],char tipo);

	 /**
	  * M�todo que introduce la infomarcion en los valores de la clase pasos.
	  * @param conA cadena donde contendra el conectorA.
	  * @param conB cadena donde contendra el conectorB.
	  * @param tipo es el caracter para saber si es de tipo conexion o verificaci�n.
	  */
	  void IntroducirConectores(char conA[],char conB[]);


};

#endif
