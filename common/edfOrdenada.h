/*************************************************/
/*                                               */
/*				   EDFORDENADA.H	             */
/*                                               */
/*************************************************/


#ifndef EDFORDENADA_H
#define EDFORDENADA_H

/*
 * Clave    : Es el tipo de la clave
 * Elemento : Es el tipo que se guardar�
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
	  int actual;  // Es un apuntador al punto de inter�s de la lista
	  int nDatos;  // Indica el nombre de datos guardados en la lista

	  /*
	   * Funci�n privada que busca la clave c. trobat ser� cierto si la clave existe y en pos tendremos la posici�n de la clave y si no existe en la posici�n donde deber�a estar.
	   * @param c la clave a buscar.
	   * @param trobat nos informa de si la clave ha existe o no.
	   * @param pos es la posici�n de la clave si existe o la posci�n donde deber�a ir en el caso de no existir.
	   */
	  void Buscar(Clave c,bool &trobat,int & pos);

  public:
	  //Parte p�blica de la clase

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
	   * M�todo que devuelve cierto o falso dependiendo de si la clave c existe o no.
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
	  void Primero(void); /**< Nos sit�a en el primer elemento de la edf. */
	  void Siguiente(void); /**< Nos desplazamos al siguiente elemento de la edf. */
	  bool  Fin(void); /**< Devuelve cierto si estamos al final de la edf y falso en caso contrario.*/
	  bool  Vacia(void); /**< Devuelve cierto en el caso de que la edf est� vac�a, falso en el caso contrario. */
	  bool  Llena(void); /**< Devuelve cierto si la edf est� llena, falso en el caso contrario. */
	  int  NElementos(void); /**< Devuelve el n�mero de elementos que tiene la edf. */

	  /**
	   * Realiza la uni�n de dos EDFs.
	   * @param edf es la edf a a�adir con la propia de la instancia.
	   */
	  EdfOrdenada operator+(EdfOrdenada<Clave,Elemento,N> edf);

	  EdfOrdenada & operator=( EdfOrdenada<Clave,Elemento,N>  &edf); /**< Operador de asignaci�n. */

};

#endif







