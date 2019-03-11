/*************************************************/
/*                                               */
/*                   LISTA2.H                     */
/*                                               */
/*************************************************/

#ifndef LISTA2_H
#define LISTA2_H


template <class T>

/**
 * Clase plantilla lista dinámica doblemente encadenada con punto de interés.
 */

class Lista2
{
	private:

		struct Nodo{
			T dato; /**< Información del nodo. */
			Nodo *siguiente; /**< puntero al siguiente node. */
		};

		Nodo *primero /**< Puntero al primer nodo. */,*ultimo /**< Puntero al úntimo nodo. */,*actual /**< Puntero al nodo actual. */;
		int nElementos; /**< Número de elementos que hay introducidos en la lista. */

	public:

		Lista2(); /**< Constructor por defecto. */
		/**
		 * Constructor de copia.
		 * @param l lista a copiar.
		 */
		Lista2(Lista2<T> &l);
		~Lista2(); /**< Destructor de la clase. */

		//Sobrecarga de operadores
		/**
		 * Sobrecarga del operador de asignación.
		 * @param l lista a asignar.
		 */
		Lista2& operator=(Lista2 &l);

		/**
		 * Método que une dos listas y devuelve una lista que es el resultado de la únión de ambas.
		 * @param l lista a unir.
		 */
		//Lista operator+(Lista l);

		void Unir(Lista2<T> l);

		/**
		 * Metodo que elimina todos los elementos que existen en una lista
		 */
		void borrartodo();


		//Métodos de la clase Lista
		/**
		 * Inserta un elemento.
		 * @param elemento dato a introducir.
		 */
		int Introducir(T elemento);
		void IntroducirElementos(T elemento);

		void Esborrar(void); /**< Esborra el elemento actual. */
		/**
		 * Esborra el elemento T de la lista.
		 * @param elemento a esborrar.
		 */
		bool Esborrar(T elemento);
		T Actual(void); /**< Obtiene el elemento actual. */
		void Primero(void); /**< Nos sitúa al principio de la lista. */
		void Siguiente(void); /**< Nos desplaza hacia el siguiente elemento. */
		void Ultimo(void); /**< Nos sitúa en el úmtimo elemento de la lista. */
//		void Anterior(void); /**< Nos situa en el anterior elemento del actual. */
		bool Fin(void); /**< Cierto si hemos llegado al final de la lista. */
		bool Vacia(void); /**< Cierto si la lista no tiene más elementos. */
		bool Llena(void); /**< Si la lista está llena. */
		int NElementos(void); /**< Devulve le número de elementos de la lista. */
		bool Existe(T elemento); /**< Devuelve cierto si elemento existe en la lista. */

};

#endif