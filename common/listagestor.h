/**********************************************************/
/*                                                        */
/*                    LISTAPASOS.H                        */
/*                                                        */
/**********************************************************/


#ifndef LISTAGESTOR_H
#define LISTAGESTOR_H

#include "pasos.h"
#include "lista.h"

/**
 * Instanciación de la clase Lista con una estructura de datos de pasos.
 */

class Listagestor:public Lista<Pasos>
{

};


#endif