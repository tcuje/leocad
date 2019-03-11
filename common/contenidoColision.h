/*************************************************/
/*                                               */
/*			   CONTENIDOCOLISION.H               */
/*                                               */
/*************************************************/

#ifndef CONTENIDOCOLISION_H
#define CONTENIDOCOLISION_H


class Conector;
//#include "conector.h"


/**
 * Clase ClaveColision.
 */

class ContenidoColision
{
  private:
	  //Parte privada de la clase
	  Conector *pCon;
	  bool final;

  public:
	 ///Constructor por defecto
	 ContenidoColision();

	 /**
	  * Constructor con parámetros.
	  * @param
	  * @param
	  */
	 ContenidoColision(Conector *con,bool fin);

	 /**
	  * Constructor de copia.
	  * @param
	  */
	 ContenidoColision(ContenidoColision &c);

	 ///Destructor de la clase conector.
	 ~ContenidoColision(void);

	 //Sobrecarga de operadores
	 /**
	  * Sobrecarga del operador de igualdad.
	  * @param
	  */
	 bool operator==(ContenidoColision c);

	 /**
	  * Sobrecarga del operador de desigualdad.
	  * @param
	  */

	 bool operator!=(ContenidoColision c);

	 /**
	  * Sobrecarga del operador de asignación.
	  * @param
	  */
	 ContenidoColision& operator=(ContenidoColision &c);

	 //Operaciones de asignar y obtener un elemento del conector
	 /*
	  * Introduce el valor de c en la variable privada contenido.
	  * @param c puntero al contenido.
	  */
	 void introducirConector(Conector *con) { pCon=con; }
	 void introducirFinal(bool fin) { final=fin; }

	 Conector *obtenerConector(void) { return pCon; }
	 bool obtenerFinal(void) { return final; }

};

#endif