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

//Operdor de asignación sobrecargado
template <class T> Lista<T> & Lista<T>::operator = (Lista<T> &l)
{
	//Añade a la lista, la lista l poniendo el nuevo actual al que era en la lista l.
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

// Cierto si la lista está vacía
// Si el primero apunta a null la lista está vacía
template <class T> bool Lista<T>::Vacia(void)
{
	return primero==NULL;
}

/*************************************************/

// Lista dinámica no lo podemos saber
template <class T> bool Lista<T>::Llena(void)
{
	return false;
}

/*************************************************/

// Sitúa el punto de interés en el primer elemento de la lista
template <class T> void  Lista<T>::Primero(void)
{
	actual=primero;
}

/*************************************************/

// Sitúa el punto de interés en el último elemento de la lista
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

//Número de elementos de la lista
template <class T> int Lista<T>::NElementos(void)
{
	return nElementos;
}

/*************************************************/

//Sitúa el puntro de interés en el siguiente elemento de la lista
template <class T> void  Lista<T>::Siguiente(void)
{
  if(!Fin()) actual=actual->siguiente;
}


/*************************************************/

// Sitúa el punt de interés en el anterior elemento de la lista
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

		//Es el último elemento
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
	//Al menos no tendré elementos repetidos y no tendré que preguntar desde fuera si existe!!!
	if(!Existe(elemento))
	{
		nuevo=new Nodo;
		if(nuevo==NULL) return -1; //Señal de que no hay más memoria
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
			return 1; //Todo ha ído bién
		}
	}
	return 1; //Todo ha ido bién pero el elemento ya existía.
	//Si existe no hacemos nada

	/*nuevo=new Nodo;
	if(nuevo==NULL) return -1; //Señal de que no hay más memoria
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
		return 1; //Todo ha ído bién
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

