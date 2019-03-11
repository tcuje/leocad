/*************************************************/
/*                                               */
/*                EDFCOLISION.H                  */
/*                                               */
/*************************************************/


#ifndef EDFCOLISION_H
#define EDFCOLISION_H

#include "contenidoColision.h"
#include "edfOrdenada.h"

class EdfColision:public EdfOrdenada<int,ContenidoColision,50>
{

};

#endif

