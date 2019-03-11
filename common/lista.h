/*************************************************/
/*                                               */
/*                   LISTA.H                     */
/*                                               */
/*************************************************/

#ifndef LISTA_H
#define LISTA_H


template <class T>

/**
 * Clase plantilla lista dinámica doblemente encadenada con punto de interés.
 */

class Lista
{
	private:

		struct Nodo{
			T dato; /**< Información del nodo. */
			Nodo *siguiente /**< puntero al siguiente node. */,*anterior; /**< Puntero al nodo anterior. */
		};

		Nodo *primero /**< Puntero al primer nodo. */,*ultimo /**< Puntero al úntimo nodo. */,*actual /**< Puntero al nodo actual. */;
		int nElementos; /**< Número de elementos que hay introducidos en la lista. */

	public:

		Lista(); /**< Constructor por defecto. */
		/**
		 * Constructor de copia.
		 * @param l lista a copiar.
		 */
		Lista(Lista<T> &l);
		~Lista(); /**< Destructor de la clase. */

		//Sobrecarga de operadores
		/**
		 * Sobrecarga del operador de asignación.
		 * @param l lista a asignar.
		 */
		Lista& operator=(Lista &l);

		/**
		 * Método que une dos listas y devuelve una lista que es el resultado de la únión de ambas.
		 * @param l lista a unir.
		 */
		//Lista operator+(Lista l);

		void Unir(Lista<T> l);

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
		void Anterior(void); /**< Nos situa en el anterior elemento del actual. */
		bool Fin(void); /**< Cierto si hemos llegado al final de la lista. */
		bool Vacia(void); /**< Cierto si la lista no tiene más elementos. */
		bool Llena(void); /**< Si la lista está llena. */
		int NElementos(void); /**< Devulve le número de elementos de la lista. */
		bool Existe(T elemento); /**< Devuelve cierto si elemento existe en la lista. */

};

#endif