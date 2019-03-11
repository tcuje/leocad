/*************************************************/
/*                                               */
/*                 DICCIONARIO.H                 */
/*                                               */
/*************************************************/


#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "tag.h"
#include "contenido.h"
#include "edfOrdenada.h"

class Diccionario:public EdfOrdenada<Tag,Contenido,10>
{

};

#endif

