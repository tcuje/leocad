#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "object.h"
#include "defines.h"
#include "typedefs.h"
#include "opengl.h"
#include "texfont.h"
#include "array.h"
/********FRAN*********/
#include "lista.h"
#include <time.h>
//#include "listaPieza.h"

#include "listaConector.h"
#include "Algebra3.h"
#include <fstream.h>
/*********************/

typedef enum
{
  LC_TRACK_NONE, LC_TRACK_START_LEFT, LC_TRACK_LEFT,
  LC_TRACK_START_RIGHT, LC_TRACK_RIGHT
} LC_MOUSE_TRACK;

class Administrador;
class Piece;
/********FRAN*********/
class Conector;
/*********************/
class Camera;
class Light;
class Group;
class Texture;
class Terrain;
class PieceInfo;
class Matrix;
class View;
class Image;

// Undo support

#include "file.h"

typedef struct LC_UNDOINFO
{
  FileMem file;
  char strText[21];
  LC_UNDOINFO* pNext;
  LC_UNDOINFO() { pNext = NULL; };
} LC_UNDOINFO;


class Project
{

/********FRAN*********/

private:


	Conector *selectCon1; /**< Primer conector seleccionado por el usuario */
	Conector *selectCon2; /**< Segundo conector seleccionado por el usuario */
	Conector *delAssembling1; /**< Conector seleccionat a desensamblar. */
	Conector *Motor;

	Administrador *adminis;

	Piece *piezaDeslizar; /**< Pieza a la que vamos a deslizar. */
	Conector *deslizarConector; /**< Conector a deslizar. */

	int nSelect; /**< Número de conectores seleccionados. */
	bool ensamblar; /**< Nos informa de si el usuario tiene activada la opción de assembling. */
	bool desconectar,desconectarPieza,deslizar;
	Lista<Piece*> piezas;

	/**
	 * Función que calcula el ángulo dado el módulo del producto vectorial y el producto escalar.
	 * opp es el módulo del producto vectorial.
	 * adj es el producto escalar.
	 */
	double angulo(double opp,double adj);

	/**
	 * Elimina los posibles asemblings entre piezas.
	 * Es utilizada cuando el usuario desabilita la opción del assembling.
	 * Se eliminan las conexiones para que después no queden inconsistencias.
	 */
	void resetearAssembling(void);

	void borrarAssemblings(void);

	/**
	 * Interfície con el usuario.
	 * Interfície para seleccionar los conectores a ensamblar.
	 * @param pCon conector seleccionado.
	 */
	void seleccionarConectores(Conector *pCon);

	/**
	 * Interfície con el usuario.
	 * interfície para confirmar el assembling entre dos conectores.
	 * @param pPieza pieza seleccionada.
	 */
	void confirmarConectores(Piece *pPieza);

	/**
	 * Crea la pieza seleccionada por el usuario leyendo el fichero LCI correspondiente.
	 * @param pPiece puntero a la pieza que hay que leer su fichero LCI y crear toda la información necesaria.
	 */
	void crearPieza(Piece *pPiece);
	void piezasNoVisitadas(void); /**< Pone como no visitadas a todas las piezas del proyecto actual. */

	/**
	 * Propaga el assembling entre "pieza" y el resto de piezas de la escena.
	 * Mira si algún conector de "pieza" puede ensamblar con algún otro de otra pieza de la misma escena.
	 * @param pieza piza a la que se propaga el assembling;
	 */
	void propagarAssembling(Piece *pieza);

	/**
	 * Método que propaga (busca conexiones secundarias) entre todas las piezas.
	 * Mira si algún conector de alguna pieza puede ensamblar con algún otro de alguna pieza de la misma escena.
	 */
	void propagarAssemblingTotal(void);

	/**
	 * Busca conexiones secundarias entre la parte dinámica de la escena y la parte estática.
	 * @param piezaDinamica pieza a la que se le ha aplicado un proceso de assembling.
	*/
	void propagarAssemblingParteDinamica(Piece *piezaDinamica);

	/**
	 * Realiza el assembling entre los conectores seleccionados por el usuario.
	 * @param estatico el conector de la pieza que no se translada/rota.
	 * @param dinamico el conector de la pieza que hay que transladar/rotar.
	 */
	void assembling(Conector *estatico,Conector *dinamico);

	/**
	 * Llena la estructura de datos "datos", con la información de todos los conectores libres
	 * de las piezas seleccionadas por el usuario.
	 * @param datos puntero a la estructura de datos donde se almacena la información de los conectores libres de todas las piezas seleccionadas.
	 */
	//void crearDatosConectores(LC_FRAN_SEL_DATA *datos);

	/**
	 * Obtiene el conector seleccionado por el usuario.
	 * @param datos puntero a la estructura de datos donde se almacena la información de los conectores libres de todas las piezas seleccionadas.
	 */
	//Conector *conectorSeleccionado(LC_FRAN_SEL_DATA *datos);

	void vaciarLista(void); /**< Vacía la lista "listaPiezas". */

	/**
	 * Introduce la pieza pPieza en la lista de piezas listaPiezas si no existe en tal pieza.
	 * Actualiza nConLibres con el número de conectores libres de la pieza, si ésta se inserta.
	 * @param pPieza puntero a la pieza.
	 * @nConLibres puntero al número de conectores libres total de todas las piezas de la lista.
	 */
	int introducirPiezaLista(Piece *pPieza);


	//void introducirPiezaLista(Piece *pPieza,int *nConLibres);


	/**
	 * Busca dentro de todas las piezas de la escena el conector ocupado con el ID indicado
	 * @param id identificador del conector
	 */
	Conector *buscarConectorOcupado(int id);

	/**
	 * Busca dentro de todas las piezas de la escena el conector libre con el ID indicado
	 * @param id identificador del conector
	 */
	Conector *buscarConectorLibre(int id);

	/**
	 * Nos devuelve el número de conectores ocupados.
	 * Cada pareja de ocupados cuenta una vez, sin repetidos.
	 */
	int numeroAssemblings(void);

	/**
	 * Restable las conexiones tal y como lee desde el fichero.
	 * Para después del Undo/Redo reestablecer las conexiones tal y como estaban.
	 * @param file fichero desde donde se leen los pares de IDs para volver a ensamblar los conectores.
	 * @param nAssemblings número de pares de IDs==número de assemblings entre conectores, sin repetidos.
	 */
	void restablecerAssemblings(File *file,int nAssemblings);

	/**
	 * Método que devuelve la lista de piezas no conectadas a una pieza dada.
	 * @param conectadas lista de piezas conectadas a una determinada pieza.
	 */
	Lista<Piece*> listaPiezasNoConectadas(Lista<Piece*> conectadas);

	/**
	 * Método que se encaraga de detectar colisiones en el proceso de deslizado.
	 * @param translacion es el vector traslacion que quiere deslizar el usuario.
	 */
	void deteccionColisionesDeslizar(float *translacion);

	/********FRAN*********/
	/****************XUS********************/
	Conector *buscarMotor();

public:
// Constructors
	Project();
	~Project();
	bool Initialize(int argc, char *argv[], char* binpath, char* libpath);
	/****************XUS********************/
	void EjecutarMotor();


// Attributes
public:
	bool IsModified()
		{ return m_bModified; }
	void SetModifiedFlag(bool bModified)
		{ m_bModified = bModified; }
	
	// Access to protected members
	unsigned char GetLastStep();
	bool IsAnimation()
		{ return m_bAnimation; }
	unsigned short GetCurrentTime ()
	  { return m_bAnimation ? m_nCurFrame : m_nCurStep; }
	int GetPieceLibraryCount()
		{ return m_nPieceCount; }
	const char* GetLibraryPath()
		{ return m_LibraryPath; }
	void SetCurrentPiece(PieceInfo* pInfo)
		{ m_pCurPiece = pInfo; }
	int GetCurrentColor()
		{ return m_nCurColor; }
	float* GetBackgroundColor()
		{ return m_fBackground; }
	Camera* GetCamera(int i);
	PieceInfo* GetPieceInfo(int index);
	void GetTimeRange(int* from, int* to)
	{
		*from = m_bAnimation ? m_nCurFrame : m_nCurStep;
		*to = m_bAnimation ? m_nTotalFrames : 255;
	}
  unsigned short GetTotalFrames () const
    { return m_nTotalFrames; }

	void GetArrays(Piece** ppPiece, Camera** ppCamera, Light** ppLight)
	{
		*ppPiece = m_pPieces;
		*ppCamera = m_pCameras;
		*ppLight = m_pLights;
	}

	void SetPathName (const char* lpszPathName, bool bAddToMRU);
	void SetTitle (const char* lpszTitle);

public:
	// Special notifications
	void DeleteContents(bool bUndo); // delete doc items etc
	void LoadDefaults(bool cameras);

	void Render(bool bToMemory);
	void SetViewSize(int cx, int cy);
	Texture* FindTexture (const char* name);
	PieceInfo* FindPieceInfo (const char* name) const;
	void CheckAutoSave();
	void GetFocusPosition(float* pos);

        void AddView (View* pView);
        void RemoveView (View* pView);
        void UpdateAllViews (View* pSender = NULL);

// Implementation
protected:
	// default implementation
	char m_strTitle[LC_MAXPATH];
	char m_strPathName[LC_MAXPATH];
	bool m_bModified;    // changed since last saved

        PtrArray<View> m_ViewList;

	char m_strAuthor[101];
	char m_strDescription[101];
	char m_strComments[256];

	// Piece library
	bool LoadPieceLibrary (char* libpath);
	char m_LibraryPath[LC_MAXPATH];	// path to the library files
	char m_AppPath[LC_MAXPATH];	// path to the LeoCAD executable
	/********FRAN*********/
	char directorioLCI[LC_MAXPATH]; /**< String con el path al directorio LCI. Por defecto es el del ejecutable. */
	/********FRAN*********/
	int m_nPieceCount;		// number of pieces
	PieceInfo* m_pPieceIdx;	// index
	int m_nTextureCount;
	Texture* m_pTextures;
  TexFont m_ScreenFont;
	char* m_pMovedReference;
	int m_nMovedCount;

	// Undo support
	LC_UNDOINFO* m_pUndoList;
	LC_UNDOINFO* m_pRedoList;
	bool m_bUndoOriginal;
	void CheckPoint (const char* text);

	// Objects
	Piece* m_pPieces;
	Camera* m_pCameras;
	Light* m_pLights;
	Group* m_pGroups;
	Camera* m_pViewCameras[4];
	Terrain* m_pTerrain;
	File* m_pClipboard[10];
	unsigned char m_nCurClipboard;

	CONNECTION_TYPE m_pConnections[LC_CONNECTIONS];

	void AddPiece(Piece* pPiece);
	void RemovePiece(Piece* pPiece);
	bool RemoveSelectedObjects();
	void FindObjectFromPoint(int x, int y, LC_CLICKLINE* pLine);
	void SelectAndFocusNone(bool bFocusOnly);
	void CalculateStep();
	void MoveSelectedObjects(float x, float y, float z);
	void RotateSelectedObjects(float x, float y, float z);
	void SnapPoint (float *point, float *reminder) const;

	// Rendering
	void RenderScene(bool bShaded, bool bDrawViewports);
	void RenderViewports(bool bBackground, bool bLines);
	void RenderBoxes(bool bHilite);
	void RenderInitialize();
	void CreateImages(Image* images, int width, int height, unsigned short from, unsigned short to, bool hilite);
	void CreateHTMLPieceList(FILE* f, int nStep, bool bImages, char* ext);

	inline bool IsDrawing()
	{
		if (m_bRendering)
			m_bStopRender = true;
		return m_bRendering;
	}

	bool m_bRendering;
	bool m_bStopRender;
	File* m_pTrackFile;
	bool m_bTrackCancel;
	int m_nTracking;
	int m_nDownX;
	int m_nDownY;
	float m_fTrack[3];
	int m_nMouse;

	void LoadViewportProjection();
	bool SetActiveViewport(int x, int y);
	bool StopTracking(bool bAccept);
	void StartTracking(int mode);
	void UpdateSelection();
	void RemoveEmptyGroups();

public:
	// Call this functions from each OS
	void OnLeftButtonDown(int x, int y, bool bControl, bool bShift);
	void OnLeftButtonUp(int x, int y, bool bControl, bool bShift);
	void OnLeftButtonDoubleClick(int x, int y, bool bControl, bool bShift);
	void OnRightButtonDown(int x, int y, bool bControl, bool bShift);
	void OnRightButtonUp(int x, int y, bool bControl, bool bShift);
	void OnMouseMove(int x, int y, bool bControl, bool bShift);
	bool OnKeyDown(char nKey, bool bControl, bool bShift);

	void SetAction(int nAction);
	void HandleNotify(LC_NOTIFY id, unsigned long param);
	void HandleCommand(LC_COMMANDS id, unsigned long nParam);

	/********FRAN*********/
	/**
	 * Modifica el estado de las variables desconectar,desconectarPieza y deslizar según la accion.
	 * @param accion nos indica si modificamos el estado de desconectar,desconectarPieza o deslizar.
	 */
	void canviarEstado(int accion);

	void conectoresNoVisitados(void);
	void transformar(unsigned short nTime,bool bAnimation,bool bAddKey);
	/********FRAN*********/

protected:
	// State variables
	unsigned char m_nViewportMode;
	unsigned char m_nActiveViewport;
	int m_nViewX;
	int m_nViewY;
	PieceInfo* m_pCurPiece;
	unsigned char m_nCurColor;
	unsigned char m_nCurAction;
	unsigned char m_nCurGroup;
	bool m_bAnimation;
	bool m_bAddKeys;
	unsigned char m_nFPS;
	unsigned char m_nCurStep;
	unsigned short m_nCurFrame;
	unsigned short m_nTotalFrames;

	unsigned long m_nScene;
	unsigned long m_nDetail;
	unsigned long m_nSnap;
	unsigned short m_nMoveSnap;
	unsigned short m_nAngleSnap;
	unsigned short m_nGridSize;
	float m_fLineWidth;
	float m_fFogDensity;
	float m_fFogColor[4];
	float m_fAmbient[4];
	float m_fBackground[4];
	float m_fGradient1[3];
	float m_fGradient2[3];
	char m_strFooter[256];
	char m_strHeader[256];

	GLuint m_nGridList;
	unsigned long m_nAutosave;
	unsigned long m_nSaveTimer;
	char m_strModelsPath[LC_MAXPATH];
	char m_strBackground[LC_MAXPATH];
	Texture* m_pBackground;

protected:
	// implementation helpers
	bool DoSave(char* lpszPathName, bool bReplace);
	bool DoFileSave();
	bool FileLoad(File* file, bool bUndo, bool bMerge);
	void FileSave(File* file, bool bUndo);
	void FileReadLDraw(File* file, Matrix* prevmat, int* nOk, int DefColor, int* nStep);

public:
	// File helpers
	bool OnNewDocument ();
	bool OnOpenDocument (const char* lpszPathName);
	bool SaveModified ();

protected:
	// mail enabling
//	void OnFileSendMail();
//	void OnUpdateFileSendMail(CCmdUI* pCmdUI);

	// TODO: Fix ! This is a hack to make things work now
	friend class CCADView;
	friend void PrintPiecesThread(void* pv);
	friend void Export3DStudio();
};

#endif // _PROJECT_H_
