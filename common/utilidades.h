/*************************************************/
/*                                               */
/*                  UTILIDADES.H                 */
/*                                               */
/*************************************************/


#ifndef UTILIDADES_H
#define UTILIDADES_H


#include "Matrix.h"
#include "Algebra3.h"
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>
#include <fstream.h>

void cadenamatriz(sirMat4d m,char cad[]);
void cadenavector(sirVector4d v,char cad[]);
char * buscarfin(char aux2[]);

bool ajuste(double a,double b);

void imprimirMatriz(Matrix m);
void imprimirMatriz(sirMat4d m);
void imprimirVector(sirVector3d v);
void imprimirVector(sirVector4d v);
void imprimirVector(float *v);
void imprimirEntero(int n);
void imprimirFloat(float n);
void imprimirDouble(double n);
void nada();

double angulo(double opp,double adj);
/**
 * Inspecciona el tag actual que se encuentra en c e incrementa ind en las unidades necesarias dependiendo del tag.
 * El par�metro tag sirve para poder comprovar que el tag actual es el que deber�a y en el fichero no existen fallos sint�cticos.
 * @param linea puntero a la linea de car�cteres actual del fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la l�nea donde nos encontramos.
 * @param tag TAG que deber�amos encontrarnos en c.
 */
bool compararTag(char *linea,int *indice,char *tag);

/**
 * Inspecciona el tag actual que se encuentra en c e incrementa ind en las unidades necesarias dependiendo del tag.
 * @param linea puntero a la linea de car�cteres actual del fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la l�nea donde nos encontramos.
 */
char *obtenerTag(char *linea,int *indice);

/**
 * Pasa los espacios que se encuntran a partir de linea[(*ind)].
 * Acaba incrementando ind hasta dejarla apuntando a otro car�cter que no sea un espacio.
 * @param linea linea de un fichero XML.
 * @param ind �ndice que nos informa en la posici�n de la l�nea donde nos encontramos.
 */
void pasarEspacios(char *linea,int *ind);

/**
 * Pasa las lineas que contienen un salto de linea.
 * Acaba incrementando hasta que encuentra un caracter que no sea un espacio.
 * @param linea linea de un fichero XML.
 */
bool lineaVacia(char *linea);

/**
 * Pasa las lineas que contienen un salto de linea.
 * Acaba incrementando hasta que encuentra un caracter que no sea un espacio.
 * @param linea linea de un fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la l�nea donde nos encontramos.
 */
bool restoLineaVacia(char *linea,int *indice);

/**
 * Lee la informacion que se encuentra dentra tag de inicio y tag de fin.
 * @param linea linea de un fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la l�nea donde nos encontramos.
 */
char *leerContenido(char *linea,int *indice);

/**
 * M�todo que pasa las l�neas vac�as del fichero f y devuelve cierto
 * en caso de que sigan habiendo m�s l�neas por leer. En caso de que
 * lleg�ramos al final del mismo devolver�a falso.
 * @param f es el fichero XML.
 * @param linea de un fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la linea donde nos encontramos.
 */
bool pasarLineasVacias(ifstream *f,char *linea,int *indice);

/**
 * M�todo que obtiene una linea del fichero f con informacion y comprueba si las siguientes
 * tambien tiene informacion y si no es asin cerrara el fichero y devolvera falso.
 * @param f es el fichero XML.
 * @param linea de un fichero XML.
 * @param indice �ndice que nos informa en la posici�n de la linea donde nos encontramos.
 */
bool obtenerLineaConInformacion(ifstream *f,char *linea,int *indice);


#endif
