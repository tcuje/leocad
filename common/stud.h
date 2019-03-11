/*************************************************/
/*                                               */
/*						STUD.H		             */
/*                                               */
/*************************************************/

#ifndef STUD_H
#define STUD_H

class Piece;

#include "noExtreme.h"
#include "matrix.h"
#include "circulo.h"
//#include "Algebra3.h"

/**
 * Clase Stud.
 * Deriva de la clase NoExtreme.
 */

class Stud : public NoExtreme
{
 //Parte p�blica
 public:
	 /**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Stud(void) { dibujo=new Circulo(); }

	 /**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Stud(int identificador,const char *nom,sirMat4d rot,Piece *pieza) : NoExtreme(identificador,nom,rot,pieza) { dibujo=new Circulo(); }

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Stud(int identificador,Piece *pieza) : NoExtreme(identificador,pieza) { dibujo=new Circulo(); }

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 Stud(Stud &c) : NoExtreme(c) {}

	 /**
	  * Destructor de la clase Stud.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Stud(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Stud& operator=(Stud &c); //Deberia llamar al del CONECTOR y a�adir lo del puntero

	 /**
	  * M�todo que permite la comunicaci�n entre un conector y sus conectados.
	  * @param r matriz de rotaci�n a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,bool sobreZ);

	 /**
	  * M�todo que permite la comunicaci�n entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t);

};

#endif
