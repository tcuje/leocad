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
 * El parámetro tag sirve para poder comprovar que el tag actual es el que debería y en el fichero no existen fallos sintácticos.
 * @param linea puntero a la linea de carácteres actual del fichero XML.
 * @param indice índice que nos informa en la posición de la línea donde nos encontramos.
 * @param tag TAG que deberíamos encontrarnos en c.
 */
bool compararTag(char *linea,int *indice,char *tag);

/**
 * Inspecciona el tag actual que se encuentra en c e incrementa ind en las unidades necesarias dependiendo del tag.
 * @param linea puntero a la linea de carácteres actual del fichero XML.
 * @param indice índice que nos informa en la posición de la línea donde nos encontramos.
 */
char *obtenerTag(char *linea,int *indice);

/**
 * Pasa los espacios que se encuntran a partir de linea[(*ind)].
 * Acaba incrementando ind hasta dejarla apuntando a otro carácter que no sea un espacio.
 * @param linea linea de un fichero XML.
 * @param ind índice que nos informa en la posición de la línea donde nos encontramos.
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
 * @param indice índice que nos informa en la posición de la línea donde nos encontramos.
 */
bool restoLineaVacia(char *linea,int *indice);

/**
 * Lee la informacion que se encuentra dentra tag de inicio y tag de fin.
 * @param linea linea de un fichero XML.
 * @param indice índice que nos informa en la posición de la línea donde nos encontramos.
 */
char *leerContenido(char *linea,int *indice);

/**
 * Método que pasa las líneas vacías del fichero f y devuelve cierto
 * en caso de que sigan habiendo más líneas por leer. En caso de que
 * llegáramos al final del mismo devolvería falso.
 * @param f es el fichero XML.
 * @param linea de un fichero XML.
 * @param indice índice que nos informa en la posición de la linea donde nos encontramos.
 */
bool pasarLineasVacias(ifstream *f,char *linea,int *indice);

/**
 * Método que obtiene una linea del fichero f con informacion y comprueba si las siguientes
 * tambien tiene informacion y si no es asin cerrara el fichero y devolvera falso.
 * @param f es el fichero XML.
 * @param linea de un fichero XML.
 * @param indice índice que nos informa en la posición de la linea donde nos encontramos.
 */
bool obtenerLineaConInformacion(ifstream *f,char *linea,int *indice);


#endif
