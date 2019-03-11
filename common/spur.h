/*************************************************/
/*                                               */
/*						SPUR.H		             */
/*                                               */
/*************************************************/

#ifndef SPUR_H
#define SPUR_H

class Piece;

#include "gear.h"
#include "matrix.h"
#include "circulo_variable.h"
//#include "Algebra3.h"

/**
 * Clase Spur.
 * Deriva de la clase Gear.
 */

class Spur : public Gear
{
protected:
	bool rotarEjeZ(sirMat4d r);

	double anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m);
	sirVector3d obtenermovimiento(float rtooth,sirVector4d vector,Conector *actual);



 //Parte pública
 public:
	 /**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Spur(void) { dibujo=new Circulo_Variable(); }

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Spur(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float r,int d) : Gear(identificador,nom,rot,pieza,r,d) { dibujo=new Circulo_Variable(); }

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Spur(int identificador,Piece *pieza) : Gear(identificador,pieza) { dibujo=new Circulo_Variable(); }

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 Spur(Spur &c) : Gear(c) {}

	 /**
	  * Destructor de la clase Spur.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Spur(void) {}

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Spur& operator=(Spur &c); //Deberia llamar al del CONECTOR y añadir lo del puntero

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,int tooth);

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t);

	 virtual bool Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t);


};

#endif
