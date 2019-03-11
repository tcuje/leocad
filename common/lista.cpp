/*************************************************/
/*                                               */
/*                  LISTA.CPP                    */
/*                                               */
/*************************************************/


#include "lista.h"
#include <afxwin.h>
#include <iostream.h>

/*************************************************/

//Constructor de la clase
template <class T> Lista<T>::Lista()
{
	actual=NULL;
	primero=NULL;
	ultimo=NULL;
	nElementos=0;
}

/*************************************************/

// Constructor de copia
template <class T> Lista<T>::Lista(Lista<T> &l)
{
	Nodo  *temp, *temp2;
	bool trobat=false;

	actual=NULL;
	primero=NULL;
	ultimo=NULL;

	//nElementos=l.NElementos();
	nElementos=l.nElementos;

	temp=l.actual; //De tipo NODO!!!-->Puede ser NULL.
	l.Primero();

	while(!l.Fin())
	{
		Introducir(l.Actual());
		if (l.actual == temp)
		{
			temp2=ultimo;
		}
		l.Siguiente();
	}

	//Volvemos a colocar el puntero actual de l donde estaba.
	l.actual=temp;
	actual=temp2;

}

/*************************************************/

// Destructor de la classe
template <class T> Lista<T>::~Lista()
{
	Primero();
	while(!Fin()) Esborrar();
}

template <class T> void Lista<T>::borrartodo()
{
	Primero();
	while(!Fin()) Esborrar();
}

/*************************************************/

//Operdor de asignaci�n sobrecargado
template <class T> Lista<T> & Lista<T>::operator = (Lista<T> &l)
{
	//A�ade a la lista, la lista l poniendo el nuevo actual al que era en la lista l.
	Nodo  *temp, *temp2;
	bool trobat=false;


	int b;
	char a[40];
	char s[5];


	actual=NULL;
	primero=NULL;
	ultimo=NULL;

	//nElementos=l.NElementos();

	nElementos=l.nElementos;


	temp=l.actual; //De tipo NODO!!!-->Puede ser NULL.
	l.Primero();

	while(!l.Fin())
	{
		Introducir(l.Actual());
		if(l.actual==temp) temp2=ultimo;
		l.Siguiente();
	}

	//Volvemos a colocar el puntero actual de l donde estaba.
	l.actual=temp;
	actual=temp2;
	return(*this);
}

/*************************************************/

// Cierto si la lista est� vac�a
// Si el primero apunta a null la lista est� vac�a
template <class T> bool Lista<T>::Vacia(void)
{
	return primero==NULL;
}

/*************************************************/

// Lista din�mica no lo podemos saber
template <class T> bool Lista<T>::Llena(void)
{
	return false;
}

/*************************************************/

// Sit�a el punto de inter�s en el primer elemento de la lista
template <class T> void  Lista<T>::Primero(void)
{
	actual=primero;
}

/*************************************************/

// Sit�a el punto de inter�s en el �ltimo elemento de la lista
template <class T> void  Lista<T>::Ultimo(void)
{
	actual=ultimo;
}

/*************************************************/

//Cierto si estamos al final de la llista
template <class T> bool Lista<T>::Fin(void)
{
	return actual==NULL;
}

/*************************************************/

//N�mero de elementos de la lista
template <class T> int Lista<T>::NElementos(void)
{
	return nElementos;
}

/*************************************************/

//Sit�a el puntro de inter�s en el siguiente elemento de la lista
template <class T> void  Lista<T>::Siguiente(void)
{
  if(!Fin()) actual=actual->siguiente;
}


/*************************************************/

// Sit�a el punt de inter�s en el anterior elemento de la lista
template <class T> void  Lista<T>::Anterior(void)
{
  if(!Fin()) actual=actual->anterior;
}

/*************************************************/

// Devuelve el contenido del elemento actual
template <class T> T Lista<T>::Actual(void)
{
	if(!Fin()) return actual->dato;
	//else return NULL;
}

/*************************************************/

// Esborra el elemento actual
template <class T> void Lista<T>::Esborrar()
{
	Nodo *posAnterior,*posSiguiente;

	if(!Fin())
	{
		posAnterior=actual->anterior;
		posSiguiente=actual->siguiente;

		//Es el primer elemento
		if(posAnterior==NULL) primero=posSiguiente;
		else posAnterior->siguiente=posSiguiente;

		//Es el �ltimo elemento
		if(posSiguiente==NULL) ultimo=posAnterior;
		else posSiguiente->anterior=posAnterior;

		delete actual;
		nElementos=nElementos-1;
		actual=posSiguiente;
	}
}

/*************************************************/

template <class T> bool Lista<T>::Esborrar(T elemento)
{
	//Esborra el elemento T.

	bool trobat=false;

	if(!Vacia())
	{
		Primero();
		while(!Fin() && !trobat)
		{
			if(Actual()==elemento)
			{
				Esborrar();
				trobat=true;
			}
			else Siguiente();
		}
	}

	return trobat;
}

/*************************************************/

//Introducir por delante un nuevo elemento
template <class T> int Lista<T>::Introducir(T elemento)
{
	Nodo *nuevo,*nodoActual,*nodoAnterior;

	//Si T existe no lo introducimos.

	//NO modifica, pero no me hace falta.
	//Al menos no tendr� elementos repetidos y no tendr� que preguntar desde fuera si existe!!!
	if(!Existe(elemento))
	{
		nuevo=new Nodo;
		if(nuevo==NULL) return -1; //Se�al de que no hay m�s memoria
		else
		{
			nuevo->dato=elemento;
			nodoActual=actual;

			if(nodoActual==NULL)
			{
				nodoAnterior=ultimo;
				ultimo=nuevo;
			}
			else
			{
				nodoAnterior=nodoActual->anterior;
				nodoActual->anterior=nuevo;
			}

			nuevo->siguiente=nodoActual;
			if(nodoAnterior==NULL) primero=nuevo;
			else nodoAnterior->siguiente=nuevo;

			nuevo->anterior=nodoAnterior;
			nElementos=nElementos+1;
			return 1; //Todo ha �do bi�n
		}
	}
	return 1; //Todo ha ido bi�n pero el elemento ya exist�a.
	//Si existe no hacemos nada

	/*nuevo=new Nodo;
	if(nuevo==NULL) return -1; //Se�al de que no hay m�s memoria
	else
	{
		nuevo->dato=elemento;
		nodoActual=actual;

		if(nodoActual==NULL)
		{
			nodoAnterior=ultimo;
			ultimo=nuevo;
		}
		else
		{
			nodoAnterior=nodoActual->anterior;
			nodoActual->anterior=nuevo;
		}

		nuevo->siguiente=nodoActual;
		if(nodoAnterior==NULL) primero=nuevo;
		else nodoAnterior->siguiente=nuevo;

		nuevo->anterior=nodoAnterior;
		nElementos=nElementos+1;
		return 1; //Todo ha �do bi�n
	}*/
}

/*************************************************/

template <class T> bool Lista<T>::Existe(T elemento)
{
	bool trobat=false;

	Primero();
	while(!Fin() && !trobat)
	{
		if(elemento==Actual()) trobat=true;
		else Siguiente();
	}

	return trobat;
}

/*************************************************/

template <class T> void Lista<T>::Unir(Lista<T> l)
{
	//Unimos listas sin modificar el actual de la propia ni el de la l.
	Nodo *temp,*temp2;
	bool trobat=false;

	//temp=l.Actual(); //Pude ser NULL.
	temp=l.actual; //De tipo NODO!!!

	if(l.NElementos()>0)
	{
		l.Primero();
		while(!l.Fin())
		{
			Introducir(l.Actual());
			if (l.actual==temp)
			{
				temp2=ultimo;
			}
			l.Siguiente();
		}
	}

	//Volvemos a colocar el puntero actual de l donde estaba.
	l.actual=temp;
	actual=temp2;

	/*l.Primero();
	while(!l.Fin() && !trobat)
	{
		if(l.Actual()==temp) trobat=true;
		else l.Siguiente();
	}*/
}

/*************************************************

template <class T> Lista<T> Lista<T>::operator + (Lista<T> l)
{
	Lista<T> aux;

	Primero();
	while(!Fin())
	{
		aux.Introducir(Actual());
		Siguiente();
	}

	if(!l.Vacia())
	{
		l.Primero();
		while(!l.Fin())
		{
			aux.Introducir(l.Actual());
			l.Siguiente();
		}
	}

	return aux;
}*/

/*************************************************/

