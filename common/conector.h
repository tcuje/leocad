/*************************************************/
/*                                               */
/*                  CONECTOR.H                   */
/*                                               */
/*************************************************/

/*
 * Clase Conector.
 * Clase base de la cual derivan el resto de conectores: Stud, StudInlet, Axle, AxleHole.
 */

#ifndef CONECTOR_H
#define CONECTOR_H

class Piece;
class File;

#include <string.h>
#include <math.h>
#include "Algebra3.h"
#include "lista.h"
#include "opengl.h"
#include "matrix.h"
#include "tag.h"
#include "contenido.h"
#include "diccionario.h"
#include "simbolo.h"
#include "contenidoColision.h"
#include "globals.h"
#include "utilidades.h"
#include "Administrador.h"


#define FRAN_PI 180 /**< Número PI en grados. */
#define LONGITUD_STUD 0.16 /**< Longitud de un conector de tipo Stud. */
#define MAX_COLISIONES 50 /**< Número máximo de clisiones. */


typedef struct{
	ContenidoColision colisiones[MAX_COLISIONES];
	int numeroColisiones;
}COLISIONES;

typedef struct{
	double distancia;
	Conector *conColision;
}DISTANCIA_CONECTOR;

typedef struct { float A,B; } FRAN_SEGMENTO;

/**
 * Clase base Conector.
 * Clase de la cual derivan el resto de conectores.
 */

class Conector
{
private:


	// Parte protected de la clase.
	// Acesible directamente por las clases derivadas de ésta.
  protected:

	 //static bool obligatorio; //Variable de clase que informa de si es obligatorio o no propagar la traslación/rotación.

	 int id; /**< Identificador único del conector. */
	 char *nombre; /**< Nombre del conector */
	 sirMat4d rotacion; /**< Matriz de transformación 3D-->Coordenadas homogéneas. */
	 Piece *madre; /**< Pieza a la que pertenece el conecto. */
	 Lista<Conector *> conectados; /**< Lista de punteros a los conectores conectados-->Axle,AxleHole(N)/Stud,StudInlet(1) */
	 Simbolo *dibujo;
	 bool visitado; /**< Nos informa si el conector ha sido visitado o no. Se utiliza para saber si un conector ocupa los dos hermanos, y si el hermano está libre. Así el hermano no vuelve allamar al otro hermano. */


	/**
	 * Método que devuelve cirto si la rotación se está realizando en el eje Z del CylindricalHole.
	 * r matriz de rotacion.
	 */
	 bool rotarEjeZ(sirMat4d r);

	/**
	  * Función que calcula el ángulo dado el módulo del producto vectorial y el producto escalar.
	  * opp es el módulo del producto vectorial.
	  * adj es el producto escalar.
	  */
	  double angulo(double opp,double adj);

	  float leerNumero(char *linea,int *ind,int lengh);
	  void leerMatriz(char *linea);
	  void leerNombre(char *linea);

	  /*
	   * Método que crea la matriz de assembling a aplicar al conector dinámico para que las normales de ambos coincidan.
	   * Este método deberá ser implementado por todas las clases derivadas de Conector.
	   * @param dinamico puntero al conector dinamico del assembling.
	   */
//	  sirMat4d coincidirNormales(Conector *dinamico);

	  /*
	   * Inicializa la parte común de todo conector.
	   * @param d diccionario de datos.
	   */
	  //void initConector(Diccionario d);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector con el eje Z hacia dentro del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	  void renderizarZDentro(float r,float g,float b);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector con el eje Z hacia dentro del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  * @param rad es el radio de la circunferencia a renderizar.
	  */
	  void renderizarZDentro(float r,float g,float b,float rad);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector con el eje Z hacia fuera del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	  void renderizarZFuera(float r,float g,float b);

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector con el eje Z hacia fuera del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  * @param rad es el radio de la circunferencia a renderizar.
	  */
	  void renderizarZFuera(float r,float g,float b,float rad);

	  /**
	   * Método común a todos los assemblings.
	   * Rota la pieza para que coincidan las normales de ambos conectores y aplica la traslación correspondiente.
	   * @param dinamico
	   * @param nTime
	   * @param bAnimation
	   * @param bAddKey
	   */
//	  void ensamblarConectores(Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);


	 /**
	  * Actualiza las listas de conectores libres y ocupados de las piezas y la de conectados del conector después del proceso de assembling.
	  * @param dinamico conector dinamico del assembling.
	  */
	 void actualizarListas(Conector *dinamico);

	 //Parte pública de la clase.
  public:
	 ///Constructor por defecto
	 Conector();

	 /**
	  * Devuelve cierto si losdos segmentos son iguales.
	  * @param AB primer segmento.
	  * @param CD segundo segmento.
	  */
	 bool iguales1D(FRAN_SEGMENTO AB,FRAN_SEGMENTO CD);

	 /**
	  * Método que lee los parámetros extras de los conectores Extream y Gear
	  * Estos parámetros pueden ser la longitud y como optativos el idLCI y el idHermanoLCI en caso del que conector tenga hermano
	  * y tambien los parámetros del radio y numero de dientes.
	  * @param d diccionario donde de encuentra la información.
	  * @param t tag que tenemos que buscar.
	  */
	 float leerNumeroParametro(Diccionario d,Tag t);


	 /**
	  * Para detectar los casos |-----|
	  *                               |------|
	  * sin que afecte a casos como |------|
	  *                             |-----------|
	  * por la restricción del ==.
	  * @param AB primer segmento.
	  * @param CD segundo segmento.
	  */
	 bool coincidenUnExtremo(FRAN_SEGMENTO AB,FRAN_SEGMENTO CD);

	 /**
	  * Método que devuelve cierto en el caso de que P esté entre AB.
	  * Se supone que los tres puntos ya están alineados. Antes se comprobó coaxialidad de conectores.
	  * Importante aclarar que todo se hace sobre un eje 1D.
	  * @param P punto que hay que saber si está entre AB.
	  * @param AB segmento.
	  */
	 bool entre1D(float P,FRAN_SEGMENTO AB);

	 /**
	  * Método que devuelve cierto en el caso de que P no esté entre AB.
	  * Se supone que los tres puntos ya están alineados. Antes se comprobó coaxialidad de conectores.
	  * Importante aclarar que todo se hace sobre un eje 1D.
	  * @param P punto que hay que saber si está entre AB.
	  * @param AB segmento.
	  */
	 bool fuera1D(float P,FRAN_SEGMENTO AB);

	 bool inferior1D(float P,FRAN_SEGMENTO AB);
	 bool superior1D(float P,FRAN_SEGMENTO AB);

	 /**
	  * Constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param nom nombre del conector.
	  * @param rot matriz de transformación 3D del conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Conector(int identificador,const char *nom,sirMat4d rot,Piece *pieza);

	 /**
	  * Otro constructor con parámetros.
	  * @param identificador id que permite identificar unívocamente el conector.
	  * @param pieza puntero a la pieza a la que pertenece el conector.
	  */
	 Conector(int identificador,Piece *pieza);

	 /**
	  * Constructor de copia.
	  * @param c conector a copiar.
	  */
	 Conector(Conector &c);

	 //Destructor de la clase conector.
	 virtual ~Conector(void);

	 //Sobrecarga de operadores
	 /**
	  * Sobrecarga del operador de igualdad.
	  * @param c conector a asignar.
	  */
	 bool operator==(Conector c);

	 /**
	  * Sobrecarga del operador de desigualdad.
	  * @param c conector a comparar.
	  */
	 bool operator!=(Conector c);

	 /**
	  * Sobrecarga del operador de asignación.
	  * El operador de asignación no se hereda por las clases derivadas de Conector!!!!!
	  * @param c conector a asignar.
	  */
	 Conector& operator=(Conector &c);

	 virtual sirVector4d obtenerPuntoInicial(void) { sirVector4d v(0,0,0,1); return v; } /**< Devuelve el punto inicial del conector en coordenadas de mundo. */
	 virtual sirVector4d obtenerPuntoFinal(void) { sirVector4d v(0,0,0,1); return v; }  /**< Devuelve el punto final del conector en coordenadas de mundo. */

	 /**
	  * Método que nos devuelve el segmento formado por el conector, en el caso de los Extreme.
	  * @param inv es la matriz del conector respecto a la que hay que transformar el segmento.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(sirMat4d W2C) { FRAN_SEGMENTO AB; AB.A=AB.B=0; return AB; }

	 /**
	  * Método que devuelve el segmento formado por el punto inicial y final del conector en 1D.
	  */
	 virtual FRAN_SEGMENTO obtenerSegmento(void)  { FRAN_SEGMENTO AB; AB.A=AB.B=0; return AB; }

	 /**
	  * Devuelve un puntero al conector hermano en caso de que tenga.
	  * Solo tiene hermanos los Extreme y no todos.
	  */
	 virtual Conector *obtenerHermano(void) { return NULL; }

	 /**
	  * Método que devuelve cierto si ninguno de los conectores conectados al conector que llama al método, que es el hermano de otro,
	  * se superponen en el espacio con el conector pasado por parámetro.
	  * @param pCon puntero al conector.
	  */
	 virtual bool segmentoLibreHermano(Conector *pCon) { return false; }

	 /**
	  * Devuelve cierto si el conector tiene hermano.
	  */
	 virtual bool tengoHermano(void) { return false; }

	 /**
	  * Introduce al hermano en el caso de los Extreme. Para los NoExtreme no hace nada.
	  * @param c hermano del conector.
	  */
	 virtual void introducirHermano(Conector *c) {}

	 //Operaciones de asignar y obtener un elemento del conector
	 /**
	  * Introduce el identificador del conector.
	  * @param identificador id del conector.
	  */
	 void introducirId(int identificador);

	 /**
	  * Introduce el nombre del conector.
	  * @param c nombre del conector.
	  */
	 void introducirNombre(char *c);

	 /**
	  * Introduce la matriz de transformación 3D del conector.
	  * @param rot matriz de transformación 3D.
	  */
	 void introducirRotacion(sirMat4d rot);

	 /**
	  * Introduce el puntero a la pieza a la cual pertenece el conector.
	  * @param p puntero a la pieza del conector.
	  */
	 void introducirMadre(Piece *p);
	 int obtenerId(void); /**< Devulve el identificador del conector. */
	 char *obtenerNombre(void); /**< Devuelve un puntero al nombre del conector. */
	 sirMat4d obtenerRotacion(void); /**< Devuelve la matriz de transformación 3D del conector. */
	 Piece *obtenerMadre(void); /**< Devulve un puntero a la pieza a la que pertence el conector. */

	 sirMat4d obtenerC2W(void); /**< Devuelve la matriz del conector en coordenadas de mundo. */

	 /**
	  * Nos devuelve la longitud libre del conector.
	  */
	 virtual double obtenerLongitudLibre(void) { return 0.0; }

	 /**
	  * Función virtual que devuelve cierto si el conector está libre.
	  * Es diferente par un conector NoExtreme que para uno Extreme.
	  */
	 virtual bool libre(void) { return true; }

	 /**
	  * Función virtual que devulve cierto si el conector está ocupado.
	  * Es diferente par un conector NoExtreme que para uno Extreme.
	  */
	 virtual bool ocupado(void) { return true; }

	 /**
	  * Desconecta a pCon de la lista de conectados.
	  * Puede que haya que actualizar las listas de la madre: ocupado-->libre.
	  * @param pCon puntero del conector a desconectar.
	  */
	 void desconectarConector(Conector *pCon);

	 /**
	  * Desconecta el conector de todos sus conectores conectados.
	  * A la vez actualiza las listas de los conectores que están conectados a sus conectados y se introducirá en la lista de conectores libres de su madre y se borrará de la lista de ocupados.
	  */
	 void desconectar(void);

	 void resetearAssemblingConector(void); /**< Desconecta al conector de todos sus conectados y para cada conectado hace lo mismo.*/
	 void resetearAssembling(void); /**< Llama al método con el mismo nombre de su pieza. */

	 /**
	  * Método que permite la comunicación de la traslación entre una pieza y sus conectores ocupados.
	  * @param t vector de traslación a comunicar.
	  */
	 virtual void mover(sirVector3d t); //Para todo tipo de conector el método mover es el mismo

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param t vector traslacion a comunicar.
	  */
	 virtual void moverConector(sirVector3d t); //Llamar al método mover de todos los conectados

	 /**
	  * Método que permite la comunicación de la rotación entre una pieza y sus conectores ocupados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotar(sirMat4d r,bool sobreZ); //Para todo tipo de conector el método rotar es el mismo

	 /**
	  * Método que permite la comunicación de la rotación entre una pieza y sus conectores ocupados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotar(float rot[4],double rtooth,sirVector3d posicion); //Para todo tipo de conector el método rotar es el mismo

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,bool sobreZ); //Llamar al método rotar de todos los conectados

	 /**
	  * Método que permite la comunicación entre un conector y sus conectados.
	  * @param r matriz de rotación a comunicar.
	  */
	 virtual void rotarConector(sirMat4d r,int tooth){} //Llamar al método rotar de todos los conectados

	 /**
	  * Método que permite la aplicación de las transformaciones después de comunicarlas, en comunicaciones pieza-conector ocupado.
	  * Los parámetros se utilizan para actualizar la estructura de datos de la animación vía keyframing.
	  */
	 void transformar(unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Método que permite la aplicación de las transformaciones después de comunicarlas, en comunicaciones conector-conector conectado.
	  * Los parámetros se utilizan para actualizar la estructura de datos de la animación vía keyframing.
	  */
	 void transformarConector(unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Método que busca lazos y cadenas en el assembling a llevar a cabo.
	  * Este método comunica a una pieza con sus conectores ocupados.
	  * @param final conector final con el que hay que buscar lozos y cadenas.
	  */
	 bool conLazosCadenas(Conector *final);

	 /**
	  * Método que busca lazos y cadenas en el assembling a llevar a cabo.
	  * Este método comunica a un conector con sus conectados.
	  * @param final conector final con el que hay que buscar lozos y cadenas.
	  */
	 bool conLazosCadenasConector(Conector *final);

	 /**
	  * Método que devuelve cierto si existe un camino de assemblings de una pieza a otra que contenga el conector final.
	  * Este método comunica a una determinada pieza con sus conectores ocupados.
	  * @param final conector final del camino.
	  * @param conDeslizados lista de conectores sobre los que el conector se desliza y por lo tanto no deben ser considerados.
	  */
	 bool caminoDeAssemblings(Conector *final,Lista<Conector*> conDeslizados);

	 /**
	  * Método que devuelve cierto si existe un camino de assemblings de una pieza a otra que contenga el conector final.
	  * Este método comunica a un determinado conector con sus conectores conectados.
	  * @param final conector final del camino.
	  * @param conDeslizados lista de conectores sobre los que el conector se desliza y por lo tanto no deben ser considerados.
	  */
	 bool caminoDeAssemblingsConector(Conector *final,Lista<Conector*> conDeslizados);

	 /**
	  * Introducimos un conector a la lista de conectados.
	  * En el caso del STUD / STUDINLET esta lista tiene 1 elemento.
	  * Para AXLE/AXLEHOLE la lista puede tener N elementos.
	  * @param c puntero del conector a introducir.
	  */
	 void introducirConector(Conector *c);
	 void eliminarConector(void); /**< Esborramos el conector conectado actual. */
	 /**
	  * Método que elimina de la lista de conectados el conector "pCon".
	  * @param pCon conector a eliminar.
	  */
	 bool eliminarConector(Conector *pCon);
	 void inicioConectores(void); /**< Nos situámos al principio de la lista de conectores conectados. */
	 void siguienteConector(void); /**< Siguiente conector conectado. */
	 bool finalConectores(void); /**< Cierto si hemos llegado al final de la lista de conectores conectados. */
	 bool vaciaConectores(void); /**< Cierto si la lista de conectores conectados está vacia. */
	 bool existeConector(Conector *pCon); /**< Cierto si existe el conector pCon en la lista de conectados. */
	 Conector *obtenerConector(void); /**< Obtener conector actual. */
	 int numeroConectados(void); /**< Devuelve el número de conectores conectados. */

	 /**
	  * Método que dibuja una figura geométrica alrededor del conector.
	  * @param r componente roja.
	  * @param g componente verde.
	  * @param b componente azul.
	  */
	 virtual void renderizarConector(float r,float g,float b) {}

	 void madreNoVisitada(void); /**< Método que llama al método pertinente de la madre. */
	 void madreNoVisitadaConector(void); /**< Método que llama para cada conector conectado al "madreNoVisitada". */

	 void madreNoVisitada1(void); /**< Método que llama al método pertinente de la madre. */
	 void madreNoVisitadaConector1(void); /**< Método que llama para cada conector conectado al "madreNoVisitada2". */

	 virtual Conector *nuevoClon(void); /**< Devuelve una copia del conector. */

	 /**
	  * Inicializa el conector con la información ecibida del diccionario.
	  * LA listas de conectados no hace falta hacerle nada.
	  * @param d diccionario de datos.
	  */
	 virtual void init(Diccionario d);

	 /**
	  * Calcula la distancia mínima al cuadrado entre el conector y la línea pasada por parámetro.
	  * @param ClickLine es la línea.
	  */
	 double distanciaMinima2(LC_CLICKLINE ClickLine);

	 bool actualizarConectoresLibres(void); /**< Se quita de la lista de conectores libres de la pieza si está ocupado (devuelve cierto). */

	 /**
	  * Método que devuelve la lista de piezas conectadas a las piezas de los conectores conectados.
	  */
	 Lista<Piece*> listaPiezasConectadasConector(void);

	 /**
	  * Método que devuelve la lista de piezas conectadas a la madre del conector.
	  */
	 Lista<Piece*> listaPiezasConectadas(void);

	 virtual bool puedeDeslizar(void) { return false; } /**< Devuelve cierto si el conector está en disposición de deslizarse sobre otro u otros. */

	 virtual void activarModoDeslizar(void) {} /**< Método que activa el modo de deslizamiento del conector. */
	 virtual void desactivarModoDeslizar(void) {} /**< Método que desactiva el modo de deslizamiento del conector. */

	 /**
	  * Método que pone al conector en modo deslizamiento, al hermano si lo tiene y llama para que la madre se deslice.
	  * @param t vector de traslación para deslizar la pieza que contiene el conector.
	  */
	 virtual void deslizar(sirVector3d t,unsigned short nTime,bool bAnimation,bool bAddKey) {}

	 /**
	  * Devuelve cierto si el conector ya ha sido visitado buscando conexiones secundarias.
	  * También se hace servir para el deslizar (detección de colisiones).
	  */
	 bool obtenerVisitado(void) { return visitado; }

	 void conectorVisitado(void) { visitado=true; } /**< Ponemos el flag visitado a cierto. */
	 void conectorNoVisitado(void) { visitado=false; } /**< Ponemos el flag visitado a falso. */

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCI(void) { return -1; }

	 /**
	  * Método que nos devuelve el Id del fichero LCI que tenía el hermano del conector.
	  * Solo se llamará después de llamar si tnegoHermano.
	  */
	 virtual int obtenerIdLCIHermano(void) { return -1; }

	 /**
	  * Calcula la distancia mínima entre los extremos de dos conectores de tipo Extreme.
	  * @param pCon puntero al conector.
	  */
	 double distanciaEntreExtremos(Conector *pCon);

	 double distanciaEntreExtremosHermanos(Conector *pCon);

	 /**
	  * Método que devuelve la EDF con los que están conectados con el conector sobre la dirección de deslizamiento al conector sobre el que se desliza.
	  * @param direccion es la direccion de deslizamiento-->Z+ o Z-.
	  * @param conDeslizar es el puntero al conector que deslizamos.
	  */
	 void conectadosColisionDeslizar(int direccion,Conector *conDeslizar,Lista<Conector*> *conColisiones);

	 /**
	  * Método que devuelve la distancia mínima a deslizar en caso de encontrar colisiones.
	  * @param direccion es la direccion de deslizamiento-->Z+ o Z-.
	  */
	 virtual DISTANCIA_CONECTOR deteccionColisionesDeslizar(int direccion,sirVector3d t) { DISTANCIA_CONECTOR c; return c; }

	 /**
	  * Método que desconecta al propio conector que lo invoca, de los conectores sobre los que se encuentre deslizándose.
	  */
	 virtual void desconectarDeslizan(void) {}

	 /**
	  * Método que devuelve la lista de conectores conectados sobre los que se puede deslizar.
	  */
	 Lista<Conector*> listaConectadosPuedenDeslizar(void);


	 /**
	  * Método público que nos devuelve la longitud del conector.
	  * Es virtual ya que los conectores de tipo segmento no poseen longitud (0), pero los de tipo segmento si.
	  */
	 virtual float obtenerLongitud(void) { return 0.0; }

	 /**
	  * Método que nos sirve para informar que el mensaje que recibimos proviene de un conector de tipo Stud.
	  * Se utiliza para el deslizamiento de conectores de tipo Cylindrical Hole, cuando éstos se encuentran conectados a conectores
	  * de tipo Stud.
	  */
	 virtual void mensajeDeStud() {}

	 virtual float obtenerradio() {return 0.0;}

	 virtual int obtenerNdientes() {return 0;}

	 virtual bool typeGear(){return false;}

	 virtual void rotarConector(unsigned short nTime,bool bAnimation,bool bAddKey){}

};

#endif

