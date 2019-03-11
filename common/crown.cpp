/*************************************************/
/*                                               */
/*					CROWN.CPP		             */
/*                                               */
/*************************************************/


#include "crown.h"
#include "piece.h"


/*************************************************/

//Operador de asignación sobrecargado (No se hereda!!!)
Crown& Crown::operator=(Crown &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}


/*************************************************/

//Redefinimos el método rotarConector de la clase conector para el Crown.
void Crown::rotarConector(sirMat4d r,int tooth/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	Conector *actual;
	sirMat4d C2W, A2W;
	sirVector4d normal(0,0,1,0),vector, vector2;
	sirVector3d rote, ruta;
	double rtooth;
	float rot[4];
	bool rotarZ;
	sirVector3d posicion;
	Matrix aux;

	double m[16];
	posicion[0]=r[0][3];
	posicion[1]=r[1][3];
	posicion[2]=r[2][3];

	rotarZ=this->rotarEjeZ(r);


	if(obligatorio && !rotarZ){Conector::rotarConector(r,false);}
	else
	{
		r.obtenerMatriz(m);
		aux.crear(m);
		aux.ToAxisAngle(rot);

		C2W=this->obtenerC2W();
		vector=C2W*normal;

		if(iguales(rot[0],vector[0])&&iguales(rot[1],vector[1])&&iguales(rot[2],vector[2]))
			rot[3]=(-1)*rot[3];

		rtooth=tooth*rot[3];
		rtooth=rtooth;

		conectados.Primero();
		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			if(rotarZ)
			{
				A2W=actual->obtenerC2W();
				vector2=A2W*normal;

				rot[0]=(float)vector2[0];
				rot[1]=(float)vector2[1];
				rot[2]=(float)vector2[2];

				actual->rotar(rot,rtooth,posicion);}
			else{

				actual->rotar(r,false);}
			conectados.Siguiente();
		}
		actual=NULL;
	}
}

/*************************************************/

void Crown::moverConector(sirVector3d t)
{
	Conector *pCon;

	//Se hagan los cálculos que se hagan siempre que se realice la traslación en el
	//eje Z del conector se recalcularán las conexiones
	//if(trasladarEjeZ(t)) recalcularConexiones=true;
	/******************************/
	recalcularConexiones=true;
	/******************************/

	if(obligatorio) Conector::moverConector(t);

	else
	{
		if(!visitado)
		{
			visitado=true;
			conectados.Primero();
			while(!conectados.Fin())
			{
				pCon=conectados.Actual();
				if (trasladarEjeZ(pCon,t))
					pCon->mover(t);
				conectados.Siguiente();
			}
		}
	}

}



/*************************************************/

bool Crown::rotarEjeZ(sirMat4d r)
{
	sirMat4d C2W,matMadre;
	sirMat4d aux,auxMat;
	sirVector4d X(1,0,0,0),Y(0,1,0,0),Z(0,0,1,0),axisXA,axisXD;
	float angulo;

//	matMadre=madre->matrizPieza();
	C2W=obtenerC2W();

	aux=r*C2W;

	axisXA=C2W*Z; //Eje Xdinámico en coordenadas de mundo.
	axisXD=aux*Z; //Eje Xestático en coordenadas de mundo-->+X,-X.

	//Hay que calcular el ángulo entre
	angulo=(float)anguloEntreEjes(axisXD,axisXA,&auxMat);


	return (angulo<=DELTA_FRAN+0.02);//&&(angulo>=(-0.09)));
}

/*************************************************/

double Crown::anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m)
{
	double normaEjeD,normaEjeS;
	double alfa,prodEscalar,normaProdVect;
	float auxRot[3];
	sirVector3d prodVect,ejeD,ejeE;
	Matrix aux;

	ejeD[0]=ejeDinamico[0];
	ejeD[1]=ejeDinamico[1];
	ejeD[2]=ejeDinamico[2];

	ejeE[0]=ejeEstatico[0];
	ejeE[1]=ejeEstatico[1];
	ejeE[2]=ejeEstatico[2];

	//Normalizamos a ambos vectores y obtenemos sus normas.
	ejeD.normalize();
	normaEjeD=ejeD.norm();
	ejeE.normalize();
	normaEjeS=ejeE.norm();

	//Producto vectorial-->estatico X dinamico-->ORDEN!!!
	prodVect=ejeD^ejeE;

	//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
	normaProdVect=prodVect.norm();

	//Calculamos el producto escalar
	prodEscalar=ejeD*ejeE;

	//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
	alfa=angulo(normaProdVect,prodEscalar);

	auxRot[0]=(float)prodVect[0];
	auxRot[1]=(float)prodVect[1];
	auxRot[2]=(float)prodVect[2];

	aux.FromAxisAngle(auxRot,(float)alfa); //Es lo mismo que crear la matriz de rotación de ángulo alfa a través del vector prodVect
	m->introducir(aux.m);

	return alfa;
}

/*************************************************/

bool Crown::Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t)
{
	int i;
	bool igual=true;

	for(i=0;i<3;i++)
	{
		if(t[i]!=0)
			if(pos1[i]!=pos2[i])
				igual=false;
	}

	return igual;
}
