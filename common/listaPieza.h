/**********************************************************/
/*                                                        */
/*						LISTAPIEZA.H                      */
/*                                                        */
/**********************************************************/


#ifndef LISTAPIEZA_H
#define LISTAPIEZA_H

#include "piece.h"
#include "lista.h"

/**
 * Instanciaci�n de la clase Lista con punteros a piezas como datos.
 */

class ListaPieza:public Lista<Piece *>
{

};


#endif