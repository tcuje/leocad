/*************************************************/
/*                                               */
/*						Worm.H		             */
/*                                               */
/*************************************************/

#ifndef Worm_H
#define Worm_H

class Piece;

#include "gear.h"
#include "matrix.h"
#include "circulo_variable.h"
//#include "Algebra3.h"

/**
 * Clase Worm.
 * Deriva de la clase Gear.
 */

class Worm : public Gear
{
protected:
	bool rotarEjeZ(sirMat4d r);

	double anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m);


 //Parte p�blica
 public:
	 /**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Worm(void) { dibujo=new Circulo_Variable(); }

	 /**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Worm(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float r,int d) : Gear(identificador,nom,rot,pieza,r,d) { dibujo=new Circulo_Variable(); }

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Worm(int identificador,Piece *pieza) : Gear(identificador,pieza) { dibujo=new Circulo_Variable(); }

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 Worm(Worm &c) : Gear(c) {}

	 /**
	  * Destructor de la clase Worm.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Worm(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Worm& operator=(Worm &c); //Deberia llamar al del CONECTOR y a�adir lo del puntero

	 /**
	  * M�todo que permite la comunicaci�n entre un conector y sus conectados.
	  * @param r matriz de rotaci�n a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,int tooth);

	 /**
	  * M�todo que permite la comunicaci�n entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t);

	 virtual bool Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t);



};

#endif
