/*************************************************/
/*                                               */
/*			    CYLINDRICALHOLE.CPP	             */
/*                                               */
/*************************************************/


#include "cylindricalHole.h" //Vigilar con la "A"!!!!!
#include "conector.h" //No se si hace falta!!!
#include "piece.h"

/*************************************************/

//Operador de asignación sobrecargado
CylindricalHole& CylindricalHole::operator=(CylindricalHole &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Extreme::operator =(c); //Operador de asignación sobrecargado de la clase Extreme
	}
	return *this;
}


/*************************************************/

void CylindricalHole::rotar(sirMat4d r,bool sobreZ/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	if(obligatorio) Extreme::rotar(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
	else
	{
		if(mensajedeStud)
		{
			mensajedeStud=false;
			Extreme::rotar(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
		}
		else
		{
			if(!rotarEjeZ(r)) Extreme::rotar(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
		}
	}
}

/*************************************************/

//Redefinimos el método rotar de la clase conector para el CylindricalHole.
void CylindricalHole::rotarConector(sirMat4d r,bool sobreZ/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	//Si rotamos respecto al eje Z del CH entonces no lo propagamos a los conectados del CylindricalHole!!!
	//Si rotamos respecto a otro eje, entonces llamamos al rotar del conector.

	Conector *actual;
	bool rotarZ;

	if(obligatorio) Extreme::rotarConector(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
	else
	{
		//if(!rotarEjeZ(r)) Extreme::rotarConector(r,nTime,bAnimation,bAddKey);
		rotarZ=rotarEjeZ(r);

		conectados.Primero();
		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			if(!strcmp(actual->obtenerNombre(),"stud")) Extreme::rotarConector(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
			else
			{
				if(!rotarZ) Extreme::rotarConector(r,sobreZ/*,nTime,bAnimation,bAddKey*/);
			}
			conectados.Siguiente();
		}
	}

	actual=NULL;
}

/*************************************************/

FRAN_SEGMENTO CylindricalHole::obtenerSegmento(sirMat4d W2C)
{
	//W2C es la matriz del conector al espacio del cual yo quiero pasar el conector actual.

	FRAN_SEGMENTO AB;
	sirMat4d C2W,C2C;
	sirVector4d A(0,0,0,1),B(0,0,longitud,1); //SON PUNTOS Y NO VECTORES!!!

	C2W=obtenerC2W();
	C2C=W2C*C2W;

	A=C2C*A;
	B=C2C*B;

	AB.A=A[2];
	AB.B=B[2];

	return AB;
}

/*************************************************/

FRAN_SEGMENTO CylindricalHole::obtenerSegmento(void)
{
	FRAN_SEGMENTO AB;

	AB.A=0;
	AB.B=longitud;

	return AB;
}

/*************************************************/

void CylindricalHole::mover(sirVector3d t/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	DISTANCIA_CONECTOR colision;
	Conector *conColision;
	sirMat4d W2C,C2W;
	sirVector4d trans(t[0],t[1],t[2],0),aux;
	sirVector3d nuevaTraslacion;
	double maxDistColision,moduloTraslacion;

	if(obligatorio) Extreme::mover(t/*,nTime,bAnimation,bAddKey*/);
	else if(mensajedeStud)
	{
		mensajedeStud=false;
		Extreme::mover(t);
	}
	else
	{
		if(!visitado)
		{
			visitado=true;

			if(!trasladarEjeZ(t)) Extreme::mover(t/*,nTime,bAnimation,bAddKey*/); //No traslada en el eje Z.
			else
			{

				//madre->transformada
				//madre->introducirTransformacion

				//Traslada en el eje Z.
				C2W=obtenerC2W();
				W2C=C2W.inverse();

				trans=W2C*trans;

				//if(madre->esPrimeraEnMover())
				//{
					//if(trans[2]>=0) colision=deteccionColisionesDeslizar(+1,t); //Miramos en el eje contrario
					//else colision=deteccionColisionesDeslizar(-1,t); //Calculamos colisiones al contrario de la dirección de traslación.
				//}
				//else
				//{
				if(trans[2]>=0) colision=deteccionColisionesDeslizar(-1,t); //Miramos en el eje contrario
				else colision=deteccionColisionesDeslizar(+1,t); //Calculamos colisiones al contrario de la dirección de traslación.
				//}

				maxDistColision=colision.distancia;
				conColision=colision.conColision;

				//madre->piezasNoVisitadas2();

				moduloTraslacion=t.norm();
				if(iguales(maxDistColision,0)) Extreme::mover(t);
				else if(iguales(maxDistColision,-1)) recalcularConexiones=true;
				else
				{
					if(iguales(moduloTraslacion,maxDistColision)) recalcularConexiones=true;
					else if(moduloTraslacion>maxDistColision) //Iguales se hubiera parado en maxDistColision==0
						{
						aux[0]=0;
						aux[1]=0;
						if(trans[2]>=0) aux[2]=maxDistColision; //???
						else aux[2]=-maxDistColision;
						aux[3]=0;

						aux=C2W*aux;

						nuevaTraslacion[0]=t[0]-aux[0];
						nuevaTraslacion[1]=t[1]-aux[1];
						nuevaTraslacion[2]=t[2]-aux[2];

						//Teóricamente debería recalcular conexiones hasta que choque.
						Extreme::mover(nuevaTraslacion);
					}
					else recalcularConexiones=true; //Teóricamente no haría falta
				}

				conColision=NULL;

				//if(iguales(maxDistColision,0)) Extreme::mover(t/*,nTime,bAnimation,bAddKey*/);
				//else recalcularConexiones=true;
			}
		}
	}
}

void CylindricalHole::moverConector(sirVector3d t/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	DISTANCIA_CONECTOR colision;
	Conector *conColision;
	sirMat4d W2C,C2W;
	sirVector4d trans(t[0],t[1],t[2],0),aux;
	sirVector3d nuevaTraslacion;
	double maxDistColision,moduloTraslacion;

	if(obligatorio) Extreme::moverConector(t/*,nTime,bAnimation,bAddKey*/);
	else if(mensajedeStud)
	{
		mensajedeStud=false;
		Extreme::moverConector(t);
	}
	else
	{
		if(!visitado)
		{
			visitado=true;
			if(!trasladarEjeZ(t)) Extreme::moverConector(t/*,nTime,bAnimation,bAddKey*/);
			else
			{
				//if(existeHermano) hermano->Conector::colisionSiDetectada();
				//Traslada en el eje Z.
				C2W=obtenerC2W();
				W2C=C2W.inverse();

				trans=W2C*trans;

				//if(!madre->esPrimeraEnMover())
				//{
					//if(trans[2]>=0) colision=deteccionColisionesDeslizar(-1);
					//else colision=deteccionColisionesDeslizar(+1);
				//}
				//else
				//{
				if(trans[2]>=0) colision=deteccionColisionesDeslizar(+1,t);
				else colision=deteccionColisionesDeslizar(-1,t);
				//}

				maxDistColision=colision.distancia;
				conColision=colision.conColision;

				moduloTraslacion=t.norm();
				if(iguales(maxDistColision,0)) conColision->mover(t); //Es mover porque el mensaje le viene de otro conector, sinó la madre no sería visitada!!! //Extreme::moverConector(t);
				else if(iguales(maxDistColision,-1)) recalcularConexiones=true;
				else
				{
					if(iguales(moduloTraslacion,maxDistColision)) recalcularConexiones=true;
					else if(moduloTraslacion>maxDistColision) //Iguales se hubiera parado en maxDistColision==0
					{
						aux[0]=0;
						aux[1]=0;
						if(trans[2]>=0) aux[2]=maxDistColision; //???
						else aux[2]=-maxDistColision;
						aux[3]=0;

						aux=C2W*aux;

						nuevaTraslacion[0]=t[0]-aux[0];
						nuevaTraslacion[1]=t[1]-aux[1];
						nuevaTraslacion[2]=t[2]-aux[2];

						//Teóricamente debería recalcular conexiones hasta que choque.
						Extreme::moverConector(nuevaTraslacion);
					}
					else recalcularConexiones=true; //Teóricamente no haría falta
				}

				conColision=NULL;

				//if(iguales(maxDistColision,0)) Extreme::moverConector(t/*,nTime,bAnimation,bAddKey*/);
				//else recalcularConexiones=true;
			}
		}
	}

}

/*************************************************/

bool CylindricalHole::trasladarEjeZ(sirVector3d t)
{
	sirMat4d C2W,W2C;
	sirVector4d trans;

	C2W=obtenerC2W();
	W2C=C2W.inverse();

	trans[0]=t[0];
	trans[1]=t[1];
	trans[2]=t[2];
	trans[3]=0;

	trans=W2C*trans;

	trans.normalize();

	if(iguales(trans[0],0) && iguales(trans[1],0) && (iguales(trans[2],1) || iguales(trans[2],-1))) return true;
	else return false;
}
