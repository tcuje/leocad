/*************************************************/
/*                                               */
/*					Rack.CPP		             */
/*                                               */
/*************************************************/


#include "rack.h"
#include "piece.h"
#include "Administrador.h"

/*************************************************/

//Operador de asignación sobrecargado (No se hereda!!!)
Rack& Rack::operator=(Rack &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}


/*************************************************/

//Redefinimos el método rotarConector de la clase conector para el Rack.
void Rack::rotarConector(sirMat4d r,int tooth/*,unsigned short nTime,bool bAnimation,bool bAddKey*/)
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

				if(strcmp(actual->obtenerNombre(),"Rack")==0)
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

void Rack::moverConector(sirVector3d t)
{
	Administrador *ad=NULL;
	Conector *actual;
	sirVector4d normal(0,0,1,0),x(0,0,1,0),vec,vectory,vectores2;
	sirVector3d vecn,vector2,posicion;
	sirMat4d resultado,C2W,A2W;
	double a, rtooth,aux[16],distancia,dientes,alfa;
	Matrix m2;
	float rot[4];

	//Se hagan los cálculos que se hagan siempre que se realice la traslación en el
	//eje Z del conector se recalcularán las conexiones
	//if(trasladarEjeZ(t)) recalcularConexiones=true;
	/******************************/
	recalcularConexiones=true;
	/******************************/

	if(obligatorio) Conector::moverConector(t);
	else
	{
		conectados.Primero();

		while(!conectados.Fin())
		{
			actual=conectados.Actual();

			if(strcmp(actual->obtenerNombre(),"Rack")==0)
			{
				Conector::moverConector(t);
			}
			else
			{
				C2W=this->obtenerC2W();
				vec=C2W*normal;
				vecn[0]=vec[0];
				vecn[1]=vec[1];
				vecn[2]=vec[2];

				resultado=ad->coincidirVectores(t,vecn);

				resultado.obtenerMatriz(aux);
				m2.crear(aux);
				m2.ToAxisAngle(rot);
				vector2[0]=rot[0];
				vector2[1]=rot[1];
				vector2[2]=rot[2];


				if(rot[3]==0)
				{
//					imprimirVector(t);

					a=t[0]+t[1]+t[2];

					if (a<0)
						distancia=(-1)*t.norm();
					else
						distancia=t.norm();


					dientes=(this->obtenerradio()*2)/(this->obtenerNdientes());
					dientes=distancia/dientes;

					A2W=actual->obtenerC2W();
					vectores2=A2W*x;
					rot[0]=(float)vectores2[0];
					rot[1]=(float)vectores2[1];
					rot[2]=(float)vectores2[2];

					posicion[0]=A2W[0][3];
					posicion[1]=A2W[1][3];
					posicion[2]=A2W[2][3];

					alfa=360.0/actual->obtenerNdientes();
					rtooth=(dientes*alfa);

					antesrack=true;

					actual->rotar(rot,rtooth,posicion);
				}

			}
/*			rot2[0]=(float)vector2[0];
			rot2[1]=(float)vector2[1];
			rot2[2]=(float)vector2[2];

			rtooth=rot2[3];

			actual->rotar(rot2,rtooth,posicion);}
			else{

			actual->rotar(r,false);}
*/			conectados.Siguiente();
		}
		actual=NULL;

		if(!visitado)
		{
			visitado=true;
			/*if(!trasladarEjeZ(t))/ Conector::moverConector(t);*/

		}
	}

}

/*************************************************/

bool Rack::trasladarEjeZ(sirVector3d t)
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

/*************************************************/

bool Rack::rotarEjeZ(sirMat4d r)
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

double Rack::anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m)
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
