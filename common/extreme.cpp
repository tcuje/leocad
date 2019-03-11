/*************************************************/
/*                                               */
/*					EXTREME.CPP		             */
/*                                               */
/*************************************************/


#include "extreme.h"
#include "piece.h"
#include "Administrador.h"

/*************************************************/

//Constructor por defecto
Extreme::Extreme(void)
{
	//Se llama automáticamente al constructor de la clase base
	//Inicializamos las variables de la propia clase.
	longitud=0;
	existeHermano=false;
	hermano=NULL;
	idHermanoLCI=-1;
	idLCI=-1;
	deslizando=false;
	mensajedeStud=false;

}

/*************************************************/

//Constructor con parámetros
Extreme::Extreme(int identificador,const char *nom,sirMat4d rot,Piece *pPieza,float l,Conector *brother) : Conector(identificador,nom,rot,pPieza)
{
	rotacion=rot;
	longitud=l; //Ya está en coordenadas LeoCAD.
	if(brother!=NULL)
	{
		existeHermano=true;
		hermano=brother;
	}
	else
	{
		existeHermano=false;
		hermano=NULL;
	}
	deslizando=false;
	mensajedeStud=false;

	//No hago nada con el id del conector hermano porque es el del fichero LCI.
	//A parte ya le pasamos el puntero al conector hermano.
}

/*************************************************/

//Operador de asignación sobrecargado no se hereda
Extreme& Extreme::operator=(Extreme &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		//Copiamos las variables de la propia clase Extreme
		longitud=c.longitud;
		existeHermano=c.existeHermano;
		hermano=c.hermano;
		idHermanoLCI=c.idHermanoLCI;
		idLCI=c.idLCI;
		deslizando=c.deslizando;
		mensajedeStud=c.mensajedeStud;
		//Copiamos el resto de variables
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}

/*************************************************/

//Constructor de copia
Extreme::Extreme(Extreme &c) : Conector(c)
{
	//Lamamos al constructor de copia de la clase conector y añadimos lo de la propia clase
	longitud=c.longitud;
	existeHermano=c.existeHermano;
	hermano=c.hermano;
	idHermanoLCI=c.idHermanoLCI;
	idLCI=c.idLCI;
	deslizando=c.deslizando;
	mensajedeStud=c.mensajedeStud;

}
/*************************************************/

bool Extreme::extremoEntreConectados(void)
{
	Conector *actual=NULL;
	sirMat4d C2W,W2C;
	FRAN_SEGMENTO CD;
	bool trobat=false;

	if(conectados.Vacia()) return false;
	else
	{
		C2W=obtenerC2W();
		W2C=C2W.inverse();
		//AB=obtenerSegmento(); //AB.A==0!!!

		conectados.Primero();
		while(!conectados.Fin() && !trobat)
		{
			actual=conectados.Actual();
			CD=actual->obtenerSegmento(W2C);
			if(entre1D(0,CD)) trobat=true; //En cuanto encontremos que coincide el estremo del conector con alguno de los conectados paramos-->OCUPADO!!!
			else conectados.Siguiente();
		}
		return trobat;
	}
}

/*************************************************/

bool Extreme::libre(void)
{
	if(conectados.Vacia()) return true; //Si no tiene ningún conector conectado estará libre.
	else if(extremoEntreConectados()) return false; //Si su extremo está entre alguno de sus conectores conectados no estará libre.
	else return true; //Si su extremo no está entr ninguno de sus conectados, si estará libre.
}

/*************************************************/

bool Extreme::ocupado(void)
{
	//No importa si hay 1 o 2 extremos.
	//Si está conectado a algún conector, entonces estará ocupado.
	if(conectados.NElementos()>=1) return true;
	else return false;
}


/*************************************************/



sirVector4d Extreme::obtenerPuntoInicial(void)
{
	sirMat4d C2W;
	sirVector4d resultado(0,0,0,1); //DEVOLVEMOS UN PUNTO!!!

	C2W=obtenerC2W();

	resultado[0]=C2W[0][3];
	resultado[1]=C2W[1][3];
	resultado[2]=C2W[2][3];

	return resultado;
}

/*************************************************/

sirVector4d Extreme::obtenerPuntoFinal(void)
{
	sirMat4d C2W;
	sirVector4d L(0,0,0,0),resultado(0,0,0,1); //DEVOLVEMOS UN PUNTO!!!

	C2W=obtenerC2W();
	L=obtenerTraslacionLongitud();

	resultado[0]=C2W[0][3]+L[0];
	resultado[1]=C2W[1][3]+L[1];
	resultado[2]=C2W[2][3]+L[2];

	return resultado;

	/*sirMat4d C2W;
	sirVector4d v(0,0,longitud,0),resultado(0,0,0,1); //DEVOLVEMOS UN PUNTO!!!

	C2W=obtenerC2W();
	v=C2W*v;

	resultado[0]=C2W[0][3]+v[0];
	resultado[1]=C2W[1][3]+v[1];
	resultado[2]=C2W[2][3]+v[2];

	return resultado;*/
}

/*************************************************/

sirVector4d Extreme::obtenerTraslacionLongitudZPositivo(void)
{
	sirMat4d C2W;
	sirVector4d L(0,0,longitud,0); //+LONGITUD

	C2W=obtenerC2W();
	L=C2W*L;

	return L;
}

/*************************************************/

bool Extreme::segmentoLibreHermano(Conector *pCon)
{
	Conector *actual;
	bool trobat=false;
	sirMat4d C2W,W2C;

	Administrador *ad;

	C2W=obtenerC2W();
	W2C=C2W.inverse();

	conectados.Primero();
	while(!conectados.Fin() && !trobat)
	{
		actual=conectados.Actual();
		if(ad->coincidencia(pCon,actual)) trobat=true;
		else conectados.Siguiente();
	}
	return (!trobat);
}



/*************************************************/

bool Extreme::coincidencia(Conector *pCon)
{
	sirMat4d C2W,W2C;
	FRAN_SEGMENTO AB,CD;

	C2W=obtenerC2W();
	W2C=C2W.inverse();

	AB=obtenerSegmento(); //También la matriz en el propio segmento!!!???!!!???!!!???!!!

	CD=pCon->obtenerSegmento(W2C);

	//Como es respecto al conector solo hace falta que cojamos la coordenada Z, que es la coaxial.
	//Hay que tener en cuenta que son coaxiales en el eje Z.
	//if(entre1D(CD.A,AB) || entre1D(CD.B,AB) || (fuera1D(CD.A,AB) && fuera1D(CD.B,AB)) ) return true;
	//else return false;

	//|-------| CIERTO   |------|
	//|-------|                 |--------------------| FALSO

	if(iguales1D(AB,CD)) return true;
	else if(coincidenUnExtremo(AB,CD)) return false;
	else if(entre1D(CD.A,AB) || entre1D(CD.B,AB) || ((inferior1D(CD.A,AB) && superior1D(CD.B,AB)) || (inferior1D(CD.B,AB) && superior1D(CD.A,AB))) ) return true;
	else return false;

}




/*************************************************/

void Extreme::initSegmento(Diccionario d)
{
	Tag t1("<lenght>"),t2("<id>"),t3("<brother>");

	longitud=leerNumeroParametro(d,t1); //Leemos la longitud.
	//Transformamos la longitud LDraw-->LeoCAD
	longitud=transformacionLeoCAD(longitud); //Longitud en coordenadas LeoCAD!!!

	if(d.Existe(t2))
	{
		idLCI=(int)leerNumeroParametro(d,t2);
		idHermanoLCI=(int)leerNumeroParametro(d,t3);

		//Como existe el hermano.
		existeHermano=true;
	}
	else existeHermano=false;
}

/*************************************************/

void Extreme::init(Diccionario d)
{
	Conector::init(d);
	initSegmento(d);
	deslizando=false;
	mensajedeStud=false;
}

/*************************************************/

double Extreme::obtenerLongitudLibre(void)
{
	//SERÍA MEJOR DISTANCIA 1D EN EL EJE Z!!!
	//Quizás no hiciera falta 1D-->Porque se supone que los conectados serán COAXIALES!!!

	//Libre si en el extremo (posición del conector más o menos) no hay conectado ningún otro conector.

	Conector *actual;
	sirMat4d C2W,A2W;
	double distMin=0,aux;

	if(conectados.Vacia()) return longitud;
	else if(libre())
	{
		C2W=obtenerC2W();
		conectados.Primero();
		actual=conectados.Actual();
		A2W=actual->obtenerC2W();
		distMin=distanciaPuntos(C2W[0][3],C2W[1][3],C2W[2][3],A2W[0][3],A2W[1][3],A2W[2][3]);
		conectados.Siguiente();
		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			A2W=actual->obtenerC2W();
			aux=distanciaPuntos(C2W[0][3],C2W[1][3],C2W[2][3],A2W[0][3],A2W[1][3],A2W[2][3]);
			if(aux<distMin) distMin=aux;
			conectados.Siguiente();
		}
		return distMin;
	}
	else return 0; //distMin==0;
}

/*************************************************/

bool Extreme::puedeDeslizar(void)
{
	//El conector será A,AH o CH.
	//Solo hay que mirar si alguno de los conectados es un A,AH o CH.
	//A->AH,A->CH.
	//AH->A.
	//CH->A.

	Conector *actual;
	bool trobat=false;

	conectados.Primero();
	while(!conectados.Fin() && !trobat)
	{
		actual=conectados.Actual();
		if( (!strcmp(actual->obtenerNombre(),"axle")) || (!strcmp(actual->obtenerNombre(),"axleHole")) || (!strcmp(actual->obtenerNombre(),"cylindricalHole")) ) trobat=true;
		else conectados.Siguiente();
	}
	return trobat;
}

/*************************************************/

Conector *Extreme::obtenerHermano(void)
{
	if(existeHermano) return hermano;
	else return NULL;
}

/*************************************************/

void Extreme::moverConector(sirVector3d t)
{
	/******************************/
	recalcularConexiones=true;
	/******************************/

	if(obligatorio) Conector::moverConector(t);
	else
	{
		if(!deslizando) Conector::moverConector(t);
	}
}

/*************************************************/

void Extreme::deslizar(sirVector3d t,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	activarModoDeslizar();
	//Si el conector tiene un hermano, también le activamos a él el modo de deslizamiento.
	if(existeHermano) hermano->activarModoDeslizar();

	//madre->deslizar(t,nTime,bAnimation,bAddKey); //Aplicamos el deslizamiento a la madre del conector.
	//Ponemos el flag de la madre y de las conectadas a ella a falso, después de mover.
	madre->comunicarTraslacion(t);
	madre->piezasNoVisitadas();
	madre->transformar(nTime,bAnimation,bAddKey);
	madre->piezasNoVisitadas();

	//Después de deslizar desactivamos el modo de deslizamiento.
	desactivarModoDeslizar();
	if(existeHermano) hermano->desactivarModoDeslizar();
	//Y EL HERMANO!!!
	//Volvemos a verificar las conexiones.
	//Lo hacemos des de fuera-->Project!!!
}

/*************************************************/

DISTANCIA_CONECTOR Extreme::deteccionColisionesDeslizar(int direccion,sirVector3d t)
{
		//Pasos:
	//	1.-Lista de conectados en dirección de deslizar (menos el conector a deslizar y su hermano, si tiene).
	//	   Contar también como elemento de la EDF los conectores sin hermano.
	//	2.-Partir la EDF original en dos listas.
	//		A).-Lista de los conectores conectados directa o indirectamente a la pieza del conector a deslizar.
	//		B).-Lista del resto.
	//	3.-Calcular distancias entre cada elemento de A con cada de B si el Z del elemento de A és más grande del Z del elemento de B, omás pequeño, dependiendo de la dirección.

	Piece *madreActual;
	Conector *actual,*hermanoActual,*dinamico,*estatico,*conStud;
	DISTANCIAS_COLISIONES distancias;
	DISTANCIA_CONECTOR colision;
	Lista<Conector *> colisiones,dinamicos,estaticos,conDeslizados;
	sirMat4d W2C;
	sirVector4d ID,FD,IS,IDC,FDC,ISC,final;
	FRAN_SEGMENTO segmento;
	double aux,distMin,finalConector,inicioConector;
	int i;
	bool existeStud=false;


	W2C=obtenerC2W();
	W2C=W2C.inverse();

	distancias.numeroDistancias=0;


	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		if(!strcmp(actual->obtenerNombre(),"stud"))
		{
			//colisiones.Introducir(actual);
			existeStud=true;
			conStud=actual;
		}
		else
		{
			actual->conectadosColisionDeslizar(direccion,this,&colisiones);
			if(actual->tengoHermano())
			{
				hermanoActual=actual->obtenerHermano();
				hermanoActual->conectadosColisionDeslizar(direccion,this,&colisiones);
			}
			else
			{
				//Y SU PUNTO OFINAL EN LA DIRECCIÓN DE DESLIZAR!!!!!!!!!!!!!!!!!

				final=actual->obtenerPuntoFinal();
				final=W2C*final;

				segmento=actual->obtenerSegmento(W2C);

				if(iguales(final[2],segmento.A))
				{
					finalConector=segmento.A;
					inicioConector=segmento.B;
				}
				else
				{
					finalConector=segmento.B;
					inicioConector=segmento.A;
				}

				if(direccion>=0)
				{
					if(finalConector<0)
					{
					}
					else if(iguales(finalConector,0) && inicioConector>0)
					{
					}
					else colisiones.Introducir(actual);
				}
				else
				{
					if(finalConector>0)
					{
					}
					else if(iguales(finalConector,0) && inicioConector<0)
					{
					}
					else colisiones.Introducir(actual);
				}
			}
		}
		conectados.Siguiente();
	}

	//Segundo paso.
	//Para encontrar los dinámicos y estáticos.
	//No vale encontrar camino a través de los que se deslizan.
	conDeslizados=listaConectadosPuedenDeslizar();

	colisiones.Primero();
	while(!colisiones.Fin())
	{
		actual=colisiones.Actual();
		madreActual=actual->obtenerMadre();

		if(madreActual->caminoDeAssemblings(this,conDeslizados)) dinamicos.Introducir(actual);
		else estaticos.Introducir(actual);

		//Hay que poner a las piezas visitadas como no visitadas,
		//para que el algoritmo funcione correctamente si tenemos
		//dos conectores de una misma pieza.

		madreActual->piezasNoVisitadas1();

		colisiones.Siguiente();
	}

	//Introducimos como dinámico el propio conector que se va a deslizar.
	//if(tengoHermano()) conectorNoVisitado();
	//else conectorVisitado();
	dinamicos.Introducir(this);

	//Tercer paso.
	//Las listas seguro que nunca estarán vacías.
	dinamicos.Primero();
	while(!dinamicos.Fin())
	{
		dinamico=dinamicos.Actual();
		estaticos.Primero();
		while(!estaticos.Fin())
		{
			estatico=estaticos.Actual();

			ID=dinamico->obtenerPuntoInicial();
			if(dinamico->tengoHermano())
			{
				hermanoActual=dinamico->obtenerHermano();
				FD=hermanoActual->obtenerPuntoInicial();
			}
			else FD=dinamico->obtenerPuntoFinal();

			//No lo puedo quitar porque si no no me detectará los conectores sin hermanos.
			if(!estatico->tengoHermano()) IS=estatico->obtenerPuntoFinal();
			else IS=estatico->obtenerPuntoInicial();

			IDC=W2C*ID;
			FDC=W2C*FD;
			ISC=W2C*IS;

			if(direccion>=0)
			{
				if(iguales(IDC[2],ISC[2]) || iguales(FDC[2],ISC[2])) distancias.distancias[distancias.numeroDistancias]=0;
				else if(IDC[2]<ISC[2]) distancias.distancias[distancias.numeroDistancias]=distanciaMinimaPuntoPuntos(IS,ID,FD);
			}
			else
			{
				if(iguales(IDC[2],ISC[2]) || iguales(FDC[2],ISC[2])) distancias.distancias[distancias.numeroDistancias]=0;
				else if(IDC[2]>ISC[2]) distancias.distancias[distancias.numeroDistancias]=distanciaMinimaPuntoPuntos(IS,ID,FD);
			}
			distancias.conectores[distancias.numeroDistancias]=estatico;
			distancias.numeroDistancias=distancias.numeroDistancias+1;

			estaticos.Siguiente();
		}
		dinamicos.Siguiente();
	}

	if(distancias.numeroDistancias==0)
	{
		colision.conColision=NULL;
		colision.distancia=-1;

		if(existeStud) conStud->mover(t);

		return colision; //return -1; //Señal de que puede deslizar hasta el infinito.
	}
	else
	{

		colision.distancia=distancias.distancias[0];
		colision.conColision=distancias.conectores[0];
		if(distancias.numeroDistancias>1)
		{
			for(i=1;i<distancias.numeroDistancias;i++)
			{
				aux=distancias.distancias[i];
				if(aux<colision.distancia)
				{
					colision.distancia=aux;
					colision.conColision=distancias.conectores[i];
				}
			}
		}

		if(existeStud) conStud->mover(t);

		return colision;
	}
}

/*************************************************/

void Extreme::desconectarDeslizan(void)
{
	Conector *actual;

	if(!visitado)
	{
		visitado=true;

		if(tengoHermano()) hermano->desconectarDeslizan();

		conectados.Primero();
		while(!conectados.Fin())
		{
			actual=conectados.Actual();
			if(actual->puedeDeslizar()) actual->desconectarDeslizan();
			conectados.Siguiente();
		}

		desconectar();
	}

}

