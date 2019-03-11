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
	  * Sobrecarga del operador de asignación.
	  * @param c pasos a asignar.
	  */
	  Pasos& operator=(Pasos &p);

	 /**
	  * Método que obtendremos el nombre del conector A.
	  * @param a cadena que obtine el nombre del conectorA.
	  */
	  void obtenerconectorA(char a[]);

	 /**
	  * Método que obtendremos el nombre del conector B.
	  * @param a cadena que obtine el nombre del conectorB.
	  */
	  void obtenerconectorB(char a[]);

	 /**
	  * Función que devuelve si los pasos son de tipo c=conexion o v=verificación.
	  */
	  char obtenertipoconexion();

	 /**
	  * Función que obtendremos el paso actual de la lista de pasos.
	  */
	  char obtenerPasos();

	 /**
	  * Método que se coloca en el primer elemento de la lista de pasos.
	  */
	  void PrimerPasos();

	 /**
	  * Método que va al siguiente pasos de la lista.
	  */
	  void SiguientePasos();

	 /**
	  * Función que devulve cierto si no existen mas pasos en esta lista.
	  */
	  bool FinPasos();

	 /**
	  * Método que eliminara todos los pasos de la lista.
	  */
	  void EliminarPasos();

	 /**
	  * Método que introducira un paso a la lista.
	  * @param paso es el paso a realizar el assembling.
	  */
	  void IntroducirPasos(char paso);

	  	 /**
	  * Función que obtendremos el paso actual de la lista de pasos.
	  */
	  char obtenerPasosV();

	 /**
	  * Método que se coloca en el primer elemento de la lista de pasos.
	  */
	  void PrimerPasosV();

	 /**
	  * Método que va al siguiente pasos de la lista.
	  */
	  void SiguientePasosV();

	 /**
	  * Función que devulve cierto si no existen mas pasos en esta lista.
	  */
	  bool FinPasosV();

	 /**
	  * Método que eliminara todos los pasos de la lista.
	  */
	  void EliminarPasosV();


	 /**
	  * Método que introducira un paso a la lista.
	  * @param paso es el paso a realizar para verificar.
	  */
	  void IntroducirPasosV(char paso);

	 /**
	  * Método que introduce la infomarcion en los valores de la clase pasos.
	  * @param conA cadena donde contendra el conectorA.
	  * @param conB cadena donde contendra el conectorB.
	  * @param tipo es el caracter para saber si es de tipo conexion o verificación.
	  */
	  void IntroducirConectores(char conA[],char conB[],char tipo);

	 /**
	  * Método que introduce la infomarcion en los valores de la clase pasos.
	  * @param conA cadena donde contendra el conectorA.
	  * @param conB cadena donde contendra el conectorB.
	  * @param tipo es el caracter para saber si es de tipo conexion o verificación.
	  */
	  void IntroducirConectores(char conA[],char conB[]);


};

#endif
