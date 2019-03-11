/*************************************************/
/*                                               */
/*					  CRUZ.H		             */
/*                                               */
/*************************************************/

#ifndef CRUZ_H
#define CRUZ_H


#include "simbolo.h"
#include "Algebra3.h"
#include "Matrix.h"

#define DISTANCIA1_CRUZ 0.10
#define DISTANCIA2_CRUZ 0.20

/**
 * Clase Cruz.
 * Clase derivada de la clase Simbolo.
 */

class Cruz : public Simbolo
{
 private:
	  /*
	   * Dibuja una parte de la cruz.
	   * @param r componente roja.
	   * @param g componente verde.
	   * @param b componente azul.
	   * @param altura altura de la cruz a dibujar.
	   */
	  void cruz(float r,float g,float b,float altura);

 //Parte pública
 public:
	/**
	  * Constructor por defecto.
	  */
	 Cruz(void) {}

	 /**
	  * Destructor de la clase Cruz.
	  * Automáticamente se llama al destructor de la clase base Simbolo.
	  */
	 virtual ~Cruz(void) {}

	 /**
	  * Función virtual pura que dibuja una figura geométrica.
	  * @param matriz es la matriz del mundo a dibujar.
	  * @param red componente roja.
	  * @param green componente verde.
	  * @param blue componente azul.
	  */
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b);
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b,float radio){};
};

#endif