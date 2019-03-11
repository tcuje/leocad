#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "defines.h"
#include "typedefs.h"
#include "console.h"
#include "listagestor.h"
#include <time.h>

/********FRAN********/
class Piece;
class Conector;
class PieceInfo;
/********FRAN********/

class Project;
extern Project* project;
/********XUS*********/
typedef struct { int cfil,ccol,cfil2,ccol2,sfil,scol,sfil2,scol2; } COLOCAR;

extern Listagestor *ges;

extern Piece * pieza_asembling;
extern PieceInfo *infospur;
extern PieceInfo *infoaxle;
extern int vale;
extern double wormthooth;

extern bool antesrack;

extern bool puedo;
extern bool opbevel;
extern COLOCAR posi;
extern bool RotacionManual;
extern bool tengoMotor;
/********FRAN********/
extern int idConector;
extern int idPieza;
extern bool recalcularConexiones;
extern bool obligatorio;
/********FRAN********/

class Messenger;
extern Messenger* messenger;

class MainWnd;
extern MainWnd* main_window;

extern unsigned char FlatColorArray[31][3];
extern unsigned char ColorArray[31][4];
extern const char* colornames[LC_MAXCOLORS];
extern const char* altcolornames[LC_MAXCOLORS];

#endif // _GLOBALS_H_
