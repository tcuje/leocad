/*************************************************/
/*                                               */
/*					 SIMBOLO.H		             */
/*                                               */
/*************************************************/

#ifndef SIMBOLO_H
#define SIMBOLO_H


#include "opengl.h"
#include "Algebra3.h"
#include "Matrix.h"


/**
 * Clase abstracta Simbolo.
 * Clase base de Cuadrado, Circulo y Cruz.
 */

class Simbolo
{
 //Parte pública
 public:
	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Simbolo(void) {}

	 /**
	  * Destructor de la clase Simbolo.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Simbolo(void) {}

	 /**
	  * Función virtual pura que dibuja una figura geométrica.
	  * @param matriz es la matriz del mundo a dibujar.
	  * @param red componente roja.
	  * @param green componente verde.
	  * @param blue componente azul.
	  */
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b)=0;
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b,float radio)=0;
};

#endif
