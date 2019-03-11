/*************************************************/
/*                                               */
/*					 CIRCULO.H		             */
/*                                               */
/*************************************************/

#ifndef CIRCULO_H
#define CIRCULO_H


#include "simbolo.h"
#include "Algebra3.h"
#include "Matrix.h"

#define RADIO_CIRCULO 0.40
#define ALTURA_CIRCULO 0.16

/**
 * Clase Circulo.
 * Clase derivada de la clase Simbolo.
 */

class Circulo : public Simbolo
{
 private:
	/**
	  * Crea un semic�rculo mediante l�neas desde inf hasta sup.
	  * @param inf
	  * @param sup
	  * @param r
	  * @param g
	  * @param b
	  * @param xant
	  * @param yant
	  */
	 void semiCirculo(int inf,int sup,float r,float g,float b,float *xant,float *yant);

 //Parte p�blica
 public:
	/**
	  * Constructor por defecto.
	  */
	 Circulo(void) {}

	 /**
	  * Destructor de la clase Circulo.
	  * Autom�ticamente se llama al destructor de la clase base Simbolo.
	  */
	 virtual ~Circulo(void) {}

	 /**
	  * Funci�n virtual pura que dibuja una figura geom�trica.
	  * @param matriz es la matriz del mundo a dibujar.
	  * @param red componente roja.
	  * @param green componente verde.
	  * @param blue componente azul.
	  */
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b);
	 virtual void dibujar(sirMat4d matriz,float r,float g,float b,float radio){};
};

#endif