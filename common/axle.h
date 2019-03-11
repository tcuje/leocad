/*************************************************/
/*                                               */
/*						AXLE.H		             */
/*                                               */
/*************************************************/

#ifndef AXLE_H
#define AXLE_H

class Piece;
class Conector; //Hace falta;

#include "extreme.h" //Include del que se deriva
#include "cruz.h"
//#include "Algebra3.h"


/**
 * Clase Axle.
 * Deriva de la clase Conector.
 */

class Axle : public Extreme
{
 //Parte privada
 private:
	 /**
	  * Calcula la distanica mínima entre el punto inicial del conector y el (inicial,final) de pCon.
	  * Devuelve min(I-IpCon,I-FpCon).
	  * @param pCon puntero al conector con el que hay que calcular la distancia.
	  */
	 //double distanciaExtremoExtremos(Conector *pCon);

 //Parte pública
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Axle(void) { dibujo=new Cruz(); }

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Axle(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float l,Conector *brother) : Extreme(identificador,nom,rot,pieza,l,brother) { dibujo=new Cruz(); }

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Axle(int identificador,Piece *pieza) : Extreme(identificador,pieza) { dibujo=new Cruz();}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 Axle(Axle &c) : Extreme(c) {}

	 /**
	  * Destructor de la clase Axle.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Axle(void) {}

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Axle& operator=(Axle &c); //Deberia llamar al del EXTREME

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	 virtual void renderizarConector(float r,float g,float b) { renderizarZFuera(r,g,b); }

	 /**
	  * Método que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(sirMat4d W2C);

	 /**
	  * Método que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(void);

	 /**
	  * Devuelve el vector traslación para sumarselo al punto inicial del conector y obtener así el punto final.
	  */
	 virtual sirVector4d obtenerTraslacionLongitud(void);

};

#endif
