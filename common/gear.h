/*************************************************/
/*                                               */
/*					  GEAR.H	  	             */
/*                                               */
/*************************************************/

#ifndef GEAR_H
#define GEAR_H

class Piece;

#include "conector.h" //Include del que se deriva
//#include "Algebra3.h"
#include "tag.h"
#include "contenido.h"
#include "diccionario.h"


/**
 * Clase Gear.
 * Deriva de la clase Conector.
 */

class Gear : public Conector
{

 protected:
	  float radio; /**< Longitud del radio del engranaje del conector en coordenadas LeoCAD. */
	  int ndientes; /**< Numero de dientes pertenecientes al engranaje */

	 /**
	  * Lee los par�metro radio y numero de dientes del engranaje.
	  * @param linea string donde se encuentra la informaci�n de la radio y el n�mero de dientes.
	  */
	 void initGear(Diccionario d);
 private:
	 virtual bool Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t){return false;}

 //Parte p�blica
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Gear(void);

	 /**
	  * Constructor con par�metros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformaci�n 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Gear(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float r,int d);

	 /**
	  * Otro constructor con par�metros.
	  * @param identificador id que permite identificar un�vocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Gear(int identificador,Piece *pieza) : Conector(identificador,pieza) {}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector + A�adir lo de la propia clase.
	  * @param c conector a copiar.
	  */
	 Gear(Gear &c);

	 /**
	  * Destructor de la clase Axle.
	  * Autom�ticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Gear(void) {}

	 /**
	  * Sobrecarga del operador de asignaci�n.
	  * El operador de asignaci�n no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Gear& operator=(Gear &c); //Deberia llamar al del CONECTOR

	 /**
	  * Devuelve cierto si el conector tiene hermano.
	  */
	 virtual bool tengoHermano(void) { return false; }

	 /**
	  * Introduce al hermano en el caso de los Extreme. Para los Gear no hace nada.
	  * @param c hermano del conector.
	  */
	 virtual void introducirHermano(Conector *c) {}

	 virtual sirVector4d obtenerPuntoInicial(void); /**< Devuelve el punto inicial del conector en coordenadas de mundo. */
	 virtual sirVector4d obtenerPuntoFinal(void); /**< Devuelve el punto final del conector en coordenadas de mundo. */

	 /**
	  * Nos devuelve la longitud libre del conector.
	  */
	 virtual double obtenerLongitudLibre(void) { return LONGITUD_STUD; }

	/**
	  * Funci�n virtual que devuelve cierto si el conector est� libre.
	  */
	 virtual bool libre(void);

	 /*
	  * Funci�n virtual que devuelve cierto si el conector est� ocupado.
	  */
	 virtual bool ocupado(void);

	 /*
	  * Inicializa el conector con la informaci�n ecibida del diccionario.
	  * @param d diccionario de datos.
	  */
	 virtual void init(Diccionario d);

	 /**
	  * M�todo que dibuja una figura geom�trica alrededor del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	 virtual void renderizarConector(float r,float g,float b) { renderizarZDentro(r,g,b,radio); }

	 /**
	  * Devuelve un puntero al conector hermano en caso de que tenga.
	  * Solo tiene hermanos los Extreme y no todos.
	  */
	 virtual Conector *obtenerHermano(void) { return NULL; }

	 virtual bool puedeDeslizar(void) { return false; } /**< Devuelve cierto si el conector est� en disposici�n de deslizarse sobre otro u otros. */

	 virtual void activarModoDeslizar(void) {} /**< M�todo que activa el modo de deslizamiento del conector. */
	 virtual void desactivarModoDeslizar(void) {} /**< M�todo que desactiva el modo de deslizamiento del conector. */

	 /**
	  * M�todo que pone al conector en modo deslizamiento, al hermano si lo tiene y llama para que la madre se deslice.
	  * @param t vector de traslaci�n para deslizar la pieza que contiene el conector.
	  */
	 virtual void deslizar(sirVector3d t,unsigned short nTime,bool bAnimation,bool bAddKey) {}

	 /**
	  * M�todo que nos devuelve el Id del fichero LCI que ten�a el conector.
	  * Solo se llamar� despu�s de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCI(void) { return Conector::obtenerIdLCI(); }

	 /**
	  * M�todo que nos devuelve el Id del fichero LCI que ten�a el hermano del conector.
	  * Solo se llamar� despu�s de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCIHermano(void) { return Conector::obtenerIdLCIHermano(); }

	 /**
	  * M�todo que desconecta al propio conector que lo invoca, de los conectores sobre los que se encuentre desliz�ndose.
	  */
	 virtual void desconectarDeslizan(void) {}

	 /**
	  * M�todo p�blico que nos devuelve la longitud del conector.
	  * Es virtual ya que los conectores de tipo segmento no poseen longitud (0), pero los de tipo segmento si.
	  */
	 virtual float obtenerLongitud(void) { return 0.0; }

	 virtual float obtenerradio(void) {return radio;}

	 virtual int obtenerNdientes(void) {return ndientes;}

	 bool espacioLibre(void); /**< Devuelve cierto si existe un punto del conector que sea posible conectar otra gear. */

	 virtual bool typeGear(void){return true;}

	 /**
	  * Funci�n que permite obtener el valor del sinus en una matriz de rotacion.
	  * @param matriz es la matriz de rotacion donde se encuentra el sinus y cosinus.
      */
	 double obtenerSinusRotacion(sirMat4d r,int &fila,int &columna);
	 /*************************************************/

	 virtual bool trasladarEjeZ(Conector *pCon,sirVector3d t);


};

#endif