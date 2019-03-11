/*************************************************/
/*                                               */
/*						MOTOR.H		             */
/*                                               */
/*************************************************/

#ifndef MOTOR_H
#define MOTOR_H

class Piece;
class Conector; //Hace falta;

#include "Axle.h" //Include del que se deriva
#include "cruz.h"
#include "utilidades.h"
//#include "Algebra3.h"


/**
 * Clase Motor.
 * Deriva de la clase Extreme.
 */

class Motor : public Axle
{
 //Parte privada
 private:
	 /**
	  * Calcula la distanica m�nima entre el punto inicial del conector y el (inicial,final) de pCon.
	  * Devuelve min(I-IpCon,I-FpCon).
	  * @param pCon puntero al conector con el que hay que calcular la distancia.
	  */
	 //double distanciaExtremoExtremos(Conector *pCon);

 //Parte p�blica
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Motor(void) { nada(); }

	 /**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Motor(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float l,Conector *brother) : Axle(identificador,nom,rot,pieza,l,brother) { nada();}

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Motor(int identificador,Piece *pieza) : Axle(identificador,pieza) { nada();}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 Motor(Motor &c) : Axle(c) {}

	 /**
	  * Destructor de la clase Axle.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Motor(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Motor& operator=(Motor &c); //Deberia llamar al del AXLE

	 /**
	  * M�todo que permite la comunicaci�n entre un conector y sus conectados.
	  * @param r matriz de rotaci�n a comunicar.
	  */
	 virtual void rotarConector(unsigned short nTime,bool bAnimation,bool bAddKey);


};

#endif
