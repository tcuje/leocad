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
 //Parte pública
 public:
	 /**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Stud(void) { dibujo=new Circulo(); }

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Stud(int identificador,const char *nom,sirMat4d rot,Piece *pieza) : NoExtreme(identificador,nom,rot,pieza) { dibujo=new Circulo(); }

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
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
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Stud(void) {}

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Stud& operator=(Stud &c); //Deberia llamar al del CONECTOR y añadir lo del puntero

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,bool sobreZ);

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t);

};

#endif
