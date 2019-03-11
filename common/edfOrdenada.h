/*************************************************/
/*                                               */
/*				   EDFORDENADA.H	             */
/*                                               */
/*************************************************/


#ifndef EDFORDENADA_H
#define EDFORDENADA_H

/*
 * Clave    : Es el tipo de la clave
 * Elemento : Es el tipo que se guardará
 * N        : Es el nombre de elementos que se pueden guardar
 */

template <class Clave,class Elemento,int N> class EdfOrdenada
{
  private:
	  //Parte privada de la clase

	  struct Nodo {
		  Clave c;
		  Elemento e;
	  };

	  Nodo *datos;
	  int actual;  // Es un apuntador al punto de interés de la lista
	  int nDatos;  // Indica el nombre de datos guardados en la lista

	  /*
	   * Función privada que busca la clave c. trobat será cierto si la clave existe y en pos tendremos la posición de la clave y si no existe en la posición donde debería estar.
	   * @param c la clave a buscar.
	   * @param trobat nos informa de si la clave ha existe o no.
	   * @param pos es la posición de la clave si existe o la posción donde debería ir en el caso de no existir.
	   */
	  void Buscar(Clave c,bool &trobat,int & pos);

  public:
	  //Parte pública de la clase

	  EdfOrdenada(); /**< Constructor por defecto de la clase EdfOrdenada. */
	  EdfOrdenada(const EdfOrdenada &e); /**< constructor de copia. */
	  ~EdfOrdenada(); /**< Destructor de la clase. */

	  /*
	   * Introduce la clave c con el elemento e asociado.
	   * Si la clave ja existe, modifica el valor del elemento.
	   * @param c clave a introducir.
	   * @param e elemento asociado a la clave a introducir.
	   */
	  void Introducir(Clave c,Elemento e);

	  /*
	   * Borra la clave c de la edf.
	   * @param clave a borrar.
	   */
	  void Borrar(Clave c);

	  /*
	   * Método que devuelve cierto o falso dependiendo de si la clave c existe o no.
	   * @param c clave a saber si exite en la edf.
	   */
	  bool  Existe(Clave c);

	  /*
	   * Devuelve el elemento asociado a la clave c.
	   * @param c clave de la que queremos consultar el elemento.
	   */
	  Elemento Consultar(Clave c);
	  Clave ClaveActual(void); /**< Devuelve la clave actual del a edf. */
	  Elemento ElementoActual(void); /**< Devuelve el elemento actual de la edf. */
	  void Primero(void); /**< Nos sitúa en el primer elemento de la edf. */
	  void Siguiente(void); /**< Nos desplazamos al siguiente elemento de la edf. */
	  bool  Fin(void); /**< Devuelve cierto si estamos al final de la edf y falso en caso contrario.*/
	  bool  Vacia(void); /**< Devuelve cierto en el caso de que la edf esté vacía, falso en el caso contrario. */
	  bool  Llena(void); /**< Devuelve cierto si la edf está llena, falso en el caso contrario. */
	  int  NElementos(void); /**< Devuelve el número de elementos que tiene la edf. */

	  /**
	   * Realiza la unión de dos EDFs.
	   * @param edf es la edf a añadir con la propia de la instancia.
	   */
	  EdfOrdenada operator+(EdfOrdenada<Clave,Elemento,N> edf);

	  EdfOrdenada & operator=( EdfOrdenada<Clave,Elemento,N>  &edf); /**< Operador de asignación. */

};

#endif







