/*************************************************/
/*                                               */
/*					AXLE.CPP		             */
/*                                               */
/*************************************************/


#include "Motor.h"
#include "conector.h" //No se si hace falta!!!
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado
Motor& Motor::operator=(Motor &c)
{

	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Axle::operator =(c); //Operador de asignación sobrecargado de la clase Axle
	}
	return *this;
}


/*************************************************/

//Redefinimos el método rotarConector de la clase conector para el Motor.
void Motor::rotarConector(/*sirMat4d r,bool sobreZ,*/unsigned short nTime,bool bAnimation,bool bAddKey)
{
	//Metodo que nos realizara la rotacion respecto al eje Z
	//Si rotamos respecto a otro eje, entonces llamamos al rotar del conector.

	Piece *pPieza=NULL;
	sirMat4d rotacion,matCentroPos,matCentroNeg,C2W;
	sirVector4d Z(0,0,1,0),axisX;
	Matrix matriz;
	float posicion[3],rot[4];
	bool trobat=false;
	int i;
	double aux[3];

	pPieza=this->obtenerMadre();

	if(pPieza!=NULL)
	{
		C2W=this->obtenerC2W();
		axisX=C2W*Z;
		aux[0]=axisX[0];
		aux[1]=axisX[1];
		aux[2]=axisX[2];

		for(i=0;i<4;i++);
			if(aux[i]< 0.001f)
				aux[i]=0;

//		imprimirVector(aux);

		matriz.Rotate(10,aux[0],aux[1],aux[2]);
		rotacion.introducir(matriz.m);

		pPieza->GetPosition(posicion);

		matCentroPos[0][3]=posicion[0];
		matCentroPos[1][3]=posicion[1];
		matCentroPos[2][3]=posicion[2];

		matCentroNeg[0][3]=-posicion[0];
		matCentroNeg[1][3]=-posicion[1];
		matCentroNeg[2][3]=-posicion[2];

		rotacion=rotacion*matCentroNeg;
		rotacion=matCentroPos*rotacion;

		pPieza->comunicarRotacion(rotacion,false);
		pPieza->piezasNoVisitadas();
		pPieza->transformar(nTime, bAnimation, bAddKey);
		pPieza->piezasNoVisitadas(); //Ponemos el flag visitada a flaso de las piezas que se les ha modificado, en este caso, las rotadas.*/
		//piezasNoVisitadas();

	}
	pPieza=NULL;

}
