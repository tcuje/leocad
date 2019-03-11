/*************************************************/
/*                                               */
/*						TAG.H                    */
/*                                               */
/*************************************************/

#ifndef TAG_H
#define TAG_H

#include "string.h"
#include "stdlib.h"

/**
 * Clase Tag.
 */

class Tag
{
  private:
	  //Parte privada de la clase
	  char *tag;

	  /*
	   * Devuelve la suma de los valores ASCII de cada uno de los carácteres de una string.
	   * @param c puntero a la cadena de carácteres.
	   */
	  int convertirEntero(char *c);

  public:
	 ///Constructor por defecto
	 Tag();

	 /**
	  * Constructor con parámetros.
	  * @param
	  * @param
	  */
	 Tag(char *t);

	 /**
	  * Constructor de copia.
	  * @param
	  */
	 Tag(Tag &t);

	 ///Destructor de la clase conector.
	 ~Tag(void);

	 //Sobrecarga de operadores
	 /**
	  * Sobrecarga del operador de igualdad.
	  * @param
	  */
	 bool operator==(Tag t);

	 /**
	  * Sobrecarga del operador de desigualdad.
	  * @param
	  */

	 bool operator!=(Tag t);

	 /**
	  * Sobrecarga del operador menor.
	  * @param
	  */
	 bool operator<(Tag t);

	 /**
	  * Sobrecarga del operador mayor.
	  * @param
	  */
	 bool operator>(Tag t);

	 /**
	  * Sobrecarga del operador de asignación.
	  * @param
	  */
	 Tag& operator=(Tag &t);

	 //Operaciones de asignar y obtener un elemento del conector
	 /*
	  * Introduce el valor de t en la variable privada tag.
	  * @param t puntero al tag.
	  */
	 void introducirTag(char *t);

	 char *obtenerTag(void) { return tag; } /**< Devuelve el valor del tag. */

};

#endif