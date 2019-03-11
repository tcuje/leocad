/*************************************************/
/*                                               */
/*              ADMINISTRADOR.CPP                */
/*                                               */
/*************************************************/


#include "Administrador.h"
#include "conector.h"
#include "Piece.h"
#include "extreme.h"
#include "pasos.h"
#include "practica.tab.h"

#define INICIO_ASSEMBLING "<assembling>"
#define INICIO_VERIFICAR "<verificar>"
#define INICIO_CONECTORA "<connectorA>"
#define INICIO_CONECTORB "<connectorB>"
#define INICIO_TYPE "<type>"
#define INICIO_STEP "<step>"

#define FIN_ASSEMBLING "</assembling>"
#define FIN_VERIFICAR "</verificar>"
#define FIN_CONECTORA "</connectorA>"
#define FIN_CONECTORB "</connectorB>"
#define FIN_TYPE "</type>"
#define FIN_STEP "</step>"

//Constructor por defecto
Administrador::Administrador(char* binpath)
{
	ges=new Listagestor();
	posible=true;
	opbevel=false;

	char cadena[300],cadena1[300];
	char fitxer[15];

	strcpy(fitxer,"manager.ges");
	strcpy(cadena,binpath);
	strcat(cadena,fitxer);
	switch(leerFicheroConnec(cadena))
	{
	case -1://Fichero no existe
		strcpy(cadena1,"Error: File ");
		strcat(cadena1,"manages.ges");
		strcat(cadena1," doesn't exist in folder ");
		AfxMessageBox(cadena1);
		break;
	case 1://Fichero con errores sintácticos
		strcpy(cadena1,"Error: File ");
		strcat(cadena1," has sintactics errors");
		AfxMessageBox(cadena1);
		break;
	case 0://Todo correcto
		break;
	}

}

/*************************************************/

Administrador::~Administrador()
{
	Pasos *pares;

	ges->Primero();
	while (!ges->Fin())
	{
		pares=new Pasos();
		*pares=ges->Actual();
		pares->EliminarPasos();
		ges->Esborrar();
		delete pares;
		ges->Siguiente();
	}
	delete ges;
}

int Administrador::leerFicheroConnec(char *path)
{
	//Si devulve -1-->Fichero no existe o el path está mal
	//            1-->Fallo sintáctico en el fichero .lci
	//            0-->Todo correcto

	//El compararTag deja "indice" apuntando al primer carácter de la línea!!!
	//La transformación de coordenadas LDraw-->LeoCAD las realizará el propio conector!!!
	int i;

	i=parser(path);

	return i;
}



bool Administrador::ExisteConector(Conector *primero,Conector *segundo,char tcon)
{
	EncontrarInstrucciones(primero,segundo,tcon);
	if(ges->Fin())
	{
		return false;
	}
	else
	{
		return true;
	}
}

/***********************************************************/


void Administrador::EncontrarInstrucciones(Conector *estatico,Conector *dinamico,char tcon)
{
	char primero[20],segundo[20], conA[20],conB[20];
	bool trobat=false;
	int b=ges->NElementos();
	Pasos *pares;

	strcpy(primero,estatico->obtenerNombre());
	strcpy(segundo,dinamico->obtenerNombre());

	ges->Primero();

	while (!trobat && b>0)
	{
		pares=new Pasos();
		*pares=ges->Actual();

		pares->obtenerconectorA(conA);
		pares->obtenerconectorB(conB);

		if((strcmp(primero,conA)==0 && strcmp(segundo,conB)==0) || (strcmp(primero,conB)==0 && strcmp(segundo,conA)==0))
		{
			trobat=true;
		}
		else
		{
			ges->Siguiente();
			b--;
		}
	delete pares;
	}

}

/*************************************************/

void Administrador::gestion(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{

	char pas,cadena[200];
	Pasos *pares;
	pares=new Pasos();


	strcpy(cadena,"Error: it is possible that the assembling has not been realised correctly\n");
	strcat(cadena,"because of a no valid step. Modify the file manager.ges for its correct function");

	EncontrarInstrucciones(estatico,dinamico,'c');
	if (ges->Fin())
	{
		AfxMessageBox("doesn't exist connector in manages.ges");
	}
	else
	{
		*pares=ges->Actual();

		pares->PrimerPasos();
		do
		{
		pas=pares->obtenerPasos();

		switch(pas)
		{
			case 'A':if(posible) coincidirN(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("coincidir");break;
			case 'B':if(posible) traslacion(estatico,dinamico,nTime,bAnimation,bAddKey);break;
			case 'C':if(posible) CoincidenciaCruz(estatico,dinamico,nTime,bAnimation,bAddKey);break;
			case 'D':if(posible) AcomodarConector(estatico,dinamico,nTime,bAnimation,bAddKey);break;
			case 'E':if(posible) LConectorConectado(estatico,dinamico);break;
			case 'F':if(posible) LConectorLibrePO(estatico,dinamico);break;
			case 'G':if(posible) Normalantinormal(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("ver");break;
			case 'H':if(posible) IntersectarPlano(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("interplano");break;
			case 'I':if(posible) UnirGear(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("unigear");break;
			case 'J':if(posible) AcomodarGear(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("acomodargear");break;
			case 'K':if(posible) Normalesa90(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("normal90");break;
			case 'L':if(posible) AjustarInclinadas(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("ajusteinclinacion");break;
			case 'M':if(posible) coincidirdientes(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("coincidirdientes");break;
			case 'N':if(posible) coincidirYZ(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("coincidirYZ");break;
			case 'O':if(posible) Normalesa90nodistancia(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("normal90nodistancia");break;
			case 'P':if(posible) AjustarInclidifnormal(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("ajuste incli normal"); break;
			case 'Q':if(posible) coincidirXZ(estatico,dinamico,nTime,bAnimation,bAddKey);AfxMessageBox("coincidirXZ");break;
			default: {posible=false;AfxMessageBox(cadena);}
		}
		pares->SiguientePasos();
		}while (!pares->FinPasos());

		delete pares;
		posible=true;
	}
}

void Administrador::coincidirXZ(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirVector4d z(0,0,1,0),x(-1,0,0,0);

	coincide(estatico,dinamico,x,z,nTime,bAnimation,bAddKey);
}

void Administrador::coincide(Conector *estatico,Conector *dinamico,sirVector4d a,sirVector4d b,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d S2W,D2W,resultado;
	sirVector4d nE,nD;
	sirVector3d normaE,normaD;
	Piece *madreDinamico;

	madreDinamico=dinamico->obtenerMadre();

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	if(strcmp(estatico->obtenerNombre(),"Rack")==0)
	{
		nE=S2W*a;
		nD=D2W*b;
		normaE[0]=nE[0];
		normaE[1]=nE[1];
		normaE[2]=nE[2];
		normaD[0]=nD[0];
		normaD[1]=nD[1];
		normaD[2]=nD[2];

	}
	else if(strcmp(dinamico->obtenerNombre(),"Rack")==0)
	{
		nE=S2W*b;
		nD=D2W*a;
		normaE[0]=nE[0];
		normaE[1]=nE[1];
		normaE[2]=nE[2];
		normaD[0]=nD[0];
		normaD[1]=nD[1];
		normaD[2]=nD[2];
	}

	resultado=coincidirVectores(normaE,normaD);

	madreDinamico->comunicarRotacion(resultado,false);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	//Para no eliminar el objeto pieza al acabar el método.
	madreDinamico=NULL;
}

void Administrador::coincidirYZ(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirVector4d z(0,0,1,0),y(0,1,0,0);

	coincide(estatico,dinamico,y,z,nTime,bAnimation,bAddKey);
}


void Administrador::coincidirdientes(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d S2W,D2W,rotar;
	sirVector4d z(0,0,1,0),x(1,0,0,0),y(0,1,0,0),nE,nD,distancia2;
	sirVector3d trans,normaE,normaD,distancia;
	Piece *madreDinamico;
	Matrix aux;
	sirMat4d matEstatico,matDinamico,resultado;
	sirVector3d nEstatico,nDinamico,prodVect;
	double normaProdVect;
	double prodEscalar;
	float auxRot[3];
	double alfa;


	madreDinamico=dinamico->obtenerMadre();

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	if(strcmp(estatico->obtenerNombre(),"Rack")==0)
	{
		//Obtenemos la translación a aplicar a la pieza dinámica y a las conectadas a ellas.
		trans=obtenerTranslacion(S2W,D2W);

		madreDinamico->comunicarTraslacion(trans);
		animacion(madreDinamico,nTime,bAnimation,bAddKey);

	}
	else if(strcmp(dinamico->obtenerNombre(),"Rack")==0)
	{
		nE=D2W*x;
		normaE[0]=nE[0];
		normaE[1]=nE[1];
		normaE[2]=nE[2];

		distancia=obtenerTranslacion(D2W,S2W);

		//Normalizamos a ambos vectores y obtenemos sus normas
		normaE.normalize();//normaEstatico=nEstatico.normalize();
		distancia.normalize();//normaDinamico=nDinamico.normalize();

		//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
		prodVect=normaE^distancia; //prodVect=nEstatico^nDinamico;

		//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
		//prodVect.normalize();//normaProdVect=prodVect.normalize(); //También obtenemos su norma
		normaProdVect=prodVect.norm();

		//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
		prodEscalar=normaE*distancia;//prodEscalar=nEstatico*nDinamico;


		//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
		alfa=angulo(normaProdVect,prodEscalar);

		//opcion para que toda pieza rote sobre su propio eje siempre
		opbevel=true;
		//Creamos la matriz de rotación con el vector y ángulo de rotación a través de él
		//utilizando la "Fórmula de Rodrigues".
/*
		nE=D2W*z;
		normaE[0]=nE[0];
		normaE[1]=nE[1];
		normaE[2]=nE[2];

		prodVect=normaE;
*/
		auxRot[0]=(float)prodVect[0];
		auxRot[1]=(float)prodVect[1];
		auxRot[2]=(float)prodVect[2];

		aux.FromAxisAngle(auxRot,(float)alfa); //Es lo mismo que crear la matriz de rotación de ángulo alfa a través del vector prodVect
		resultado.introducir(aux.m);

		madreDinamico->comunicarRotacion(resultado,false);
		animacion(madreDinamico,nTime,bAnimation,bAddKey);

	}
	//Para no eliminar el objeto pieza al acabar el método.
	madreDinamico=NULL;
}
void Administrador::AjustarInclinadas(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d S2W,D2W;
	sirVector4d normal(0,0,1,0),nE,nD;
	sirVector3d trans,normaE,normaD,auxE,auxD;
	Piece *madreDinamico;

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	normaD=obtenerTranslacion(D2W,S2W);;

	normaD.normalize();

	traslacion(estatico,dinamico,nTime,bAnimation, bAddKey);

	madreDinamico=dinamico->obtenerMadre();

	nE=S2W*normal;
	normaE[0]=nE[0];
	normaE[1]=nE[1];
	normaE[2]=nE[2];

	trans=(-1)*dinamico->obtenerradio()*normaE;

	opbevel=true;

	madreDinamico->comunicarTraslacion(trans);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=dinamico->obtenerMadre();

	trans=estatico->obtenerradio()*normaD;

	madreDinamico->comunicarTraslacion(trans);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=NULL;
}

void Administrador::AjustarInclidifnormal(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d S2W,D2W;
	sirVector4d normal(0,0,1,0),nE,nD;
	sirVector3d trans,trans1,normaE,normaD,auxE,auxD, novalido(0,0,0);
	Piece *madreDinamico;

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	normaD=obtenerTranslacion(D2W,S2W);;

	normaD.normalize();

	traslacion(estatico,dinamico,nTime,bAnimation, bAddKey);

	madreDinamico=dinamico->obtenerMadre();

	if((strcmp(estatico->obtenerNombre(),"Worm")==0)||(strcmp(estatico->obtenerNombre(),"Rack")==0))
		nE=D2W*normal;
	else
		nE=S2W*normal;

	normaE[0]=nE[0];
	normaE[1]=nE[1];
	normaE[2]=nE[2];

	if((strcmp(estatico->obtenerNombre(),"Worm")==0))
	{
		trans=estatico->obtenerradio()*normaE;
		trans1=dinamico->obtenerradio()*normaD;
	}
	else if(strcmp(estatico->obtenerNombre(),"Rack")==0)
	{
		trans=dinamico->obtenerradio()*normaE;
		trans1=novalido;
	}
	else if(strcmp(dinamico->obtenerNombre(),"Rack")==0)
	{
		trans=novalido;
		trans1=estatico->obtenerradio()*normaD;
	}
	else
	{
		trans=(-1)*dinamico->obtenerradio()*normaE;
		trans1=estatico->obtenerradio()*normaD;
	}

	opbevel=true;

	madreDinamico->comunicarTraslacion(trans);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=dinamico->obtenerMadre();

	madreDinamico->comunicarTraslacion(trans1);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=NULL;
}

void Administrador::Normalesa90 (Conector *estatico,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d matNormales;
	sirVector4d normal(0,0,1,0);
	sirMat4d S2W,D2W;
	sirVector4d nD;
	sirVector3d nEstatico,nDinamico;

	//Conectores en coordenadas de mundo.
	D2W=dinamico->obtenerC2W();

	//Vector normal del conector estático en coordenadas de mundo
	nD=D2W*normal;
	nDinamico[0]=nD[0];
	nDinamico[1]=nD[1];
	nDinamico[2]=nD[2];

	nEstatico=CoincidirNormales90(estatico,dinamico);
	matNormales=coincidirVectores(nEstatico,nDinamico);

	Recalculo_traslacion(matNormales,dinamico,nTime,bAnimation,bAddKey);
}

void Administrador::Recalculo_traslacion(sirMat4d matNormales,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico;
	sirMat4d matCentroPos,matCentroNeg;
	float pos[3];

	madreDinamico=dinamico->obtenerMadre();
	madreDinamico->GetPosition(pos);

	matCentroPos[0][3]=pos[0];
	matCentroPos[1][3]=pos[1];
	matCentroPos[2][3]=pos[2];

	matCentroNeg[0][3]=-pos[0];
	matCentroNeg[1][3]=-pos[1];
	matCentroNeg[2][3]=-pos[2];

	matNormales=matNormales*matCentroNeg;
	matNormales=matCentroPos*matNormales;

	madreDinamico->comunicarRotacion(matNormales,false);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=NULL;

}

void Administrador::Normalesa90nodistancia (Conector *estatico,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey)
{
	sirMat4d matNormales,matDinamico;
	sirMat4d S2W,D2W;
	sirVector4d nE,nD,normal(0,0,1,0);
	sirVector3d nEstatico,nDinamico,V0,Tu;
	double longradio;

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	//Vector normal del conector estático en coordenadas de mundo
	nE=S2W*normal;
	nEstatico[0]=nE[0];
	nEstatico[1]=nE[1];
	nEstatico[2]=nE[2];

	nD=D2W*normal;
	nDinamico[0]=nD[0];
	nDinamico[1]=nD[1];
	nDinamico[2]=nD[2];

	if(strcmp(dinamico->obtenerNombre(),"Rack")==0)
		longradio=estatico->obtenerradio();
	else
		longradio=dinamico->obtenerradio();

	V0=obtenerinterseccionradio(D2W,S2W,0,longradio);

	V0.normalize();

	nEstatico.normalize();

	Tu=V0^nEstatico;

	if(strcmp(estatico->obtenerNombre(),"Rack")==0)
		Tu=(-1)*Tu;

	matNormales=coincidirVectores(Tu,nDinamico);

	Recalculo_traslacion(matNormales,dinamico,nTime,bAnimation,bAddKey);

}
sirMat4d Administrador::RotarSobresuEje(sirVector3d auxRot,double angulo,Conector *pCon)
{
	Piece *madreConector;
	sirMat4d matCentroPos,matCentroNeg,resultado;
	float pos[3];
	Matrix aux;

	float auxi[3];
	auxi[0]=(float)auxRot[0];
	auxi[1]=(float)auxRot[1];
	auxi[2]=(float)auxRot[2];

	aux.FromAxisAngle(auxi,(float)angulo); //Es lo mismo que crear la matriz de rotación de ángulo alfa a través del vector prodVect
	resultado.introducir(aux.m);

	//NO ESTOY SEGURO!!!
	//Rotamos respecto al centro del conector y no respecto al centro de la pieza, que no tienen porqué coincidir.
	madreConector=pCon->obtenerMadre();
	madreConector->GetPosition(pos);

	matCentroPos[0][3]=pos[0];//D2W[0][3];
	matCentroPos[1][3]=pos[1];//D2W[1][3];
	matCentroPos[2][3]=pos[2];//D2W[2][3];

	matCentroNeg[0][3]=-pos[0];//-D2W[0][3];
	matCentroNeg[1][3]=-pos[1];//-D2W[1][3];
	matCentroNeg[2][3]=-pos[2];//-D2W[2][3];

	resultado=resultado*matCentroNeg;
	resultado=matCentroPos*resultado;

	madreConector=NULL;

	return resultado;
}
double Administrador::anguloRealConectores(Conector *estatico,Conector *dinamico)
{
	Piece * madreDinamico;
	double temp;
	sirMat4d matCentroPos,matCentroNeg,resultado,matMadreDinamico;
	sirVector3d auxRot;
	Matrix aux;

	temp=anguloEntreConectores(estatico,dinamico);

	sirMat4d S2W,D2W,auxMat;
	sirVector4d X(1,0,0,0),Y(0,1,0,0);
	sirVector4d axisXD,axisXS,axisYS;
	double angulo;

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	auxRot[0]=0;
	auxRot[1]=1;
	auxRot[2]=0;

	resultado=RotarSobresuEje(auxRot,temp,dinamico);
	madreDinamico=dinamico->obtenerMadre();
	matMadreDinamico=madreDinamico->matrizPieza();

	matMadreDinamico=resultado*matMadreDinamico;
	D2W=matMadreDinamico*dinamico->obtenerRotacion();

	axisXD=D2W*X; //Eje Xdinámico en coordenadas de mundo.
	axisXS=S2W*X; //Eje Xestático en coordenadas de mundo-->+X,-X.

	//Hay que calcular el ángulo entre
	angulo=anguloEntreEjes(axisXD,axisXS,&auxMat); //Xd,Xs

	madreDinamico=NULL;

	if(angulo==0)return temp;
	else{return (temp*(-1));}

}

sirMat4d Administrador::Acoplamiento(Conector *estatico,Conector *dinamico)
{
	Piece *madreDinamico, *madreEstatico;

	sirMat4d matMadreEstatico,matDinamico,matMadreDinamico;
	sirVector3d trans,ctrans,prodVect,Xaux,auxRot;
	sirVector4d X(1,0,0,0),Z(0,0,1,0),Xmundo;
	int fracdientes,fracdientes2;
	sirMat4d S2W,D2W,matCentroPos,matCentroNeg,resultado;
	double angulodinamico,anguloestatico,temp,temp2,temp3,alfa,normaProdVect,prodEscalar;
	Matrix aux;

	madreEstatico=estatico->obtenerMadre();
	madreDinamico=dinamico->obtenerMadre();
	matDinamico=dinamico->obtenerRotacion();

	//Obtenemos las matrices de las madres después porqué a la dinámica se le habrá aplicado una rotación.
	matMadreDinamico=madreDinamico->matrizPieza(); //Matriz de la pieza dinámica ROTADA!!!
	matMadreEstatico=madreEstatico->matrizPieza();

	//Conectores en coordenadas de mundo.
	S2W=matMadreEstatico*estatico->obtenerRotacion();;
	D2W=matMadreDinamico*matDinamico;

	//Obtenemos la translación a aplicar a la pieza dinámica y a las conectadas a ellas.
	trans=obtenerTranslacion(S2W,D2W);

	Xmundo=S2W*X;

	Xaux[0]=Xmundo[0];
	Xaux[1]=Xmundo[1];
	Xaux[2]=Xmundo[2];

	ctrans=trans;
	//Normalizamos a ambos vectores y obtenemos sus normas
	trans.normalize();
	Xaux.normalize();

	//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
	prodVect=trans^Xaux;

	//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
	normaProdVect=prodVect.norm();

	//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
	prodEscalar=trans*Xaux;//prodEscalar=nEstatico*nDinamico;

	//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
	alfa=angulo(normaProdVect,prodEscalar);

	//calculo del angulo de medio diente
	angulodinamico=2*dinamico->obtenerNdientes();
	angulodinamico=360/angulodinamico;
	anguloestatico=2*estatico->obtenerNdientes();
	anguloestatico=360/anguloestatico;
	temp3=180-alfa;

	fracdientes=(int)(alfa/anguloestatico);
	fracdientes2=(int)(temp3/angulodinamico);

	if((fracdientes%2==0 && fracdientes2%2!=0) || (fracdientes%2!=0 && fracdientes2%2==0))
	{
		temp=alfa-(fracdientes*anguloestatico);
		temp2=temp3-(fracdientes2*angulodinamico);

		temp=temp2-temp-anguloRealConectores(estatico,dinamico);
//		temp=temp*(-1);

		if(ctrans[0]<0 && ctrans[2]>0)
		{
			temp=temp*(-1);
		}
	}
	else
	{
		temp=angulodinamico;
	}

	D2W=dinamico->obtenerC2W();
	Xmundo=D2W*Z;
	auxRot[0]=Xmundo[0];
	auxRot[1]=Xmundo[1];
	auxRot[2]=Xmundo[2];

	resultado=RotarSobresuEje(auxRot,temp,dinamico);
	madreEstatico=NULL;
	madreDinamico=NULL;

	return resultado;
}


/*************************************************/

void Administrador::AcomodarGear(Conector *estatico,Conector *dinamico, unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico;
	sirMat4d matEjes;
	sirVector3d trans;

	madreDinamico=dinamico->obtenerMadre();

	//Calculamos el ángulo mínimo entre Xd y (Xs,-Xs,Ys,-Ys).
	matEjes=Acoplamiento(estatico,dinamico);

	//Aplicamos la rotación para que (Xs,Ys)=90º(Xd,Yd) a la pieza dinámica.
	//Automáticamente el eje Yd quedará fijado al fijar el Xd.
	//madreDinamico->rotar(matEjes,nTime,bAnimation,bAddKey);

	madreDinamico->comunicarRotacion(matEjes,false);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	//Para que al acabar el método no se elimine el objeto pieza.
	madreDinamico=NULL;

}

/*************************************************/

void Administrador::Normalantinormal(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	if(!igualdadNormales(estatico,dinamico,true))
	{
		coincidirN(estatico,dinamico,nTime,bAnimation,bAddKey);
	}
}

/*************************************************/

void Administrador::IntersectarPlano(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico, *madreEstatico;
	sirMat4d matMadreDinamico,matMadreEstatico,S2W,D2W,matDinamico;
	sirVector3d trans, Pn,R0,Rd;
	sirVector4d normal(0,0,1,0),nE,nD;

	madreEstatico=estatico->obtenerMadre();
	madreDinamico=dinamico->obtenerMadre();
	matDinamico=dinamico->obtenerRotacion();

	//Obtenemos las matrices de las madres después porqué a la dinámica se le habrá aplicado una rotación.
	matMadreDinamico=madreDinamico->matrizPieza(); //Matriz de la pieza dinámica ROTADA!!!
	matMadreEstatico=madreEstatico->matrizPieza();

	//Conectores en coordenadas de mundo.
	S2W=matMadreEstatico*estatico->obtenerRotacion();
	D2W=matMadreDinamico*matDinamico;

	trans=Equacion_plano(S2W,D2W);
	if(posible)
	{
		madreDinamico->comunicarTraslacion(trans);
		animacion(madreDinamico,nTime,bAnimation,bAddKey);
	}
	//Para no eliminar el objeto pieza al acabar el método.
	madreDinamico=NULL;
	madreEstatico=NULL;
}

sirVector3d Administrador::Equacion_plano(sirMat4d S2W,sirMat4d D2W)
{
	sirVector3d Pn,R0,Rd;
	sirVector4d normal(0,0,1,0),nE,nD;
	double D,Ax,By,Cz,t;

	//Normal Estatico
	nE=S2W*normal;
	Pn[0]=nE[0];
	Pn[1]=nE[1];
	Pn[2]=nE[2];

	//Normal Dinamico
	nD=D2W*normal;
	Rd[0]=nD[0];
	Rd[1]=nD[1];
	Rd[2]=nD[2];

	R0[0]=D2W[0][3];
	R0[1]=D2W[1][3];
	R0[2]=D2W[2][3];

	//Equacion del plano
	Ax=S2W[0][3]*nE[0];
	By=S2W[1][3]*nE[1];
	Cz=S2W[2][3]*nE[2];
	D=(-1)*(Ax+By+Cz);
	t=((-1)*(Pn*R0+D))/(Pn*Rd);

	if(Pn*Rd==0)
	{
		posible=false;
		AfxMessageBox("the assembling is ambiguous,try to colocate the piece better");
		return(0,0,0);
	}
	else
	{
		return (t*Rd);
	}
}


bool Administrador::PossibleUnir(Conector *estatico,Conector *dinamico,sirMat4d S2W,sirVector3d resultado,sirMat4d matMadreDinamico)
{
	Piece *madreAEstatico, *madreADinamico;
	Conector *AEstatico, *ADinamico;
	sirMat4d D2W,AS2W,simula2W,AD2W,matMadreAEstatico,matMadreSimula,matMadreADinamico;
	sirVector3d trans;
	float longitud;
	bool sol=true;

	matMadreSimula=matMadreDinamico;
	matMadreSimula.trasladar(resultado);

	simula2W=matMadreSimula*dinamico->obtenerRotacion();

	estatico->inicioConectores();
	while(!estatico->finalConectores() && sol)
	{
		AEstatico=estatico->obtenerConector();
		if(AEstatico->typeGear())
		{
			madreAEstatico=AEstatico->obtenerMadre();
			matMadreAEstatico=madreAEstatico->matrizPieza();
			AS2W=matMadreAEstatico*AEstatico->obtenerRotacion();

			trans=obtenerTranslacion(simula2W,AS2W);

			longitud=(float)trans.norm();

			if(longitud<(AEstatico->obtenerradio()+estatico->obtenerradio()))
				sol=false;

			dinamico->inicioConectores();
			while(!dinamico->finalConectores() && sol)
			{
				ADinamico=dinamico->obtenerConector();
				if(ADinamico->typeGear())
				{
					madreADinamico=ADinamico->obtenerMadre();
					matMadreADinamico=madreADinamico->matrizPieza();
					matMadreADinamico.trasladar(resultado);
					AD2W=matMadreADinamico*ADinamico->obtenerRotacion();

					trans=obtenerTranslacion(AD2W,AS2W);

					longitud=(float)trans.norm();

					if(longitud<(ADinamico->obtenerradio()+AEstatico->obtenerradio()))
						sol=false;

					trans=obtenerTranslacion(AD2W,S2W);

					longitud=(float)trans.norm();

					if(longitud<(ADinamico->obtenerradio()+estatico->obtenerradio()))
						sol=false;

				}
				dinamico->siguienteConector();
			}

		}
		estatico->siguienteConector();
	}
	madreAEstatico=NULL;
	madreADinamico=NULL;

	return sol;
}

/*************************************************/

void Administrador::UnirGear(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico, *madreEstatico;
	sirMat4d matMadreDinamico,matMadreEstatico,S2W,D2W,matDinamico,AS2W,simula2W,AD2W;
	sirMat4d matMadreAEstatico,matMadreSimula,matMadreADinamico;
	sirVector3d resultado;
	float radioestatico, radiodinamico;
	char cadena[500];

	madreEstatico=estatico->obtenerMadre();
	madreDinamico=dinamico->obtenerMadre();
	matDinamico=dinamico->obtenerRotacion();

	radioestatico=estatico->obtenerradio();
	radiodinamico=dinamico->obtenerradio();


	//Obtenemos las matrices de las madres después porqué a la dinámica se le habrá aplicado una rotación.
	matMadreDinamico=madreDinamico->matrizPieza(); //Matriz de la pieza dinámica ROTADA!!!
	matMadreEstatico=madreEstatico->matrizPieza();

	//Conectores en coordenadas de mundo.
	S2W=matMadreEstatico*estatico->obtenerRotacion();
	D2W=matMadreDinamico*matDinamico;


	//Obtenemos la translación a aplicar a la pieza dinámica y a las conectadas a ellas.
	if(strcmp(dinamico->obtenerNombre(),"Rack")==0)
	{
		radiodinamico=0;
	}
	if(strcmp(estatico->obtenerNombre(),"Rack")==0)
	{
		radioestatico=0;
	}

	resultado=obtenerinterseccionradio(S2W,D2W,radioestatico,radiodinamico);

	posible=PossibleUnir(estatico,dinamico,S2W,resultado,matMadreDinamico);


	if(posible)
	{
		madreDinamico->comunicarTraslacion(resultado);
		animacion(madreDinamico,nTime,bAnimation,bAddKey);
	}
	else
	{
		strcpy(cadena,"es ambiguo el assembling intentar de colocar mejor la pieza");
		AfxMessageBox(cadena);
	}


	//Para no eliminar el objeto pieza al acabar el método.
	madreDinamico=NULL;
	madreEstatico=NULL;
}

/*************************************************/

bool Administrador::gestionVeri(Conector *pCon1,Conector *pCon2)
{

	bool opcion=true,gear=false;
	char pas,cadena [200];
	Pasos *pares;
	pares=new Pasos();

	strcpy(cadena,"Error: it is possible that the assembling has not been realised correctly\n");
	strcat(cadena,"because of a no valid step. Modify the file manager.ges for its correct function");

	EncontrarInstrucciones(pCon1,pCon2,'v');
	if (strcmp(pCon1->obtenerNombre(),"Spur")==0 && strcmp(pCon2->obtenerNombre(),"Spur")==0)
		gear=true;
	if (ges->Fin())
	{
		return false;
	}
	else
	{
		*pares=ges->Actual();

		pares->PrimerPasosV();
		do
		{
		pas=pares->obtenerPasosV();
		switch(pas)
		{
			case 'A': opcion=(opcion && igualdadNormales(pCon1,pCon2,gear));break;
			case 'B': opcion=(opcion && mismaPosicion(pCon1,pCon2));break;
			case 'C': opcion=(opcion && (pCon2->obtenerLongitudLibre()>=LONGITUD_STUD));break;
			case 'D': opcion=(opcion && coaxiales(pCon1,pCon2));break;
			case 'E': opcion=(opcion && coincidencia(pCon1,pCon2));break;
			case 'F': opcion=(opcion && segmentoLibre(pCon1,pCon2));break;
			case 'G': opcion=(opcion && coincidirX(pCon1,pCon2));break;
			case 'H': opcion=(opcion && distanciaRadios(pCon1,pCon2));break;
			case 'I': opcion=(opcion && igualdadNormales90(pCon1,pCon2));break;
			case 'J': opcion=(opcion && distanciaInclinadas(pCon1,pCon2));break;
			case 'K': opcion=(opcion && distanciacentro(pCon1,pCon2));break;
			default: AfxMessageBox(cadena);
		}
		pares->SiguientePasosV();
		}while (!pares->FinPasosV());

		delete pares;

	return opcion;
	}
}


/*************************************************/
bool Administrador::distanciacentro(Conector *pCon1,Conector *pCon2)
{
	sirMat4d S2W,D2W;
	sirVector4d normal(0,0,1,0),nE,nD;
	sirVector3d trans1,trans2,normaE,normaD,auxi;
	double cate1,cate2,dradio;

	//Conectores en coordenadas de mundo.
	S2W=pCon1->obtenerC2W();
	D2W=pCon2->obtenerC2W();

	nE=obtenerTranslacion(D2W,S2W);
	normaE[0]=nE[0];
	normaE[1]=nE[1];
	normaE[2]=nE[2];

	if(strcmp(pCon1->obtenerNombre(),"Rack")==0)
	{
		cate1=pCon2->obtenerradio()+0.02;
		cate2=(normaE*normaE)-(cate1*cate1);

		dradio=pCon1->obtenerradio()/pCon1->obtenerNdientes();
		dradio=dradio+pCon1->obtenerradio();
		dradio=dradio*dradio;


		if((cate2)<dradio)
			return true;
		else return false;


	}
	else if(strcmp(pCon2->obtenerNombre(),"Rack")==0)
	{
		cate1=pCon1->obtenerradio()+0.02;
		cate2=(normaE*normaE)-(cate1*cate1);

		dradio=pCon2->obtenerradio()/pCon2->obtenerNdientes();
		dradio=dradio+pCon2->obtenerradio();
		dradio=dradio*dradio;

		if((cate2)<dradio)
			return true;
		else return false;

	}
}

/*************************************************/
bool Administrador::distanciaInclinadas(Conector *pCon1,Conector *pCon2)
{
	sirMat4d S2W,D2W;
	sirVector4d normal(0,0,1,0),nE,nD;
	sirVector3d trans1,trans2,normaE,normaD,auxi;


	//Conectores en coordenadas de mundo.
	S2W=pCon1->obtenerC2W();
	D2W=pCon2->obtenerC2W();

	nE=S2W*normal;
	normaE[0]=nE[0];
	normaE[1]=nE[1];
	normaE[2]=nE[2];

	nD=D2W*normal;
	normaD[0]=nD[0];
	normaD[1]=nD[1];
	normaD[2]=nD[2];

	//obtener distancia entre radios por pieza
	trans1=pCon1->obtenerradio()*normaD;
	trans2=pCon2->obtenerradio()*normaE;

	//obtener la posicio de la piezas
	normaE[0]=S2W[0][3];
	normaE[1]=S2W[1][3];
	normaE[2]=S2W[2][3];

	normaD[0]=D2W[0][3];
	normaD[1]=D2W[1][3];
	normaD[2]=D2W[2][3];

	auxi=normaE+trans1-trans2;
	auxi=auxi-normaD;

	return ((fabs(auxi[0])<DELTA_FRAN)&&(fabs(auxi[1])<DELTA_FRAN)&&(fabs(auxi[2])<DELTA_FRAN));

 }

/*************************************************/
bool Administrador::distanciaRadios(Conector *pCon1,Conector *pCon2)
{
	sirMat4d C2W,D2W;
	sirVector3d pos1,pos2,pos3, diferencia,trans;
	double distancia1, distancia2;
	bool sigue=false;

	//Conectores en coordenadas de mundo.
	C2W=pCon1->obtenerC2W();
	D2W=pCon2->obtenerC2W();

/*	trans=Equacion_plano(C2W,D2W);

	if(trans.norm()<DELTA_FRAN && trans.norm()>((-1)*DELTA_FRAN))
		sigue=true;

	if(sigue)
	{
*/		//obtener posicion de la pieza 1
		pos1[0]=C2W[0][3];
		pos1[1]=C2W[1][3];
		pos1[2]=C2W[2][3];

		//obtener posicion de la pieza a comunicar traslacion
		pos2[0]=D2W[0][3];
		pos2[1]=D2W[1][3];
		pos2[2]=D2W[2][3];

		diferencia=pos1-pos2;
		distancia1=diferencia.norm();

		distancia2=pCon1->obtenerradio()+pCon2->obtenerradio();

		if(distancia1-distancia2<DELTA_FRAN && distancia1-distancia2>((-1)*DELTA_FRAN))return true;
		else return false;
//	}
//	else return false;
}

/*************************************************/

double Administrador::anguloEntreConectores(Conector *pCon1,Conector *pCon2)
{
	sirMat4d S2W,D2W,auxMat;
	sirVector4d X(1,0,0,0),Y(0,1,0,0);
	sirVector4d axisXD,axisXS,axisYS;
	double angulo,temp;

	//Conectores en coordenadas de mundo.
	S2W=pCon1->obtenerC2W();
	D2W=pCon2->obtenerC2W();

	axisXD=D2W*X; //Eje Xdinámico en coordenadas de mundo.
	axisXS=S2W*X; //Eje Xestático en coordenadas de mundo-->+X,-X.
	axisYS=S2W*Y; //Eje Yestático en coordenadas de mundo-->+Y,-Y.

	//Hay que calcular el ángulo entre
	angulo=anguloEntreEjes(axisXD,axisXS,&auxMat); //Xd,Xs

	axisXS[0]=-axisXS[0]; axisXS[1]=-axisXS[1]; axisXS[2]=-axisXS[2]; axisXS[3]=-axisXS[3];
	temp=anguloEntreEjes(axisXD,axisXS,&auxMat); //Xd,-Xs
	if(temp<angulo) angulo=temp;

	temp=anguloEntreEjes(axisXD,axisYS,&auxMat); //Xd,Ys
	if(temp<angulo) angulo=temp;

	axisYS[0]=-axisYS[0]; axisYS[1]=-axisYS[1]; axisYS[2]=-axisYS[2]; axisYS[3]=-axisYS[3];
	temp=anguloEntreEjes(axisXD,axisYS,&auxMat); //Xd,-Ys
	if(temp<angulo) angulo=temp;

	return angulo;
}

/*************************************************/

bool Administrador::coincidirX(Conector *pCon1,Conector *pCon2)
{
	//4.-(Xs,Ys)=0º,90º,180º,270º,360º(Xd,Yd).

	double angulo;

	angulo=anguloEntreConectores(pCon1,pCon2);
	//POR MOTIVOS DE ROBUSTEZ UTILIZAMOS LA FUNCIÓN IGUALES Y NO EL OPERADOR ==
	if(iguales(angulo,0) || iguales(angulo,90) || iguales(angulo,180) || iguales(angulo,270) || iguales(angulo,360)) return true;
	else return false;
}


/*************************************************/

bool Administrador::segmentoLibre(Conector *pCon1,Conector *pCon2)
{
	//Méotodo que devuelve cierto si el conector pCon no coincide con ninguno de los conectores
	//conectados al propio conector.

	Conector *actual;
	bool trobat=false;
	sirMat4d C2W,W2C;

	C2W=pCon1->obtenerC2W();
	W2C=C2W.inverse();

	pCon1->inicioConectores();
	while(!pCon1->finalConectores() && !trobat)
	{
		actual=pCon1->obtenerConector();
		if(coincidencia(pCon2,actual)) trobat=true;
		else pCon1->siguienteConector();
	}
	return (!trobat);
}


/*************************************************/

bool Administrador::coincidencia(Conector *pCon1,Conector *pCon2)
{
	sirMat4d C2W,W2C;
	FRAN_SEGMENTO AB,CD;

	C2W=pCon1->obtenerC2W();
	W2C=C2W.inverse();

	AB=pCon1->obtenerSegmento(); //También la matriz en el propio segmento!!!???!!!???!!!???!!!

	CD=pCon2->obtenerSegmento(W2C);

	//Como es respecto al conector solo hace falta que cojamos la coordenada Z, que es la coaxial.
	//Hay que tener en cuenta que son coaxiales en el eje Z.
	//if(entre1D(CD.A,AB) || entre1D(CD.B,AB) || (fuera1D(CD.A,AB) && fuera1D(CD.B,AB)) ) return true;
	//else return false;

	//|-------| CIERTO   |------|
	//|-------|                 |--------------------| FALSO

	if(pCon1->iguales1D(AB,CD)) return true;
	else if(pCon1->coincidenUnExtremo(AB,CD)) return false;
	else if(pCon1->entre1D(CD.A,AB) || pCon1->entre1D(CD.B,AB) || ((pCon1->inferior1D(CD.A,AB) && pCon1->superior1D(CD.B,AB)) || (pCon1->inferior1D(CD.B,AB) && pCon1->superior1D(CD.A,AB))) ) return true;
	else return false;

}


/*************************************************/

bool Administrador::coaxiales(Conector *pCon1,Conector *pCon2)
{
	LC_CLICKLINE linea;
	sirVector4d I(0,0,0,1),F(0,0,0,1),CI(0,0,0,1);

	//Con esto no habrá problemas de Z+ y Z-.
	I=pCon1->obtenerPuntoInicial();
	F=pCon1->obtenerPuntoFinal();

	CI=pCon2->obtenerPuntoInicial();

	linea.a1=I[0];
	linea.b1=I[1];
	linea.c1=I[2];

	linea.a2=F[0];
	linea.b2=F[1];
	linea.c2=F[2];

	//Por motivos de robusteza miramos que la distancia punto-recta sea más pequeña o igual que una certa delta.
	if(distanciaPuntoRecta(CI[0],CI[1],CI[2],linea)<=DELTA_FRAN) return true; //Coaxial.
	else return false; //No Coaxial.
}


/*************************************************/

bool Administrador::mismaPosicion(Conector *pCon1,Conector *pCon2)
{
	sirMat4d mat1,mat2;

	mat1=pCon1->obtenerC2W();
	mat2=pCon2->obtenerC2W();

	if(distanciaPuntos(mat1[0][3],mat1[1][3],mat1[2][3],mat2[0][3],mat2[1][3],mat2[2][3])<=DELTA_FRAN) return true;
	else return false;
}


/*************************************************/

bool Administrador::igualdadNormales(Conector *pCon1,Conector *pCon2,bool gear)
{
	sirMat4d C2W1,C2W2;
	sirVector4d N1(0,0,1,0),N2(0,0,1,0);
	bool resultat;

	C2W1=pCon1->obtenerC2W();
	C2W2=pCon2->obtenerC2W();

	N1=C2W1*N1;
	N2=C2W2*N2;
	N1.normalize();
	N2.normalize();

	if(iguales(N1[0],N2[0]) && iguales(N1[1],N2[1]) && iguales(N1[2],N2[2])) resultat=true;
	else resultat=false;

	if(gear && !resultat)
	{
		N1.inversa();

		if(iguales(N1[0],N2[0]) && iguales(N1[1],N2[1]) && iguales(N1[2],N2[2])) resultat=true;
		else resultat=false;
	}
	return resultat;
}

/*************************************************/

bool Administrador::igualdadNormales90(Conector *pCon1,Conector *pCon2)
{
	sirMat4d C2W1,C2W2;
	sirVector4d N1(0,0,1,0),N2(0,0,1,0);
	sirVector3d prodVect,nor1,nor2;
	double normaProdVect;
	double prodEscalar;
	double alfa;
	C2W1=pCon1->obtenerC2W();
	C2W2=pCon2->obtenerC2W();

	N1=C2W1*N1;
	nor1[0]=N1[0];
	nor1[1]=N1[1];
	nor1[2]=N1[2];

	N2=C2W2*N2;
	nor2[0]=N2[0];
	nor2[1]=N2[1];
	nor2[2]=N2[2];

	nor1.normalize();
	nor2.normalize();

	//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
	prodVect=nor2^nor1; //prodVect=normal^normal2;

	//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
	//prodVect.normalize();//normaProdVect=prodVect.normalize(); //También obtenemos su norma
	normaProdVect=prodVect.norm();

	//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
	prodEscalar=nor2*nor1;//prodEscalar=normal*normal2;

	//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
	alfa=angulo(normaProdVect,prodEscalar);

	if(alfa>(90-DELTA_FRAN) && alfa<(90+DELTA_FRAN))
		return true;
	else
		return false;
}

/*************************************************/

void Administrador::CoincidenciaCruz(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico;
	sirMat4d matEjes;
	sirVector3d trans;

	madreDinamico=dinamico->obtenerMadre();

	//Calculamos el ángulo mínimo entre Xd y (Xs,-Xs,Ys,-Ys).
	matEjes=minimoAnguloX(estatico,dinamico);

	//Aplicamos la rotación para que (Xs,Ys)=90º(Xd,Yd) a la pieza dinámica.
	//Automáticamente el eje Yd quedará fijado al fijar el Xd.
	//madreDinamico->rotar(matEjes,nTime,bAnimation,bAddKey);

	madreDinamico->comunicarRotacion(matEjes,false);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	//Para que al acabar el método no se elimine el objeto pieza.
	madreDinamico=NULL;

}


/*************************************************/

sirMat4d Administrador::minimoAnguloX(Conector *estatico,Conector *dinamico)
{
	Piece *madreDinamico;
	sirMat4d S2W,D2W,matCentroPos,matCentroNeg;
	sirMat4d auxMat,resultado;
	sirVector4d X(1,0,0,0),Y(0,1,0,0);
	sirVector4d axisXD,axisXS,axisYS;
	double angulo,temp;
	float pos[3];

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	axisXD=D2W*X; //Eje Xdinámico en coordenadas de mundo.
	axisXS=S2W*X; //Eje Xestático en coordenadas de mundo-->+X,-X.
	axisYS=S2W*Y; //Eje Yestático en coordenadas de mundo-->+Y,-Y.

	//Hay que calcular el ángulo entre
	angulo=anguloEntreEjes(axisXD,axisXS,&auxMat); //Xd,Xs
	resultado=auxMat;
	axisXS[0]=-axisXS[0]; axisXS[1]=-axisXS[1]; axisXS[2]=-axisXS[2]; axisXS[3]=-axisXS[3];
	temp=anguloEntreEjes(axisXD,axisXS,&auxMat); //Xd,-Xs
	if(temp<angulo)
	{
		angulo=temp;
		resultado=auxMat;
	}
	temp=anguloEntreEjes(axisXD,axisYS,&auxMat); //Xd,Ys
	if(temp<angulo)
	{
		angulo=temp;
		resultado=auxMat;
	}
	axisYS[0]=-axisYS[0]; axisYS[1]=-axisYS[1]; axisYS[2]=-axisYS[2]; axisYS[3]=-axisYS[3];
	temp=anguloEntreEjes(axisXD,axisYS,&auxMat); //Xd,-Ys
	if(temp<angulo)
	{
		angulo=temp;
		resultado=auxMat;
	}

	//NO ESTOY SEGURO!!!
	//Rotamos respecto al centro del conector y no respecto al centro de la pieza, que no tienen porqué coincidir.
	madreDinamico=dinamico->obtenerMadre();
	madreDinamico->GetPosition(pos);

	matCentroPos[0][3]=pos[0];//D2W[0][3];
	matCentroPos[1][3]=pos[1];//D2W[1][3];
	matCentroPos[2][3]=pos[2];//D2W[2][3];

	matCentroNeg[0][3]=-pos[0];//-D2W[0][3];
	matCentroNeg[1][3]=-pos[1];//-D2W[1][3];
	matCentroNeg[2][3]=-pos[2];//-D2W[2][3];

	resultado=resultado*matCentroNeg;
	resultado=matCentroPos*resultado;

	return resultado;
}


/*************************************************/

double Administrador::anguloEntreEjes(sirVector4d ejeDinamico,sirVector4d ejeEstatico,sirMat4d *m)
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

void Administrador::AcomodarConector(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	//En el assembling Axle-CylindricalHole no hace falta que se cumpla (Xs,Ys)=90º(Xd,Yd).

	Piece *madreDinamico;
	sirMat4d matEjes;
	sirVector3d trans;

	madreDinamico=dinamico->obtenerMadre();


	//Ahora ya tenemos el extremo de la piezas dinámica perfectamente acomodado sobre el extremo de la pieza estática.
	//Obtenemos la translación a aplicar a la pieza dinámica para encajarla con la estática.
	trans=encajarConector(estatico,dinamico);

	//Trasladamos la distancia más pequeña de ambas piezas.
	//madreDinamico->mover(trans,nTime,bAnimation,bAddKey);

	madreDinamico->comunicarTraslacion(trans);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico->piezasNoVisitadas(); //Ponemos como no visitadas las piezas a las que les hemos aplicado las transformaciones.

	//Para que al acabar el método no se elimine el objeto pieza.
	madreDinamico=NULL;
}


/*************************************************/

sirVector3d Administrador::encajarConector(Conector *estatico,Conector *dinamico)
{
	//Determinar la longitud a trasladar la pieza dinámica una vez acomodada para encajarla.

	Extreme *pCon=dynamic_cast<Extreme*>(dinamico);
	sirMat4d matMadre;
	sirVector3d longTrans(0,0,0);
	sirVector4d longTrans1(0,0,0,0);
	double longDinamico,longEstatico;

	matMadre=estatico->obtenerMadre()->matrizPieza();

	longDinamico=pCon->obtenerLongitudLibre();
	longEstatico=estatico->obtenerLongitudLibre();

	if(longDinamico>=longEstatico) longTrans1[2]=longEstatico;
	else longTrans1[2]=longDinamico;

	//Simepre sobre le je Z del conector estático.
	//Si el estático es un axle lo hacemos en el eje -Z, porque va hacia fuera del conector.
	if(!strcmp(estatico->obtenerNombre(),"axle")) longTrans1[2]=-longTrans1[2];

	longTrans1=estatico->obtenerRotacion()*longTrans1;
	longTrans1=matMadre*longTrans1;

	//Lo aplicams en el eje Z del conector!!!-->COMO LO HACEMOS???!!!
	longTrans[0]=longTrans1[0];
	longTrans[1]=longTrans1[1];
	longTrans[2]=longTrans1[2];

	//Devolvemos la translación a aplicar.
	return longTrans;
}



/*************************************************/

void Administrador::LConectorConectado(Conector *estatico,Conector *dinamico)
{
	Piece *madreDinamico, *madreEstatico;

	madreDinamico=dinamico->obtenerMadre();
	madreEstatico=estatico->obtenerMadre();

	//Actualizamos las listas de conectores conectados de ambos conectores.
	estatico->introducirConector(dinamico); //Actualizamos las listas de conectados del conector estático.
	dinamico->introducirConector(estatico); //Actualizamos las listas de conectados del conector dinámico.

	madreDinamico=NULL;
	madreEstatico=NULL;
}


/*************************************************/

void Administrador::LConectorLibrePO(Conector *estatico,Conector *dinamico)
{
	Piece *madreDinamico, *madreEstatico;

	madreDinamico=dinamico->obtenerMadre();
	madreEstatico=estatico->obtenerMadre();

	//Actualizamos las listas de conectores ocupados y libres de las madres.
	//Seguro que los conectores estatrán en conOcupados.
	madreEstatico->introducirConectorOcupado(estatico);
	madreDinamico->introducirConectorOcupado(dinamico);

	//Después del assembling seguro que los extremos de los conectores no estarán libres.
	//Será con el desplazar o desconectar que podremos volverlo a que esté libre.
	if (!estatico->typeGear() && !dinamico->typeGear())
	{
		madreEstatico->esborrarConectorLibre(estatico->obtenerId());
		madreDinamico->esborrarConectorLibre(dinamico->obtenerId());
	}

	madreEstatico=NULL;
	madreDinamico=NULL;
}

/*************************************************/

void Administrador::traslacion(Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico, *madreEstatico;
	sirMat4d matMadreDinamico,matMadreEstatico,S2W,D2W,matDinamico;
	sirVector3d trans;

	madreEstatico=estatico->obtenerMadre();
	madreDinamico=dinamico->obtenerMadre();
	matDinamico=dinamico->obtenerRotacion();


	//Obtenemos las matrices de las madres después porqué a la dinámica se le habrá aplicado una rotación.
	matMadreDinamico=madreDinamico->matrizPieza(); //Matriz de la pieza dinámica ROTADA!!!
	matMadreEstatico=madreEstatico->matrizPieza();

	//Conectores en coordenadas de mundo.
	S2W=matMadreEstatico*estatico->obtenerRotacion();;
	D2W=matMadreDinamico*matDinamico;

	//Obtenemos la translación a aplicar a la pieza dinámica y a las conectadas a ellas.
	trans=obtenerTranslacion(S2W,D2W);

	madreDinamico->comunicarTraslacion(trans);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);
	//Para no eliminar el objeto pieza al acabar el método.
	madreDinamico=NULL;
	madreEstatico=NULL;
}


/*************************************************/

void Administrador::coincidirN (Conector *estatico,Conector *dinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Piece *madreDinamico;
	sirMat4d matNormales,matDinamico;
	sirVector4d normal(0,0,1,0);

	madreDinamico=dinamico->obtenerMadre();

	matNormales=coincidirNormales(estatico,dinamico,normal,normal,0);
	madreDinamico->comunicarRotacion(matNormales,false);
	animacion(madreDinamico,nTime,bAnimation,bAddKey);

	madreDinamico=NULL;
}


/*************************************************/

void Administrador::animacion (Piece *madreDinamico,unsigned short nTime,bool bAnimation,bool bAddKey)
{
	madreDinamico->piezasNoVisitadas();
	madreDinamico->transformar(nTime,bAnimation,bAddKey);
	madreDinamico->piezasNoVisitadas();
}


/*************************************************/

sirMat4d Administrador::coincidirNormales(Conector *estatico,Conector *dinamico,sirVector4d normal,sirVector4d normal2, double alfa)
{
	Piece *madreDinamico, *madreEstatico;
	Matrix aux;
	sirMat4d matEstatico,matDinamico,matPiezaS,matPiezaD,resultado;
	sirVector3d nEstatico,nDinamico,prodVect;
	sirVector4d nE,nD;


	madreDinamico=dinamico->obtenerMadre();
	madreEstatico=estatico->obtenerMadre();
	matPiezaS=madreEstatico->matrizPieza();
	matPiezaD=madreDinamico->matrizPieza();

	matDinamico=dinamico->obtenerRotacion();

	//Matrices de los conectores en coordenadas de mundo!!!
	matEstatico=matPiezaS*estatico->obtenerRotacion();
	matDinamico=matPiezaD*matDinamico;

	if(vale==1 && (strcmp(estatico->obtenerNombre(),"Worm")==0 || strcmp(dinamico->obtenerNombre(),"Worm")==0))
	{
		nEstatico[0]=normal[0];
		nEstatico[1]=normal[1];
		nEstatico[2]=normal[2];
	}
	else
	{
		//Vector normal del conector estático en coordenadas de mundo
		nE=matEstatico*normal;
		nEstatico[0]=nE[0];
		nEstatico[1]=nE[1];
		nEstatico[2]=nE[2];
	}

	//Vector normal del conector dinámico en coordenadas de mundo
	nD=matDinamico*normal2;
	nDinamico[0]=nD[0];
	nDinamico[1]=nD[1];
	nDinamico[2]=nD[2];

	madreDinamico=NULL;
	madreEstatico=NULL;


	resultado=coincidirVectores(nEstatico,nDinamico);
	return resultado;
}

/*************************************************/

sirMat4d Administrador::coincidirVectores(sirVector3d normal,sirVector3d normal2)
{
	Matrix aux;
	sirMat4d matEstatico,matDinamico,matPiezaS,matPiezaD,resultado;
	sirVector3d prodVect;
	sirVector4d nE,nD;
	double normaEstatico,normaDinamico,normaProdVect;
	double prodEscalar;
	float auxRot[3];
	double alfa;


	//Normalizamos a ambos vectores y obtenemos sus normas
	normal.normalize();//normaEstatico=normal.normalize();
	normaEstatico=normal.norm();
	normal2.normalize();//normaDinamico=normal2.normalize();
	normaDinamico=normal2.norm();

	//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
	prodVect=normal2^normal; //prodVect=normal^normal2;

	//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
	//prodVect.normalize();//normaProdVect=prodVect.normalize(); //También obtenemos su norma
	normaProdVect=prodVect.norm();

	//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
	prodEscalar=normal2*normal;//prodEscalar=normal*normal2;

	//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
	alfa=angulo(normaProdVect,prodEscalar);

	//opcion para que toda pieza rote sobre su propio eje siempre
	opbevel=true;
	//Creamos la matriz de rotación con el vector y ángulo de rotación a través de él
	//utilizando la "Fórmula de Rodrigues".

	auxRot[0]=(float)prodVect[0];
	auxRot[1]=(float)prodVect[1];
	auxRot[2]=(float)prodVect[2];

	aux.FromAxisAngle(auxRot,(float)alfa); //Es lo mismo que crear la matriz de rotación de ángulo alfa a través del vector prodVect
	resultado.introducir(aux.m);

	return resultado;
}

/*******************************************************/


/*************************************************/

sirMat4d Administrador::coincidirVectores(sirVector3d normal,sirVector3d normal2,sirVector3d rotacion)
{
	Matrix aux;
	sirMat4d matEstatico,matDinamico,matPiezaS,matPiezaD,resultado;
	sirVector3d prodVect;
	sirVector4d nE,nD;
	double normaEstatico,normaDinamico,normaProdVect;
	double prodEscalar;
	float auxRot[3];
	double alfa;


//Normalizamos a ambos vectores y obtenemos sus normas
	normal.normalize();//normaEstatico=normal.normalize();
	normaEstatico=normal.norm();
	normal2.normalize();//normaDinamico=normal2.normalize();
	normaDinamico=normal2.norm();

	//Producto vectorial-->estatico X dinamico-->VIGILAR EL ORDEN!!!
	prodVect=normal2^normal; //prodVect=normal^normal2;

	//Normalizamos el vector resultante del producto vectorial-->Hace falta!!!
	//prodVect.normalize();//normaProdVect=prodVect.normalize(); //También obtenemos su norma
	normaProdVect=prodVect.norm();

	//Calculamos el producto escalar de los dos vectores de los conectores a ensamblar
	prodEscalar=normal2*normal;//prodEscalar=normal*normal2;

	//Con el seno y el coseno obtenemos el angulo de rotación a través del vector producto vectorial
	alfa=angulo(normaProdVect,prodEscalar);

	//opcion para que toda pieza rote sobre su propio eje siempre
	opbevel=true;
	//Creamos la matriz de rotación con el vector y ángulo de rotación a través de él
	//utilizando la "Fórmula de Rodrigues".
	prodVect=rotacion;

	auxRot[0]=(float)prodVect[0];
	auxRot[1]=(float)prodVect[1];
	auxRot[2]=(float)prodVect[2];

	aux.FromAxisAngle(auxRot,(float)alfa); //Es lo mismo que crear la matriz de rotación de ángulo alfa a través del vector prodVect
	resultado.introducir(aux.m);

	return resultado;
}

/*******************************************************/

sirVector3d Administrador::CoincidirNormales90(Conector *estatico, Conector *dinamico)
{
	sirMat4d S2W,D2W;
	sirVector3d trans;

	//Conectores en coordenadas de mundo.
	S2W=estatico->obtenerC2W();
	D2W=dinamico->obtenerC2W();

	trans=Equacion_plano(S2W,D2W);

	D2W[0][3]=D2W[0][3]+trans[0];
	D2W[1][3]=D2W[1][3]+trans[1];
	D2W[2][3]=D2W[2][3]+trans[2];

	trans=obtenerTranslacion(D2W,S2W);

	return trans;
}


/*************************************************/

double Administrador::angulo(double opp,double adj)
{
	//Función que alculo el ángulo con la tangente opp/adj
	//El valor que devulve se encuentra entre PI y -PI

	double angulo;

	//Obtenemos el ángulo básico
	if(fabs(adj)<0.0001) angulo=M_PI/2; //M_PI-->En radianes
	else angulo=fabs(atan(opp/adj));

	//Miramos si estamos en el cuadrante 2 o 3
	if(adj<0) angulo=M_PI-angulo; //(angulo > PI/2) o (angulo < -PI/2)

	//Miramos si estamos en el cuadrante 3 0 4
	if(opp<0) angulo=-angulo;

	//Ángulo debe de estaren grados y no en radianes!!!
	angulo=angulo*180/M_PI;
	//angulo*=180/M_PI;

	return angulo;
}