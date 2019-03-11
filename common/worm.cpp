/*************************************************/
/*                                               */
/*					Worm.CPP		             */
/*                                               */
/*************************************************/


#include "Worm.h"
#include "piece.h"
#include "Administrador.h"

/*************************************************/

//Operador de asignación sobrecargado (No se hereda!!!)
Worm& Worm::operator=(Worm &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}


/*************************************************/

//Redefinimos el método rotarConector de la clase conector para el Worm.
void Worm::rotarConector(sirMat4d r,int tooth/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
{
	Conector *actual;
	sirMat4d C2W, A2W,auxMat;
	sirVector4d normal(0,0,1,0),vector, vector2,vec;
	sirVector3d rote, ruta, auxili;
	float rtooth,rot[4],rot2[4],angulo;
	bool rotarZ;
	sirVector3d posicion;
	Matrix aux;

	//Areglo
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

		vec[0]=(double)rot[0];
		vec[1]=(double)rot[1];
		vec[2]=(double)rot[2];
		vec[3]=0;
		rot2[3]=rot[3];

		C2W=this->obtenerC2W();
		vector=C2W*normal;

		conectados.Primero();

		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			if(rotarZ)
			{
				A2W=actual->obtenerC2W();
				vector2=A2W*normal;

				if(strcmp(actual->obtenerNombre(),"Spur")==0)
				{
					angulo=(float)anguloEntreEjes(vec,vector,&auxMat);
					if(angulo<=DELTA_FRAN+0.02)
					{
						rot2[3]=rot[3];
					}
					else
						rot2[3]=(-1)*rot[3];
				}

				if(strcmp(actual->obtenerNombre(),"Worm")==0)
				{
					angulo=(float)anguloEntreEjes(vec,vector2,&auxMat);
					if(angulo<=DELTA_FRAN+0.02)
						rot2[3]=rot[3];
					else
						rot2[3]=(-1)*rot[3];
				}

				rot2[0]=(float)vector2[0];
				rot2[1]=(float)vector2[1];
				rot2[2]=(float)vector2[2];


				rtooth=rot2[3];

				actual->rotar(rot2,rtooth,posicion);}
			else{

				actual->rotar(r,false);}
			conectados.Siguiente();
		}
		actual=NULL;
	}
}
/*************************************************/

void Worm::moverConector(sirVector3d t)
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


bool Worm::Ultimo_contacto(sirVector3d pos1,sirVector3d pos2, sirVector3d t)
{
	sirMat4d C2W,W2C;
	sirVector4d trans,normal(0,0,1,0),NP;
	sirVector3d nw,prodVect;
	double normaProdVect, prodEscalar, alfa;

	C2W=this->obtenerC2W();
	W2C=C2W.inverse();

	trans[0]=t[0];
	trans[1]=t[1];
	trans[2]=t[2];
	trans[3]=0;

	trans=W2C*trans;

	trans.normalize();

	imprimirVector(t);
	imprimirVector(pos1);
	imprimirVector(pos2);

	if(iguales(trans[0],0) && iguales(trans[1],0) && (iguales(trans[2],1) || iguales(trans[2],-1))) return true;
	else
	{
		NP=C2W*normal;
		nw[0]=NP[0];
		nw[1]=NP[1];
		nw[2]=NP[2];

		nw.normalize();
		t.normalize();

		//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
		prodVect=t^nw; //prodVect=normal^normal2;

		//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
		//prodVect.normalize();//normaProdVect=prodVect.normalize(); //También obtenemos su norma
		normaProdVect=prodVect.norm();

		//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
		prodEscalar=t*nw;//prodEscalar=normal*normal2;

		//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
		alfa=angulo(normaProdVect,prodEscalar);

		if(alfa>(90-DELTA_FRAN+2) && alfa<(90+DELTA_FRAN-2))
			return true;
		else
			return false;
	}
}


/*************************************************/

bool Worm::rotarEjeZ(sirMat4d r)
{
	sirMat4d C2W,matMadre;
	sirMat4d aux,auxMat;
	sirVector4d Z(0,0,1,0),axisXA,axisXD;
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

double Worm::anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m)
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
