/*************************************************/
/*                                               */
/*				   EDFORDENADA.H	             */
/*                                               */
/*************************************************/


#include "edfOrdenada.h"

/*************************************************/

// Constructor de la classe
template <class Clave,class Elemento,int N>
EdfOrdenada<Clave,Elemento,N> :: EdfOrdenada()
{
	actual=0;
	nDatos=0;

	datos = new Nodo[N];
	//if(datos==NULL) AfxMessageBox("There's enough memory.");
}

/*************************************************/

// Constructor de copia
template <class Clave,class Elemento,int N>
EdfOrdenada<Clave,Elemento,N> :: EdfOrdenada(const EdfOrdenada &e)
{
	int i;

	actual=e.actual;
	nDatos=e.nDatos;

	datos = new Nodo[N];
	//if(datos==NULL) AfxMessageBox("There's enough memory.");

	for(i=0;i<nDatos;i++)
	{
		datos[i].c=e.datos[i].c;
		datos[i].e=e.datos[i].e;
	}
}

/*************************************************/

// Destructor de la classe
template <class Clave,class Elemento,int N>
EdfOrdenada<Clave,Elemento,N> :: ~EdfOrdenada()
{
	delete [] datos;
	datos = NULL;
}

/*************************************************/

template <class Clave,class Elemento,int N>
bool EdfOrdenada<Clave,Elemento,N> :: Vacia(void)
{
	return (nDatos==0);
}

/*************************************************/

template <class Clave,class Elemento,int N>
bool EdfOrdenada<Clave,Elemento,N> :: Llena()
{
	return (nDatos==N);
}

/*************************************************/

template <class Clave,class Elemento,int N>
void  EdfOrdenada<Clave,Elemento,N> :: Buscar(Clave c,bool &trobat,int & pos)
{
	int inferior,superior,medio;

	inferior=0;
	superior=nDatos;
	while(inferior<superior)
	{
		medio=(inferior+superior)/2;
		if(c>datos[medio].c) inferior=medio+1;
		else superior=medio;
	}

	pos=inferior;
	if(pos<nDatos) trobat=(c==datos[pos].c);
	else trobat=0;
}

/*************************************************/

template <class Clave,class Elemento,int N>
EdfOrdenada<Clave,Elemento,N> & EdfOrdenada<Clave,Elemento,N> :: operator = (EdfOrdenada &edf)
{
	int i;

	if(datos!=edf.datos) //Esto está bién???
	{
		if(datos!=NULL) delete [] datos;

		actual=edf.actual;
		nDatos=edf.nDatos;
		datos= new Nodo[N];

		for(i=0;i<N;i++)
		{
			datos[i].c=edf.datos[i].c;
			datos[i].e=edf.datos[i].e;
		}
	}
	return(*this);
}

/*************************************************/

template <class Clave,class Elemento,int N>
void EdfOrdenada<Clave,Elemento,N> :: Introducir(Clave c,Elemento e)
{
	int i,j;
	bool trobat;

	Buscar(c,trobat,i);
	if(trobat)
	{
		datos[i].e=e;
		actual=i;
	}
	else if(Llena()) {} //Llena!!!
	else
	{
		for(j= nDatos-1;j>=i;j--)
		{
			datos[j+1]=datos[j];
		}

		nDatos++;
		datos[i].c=c;
		datos[i].e=e;
		actual=i;
	}
}

/*************************************************/

template <class Clave,class Elemento,int N>
void EdfOrdenada<Clave,Elemento,N> :: Borrar(Clave c)
{
	int i,j;
	bool trobat;

	Buscar(c,trobat,i);
	if(trobat)
	{
		// S'esborra conservant l'ordre
		nDatos--;
		for(j=i;j<nDatos;j++)
		{
			datos[j]=datos[j+1];
		}
		actual=i;
	}
}

/*************************************************/

template <class Clave,class Elemento,int N>
bool EdfOrdenada<Clave,Elemento,N> :: Existe(Clave c)
{
	int i;
	bool trobat;

	Buscar(c,trobat,i);
	return trobat;
}

/*************************************************/

template <class Clave,class Elemento,int N>
Elemento EdfOrdenada<Clave,Elemento,N> :: Consultar(Clave c)
{
	int i;
	bool trobat;
	Elemento resultado;

	Buscar(c,trobat,i);
	if(trobat) resultado=datos[i].e;
	else {} //La clave no existe!!!

	return(resultado);
}

/*************************************************/

template <class Clave,class Elemento,int N>
void EdfOrdenada<Clave,Elemento,N>:: Primero(void)
{
	actual=0;
}

/*************************************************/

template <class Clave,class Elemento,int N>
void EdfOrdenada<Clave,Elemento,N>:: Siguiente(void)
{
	if(Fin()) {} //Fin del recorrido!!!
	else actual++;
}

/*************************************************/

template <class Clave,class Elemento,int N>
bool EdfOrdenada<Clave,Elemento,N>:: Fin(void)
{
  return (actual==nDatos);
}

/*************************************************/

template <class Clave,class Elemento,int N>
Clave EdfOrdenada<Clave,Elemento,N>:: ClaveActual(void)
{
	Clave resultado;

	if(Fin()) {} //Fin del recorrido!!!
	else resultado=datos[actual].c;

	return resultado;
}

/*************************************************/

template <class Clave,class Elemento,int N>
Elemento EdfOrdenada<Clave,Elemento,N>:: ElementoActual(void)
{
	Elemento resultado;

	if(Fin()) {} //Fin del recorrido!!!
	else resultado=datos[actual].e;

	return resultado;
}

/*************************************************/

template <class Clave,class Elemento,int N>
int EdfOrdenada<Clave,Elemento,N>:: NElementos(void)
{
	return(nDatos);
}

/*************************************************/

template <class Clave,class Elemento,int N>
EdfOrdenada<Clave,Elemento,N> EdfOrdenada<Clave,Elemento,N>::operator +(EdfOrdenada edf)
{
	EdfOrdenada<Clave,Elemento,N> resultado;
	Clave c;
	Elemento e;

	resultado=(*this); //CUIDADO!!!!!!!!!!!!!!!!!

	edf.Primero();
	while(!edf.Fin())
	{
		c=edf.ClaveActual();
		e=edf.ElementoActual();
		resultado.Introducir(c,e); //Si estuviera la distancia repetida se machacaría!!!!!!!!!
		edf.Siguiente();
	}

	return resultado;
}

