/*************************************************/
/*                                               */
/*				CIRCULO_VARIABLE.H		         */
/*                                               */
/*************************************************/

#ifndef CIRCULO_VARIABLE_H
#define CIRCULO_VARIABLE_H


#include "simbolo.h"
#include "Algebra3.h"
#include "Matrix.h"

#define RADIO_CIRCULO 0.40
#define ALTURA_CIRCULO 0.16

/**
 * Clase Circulo_Variable.
 * Clase derivada de la clase Simbolo.
 */

class Circulo_Variable : public Simbolo
{
 private:
	/**
	  * Crea un semicírculo mediante líneas desde inf hasta sup.
	  * @param inf
	  * @param sup
	  * @param r
	  * @param g
	  * @param b
	  * @param xant
	  * @param yant
	  */
	 void semiCirculo(int inf,int sup,float r,float g,float b,float *xant,float *yant,float radio);

 //Parte pública
 public:
	/**
	  * Constructor por defecto.
	  */
	 Circulo_Variable(void) {}

	 /**
	  * Destructor de la clase Circulo_Varible.
	  * Automáticamente se llama al destructor de la clase base Simbolo.
	  */
	 virtual ~Circulo_Variable(void) {}

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