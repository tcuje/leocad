/**********************************************************/
/*                                                        */
/*               LISTACONTENIDOCOLISION.H                 */
/*                                                        */
/**********************************************************/


#ifndef LISTACONTENIDOCOLISION_H
#define LISTACONTENIDOCOLISION_H

//class Conector;
//#include "conector.h"
#include "contenidoColision.h"
#include "lista.h"

/**
 * Instanciaci�n de la clase Lista con punteros a conectores como datos.
 */

class ListaContenidoColision:public Lista<ContenidoColision *>
{

};


#endif