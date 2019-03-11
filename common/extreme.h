/*************************************************/
/*                                               */
/*					 EXTREME.H		             */
/*                                               */
/*************************************************/

#ifndef EXTREME_H
#define EXTREME_H

class Piece;

#include "conector.h" //Include del que se deriva
//#include "Algebra3.h"
#include "tag.h"
#include "contenido.h"
#include "diccionario.h"
#include "lista.h"
#include "contenidoColision.h"


#define DISTANCIA_LIBRE 0.002 //Provar empíricamente.
#define MAX_DISTANCIAS 50


typedef struct{
	double distancias[MAX_DISTANCIAS];
	Conector *conectores[MAX_DISTANCIAS];
	int numeroDistancias;
}DISTANCIAS_COLISIONES;


/**
 * Clase Extreme.
 * Deriva de la clase Conector.
 */

class Extreme : public Conector
{
 protected:
	 //Parte protected de la clase
	 float longitud; /**< Longitud del conector en coordenadas LeoCAD. */
	 bool existeHermano; /**< Cierto si tenemos hermano. */
	 bool mensajedeStud; /**< Para saber si el mensaje del rotar recibido por un Cylindrical Hole, ha sifo a través de un Stud, para que rote también. */

	 /**
	  * Es el ID del fichero LCI y no el de la instancia.
	  * Para buscar el conector hermano después de cargar la información.
	  * Con ello conseguimos que pueda estar dentro del fichero en la línea que quiera y no tengan que estar consecutivos.
	  */
	 int idHermanoLCI;
	 int idLCI; /**< El propio id del conector en el fichero LCI. */

	 Conector *hermano; /**<Puntero al hermnao, en caso de tener. */
	 bool deslizando; /**< Nos informa si el conector se está o no deslizando. */

	 /**
	  * Lee los parámetro longitud y extremos de la línea de carácteres.
	  * @param linea string donde se encuentra la información de la longitud y el número de extremos.
	  */
	 void initSegmento(Diccionario d);

	 bool extremoEntreConectados(void); /**< Devuelve cierto si el punt inicial del conector Extremo está entre el segmento que forma alguno de sus conectados. */

	 /**
	  * Devuelve el vector traslación para sumarselo al punto inicial del conector y obtener así el punto final.
	  * Este método es utilizado por AxleHole CylindricalHole porque tiene el vector traslación +LONGITUD.
	  */
	 sirVector4d obtenerTraslacionLongitudZPositivo(void);



 //Parte pública
 public:

	/**
	  * Constructor por defecto.
	  * No hace falta que se implementa nada porque se llama al constructor de la clase base, Conector.
	  */
	 Extreme(void);

	 /**
	  * Constructor con parámetros.
	  * Solo hace falta llamar al constructor de la clase base.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Extreme(int identificador,const char *nom,sirMat4d rot,Piece *pieza,float l,Conector *brother);

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Extreme(int identificador,Piece *pieza) : Conector(identificador,pieza) {}

	 /**
	  * Constructor de copia.
	  * Llamamos al constructor de copia de la clase base Conector + Añadir lo de la propia clase.
	  * @param c conector a copiar.
	  */
	 Extreme(Extreme &c);

	 /**
	  * Destructor de la clase Axle.
	  * Automáticamente se llama al destructor de la clase base Conector.
	  */
	 virtual ~Extreme(void) { hermano=NULL; }

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clase base Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Extreme& operator=(Extreme &c); //Deberia llamar al del CONECTOR

	 /**
	  * Devuelve el vector traslación para sumarselo al punto inicial del conector y obtener así el punto final.
	  */
	 virtual sirVector4d obtenerTraslacionLongitud(void) { sirVector4d V(0,0,0,0); return V; }

	 virtual sirVector4d obtenerPuntoInicial(void); /**< Devuelve el punto inicial del conector en coordenadas de mundo. */
	 virtual sirVector4d obtenerPuntoFinal(void); /**< Devuelve el punto final del conector en coordenadas de mundo. */

	 /**
	  * Método que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(sirMat4d W2C) { FRAN_SEGMENTO AB; AB.A=AB.B=0; return AB; }

	 /**
	  * Método que devuelve el segmento formado por el punto inicial y final del conector en 1D.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(void) { FRAN_SEGMENTO AB; AB.A=AB.B=0; return AB; }

	 /**
	  * Devuelve un puntero al conector hermano en caso de que tenga.
	  * Solo tiene hermanos los Extreme y no todos.
	  */
	 virtual Conector *obtenerHermano(void);

	 /**
	  * Método que devuelve cierto si ninguno de los conectores conectados al conector que llama al método, que es el hermano de otro,
	  * se superponen en el espacio con el conector pasado por parámetro.
	  * @param pCon puntero al conector.
	  */
	 virtual bool segmentoLibreHermano(Conector *pCon);

	 /**
	  * Devuelve cierto si el conector tiene hermano.
	  */
	 virtual bool tengoHermano(void) { return existeHermano; }

	 /**
	  * Introduce al hermano en el caso de los Extreme. Para los NoExtreme no hace nada.
	  * @param c hermano del conector.
	  */
	 virtual void introducirHermano(Conector *c) { hermano=c; }

	 /**
	  * Nos devuelve la longitud libre del conector.
	  */
	 virtual double obtenerLongitudLibre(void);

	 /*
	  * Método que nos informa del estado del conector.
	  * Después de cada assembling hay que preguntar por el estado del conector
	  * para tener actualizadas las listas de conectores libres y ocupados de las madres.
	  */
	 virtual bool libre(void);

	 /*
	  * Función virtual que devulve cierto si el conector está ocupado.
	  */
	 virtual bool ocupado(void);

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t);

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
	 virtual void renderizarConector(float r,float g,float b) {}

	 /**
	  * Método que mira si coinciden los segmentos de los conectores.
	  * @param pCon puntero al conector.
	  */
	 virtual bool coincidencia(Conector *pCon);

	 virtual bool puedeDeslizar(void); /**< Devuelve cierto si el conector está en disposición de deslizarse sobre otro u otros. */

	 virtual void activarModoDeslizar(void) { deslizando=true; } /**< Método que activa el modo de deslizamiento del conector. */
	 virtual void desactivarModoDeslizar(void) { deslizando=false; } /**< Método que desactiva el modo de deslizamiento del conector. */

	 /**
	  * Método que pone al conector en modo deslizamiento, al hermano si lo tiene y llama para que la madre se deslice.
	  * @param t vector de traslación para deslizar la pieza que contiene el conector.
	  */
	 virtual void deslizar(sirVector3d t,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCI(void) { return idLCI; }

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el hermano del conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCIHermano(void) { return idHermanoLCI; }

	 /**
	  * Método que devuelve la distancia mínima a deslizar en caso de encontrar colisiones.
	  * @param direccion es la direccion de deslizamiento-->Z+ o Z-.
	  */
	 virtual DISTANCIA_CONECTOR deteccionColisionesDeslizar(int direccion,sirVector3d t);

	 /**
	  * Método que desconecta al propio conector que lo invoca, de los conectores sobre los que se encuentre deslizándose.
	  */
	 virtual void desconectarDeslizan(void);

	 /**
	  * Método público que nos devuelve la longitud del conector.
	  * Es virtual ya que los conectores de tipo segmento no poseen longitud (0), pero los de tipo segmento si.
	  */
	 virtual float obtenerLongitud(void) { return longitud; }

	 /**
	  * Método que nos sirve para informar que el mensaje que recibimos proviene de un conector de tipo Stud.
	  * Se utiliza para el deslizamiento de conectores de tipo Cylindrical Hole, cuando éstos se encuentran conectados a conectores
	  * de tipo Stud.
	  */
	 virtual void mensajeDeStud() { mensajedeStud=true; }

};

#endif
