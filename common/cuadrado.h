/*************************************************/
/*                                               */
/*					CUADRADO.H		             */
/*                                               */
/*************************************************/

#ifndef CUADRADO_H
#define CUADRADO_H


#include "simbolo.h"
#include "Algebra3.h"
#include "Matrix.h"


#define ANCHURA_CUADRADO 0.50
#define ALTURA_CUADRADO 0.16

/**
 * Clase Cuadrado.
 * Clase derivada de la clase Simbolo.
 */

class Cuadrado : public Simbolo
{
 private:
	  /**
	   * Dibuja un lado del cuadrado.
	   * @param r componente roja del color.
	   * @param g componenete verde del color.
	   * @param b componente amarilla del color.
	   */
	 void lado(float r,float g,float b);

	 /**
	   * Dibuja un lado del cuadrado.
	   * @param r componente roja del color.
	   * @param g componenete verde del color.
	   * @param b componente amarilla del color.ç
	   * @param radio longitud de un rack
	   */
	 void lado(float r,float g,float b,float radio);

	 /**
	   * Dibuja un lado del cuadrado.
	   * @param r componente roja del color.
	   * @param g componenete verde del color.
	   * @param b componente amarilla del color.ç
	   * @param radio longitud de un rack
	   */
	 void ladoc(float r,float g,float b,float radio);



 //Parte pública
 public:
	/**
	  * Constructor por defecto.
	  */
	 Cuadrado(void) {}

	 /**
	  * Destructor de la clase Cuadrado.
	  * Automáticamente se llama al destructor de la clase base Simbolo.
	  */
	 virtual ~Cuadrado(void) {}

	 /**
	  * Función virtual pura que dibuja una figura geométrica.
	  * @param matriz es la matriz del mundo a dibujar.
	  * @param red componente roja.
	  * @param green componente verde.
	  * @param blue componente azul.
	  */
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b);
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b,float radio);
};

#endif