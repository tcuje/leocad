//
//	piece.h
////////////////////////////////////////////////////

#ifndef _PIECE_H_
#define _PIECE_H_

class File;
class Piece;
class Group;
class PieceInfo;
/********FRAN*********/
class Conector;
class Stud;
class StudInlet;
class Extreme;
class Axle;
class AxleHole;
class CylindricalHole;
class Administrador;
//class Sphere;
/*********************/


#include "object.h"
#include "globals.h"
#include "typedefs.h"
#include "defines.h"
/********FRAN*********/
#include <fstream.h>
#include "lista.h"
//#include "listaPieza.h"
#include "listaConector.h"
#include "tag.h"
#include "contenido.h"
#include "diccionario.h"
#include "Algebra3.h"
/*********************/

#define LC_PIECE_HIDDEN		0x01
#define LC_PIECE_SELECTED	0x02
#define LC_PIECE_FOCUSED	0x04

typedef enum {
  LC_PK_POSITION,
  LC_PK_ROTATION,
  LC_PK_COUNT
} LC_PK_TYPES;

class Piece : public Object
{
public:
  Piece (PieceInfo* pPieceInfo);
  ~Piece ();

  void Select (bool bSelecting, bool bFocus, bool bMultiple);
  virtual void InsertTime (unsigned short start, bool animation, unsigned short time);
  virtual void RemoveTime (unsigned short start, bool animation, unsigned short time);





	Piece* m_pNext;
	Piece* m_pLink;

	void Hide()
		{ m_nState = LC_PIECE_HIDDEN; }
	void UnHide()
		{ m_nState &= ~LC_PIECE_HIDDEN; }
	bool IsHidden()
		{ return (m_nState & LC_PIECE_HIDDEN) != 0; }
	bool IsSelected()
		{ return (m_nState & LC_PIECE_SELECTED) != 0; }
	bool IsFocused()
		{ return (m_nState & LC_PIECE_FOCUSED) != 0; }

	void MinIntersectDist(LC_CLICKLINE* pLine);
	bool IsVisible(unsigned short nTime, bool bAnimation);
	void Initialize(float x, float y, float z, unsigned char nStep, unsigned short nFrame, unsigned char nColor);
	void Initialize(float x, float y, float z, float *r, unsigned char nStep, unsigned short nFrame, unsigned char nColor);
	void CreateName(Piece* pPiece);
	void AddConnections(CONNECTION_TYPE* pConnections);
	void RemoveConnections(CONNECTION_TYPE* pConnections);
	void CompareBoundingBox(float box[6]);
	void SetPieceInfo(PieceInfo* pPieceInfo);
	bool FileLoad(File& file, char* name);
	void FileSave(File& file, Group* pGroups);

	void CalculateConnections(CONNECTION_TYPE* pConnections, unsigned short nTime, bool bAnimation, bool bForceRebuild, bool bFixOthers);
	void UpdatePosition(unsigned short nTime, bool bAnimation);
	void Move(unsigned short nTime, bool bAnimation, bool bAddKey, float dx, float dy, float dz);

	void DoGroup(Group* pGroup);
	void UnGroup(Group* pGroup);
	Group* GetTopGroup();
	void SetGroup(Group* pGroup)
		{ m_pGroup = pGroup; }
	Group* GetGroup()
		{ return m_pGroup; }
	void SetName(char* name)
		{ strcpy(m_strName, name); }
	const char* GetName()
		{ return m_strName; }
	const unsigned char GetColor()
		{ return m_nColor; }
	void SetColor(unsigned char color)
		{ m_nColor = color; }
	PieceInfo* GetPieceInfo()
		{ return m_pPieceInfo; }
	void SetStepShow(unsigned char step)
		{ m_nStepShow = step; }
	const unsigned char GetStepShow()
		{ return m_nStepShow; }
	void SetStepHide(unsigned char step)
		{ m_nStepHide = step; }
	const unsigned char GetStepHide()
		{ return m_nStepHide; }
	void SetFrameShow(unsigned short frame)
		{ m_nFrameShow = frame; }
	const unsigned short GetFrameShow()
		{ return m_nFrameShow; }
	void SetFrameHide(unsigned short frame)
		{ m_nFrameHide = frame; }
	const unsigned short GetFrameHide()
		{ return m_nFrameHide; }
	const float* GetConstPosition()
		{ return m_fPosition; }
	void GetPosition (float* position)
		{ memcpy(position, m_fPosition, sizeof(m_fPosition)); }
	void GetRotation (float* rotation)
		{ memcpy(rotation, m_fRotation, sizeof(m_fRotation)); }

	void Render(bool bLighting, bool bNoAlpha, bool bEdges, unsigned char* nLastColor, bool* bTrans);
	inline void RenderBox(bool bHilite, float fLineWidth)
	{
		glPushMatrix();
		glTranslatef(m_fPosition[0], m_fPosition[1], m_fPosition[2]);
		glRotatef(m_fRotation[3], m_fRotation[0], m_fRotation[1], m_fRotation[2]);

		if (bHilite && ((m_nState & LC_PIECE_SELECTED) != 0))
		{
			glColor3ubv(FlatColorArray[m_nState & LC_PIECE_FOCUSED ? LC_COL_FOCUSED : LC_COL_SELECTED]);
			glLineWidth(2*fLineWidth);
			glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glCallList(m_nBoxList);
			glPopAttrib();
			glLineWidth(fLineWidth);
		}
		else
		{
			glColor3ubv(FlatColorArray[m_nColor]);
			glCallList(m_nBoxList);
		}
		glPopMatrix();
	}

	inline bool IsTransparent()
	{
		if (m_nColor < 14) return false;
		if (m_nColor > 21) return false;
		return true;
	};

	void crearConector(char *nombre,Diccionario d);

	/********FRAN*********/
	/**
	 * Introducir un nuevo conector libre en la lista de conectores libres.
	 * @param c puntero al conector a introducir como conector libre de la pieza.
	 */
	int introducirConectorLibre(Conector *c);
	void esborrarConectorLibre(void); /**< Elimina el conector libre actual. */
	/**
	 * Elimina el conector libre con el id indicado.
	  * Devuelve cierto si el conector ha sido borrado satisfactoriamente, de otro modo devuelve falso.
	 * @param id identificador de conector a eliminar de la lista de conectores libres.
	 */
	bool esborrarConectorLibre(int id);
	Conector *obtenerActualLibre(void); /**< Obtiene el conector actual libre. */
	void primeroLibre(void); /**< Se sitúa en el primer conector libre. */
	void siguienteLibre(void); /**< Se sitúa en el siguiente conector libre. */
	void ultimoLibre(void); /**< Nos sitúa en el último conector de la lista de conectores libres. */
	void anteriorLibre(void); /**< Nos sitúa sobre el conector anterior al actual en la lista de conectores libres. */
	bool finLibre(void); /**< Cierto si hemos llegado al final de la lista de conectores libres. */
	bool vaciaLibre(void); /**< Cierto si la lista de conectores libres está vacía. */
	bool llenaLibre(void); /**< Siempre es falso,ya que la lista está implementada dinámicacmente. */
	int nElementosLibre(void); /**< Devuelve el número de conectores que hay en la lista de conectores libres. */

	/**
	 * Introducir un nuevo conector en la lista de conectores ocupados.
	 * @param c puntero al conector a introducir como conector ocupado de la pieza.
	 */
	int introducirConectorOcupado(Conector *c);
	void esborrarConectorOcupado(void); /**< Eliminar el conector ocupado actual. */
	/**
	 * Elimina el conector ocupado con el id indicado.
	 * Devuelve cierto si el conector ha sido borrado satisfactoriamente, de otro modo devuelve falso.
	 * @param id identificador del conector a eliminar de la lista de conectores ocupados.
	 */
	bool esborrarConectorOcupado(int id);
	Conector *obtenerActualOcupado(void); /**< Obtiene el conector actual ocupado. */
	void primeroOcupado(void); /**< Se sitúa en el primer conector ocupado. */
	void siguienteOcupado(void); /**< Se sitúa en el siguiente conector ocupado. */
	void ultimoOcupado(void); /**< Nos sitúa en el último conector de la lista de conectores ocupados. */
	void anteriorOcupado(void); /**< Nos sitúa sobre el conector anterior al actual en la lista de conectores ocupados. */
	bool finOcupado(void); /**< Cierto si hemos llegado al final de la lista de conectores ocupados. */
	bool vaciaOcupado(void); /**< Cierto si la lista de conectores ocupados está vacía. */
	bool llenaOcupado(void); /**< Siempre es falso,ya que la lista está implementada dinámicacmente. */
	int nElementosOcupado(void); /**< Devuelve el número de conectores que hay en la lista de conectores ocupados. */

	/**
	 * Devuelve cierto si el conector pCon exite dentro de la lista de conectores ocupados.
	 * @param pCon puntero al conector a buscar.
	 */
	bool existeOcupado(Conector *pCon) { return conOcupados.Existe(pCon); }

	/**
	 * Busca el conector con el id indicado. Si existe lo devuleve.
	 * @param id el identificador del conector a buscar.
	 */
	Conector *buscarConectorOcupado(int id);
	Conector *buscarConectorLibre(int id);

	/**
	 * Función que devulve un puntero al conector más cercano a la recta ClickLine.
	 * Nos permite saber cual es el conector libre, de la pieza seleccionada, que está más cercano al lugar donde haya clicado el usuario.
	 * @param ClickLine línea resultante del lugar donde el usuario clicó en pantalla. Se utilizará para el cáclulo de la D^2(punto,recta), donde punto serán los centros de los conectores de la pieza seleccionada.
	 */
	Conector *conectorCercano(LC_CLICKLINE linea);

	/**
	 * Función que devuleve un puntero al conector más cercano a la linea.
	 * Nos permite saber cual es el conector ocupado, de la pieza seleccionada, que está más cercano al lugar donde haya clicado el usuario.
	 * @param linea línea resultante del lugar donde el usuario clicó en pantalla. Se utilizará para el cáclulo de la D^2(punto,recta), donde punto serán los centros de los conectores de la pieza seleccionada.
	 */
	Conector *conectorOcupadoCercano(LC_CLICKLINE linea);

	void piezaVisitada(void); /**< Actualiza el flag visitada de la pieza a cierto. */
	void piezaNoVisitada(void); /**< Actualiza el flag visitada de la pieza a falso. */
	void piezasNoVisitadas(void); /**< Pone como no visitada a ella misma y a todas las piezas conectadas a ella. Utiliza el flag visitada. */

	void piezasNoVisitadas1(void); /**< Pone como no visitada a ella misma y a todas las piezas conectadas a ella. Utiliza el flag visitada2. */

	bool obtenerEstadoVisita(void); /**< Devuelve cierto o falso dependiendo de si la pieza ha sido o no visitada. */

	/**
	 * Actualiza la rotación de la pieza.
	 * La rotación de una pieza en el leoCAD es almacenada en un vector de 4 floats.
	 * @param rot nueva rotación de la pieza.
	 */
	sirMat4d matrizPieza(void); /**< Función que devuelve la matriz de la pieza. */

	/**
	 * Actualiza la rotación de la pieza.
	 * @param rot vector de 4 floats que nos indica la rotación de la pieza en el mundo.
	 */
	void actualizarRotacion(float *rot);

	/**
	 * Actualiza la posición de la pieza.
	 * @param pos vector de 3 floats que nos indica la posición de la pieza en el mundo.
	 */
	void actualizarPosicion(float *pos);

	/**
	 * Buscamos hermanos entre los conectores de una pieza después de leer el fichero LCI.
	 * Dos conectores serán hermanos si:
	 *	1.-Coaxiales.
	 *	2.-PErtenecen a la misma pieza.
	 *	3.-No hay nada (conector de la misma pieza) entre los dos en el eje en el que son coaxiales.
	 *	4.-Son Extremos y del mismo tipo.
	 *	5.-Sus ids se diferencian en una unidad.
	 *	6.-Solo se tiene un hermano.
	 */
	void buscarHermanos(void);

	/**
	 * Función que lee un fichero LCI con toda la información sobre los conectores de una determinada pieza.
	 * Devuelve -1: Fichero no existe o el path es erróneo. / 0: Fallo sintáctico en el fichero. / 1: Todo correcto.
	 * @param path path donde se encuentra el fichero LCI a leer.
	 */
	int leerFicheroLCI(char *path);

	/**
	 * Función que devulve cierto si hay un ciclo desde la pieza actual, que es la que tiene el conector libre seleccionado, hasta la pieza del conector final.
	 * @param final es el conector hasta el que hay que intentar encontrar un ciclo (o lazo).
	 */
	bool assemblingConLazosCadenas(Conector *final);

	bool caminoDeAssemblings(Conector *final,Lista<Conector*> conDeslizados);

	void conectoresNoVisitados(void);

	/**
	 * Función que propaga el assembling entre dos piezas.
	 * Pone como conectores ocupados los que encajen.
	 * @param pPieza puntero a la pieza a ensamblar.
	 */
	void propagarAssembling(Piece *pPieza,Administrador *adminis);

	void actualizarConectoresLibres(void); /**< Actualiza la lista de conectores libres de la pieza. */

	/**
	 * Eliminamos todos los posibles assemblings entre piezas.
	 * Se eliminan las conexiones para que después no queden inconsistencias.
	 */
	void resetearAssembling(void);

	/**
	 * Pone como libres los conectores del resto de piezas que estaban conectados a ella.
	 */
	void borrar(void);

	void borrarConectoresLibres(void); /**< Vacía la lista de conetores libres. */
	void borrarConectoresOcupados(void); /**< Vacía la lista de conetores ocupados.*/

	/**
	 * Actualiza la posición/rotación del BoundingBox de la pieza.
	 */
	void actualizarBoundingBox(void);

	int nConectoresLibres(void);

	bool operator==(Piece c);
	int obtenerId(void); /**< Devuelve el ID de la pieza. */

	/**
	 * Método que devuelve la lista de piezas conectadas, sin incluir la conectada al conector dinámico.
	 * El parámetro es necesario porque cuando se propaga el Assembling ya se están apuntando la pieza dinámica y la estática.
	 * @param dinamico puntero al conector dinámico que participa en el proceso de assembling.
	 */
	Lista<Piece*> listaPiezasConectadas(Conector *dinamico);

	Lista<Piece*> listaPiezasConectadas(void); /**< Método que devuelve la lista de piezas conectadas. */

	bool puedeDeslizar(void); /**< Devuelve cierto si tiene algún conector en disposición de deslizarse sobre algún otro. */

	/**
	 * Nos devuelve el conector más cercano a línea, el cual esté en disposición de deslizar.
	 * @param linea para calcular la distancia del conector a la línea.
	 */
	Conector *conectorCercanoDeslizar(LC_CLICKLINE linea);

	//bool esPrimeraEnMover(void); //{ return primeraMover; }
	//void siEsPrimeraEnMover(void) { primeraMover=true; }
	//void noEsPrimeraEnMover(void) { primeraMover=false; }

	void comunicarTraslacion(sirVector3d t);
	void comunicarRotacion(sirMat4d r,bool sobreZ);
	void comunicarRotacion(float rot[4],double rthoot,sirVector3d posicion);

	void transformar(unsigned short nTime,bool bAnimation,bool bAddKey);

	void introducirTransformacion(sirMat4d M) { transformacion=M; }

	void introducirRotacion(float *rot) { m_fRotation[0]=rot[0]; m_fRotation[1]=rot[1]; m_fRotation[2]=rot[2]; m_fRotation[3]=rot[3]; }
	void introducirPosicion(float *pos) { m_fPosition[0]=pos[0]; m_fPosition[1]=pos[1]; m_fPosition[2]=pos[2]; }
	/*********************/

	Conector *obtenerMotor();

	void actualizar(unsigned short nTime,bool bAnimation,bool bAddKey);
	void Imprimirrotacion();

/*
	inline void UseTransform()
	{
		glTranslatef(m_fPosition[0], m_fPosition[1], m_fPosition[2]);
		glRotatef(m_fRotation[3], m_fRotation[0], m_fRotation[1], m_fRotation[2]);
	}
*/
protected:
	void LineFacet(float* p1, float* p2, float* p3, float* p4, LC_CLICKLINE* pLine);
	void BuildDrawInfo();

	// Atributes
	PieceInfo* m_pPieceInfo;
	Group* m_pGroup;

	unsigned short m_nFrameShow;
	unsigned short m_nFrameHide;
	unsigned char m_nStepShow;
	unsigned char m_nStepHide;

	unsigned char m_nColor;
	unsigned char m_nState;
	char m_strName[81];

	// Temporary variables
	float m_fPosition[3];
	float m_fRotation[4];
	GLuint m_nBoxList;
	CONNECTION* m_pConnections;
	void* m_pDrawInfo;

	/********FRAN*********/
	ListaConector conLibres; /**< Lista de conectores libres. */
	ListaConector conOcupados; /**< Lista de conectores ocupados. */
	bool visitada; /**< Flag para saber si la pieza ha sido visitada-->Algoritmos recursivos Trans/Rot. */

	/*********PRUEVA********/
	bool visitada1;
	bool visitada2;
	/*********PRUEVA********/

	int id; /**< Identificador de la pieza. */
	//bool primeraMover;
	bool primera;
	bool transformada;
	sirMat4d transformacion;
	bool rotacionActivada,traslacionActivada;

	/**********XUS***********/
	bool ejeZ;
	Conector *rotor;
};


#endif // _PIECE_H
