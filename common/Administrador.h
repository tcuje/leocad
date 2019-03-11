/*************************************************/
/*                                               */
/*               ADMINISTRADOR.H                 */
/*                                               */
/*************************************************/


#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "conector.h"
#include <string.h>
#include "lista.h"
#include "utilidades.h"

#include <fstream.h>

#include "Matrix.h"
#include "Algebra3.h"
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>
#include "listagestor.h"
#include "pasos.h"



class Piece;
class Conector;


class Administrador

{
private:


//	 Listagestor *ges;
	 bool posible;

	 bool distanciaRadios(Conector *pCon1,Conector *pCon2);

	 void coincidirYZ(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);


	 void AjustarInclinadas(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 void coincidirdientes(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 sirMat4d coincidirVectores(sirVector3d normal,sirVector3d normal2,sirVector3d rotacion);

	 sirVector3d CoincidirNormales90(Conector *estatico,Conector *dinamico);

	 sirVector3d Equacion_plano(sirMat4d S2W,sirMat4d D2W);
	 /**
	  * M�todo que crea la matriz de assembling a aplicar al conector din�mico para que las normales de ambos coincidan.
	  * @param estatico puntero al conector estatico del assembling.
	  * @param dinamico puntero al conector dinamico del assembling.
	  * @param normal vector a coincidir en orientacion
	  * @param alfa angulo en que deben coincidir las normales.
	  */
	  sirMat4d coincidirNormales(Conector *estatico,Conector *dinamico,sirVector4d normal,sirVector4d normal2,double alfa);

	 /**
	  * M�todo que obtiene la translaci�n a aplicar a la pieza din�mica para encajarla con la est�tica.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void AcomodarConector(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * M�todo que aplica la rotaci�n para que (Xs,Ys)=90�(Xd,Yd) a la pieza din�mica.
	  * Autom�ticamente el eje Yd quedar� fijado al fijar el Xd.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void CoincidenciaCruz(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * M�todo que calcula el �ngulo entre los dos ejes pasados por par�metro.
	  * @param ejeDinamico es el eje del conector din�mico.
	  * @param ejeEstatico es el eje del conector est�tico.
	  * @param m puntero a la matriz sobre la que se crea la matroz de rotaci�n para que (Xs,Ys)=90�(Xd,Yd).
	  */
	  double anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m);

	 /**
	  * Funci�n que crea la matriz a aplicar al conector din�mico para que (Xs,Ys)=90�(Xd,Yd).
	  * @param estatico es el puntero al conector estatico del assembling.
	  * @param dinamico es el puntero al conector din�mico del assembling.
	  */
	  sirMat4d minimoAnguloX(Conector *estatico,Conector *dinamico);

	 /**
	  * M�todo que devuleve la traslaci�n a aplicar a la pieza din�mica para encajarla
	  * dentro de la est�tica. Tambi�n actualiza el estado (libre/ocupado) de ambos conectores,
	  * as� como las longitudes libres de los extremos implicados en el assembing.
	  * @param estatico conector estatico del assembling.
	  * @param dinamico conector din�mico implicado en el assembling.
	  */
	  sirVector3d encajarConector(Conector *estatico,Conector *dinamico);

	 /**
	  * Funcion que me gestiona la actualizacion de lista de conectores ocupados.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  */
	  void LConectorLibrePO(Conector *estatico,Conector *dinamico);

	 /**
	  * Funci�n que me gestiona la actualizacion de lista de conectores libres
	  * y ocupados de la piezas
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  */
	  void LConectorConectado(Conector *estatico,Conector *dinamico);

	 /**
	  * Funci�n que me hace la tranformacion de la escena.
	  * @param madreDinamico es la pieza que sufrira las transfomaciones.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void animacion (Piece *madreDinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * M�todo com�n a todos los assemblings.
	  * Rota la pieza para que coincidan las normales de ambos conectores.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void coincidirN (Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Funcion que me realiza el calculo de la traslacions i que ademas lo realiza visualment
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void traslacion(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Funci�n que calcula el �ngulo dado el m�dulo del producto vectorial y el producto escalar.
	  * opp es el m�dulo del producto vectorial.
	  * adj es el producto escalar.
	  */
	  double angulo(double opp,double adj);

	 /**
	  * Funci�n que calcula si dos conectores se encuentran en la misma posici�n.
	  * @param pCon1 puntero al conector.
	  * @param pCon2 puntero al conector.
	  */
	  bool mismaPosicion(Conector *pCon1,Conector *pCon2);


	 /**
	  * Funci�n que devuelve cierto si dos conectores son coaxiales.
	  * @param pCon1 puntero al conector 1 a comparar con el 2.
	  * @param pCon2 puntero al conector 2 a comparar con el 1.
	  */
	  bool coaxiales(Conector *pCon1,Conector *pCon2);

	 /**
	  * Funci�n que devuelve cierto si el segmento de pCon2 est� libre en el conector pCon1.
	  * Si coge parte del hermano, tambi�n hay que mirar que est� libre.
	  * @param pCon1 puntero al conector.
	  * @param pCon2 puntero al conector.
	  */
	  bool segmentoLibre(Conector *pCon1,Conector *pCon2);

	 /**
	  * Funcion que devuelve cierto si (Xestatico,Yestatico)=0�,90�,180�,270�,360�(Xdinamico,Ydinamico).
	  * @param pCon1 puntero al conector estatico.
	  * @param pCon2 puntero al conector dinamico.
	  */
	  bool coincidirX(Conector *pCon1,Conector *pCon2);

	 /**
	  * Funci�n que devuelve el m�nimo �ngulo entre el eje X del conector y el X,-X,Y,-Y de pCon.
	  * Si el �ngulo es 0�,90�,180�,270� o 360� entonces los dos conectores estar�n en forma de cruz.
	  * @param pCon1 puntero al conector.
	  * @param pCon2 puntero al conector.
	  */
	  double anguloEntreConectores(Conector *pCon1,Conector *pCon2);

	 /**
	  * M�todo que busca el par de conectores para un tipo determinado, en caso que no estubieran
	  * definidos llegariamos al final de la lista y el metodo acabaria.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param tcon es el tipo de intrucciones si son para conectar o para verificar
	  */
	  void EncontrarInstrucciones(Conector *estatico,Conector *dinamico,char tcon);

	 /**
	  * Funci�n que lee el fichero de conexiones que continen un par de conectores
	  * y la informaci�n de los pasos para conectarlos. Devuelve -1: Fichero no existe
	  * o el path es err�neo. / 0: Fallo sint�ctico en el fichero. / 1: Todo correcto.
	  * @param path path donde se encuentra el fichero LCI a leer.
	  */
	  int leerFicheroConnec(char *path);

	 /**
	  * Rota la pieza para que coincidan las normales de ambos conectores siempre que no coincidan con
	  * la normal o con su opuesta.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void Normalantinormal(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void IntersectarPlano(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void UnirGear(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void AcomodarGear(Conector *estatico,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey);

	  sirMat4d Acoplamiento(Conector *estatico,Conector *dinamico);

	  void Normalesa90(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  bool PossibleUnir(Conector *estatico,Conector *dinamico,sirMat4d S2W,sirVector3d resultado,sirMat4d matMadreDinamico);

	  double anguloRealConectores(Conector *estatico,Conector *dinamico);

	  sirMat4d RotarSobresuEje(sirVector3d auxRot,double angulo,Conector *pCon);

	  bool distanciaInclinadas(Conector *pCon1,Conector *pCon2);

	  bool distanciacentro(Conector *pCon1,Conector *pCon2);

	  void Recalculo_traslacion(sirMat4d matNormales,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void Normalesa90nodistancia (Conector *estatico,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey);

	  void AjustarInclidifnormal(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void coincidirXZ(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	  void coincide(Conector *estatico,Conector *dinamico,sirVector4d a,sirVector4d b,unsigned short nTime,bool bAnimation,bool bAddKey);


public:
	 //Constructor por defecto
	  Administrador(char* binpath);
	 //Destructor por defecto
	  ~Administrador();

	  bool igualdadNormales90(Conector *pCon1,Conector *pCon2);

	 /**
	  * Funci�n que mira si coinciden los segmentos de los conectores.
	  * @param pCon1 puntero al conector
	  * @param pCon2 puntero al conector.
	  */
	  bool coincidencia(Conector *pCon1,Conector *pCon2);

	 /**
	  * M�todo que gestiona los pasos a realizar para que provoque el assembling entre los
	  * conectores estatico y dinamico.
	  * @param estatico puntero al conector estatico.
	  * @param dinamico puntero al conector dinamico.
	  * @param nTime
	  * @param bAnimation
	  * @param bAddKey
	  */
	  void gestion(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey);

	 /**
	  * Funcion que gestiona verificacion entre los conectores estatico y dinamico por si estos
	  * tubieran conexions secundarias a otras piezas. Si es a si y cumplen dichas condiciones
	  * entonces devolvera cierto.
	  * @param pCon1 puntero al conector estatico.
	  * @param pCon2 puntero al conector dinamico.
	  */
	  bool gestionVeri(Conector *pCon1,Conector *pCon2);

	 /**
	  * Funcion que devuelve cierto si los dos conectores se pueden conectar o verificar sus
	  * conexiones secundarias.
	  * @param primero puntero de un conector.
	  * @param segundo puntero del otro conector.
	  * @param tcon tipo de conexion
	  */
	  bool ExisteConector(Conector *primero,Conector *segundo,char tcon);

	 /**
	  * Funci�n que devuelve cierto si las normales de ambos conectores son la misma.
	  * @param pCon1 puntero al conector.
	  * @param pCon2 puntero al conector.
	  */
	  bool igualdadNormales(Conector *pCon1,Conector *pCon2,bool gear);

	  sirMat4d coincidirVectores(sirVector3d normal,sirVector3d normal2);


};

#endif
