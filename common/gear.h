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
	  * Lee los parámetro radio y numero de dientes del engranaje.
	  * @param linea string donde se encuentra la información de la radio y el número de dientes.
	  */
	 void initGear(Diccionario d);
 private:
	 virtual bool Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t){return false;}

 //Parte pública
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Gear(void);

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Gear(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float r,int d);

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Gear(int identificador,Piece *pieza) : Conector(identificador,pieza) {}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector + Añadir lo de la propia clase.
	  * @param c conector a copiar.
	  */
	 Gear(Gear &c);

	 /**
	  * Destructor de la clase Axle.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Gear(void) {}

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
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
	  * Función virtual que devuelve cierto si el conector está libre.
	  */
	 virtual bool libre(void);

	 /*
	  * Función virtual que devuelve cierto si el conector está ocupado.
	  */
	 virtual bool ocupado(void);

	 /*
	  * Inicializa el conector con la información ecibida del diccionario.
	  * @param d diccionario de datos.
	  */
	 virtual void init(Diccionario d);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector.
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

	 virtual bool puedeDeslizar(void) { return false; } /**< Devuelve cierto si el conector está en disposición de deslizarse sobre otro u otros. */

	 virtual void activarModoDeslizar(void) {} /**< Método que activa el modo de deslizamiento del conector. */
	 virtual void desactivarModoDeslizar(void) {} /**< Método que desactiva el modo de deslizamiento del conector. */

	 /**
	  * Método que pone al conector en modo deslizamiento, al hermano si lo tiene y llama para que la madre se deslice.
	  * @param t vector de traslación para deslizar la pieza que contiene el conector.
	  */
	 virtual void deslizar(sirVector3d t,unsigned short nTime,bool bAnimation,bool bAddKey) {}

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCI(void) { return Conector::obtenerIdLCI(); }

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el hermano del conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCIHermano(void) { return Conector::obtenerIdLCIHermano(); }

	 /**
	  * Método que desconecta al propio conector que lo invoca, de los conectores sobre los que se encuentre deslizándose.
	  */
	 virtual void desconectarDeslizan(void) {}

	 /**
	  * Método público que nos devuelve la longitud del conector.
	  * Es virtual ya que los conectores de tipo segmento no poseen longitud (0), pero los de tipo segmento si.
	  */
	 virtual float obtenerLongitud(void) { return 0.0; }

	 virtual float obtenerradio(void) {return radio;}

	 virtual int obtenerNdientes(void) {return ndientes;}

	 bool espacioLibre(void); /**< Devuelve cierto si existe un punto del conector que sea posible conectar otra gear. */

	 virtual bool typeGear(void){return true;}

	 /**
	  * Función que permite obtener el valor del sinus en una matriz de rotacion.
	  * @param matriz es la matriz de rotacion donde se encuentra el sinus y cosinus.
      */
	 double obtenerSinusRotacion(sirMat4d r,int &fila,int &columna);
	 /*************************************************/

	 virtual bool trasladarEjeZ(Conector *pCon,sirVector3d t);


};

#endif