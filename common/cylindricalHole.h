/*************************************************/
/*                                               */
/*				CYLINDRICALHOLE.H                */
/*                                               */
/*************************************************/

#ifndef CYLINDRICALHOLE_H
#define CYLINDRICALHOLE_H

class Piece;
class Conector; //Hace falta;

#include "extreme.h" //Include del que se deriva
#include "circulo.h"
//#include "Algebra3.h"
#include "globals.h"


/**
 * Clase CylindricalHole.
 * Deriva de la clase Extreme.
 */

class CylindricalHole : public Extreme
{
 //Parte privada
 protected:
	 /**
	  * Devuelve cierto si la traslación está hecha en el eje Z del conector.
	  * @param t vector traslación a aplicar a la pieza del conector.
	  */
	 bool trasladarEjeZ(sirVector3d t);

 //Parte pública
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 CylindricalHole(void) { dibujo=new Circulo(); }

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 CylindricalHole(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float l,Conector *brother) : Extreme(identificador,nom,rot,pieza,l,brother) { dibujo=new Circulo(); }

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 CylindricalHole(int identificador,Piece *pieza) : Extreme(identificador,pieza) { dibujo=new Circulo();}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector.
	  * @param c conector a copiar.
	  */
	 CylindricalHole(CylindricalHole &c) : Extreme(c) {}

	 /**
	  * Destructor de la clase Axle.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~CylindricalHole(void) {}

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 CylindricalHole& operator=(CylindricalHole &c); //Deberia llamar al del EXTREME

	 /**
	  * Redefinimos el método rotar de la clase Conector.
	  * La diferencia está en que si se reota respecto al eje Z del CylindricalHole no se hace nada. Sinó, se llama al método de la clase base Extreme (Conector).
	  * @param r matriz de rotación.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	 */
	 virtual void rotar(sirMat4d r,bool sobreZ/*,unsigned short nTime,bool bAnimation,bool bAddKey*/);

	 /**
	  * Redefinimos el método rotarConector de la clase Conector.
	  * La diferencia está en que si se reota respecto al eje Z del CylindricalHole no se hace nada. Sinó, se llama al método de la clase base Extreme.
	  * @param r matriz de rotación.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	 */
	 virtual void rotarConector(sirMat4d r,bool sobreZ/*,unsigned short nTime,bool bAnimation,bool bAddKey*/);

	 /**
	  * Redefinimos el método mover de la clase Conector.
	  * La diferencia está en que si se traslada en el eje Z del Cylindrical Hole (+-) estamos deslizando, y por lo tanto no propagamos el mover.
	  * @param t vector traslación
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	 virtual void mover(sirVector3d t/*,unsigned short nTime,bool bAnimation,bool bAddKey*/);

	 /**
	  * Redefinimos el método moverConector de la clase Conector.
	  * La diferencia está en que si se traslada en el eje Z del Cylindrical Hole (+-) estamos deslizando, y por lo tanto no propagamos el mover.
	  * @param t vector traslación
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	 virtual void moverConector(sirVector3d t/*,unsigned short nTime,bool bAnimation,bool bAddKey*/);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	 virtual void renderizarConector(float r,float g,float b) { renderizarZDentro(r,g,b); }

	 /**
	  * Calcula la distancia entre (x,y,z) y el centro del conector.
	  * Para los conectores Extreme devuelve la distancia mínima entre (x,y,z) y los dos extremos.
	  * Para los conectores NoExtreme devuelve la distancia mínima entre (x,y,z) y el centro del conector.
	  */
	 //virtual double distanciaConectores(Conector *pCon);

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
	 virtual sirVector4d obtenerTraslacionLongitud(void) { return obtenerTraslacionLongitudZPositivo(); }

};

#endif
