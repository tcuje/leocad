/*************************************************/
/*                                               */
/*				     GEAR.CPP 	                 */
/*                                               */
/*************************************************/


#include "gear.h"
#include "piece.h"

/*************************************************/

//Constructor por defecto
Gear::Gear(void)
{
	//Se llama automáticamente al constructor de la clase base
	//Inicializamos las variables de la propia clase.
	radio=0;
	ndientes=0;
}

/*************************************************/

//Constructor con parámetros
Gear::Gear(int identificador,const char *nom,sirMat4d rot,Piece *pPieza,float r,int d) : Conector(identificador,nom,rot,pPieza)
{

	radio=r; //Ya está en coordenadas LeoCAD.
	ndientes=d;


	//No hago nada con el id del conector hermano porque es el del fichero LCI.
	//A parte ya le pasamos el puntero al conector hermano.
}

/*************************************************/

//Operador de asignación sobrecargado no se hereda
Gear& Gear::operator=(Gear &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		//Copiamos las variables de la propia clase Extreme
		radio=c.radio;
		ndientes=c.ndientes;
		//Copiamos el resto de variables
		Conector::operator =(c); //Operador de asignación sobrecargado de la clase Conector
	}
	return *this;
}

/*************************************************/

//Constructor de copia
Gear::Gear(Gear &c) : Conector(c)
{
	//Lamamos al constructor de copia de la clase conector y añadimos lo de la propia clase
	radio=c.radio;
	ndientes=c.ndientes;
}

/*************************************************/

bool Gear::espacioLibre(void)
{
	Conector *actual=NULL;
	sirMat4d C2W,W2C;
	bool trobat=false;
	float roriginal;
	double longitud;

	roriginal=obtenerradio();
	longitud=2*roriginal*M_PI;

	if(conectados.Vacia()) return false;
	else
	{
		C2W=obtenerC2W();
		W2C=C2W.inverse();

		conectados.Primero();
		while(!conectados.Fin() && !trobat)
		{
			actual=conectados.Actual();
			longitud=longitud-(1.5*actual->obtenerradio());
			if(longitud<0) trobat=true; //En cuanto encontremos que coincide el estremo del conector con alguno de los conectados paramos-->OCUPADO!!!
			else conectados.Siguiente();
		}
		return trobat;
	}
	actual=NULL;
}

/*************************************************/

bool Gear::libre(void)
{

	if(conectados.Vacia()) return true; //Si no tiene ningún conector conectado estará libre.
	else if(espacioLibre()) return false; //Si tiene no tiene espacio para conectarse alguno de sus conectores conectados no estará libre.
	else return true; //Si su extremo no está entr ninguno de sus conectados, si estará libre.
}

/*************************************************/

bool Gear::ocupado()
{
	//No importa si hay 1 o 2 extremos.
	//Si está conectado a algún conector, entonces estará ocupado.
	if(conectados.NElementos()>=1) return true;
	else return false;
}

/*************************************************/

void Gear::initGear(Diccionario d)
{
	Tag t1("<radius>"),t2("<tooth>");

	radio=leerNumeroParametro(d,t1); //Leemos el radio
	ndientes=(int)leerNumeroParametro(d,t2);
}

/*************************************************/

void Gear::init(Diccionario d)
{
	Conector::init(d);
	initGear(d);
}

/*************************************************/

sirVector4d Gear::obtenerPuntoInicial(void)
{
	sirMat4d C2W;
	sirVector4d v(0,0,0,1);

	C2W=obtenerC2W();

	v[0]=C2W[0][3];
	v[1]=C2W[1][3];
	v[2]=C2W[2][3];

	return v;
}

/*************************************************/

sirVector4d Gear::obtenerPuntoFinal(void)
{
	sirMat4d C2W;
	sirVector4d v1(0,0,0,1),v2(0,0,LONGITUD_STUD,0);

	C2W=obtenerC2W();

	//v1->PUNTO!!!
	//v2->VECTOR TRASLACIÓN!!!

	v1[0]=C2W[0][3];
	v1[1]=C2W[1][3];
	v1[2]=C2W[2][3];

	v2=C2W*v2;

	v1[0]=v1[0]+v2[0];
	v1[1]=v1[1]+v2[1];
	v1[2]=v1[2]+v2[2];

	return v1;
}

double Gear::obtenerSinusRotacion(sirMat4d r,int &fila,int &columna)
{

	return 0.0;//angulo;
}

/*************************************************/

bool Gear::trasladarEjeZ(Conector *pCon,sirVector3d t)
{
	sirMat4d C2W,D2W;
	sirVector3d pos1,pos2,pos3, diferencia;
	double distancia1, distancia2;

	C2W=this->obtenerC2W();
	D2W=pCon->obtenerC2W();

	//obtener posicion de la pieza 1
	pos1[0]=C2W[0][3];
	pos1[1]=C2W[1][3];
	pos1[2]=C2W[2][3];

	//obtener posicion de la pieza a comunicar traslacion
	pos2[0]=D2W[0][3];
	pos2[1]=D2W[1][3];
	pos2[2]=D2W[2][3];

	diferencia=pos1-pos2;
	distancia1=diferencia.norm();

	pos3=pos1+t;

	diferencia=pos3-pos2;
	distancia2=diferencia.norm();

	if(distancia1>distancia2) return true;
	else if(Ultimo_contacto(pos1,pos2,t))
		return true;
		else return false;

}

