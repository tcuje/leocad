/*************************************************/
/*                                               */
/*					 BALL.H 		             */
/*                                               */
/*************************************************/

#ifndef BALL_H
#define BALL_H


#include "simbolo.h"
#include "Algebra3.h"
#include "Matrix.h"

#define RADIO_CIRCULO 0.40
#define RADIO_CIRCULO1 0.35
#define RADIO_CIRCULO2 0.28
#define RADIO_CIRCULO3 0.18
#define ALTURA_CIRCULO 0.16

/**
 * Clase Circulo.
 * Clase derivada de la clase Simbolo.
 */

class Ball : public Simbolo
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
	 void Circulo(int inf,int sup,float r,float g,float b,float *xant,float *yant,float radio,float dis);

 //Parte pública
 public:
	/**
	  * Constructor por defecto.
	  */
	 Ball(void) {}

	 /**
	  * Destructor de la clase Circulo.
	  * Automáticamente se llama al destructor de la clase base Simbolo.
	  */
	 virtual ~Ball(void) {}

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