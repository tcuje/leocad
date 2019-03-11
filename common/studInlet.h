/*************************************************/
/*                                               */
/*					STUDINLET.H		             */
/*                                               */
/*************************************************/

#ifndef STUD_INLET_H
#define STUD_INLET_H


class Piece;

#include "noExtreme.h"
#include "cuadrado.h"
//#include "Algebra3.h"

/**
 * Clase StudInlet.
 * Deriva de la clase NoExtreme.
 */

class StudInlet : public NoExtreme
{
 //Parte p�blica
 public:
	 /**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 StudInlet(void) { dibujo=new Cuadrado(); }
	/**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 StudInlet(int identificador,const char *nom,sirMat4d rot,Piece *pieza) : NoExtreme(identificador,nom,rot,pieza) { dibujo=new Cuadrado(); }

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 StudInlet(int identificador,Piece *pieza) : NoExtreme(identificador,pieza) { dibujo=new Cuadrado(); }

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 StudInlet(StudInlet &c) : NoExtreme(c) {}

	 /**
	  * Destructor de la clase StudInlet.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~StudInlet(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 StudInlet& operator=(StudInlet &c);

};

#endif
