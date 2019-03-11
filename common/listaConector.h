/**********************************************************/
/*                                                        */
/*                   LISTACONECTOR.H                      */
/*                                                        */
/**********************************************************/


#ifndef LISTACONECTOR_H
#define LISTACONECTOR_H

//class Conector;
#include "conector.h"
#include "lista.h"

/**
 * Instanciación de la clase Lista con punteros a conectores como datos.
 */

class ListaConector:public Lista<Conector *>
{

};


#endif