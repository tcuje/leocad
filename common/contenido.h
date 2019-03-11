/*************************************************/
/*                                               */
/*				  CONTENIDO.H                    */
/*                                               */
/*************************************************/

#ifndef CONTENIDO_H
#define CONTENIDO_H

#include "string.h"

/**
 * Clase Contenido.
 */

class Contenido
{
  private:
	  //Parte privada de la clase
	  char *contenido;

  public:
	 ///Constructor por defecto
	 Contenido();

	 /**
	  * Constructor con parámetros.
	  * @param
	  * @param
	  */
	 Contenido(char *c);

	 /**
	  * Constructor de copia.
	  * @param
	  */
	 Contenido(Contenido &c);

	 ///Destructor de la clase conector.
	 ~Contenido(void);

	 //Sobrecarga de operadores
	 /**
	  * Sobrecarga del operador de igualdad.
	  * @param
	  */
	 bool operator==(Contenido c);

	 /**
	  * Sobrecarga del operador de desigualdad.
	  * @param
	  */

	 bool operator!=(Contenido c);

	 /**
	  * Sobrecarga del operador de asignación.
	  * @param
	  */
	 Contenido& operator=(Contenido &c);

	 //Operaciones de asignar y obtener un elemento del conector
	 /*
	  * Introduce el valor de c en la variable privada contenido.
	  * @param c puntero al contenido.
	  */
	 void introducirContenido(char *c);

	 char *obtenerContenido(void) { return contenido; } /**< Devuelve el valor del contenido. */

};

#endif