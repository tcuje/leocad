/*************************************************/
/*                                               */
/*                  LISTA2.CPP                    */
/*                                               */
/*************************************************/


#include "lista2.h"
#include <afxwin.h>
#include <iostream.h>

/*************************************************/

//Constructor de la clase
template <class T> Lista2<T>::Lista2()
{
	actual=NULL;
	primero=NULL;
	ultimo=NULL;
	nElementos=0;
}

/*************************************************/

// Constructor de copia
template <class T> Lista2<T>::Lista2(Lista2<T> &l)
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
template <class T> Lista2<T>::~Lista2()
{
	Primero();
	while(!Fin()) Esborrar();
}

template <class T> void Lista2<T>::borrartodo()
{
	Primero();
	while(!Fin()) Esborrar();
}

/*************************************************/

//Operdor de asignación sobrecargado
template <class T> Lista2<T> & Lista2<T>::operator = (Lista2<T> &l)
{
	//Añade a la lista, la lista l poniendo el nuevo actual al que era en la lista l.
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
template <class T> bool Lista2<T>::Vacia(void)
{
	return primero==NULL;
}

/*************************************************/

// Lista dinámica no lo podemos saber
template <class T> bool Lista2<T>::Llena(void)
{
	return false;
}

/*************************************************/

// Sitúa el punto de interés en el primer elemento de la lista
template <class T> void  Lista2<T>::Primero(void)
{
	actual=primero;
}

/*************************************************/

// Sitúa el punto de interés en el último elemento de la lista
template <class T> void  Lista2<T>::Ultimo(void)
{
	actual=ultimo;
}

/*************************************************/

//Cierto si estamos al final de la llista
template <class T> bool Lista2<T>::Fin(void)
{
	return actual==NULL;
}

/*************************************************/

//Número de elementos de la lista
template <class T> int Lista2<T>::NElementos(void)
{
	return nElementos;
}

/*************************************************/

//Sitúa el puntro de interés en el siguiente elemento de la lista
template <class T> void  Lista2<T>::Siguiente(void)
{
  if(!Fin()) actual=actual->siguiente;
}

/*************************************************/

// Sitúa el punt de interés en el anterior elemento de la lista
/*template <class T> void  Lista2<T>::Anterior(void)
{
  if(!Fin()) actual=actual->anterior;
}

/*************************************************/

// Devuelve el contenido del elemento actual
template <class T> T Lista2<T>::Actual(void)
{
	if(!Fin()) return actual->dato;
	//else return NULL;
}

/*************************************************/

// Esborra el elemento actual
template <class T> void Lista2<T>::Esborrar()
{
	Nodo *posAnterior;


	if(!Fin())
	{
		posAnterior=primero;
		while (posAnterior->siguiente != actual)
		{
			posAnterior=posAnterior->siguiente;
		}

		posAnterior->siguiente=actual->siguiente;


		delete actual;
		nElementos=nElementos-1;
		actual=posAnterior;
	}
}

/*************************************************/

template <class T> bool Lista2<T>::Esborrar(T elemento)
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
template <class T> int Lista2<T>::Introducir(T elemento)
{
	Nodo *nuevo;
	T s[5];
	s[1]=elemento;
	s[2]='\0';
	AfxMessageBox(s);

	if(elemento==NULL)
		AfxMessageBox("hola");

	//Si T existe no lo introducimos.

	//NO modifica, pero no me hace falta.
	//Al menos no tendré elementos repetidos y no tendré que preguntar desde fuera si existe!!!
	if (elemento!=NULL)
	{
	if(!Existe(elemento))
	{
		nuevo=new Nodo;
		if(nuevo==NULL) return -1; //Señal de que no hay más memoria
		else
		{
			AfxMessageBox("hola listas que estoy por aqui solito ja ja ja ja 222222222222222");
			nuevo->dato=elemento;
			AfxMessageBox("hola listas 3333333333333333333333333333333333333333333333333333333");

			nuevo->siguiente=NULL;

			if (Vacia())
			{
				primero=nuevo;
			}
			else
			{
				ultimo->siguiente=nuevo;
			}

			ultimo=nuevo;
			actual=nuevo;

			nElementos=nElementos+1;
			return 1; //Todo ha ído bién
		}
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

template <class T> bool Lista2<T>::Existe(T elemento)
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

template <class T> void Lista2<T>::Unir(Lista2<T> l)
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

//Introducir por delante un nuevo elemento
template <class T> void Lista2<T>::IntroducirElementos(T elemento)
{
	Nodo *nuevo;
	T hola;

	//Si T existe no lo introducimos.

	//NO modifica, pero no me hace falta.
	//Al menos no tendré elementos repetidos y no tendré que preguntar desde fuera si existe!!!
	if(!Existe(elemento))
	{
		nuevo=new Nodo;
		if(nuevo==NULL) AfxMessageBox("no hay memoria"); //Señal de que no hay más memoria
		else
		{
			AfxMessageBox("hola listas que estoy por aqui solito ja ja ja ja 222222222222222");
			nuevo->dato=elemento;
			AfxMessageBox("hola listas 3333333333333333333333333333333333333333333333333333333");

			nuevo->siguiente=NULL;

			if (Vacia())
			{
				primero=nuevo;
			}
			else
			{
				ultimo->siguiente=nuevo;
			}

			ultimo=nuevo;

			actual=nuevo;

			nElementos=nElementos+1;

			if(hola==elemento) AfxMessageBox("me boy");

			//return 1; //Todo ha ído bién
		}
	}
	//return 1; //Todo ha ido bién pero el elemento ya existía.
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