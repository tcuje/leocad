/*************************************************/
/*                                               */
/*					AXLEHOLE.H		             */
/*                                               */
/*************************************************/

#ifndef AXLE_HOLE_H
#define AXLE_HOLE_H

class Piece; //->Hay que incluirla si ya la tiene la clase CONECTOR-->Creo que NOOOOOO!!!!!!
class Conector;

#include "extreme.h" //Include del que se deriva
#include "cruz.h"
//#include "Algebra3.h"

/**
 * Clase AxleHole.
 * Deriva de la clase Conector.
 */

class AxleHole : public Extreme
{
 //Parte p�blica
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 AxleHole(void) { dibujo=new Cruz(); }

	 /**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 AxleHole(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float l,Conector *brother) : Extreme(identificador,nom,rot,pieza,l,brother) { dibujo=new Cruz(); }

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 AxleHole(int identificador,Piece *pieza) : Extreme(identificador,pieza) { dibujo=new Cruz(); }

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 AxleHole(AxleHole &c) : Extreme(c) {}

	 /**
	  * Destructor de la clase AxleHole.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~AxleHole(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 AxleHole& operator=(AxleHole &c); //Deberia llamar al del EXTREME

	 /**
	  * M�todo que dibuja una figura geom�trica alrededor del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	 virtual void renderizarConector(float r,float g,float b) { renderizarZDentro(r,g,b); }

	 /**
	  * M�todo que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(sirMat4d W2C);

	 /**
	  * M�todo que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(void);

	 /**
	  * Devuelve el vector traslaci�n para sumarselo al punto inicial del conector y obtener as� el punto final.
	  */
	 virtual sirVector4d obtenerTraslacionLongitud(void)  { return obtenerTraslacionLongitudZPositivo(); }

};

#endif
