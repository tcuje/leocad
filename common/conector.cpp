/*************************************************/
/*                                               */
/*				   CONECTOR.CPP                  */
/*                                               */
/*************************************************/

#include "conector.h"
#include "piece.h"
#include "file.h" //CUIDADO!!!!!!!!!

/*************************************************/

//Constructor por defecto
Conector::Conector(void)
{
	id=-1; //Aun no se le ha asignado un conector válido
	nombre=new char[1];
	strcpy(nombre,"");
	//Matriz identidad como matriz por defecto
	madre=NULL;
	dibujo=NULL; //Como nunca se hará una instancia de Conector...
	visitado=false;
	//Con conectados no hace falta hacer nada en el constructor por defecto
}

/*************************************************/

//Constructor con parámetros
Conector::Conector(int identificador,const char *nom,sirMat4d rot,Piece *pieza)
{
	id=identificador;
	nombre=new char[strlen(nom)+1];
	strcpy(nombre,nom);
	rotacion=rot;
	madre=pieza;
	dibujo=NULL; //Nunca se hará una instancia de conector.
	visitado=false;
}

/*************************************************/

Conector::Conector(int identificador,Piece *pieza)
{
	id=identificador;
	madre=pieza;
	nombre=new char[1];
	strcpy(nombre,"");
	dibujo=NULL; //Nunca se hará una instacia de conector.
	visitado=false;
	//La rotación se introducirá con el init!!!
}

/*************************************************/

//Constructor de copia
Conector::Conector(Conector &c)
{
	id=c.id;
	nombre=new char[strlen(c.nombre)+1];
	strcpy(nombre,c.nombre);
	rotacion=c.rotacion;

	madre=c.madre;
	conectados=c.conectados; //Asignamos listas-->Está bién porque son objetos.
	dibujo=c.dibujo;
	visitado=c.visitado;
}

/*************************************************/

Conector::~Conector(void)
{
	delete [] nombre;
	madre=NULL;

	/*Para que si se destruye una pieza que estaba conectada, al llamar al constructor
	de la lista de conectados no se eliminen los objetos conectores que estuvieran
	conectados a los de la pieza borrada.*/

	Conector *pCon;

	//NO HARÍA FALTA!!!-->Porque al eliminar una pieza, ya se desconectan los conectores, si se encuentran conectados!!!
	//Si no eliminamos de la lista los conectores que puedan estar conectados
	//entonces la lista haría un delete y perderíamos el objeto!!!
	if(!conectados.Vacia())
	{
		conectados.Primero();
		while(!conectados.Fin())
		{
			pCon=conectados.Actual();
			pCon->eliminarConector(); //Eliminamos el conector actual!!!
			//pCon->introducirConector(NULL);
			conectados.Siguiente();
		}
	}

	delete dibujo; //Si que hay que hacer delete.Es diferente del caso de la pieza.

	//No hace falta llamar al destructor de la clase Lista-->Se llama automático al destruirse la variable?????
}


/*************************************************/

//Sobrecarga de operadores

bool Conector::operator==(Conector c)
{
	return id==c.id;
}

/*************************************************/

bool Conector::operator!=(Conector c)
{
	return id!=c.id;
}

/*************************************************/

//Operador de asignación sobrecargado
Conector& Conector::operator=(Conector &c)
{
	//Si los objectos son diferentes...
	if(*this!=c)
	{
		id=c.id;
		delete [] nombre;
		nombre=new char[strlen(c.nombre)+1];
		strcpy(nombre,c.nombre);
		rotacion=c.rotacion;
		madre=c.madre;
		conectados=c.conectados; //El operador de asignación de la lista ya hará su pertinente trabajo!!!!!!!
		dibujo=c.dibujo;
		visitado=c.visitado;
	}
	return *this;
}

/*************************************************/

float Conector::leerNumeroParametro(Diccionario d,Tag t)
{
	Contenido c;
	int indice=0,l;
	char *linea;

	c=d.Consultar(t);
	linea=c.obtenerContenido();
	l=strlen(linea);
	pasarEspacios(linea,&indice); //Pasamos los posibles espacios iniciales.
	return leerNumero(linea,&indice,l); //Leemos el ID del fichero LCI del conector.
}

/*************************************************/

void Conector::introducirId(int identificador)
{
	id=identificador;
}

/*************************************************/

void Conector::introducirNombre(char *c)
{
	delete [] nombre;
	nombre=new char[strlen(c)+1];
	strcpy(nombre,c);
}

/*************************************************/

void Conector::introducirRotacion(sirMat4d rot)
{
	rotacion=rot;
}

/*************************************************/

void Conector::introducirMadre(Piece *p)
{
	madre=p;
}

/*************************************************/

int Conector::obtenerId(void)
{
	return id;
}

/*************************************************/

char * Conector::obtenerNombre(void)
{
	return nombre;
}

/*************************************************/

sirMat4d Conector::obtenerRotacion(void)
{
	return rotacion;
}

/*************************************************/

sirMat4d Conector::obtenerC2W(void)
{
	sirMat4d P2W;

	P2W=madre->matrizPieza();
	return P2W*rotacion;
}

/*************************************************/

Piece *Conector::obtenerMadre(void)
{
	return madre;
}

/*************************************************/

void Conector::introducirConector(Conector *c)
{
	conectados.Introducir(c);
}

/*************************************************/

void Conector::eliminarConector(void)
{
	conectados.Esborrar(); //eliminamos el conector conectado actual
}

/*************************************************/

bool Conector::eliminarConector(Conector *pCon)
{
	return conectados.Esborrar(pCon);
}

/*************************************************/

void Conector::inicioConectores(void)
{
	conectados.Primero();
}

/*************************************************/

void Conector::siguienteConector(void)
{
	conectados.Siguiente();
}

/*************************************************/

bool Conector::finalConectores(void)
{
	return conectados.Fin();
}

/*************************************************/

bool Conector::existeConector(Conector *pCon)
{
	return conectados.Existe(pCon);
}

/*************************************************/

bool Conector::vaciaConectores(void)
{
	return conectados.Vacia();
}

/*************************************************/

Conector *Conector::obtenerConector(void)
{
	//Obtener conector actual
	return conectados.Actual();
}

/*************************************************/

int Conector::numeroConectados(void)
{
	return conectados.NElementos();
}

/*************************************************/

void Conector::renderizarZDentro(float r,float g,float b)
{
	sirMat4d matPieza,C2W,aux;

	float pos[3],rot[4];
	double auxiliar[16];
	Matrix m;

	matPieza=madre->matrizPieza();
	aux=rotacion;
	aux[0][2]=-aux[0][2];
	aux[1][2]=-aux[1][2];
	aux[2][2]=-aux[2][2];
	C2W=matPieza*aux;

	/***************** XUS ***********************/

	C2W.obtenerMatriz(auxiliar);
	m.crear(auxiliar);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	glBegin(GL_LINES);

	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);

	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);

	glEnd();

	glPopMatrix();
	/***************** XUS ***********************/

	dibujo->dibujar(C2W,r,g,b);
}

/*************************************************/

void Conector::renderizarZDentro(float r,float g,float b,float rad)
{
	sirMat4d matPieza,C2W,aux;
	float pos[3],rot[4];
	double auxiliar[16];
	Matrix m;


	matPieza=madre->matrizPieza();
	aux=rotacion;
	aux[0][2]=-aux[0][2];
	aux[1][2]=-aux[1][2];
	aux[2][2]=-aux[2][2];
	C2W=matPieza*aux;

	/***************** XUS ***********************/

	C2W.obtenerMatriz(auxiliar);
	m.crear(auxiliar);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	glBegin(GL_LINES);

	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);

	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);

	glEnd();

	glPopMatrix();
	/***************** XUS ***********************/

	dibujo->dibujar(C2W,r,g,b,rad);
}

/*************************************************/

void Conector::renderizarZFuera(float r,float g,float b)
{
	sirMat4d matPieza,C2W;
	float pos[3],rot[4];
	double auxiliar[16];
	Matrix m;

	matPieza=madre->matrizPieza();
	C2W=matPieza*rotacion;

	/***************** XUS ***********************/

	C2W.obtenerMatriz(auxiliar);
	m.crear(auxiliar);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	glBegin(GL_LINES);

	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);

	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);

	glEnd();

	glPopMatrix();
	/***************** XUS ***********************/
	dibujo->dibujar(C2W,r,g,b);
}

/*************************************************/

void Conector::renderizarZFuera(float r,float g,float b,float rad)
{
	sirMat4d matPieza,C2W;
	float pos[3],rot[4];
	double auxiliar[16];
	Matrix m;

	matPieza=madre->matrizPieza();
	C2W=matPieza*rotacion;

	/***************** XUS ***********************/

	C2W.obtenerMatriz(auxiliar);
	m.crear(auxiliar);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);


	glBegin(GL_LINES);

	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);

	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);

	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);

	glEnd();

	glPopMatrix();
	/***************** XUS ***********************/

	dibujo->dibujar(C2W,r,g,b,rad);
}

/*************************************************/

void Conector::transformar(unsigned short nTime,bool bAnimation,bool bAddKey)
{
	madre->transformar(nTime,bAnimation,bAddKey);
}

/*************************************************/

void Conector::transformarConector(unsigned short nTime,bool bAnimation,bool bAddKey)
{
	Conector *actual;

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		actual->transformar(nTime,bAnimation,bAddKey);
		conectados.Siguiente();
	}
}

/*************************************************/

void Conector::mover(sirVector3d t)
{
	/******************************/
	recalcularConexiones=true;
	/******************************/

	madre->comunicarTraslacion(t);
}

/*************************************************/

void Conector::moverConector(sirVector3d t)
{
	Conector *pCon;

	/******************************/
	recalcularConexiones=true;
	/******************************/

	conectados.Primero();
	while(!conectados.Fin())
	{
		pCon=conectados.Actual();
		pCon->mover(t);
		conectados.Siguiente();
	}
}

/*************************************************/

void Conector::rotar(sirMat4d r,bool sobreZ)
{
	madre->comunicarRotacion(r,sobreZ);
}

/*************************************************/

void Conector::rotar(float rot[4],double rtooth,sirVector3d posicion)
{
	madre->comunicarRotacion(rot,rtooth,posicion);
}

/*************************************************/


void Conector::rotarConector(sirMat4d r,bool sobreZ)
{
	Conector *pCon;

	conectados.Primero();
	while(!conectados.Fin())
	{
		//Para Stud,StudInlet y AxleHole será una iteración,para el Cylindrical 1 o 2 y para el Axle N.
		//N=nº de conectores conectados
		pCon=conectados.Actual();
		pCon->rotar(r,sobreZ);
		conectados.Siguiente();
	}
}


/*************************************************/

bool Conector::conLazosCadenas(Conector *final)
{
	return madre->assemblingConLazosCadenas(final);
}

/*************************************************/

bool Conector::conLazosCadenasConector(Conector *final)
{
	Conector *pCon;
	bool cadena=false;

	conectados.Primero();
	while((!conectados.Fin()) && (!cadena))
	{
		pCon=conectados.Actual();
		if(pCon->conLazosCadenas(final)) cadena=true;
		else conectados.Siguiente();
	}
	return cadena;
}

/*************************************************/

double Conector::angulo(double opp,double adj)
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


/*************************************************/

void Conector::actualizarListas(Conector *dinamico)
{
	Piece *madreDinamico;

	madreDinamico=dinamico->obtenerMadre();

	//Actualizamos las listas de conectores conectados de ambos conectores.
	introducirConector(dinamico); //Actualizamos las listas de conectados del conector estático.
	dinamico->introducirConector(this); //Actualizamos las listas de conectados del conector dinámico.

	//Actualizamos las listas de conectores ocupados y libres de las madres.
	//Seguro que los conectores estatrán en conOcupados.
	madre->introducirConectorOcupado(this);
	madreDinamico->introducirConectorOcupado(dinamico);

	//Después del assembling seguro que los extremos de los conectores no estarán libres.
	//Será con el desplazar o desconectar que podremos volverlo a que esté libre.
	madre->esborrarConectorLibre(id);
	madreDinamico->esborrarConectorLibre(dinamico->obtenerId());

	madreDinamico=NULL;
}

/*************************************************/

void Conector::madreNoVisitada(void)
{
	madre->piezasNoVisitadas();
}

/*************************************************/

void Conector::madreNoVisitada1(void)
{
	madre->piezasNoVisitadas1();
}

/*************************************************/

void Conector::madreNoVisitadaConector(void)
{
	Conector *conectado;

	conectados.Primero();
	while(!conectados.Fin())
	{
		conectado=conectados.Actual();
		conectado->madreNoVisitada();
		conectados.Siguiente();
	}
}

/*************************************************/

void Conector::madreNoVisitadaConector1(void)
{
	Conector *conectado;

	conectados.Primero();
	while(!conectados.Fin())
	{
		conectado=conectados.Actual();
		conectado->madreNoVisitada1();
		conectados.Siguiente();
	}
}

/*************************************************/

void Conector::desconectarConector(Conector *pCon)
{
	//Si al deconectar un desconectado y este queda libre, entonces lo liberamos.

	//Un conector Extreme puede estar libre y ocupado a la vez.
	conectados.Esborrar(pCon);
	if(libre())
	{
		//Si al desconectar queda libre, entonces lo introducimos en conLibres de su pieza.
		madre->introducirConectorLibre(this); //Nunca habrán repetidos en las listas!!!
	}
	if(!ocupado())
	{
		//Al desconectarla puede o no dejar de estar ocupado.Si ya no está ocupado lo eliminamos de la lista conOcupados de su madre.
		madre->esborrarConectorOcupado(id);
	}

}

/*************************************************/

void Conector::desconectar(void)
{
	Conector *actual;

	//Eliminamos de las listados de los conectores conectados a éste, el propio conector
	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		actual->desconectarConector(this); //Puede ser que al eliminar el conector de los conectados de actual, canvie actual de ocupado a libre de su pieza.
		conectados.Siguiente();
	}

	//Vaciamos la lista de conectados
	conectados.Primero();
	while(!conectados.Vacia())
	{
		conectados.Esborrar();
	}

	//Como se borran todos los assemblings entre el conector y los conectados...
	madre->esborrarConectorOcupado(id); //entonces lo quitamos de la lista de ocupados
	madre->introducirConectorLibre(this); //y lo introducimos en la lista de conectores libres de su madre.
}

/*************************************************/

void Conector::resetearAssemblingConector(void)
{
	Conector *actual=NULL;

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		actual->resetearAssembling();
		conectados.Siguiente();
	}

	conectados.Primero();
	while(!conectados.Vacia())
	{
		conectados.Esborrar();
	}
}

/*************************************************/

void Conector::resetearAssembling(void)
{
	madre->resetearAssembling();
}

/*************************************************/

Conector *Conector::nuevoClon(void)
{
	Conector *pCon;

	pCon=new Conector(id,nombre,rotacion,madre);
	//Y LA LISTA DE CNECTADOS!!!!!!!!!!!!!!!!!!!!!!->NOS INTERESA????????????
	idConector=idConector+1; //Vigilar en la clase proyecto!!!-->Variable EXTERNA!!!
	return pCon;
}

/*************************************************/

float Conector::leerNumero(char *linea,int *ind,int lengh)
{
	int i=0;
	char aux[15];

	while(linea[(*ind)]!=' ' && (*ind)<lengh)
	{
		aux[i]=linea[(*ind)];
		i=i+1;
		(*ind)=(*ind)+1;
	}

	aux[i]='\0'; //es "i" porque se suma antes de salir
	return atof(aux);
}

/*************************************************/


void Conector::leerMatriz(char *linea)
{
	int longitud,indice=0;
	int fila=0,columna=0;

	longitud=strlen(linea);
	pasarEspacios(linea,&indice); //Por si a caso hay espacios iniciales
	//suponemos que "indice" apunta al primer número
	while(indice<longitud) //CUIDADÍN!!!
	{
		//Fichero LCI tienen los vectores en columna!!!!!!!!! (Diferente de LDraw)!!!!!!
		rotacion[fila][columna]=leerNumero(linea,&indice,longitud); //leemos el número actual
		if(fila==3)
		{
			columna=columna+1;
			fila=0;
		}
		else fila=fila+1;
		if(linea[indice+1]==' ') pasarEspacios(linea,&indice);
		else indice=indice+1;
	}

	//Transformamos la matriz de coordenadas LDraw-->LeoCAD.
	rotacion.transformacionLeoCAD();
}

/*************************************************/

void Conector::leerNombre(char *linea)
{
	char aux[25];
	int indice=0,longitud;

	longitud=strlen(linea);
	pasarEspacios(linea,&indice); //Pasamos los posibles espacios iniciales
	while(indice<longitud)
	{
		aux[indice]=linea[indice];
		//Nodeberian haber espacios en el nombre-->Ya estaremos colocados en el siguiente carácter del nombre a leer.
		if(linea[indice+1]==' ') pasarEspacios(linea,&indice);
		else indice=indice+1;
	}
	aux[indice]='\0'; //Señal de fin de string.
	introducirNombre(aux);
}

/*************************************************/

//Antes era initConector
void Conector::init(Diccionario d)
{
	Tag t("<name>");
	Contenido c1,c2;

	c1=d.Consultar(t);
	t.introducirTag("<matrix>");
	c2=d.Consultar(t);

	leerNombre(c1.obtenerContenido());
	leerMatriz(c2.obtenerContenido());
	visitado=false;
}

/*************************************************/

double Conector::distanciaMinima2(LC_CLICKLINE ClickLine)
{
	sirMat4d matPieza,C2W;

	matPieza=madre->matrizPieza();
	C2W=matPieza*rotacion;
	return distanciaPuntoRecta(C2W[0][3],C2W[1][3],C2W[2][3],ClickLine);
}


/*************************************************/

bool Conector::actualizarConectoresLibres(void)
{
	if(!libre())
	{
		madre->esborrarConectorLibre(id);
		return true;
	}
	else return false;
}

/*************************************************/

Lista<Piece*> Conector::listaPiezasConectadasConector(void)
{
	Conector *actual;
	Lista<Piece*> conectadas;

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		conectadas.Unir(actual->listaPiezasConectadas());
		conectados.Siguiente();
	}

	return conectadas;
}

/*************************************************/

Lista<Piece*> Conector::listaPiezasConectadas(void)
{
	return madre->listaPiezasConectadas();
}

/*************************************************/

bool Conector::iguales1D(FRAN_SEGMENTO AB,FRAN_SEGMENTO CD)
{
	if((iguales(AB.A,CD.A) && iguales(AB.B,CD.B)) ||(iguales(AB.A,CD.B) && iguales(AB.B,CD.A))) return true;
	else return false;
}

/*************************************************/

bool Conector::coincidenUnExtremo(FRAN_SEGMENTO AB,FRAN_SEGMENTO CD)
{
	//Cierto si coincide un extremo y los otros no están entre los segmentos.
	//No lo hago utilizando los métodos entre1D porque utilizan el ==.
	float igualAB,igualCD,diferenteAB,diferenteCD;
	bool igual=false;

	if(iguales(AB.A,CD.A))
	{
		igualAB=AB.A;
		igualCD=CD.A;
		diferenteAB=AB.B;
		diferenteCD=CD.B;
		igual=true;
	}
	else if(iguales(AB.A,CD.B))
	{
		igualAB=AB.A;
		igualCD=CD.B;
		diferenteAB=AB.B;
		diferenteCD=CD.A;
		igual=true;
	}
	else if(iguales(AB.B,CD.A))
	{
		igualAB=AB.B;
		igualCD=CD.A;
		diferenteAB=AB.A;
		diferenteCD=CD.B;
		igual=true;
	}
	else if(iguales(AB.B,CD.B)) //Hay que preguntarlo porque en el caso de que no fueran iguales también entraría.
	{
		//AB.B==CD.B
		igualAB=AB.B;
		igualCD=CD.B;
		diferenteAB=AB.A;
		diferenteCD=CD.A;
		igual=true;
	}
	else igual=false;

	if(igual)
	{
		if((diferenteAB<igualCD && diferenteCD>igualAB) || (diferenteAB>igualCD && diferenteCD<igualAB)) return true;
		else return false;
	}
	else return false;
}
/*************************************************/

bool Conector::entre1D(float P,FRAN_SEGMENTO AB)
{
	//Devuelve cierto si el punto P está entre el segmento (A,B)-->1D.
	//Los tres puntos están alineados (coaxiales).

	//A|------|B
	//B|------|A

	//if((P>=AB.A && P<=AB.B) || (P>=AB.B && P<=AB.A)) return true;
	//else return false;

	//Por motivos de robustes utilizamos el iguales y no el ==.
	if(((P>AB.A || iguales(P,AB.A)) && (P<AB.B || iguales(P,AB.B))) || ((P>AB.B || iguales(P,AB.B)) && (P<AB.A || iguales(P,AB.A)))) return true;
	else return false;

	//RESTRICCIÓN!!!!!!!!!!!!!!!!!!!!!!!!!!
	//if((P>AB.A && P<AB.B) || (P>AB.B && P<AB.A)) return true;
	//else return false;
}

/*************************************************/

bool Conector::fuera1D(float P,FRAN_SEGMENTO AB)
{
	//Devuelve cierto si el punto P está fuera del segmento (A,B)-->1D.
	//Los tres puntos están alineados (coaxiales).

	//A|------|B
	//B|------|A

	//Estrictamente fuera.

	if((P<AB.A && P<AB.B) || (P>AB.A && P>AB.B)) return true;
	else return false;
}

/*************************************************/

bool Conector::inferior1D(float P,FRAN_SEGMENTO AB)
{
	//Devuelve cierto si el punto P está por debajo del segmento AB.
	//Los tres puntos están alineados (coaxiales).

	//P    A|--------|B
	//P    B|--------|A->???

	if(P<AB.A && P<AB.B) return true;
	else return false;
}

/*************************************************/

bool Conector::superior1D(float P,FRAN_SEGMENTO AB)
{

	if(P>AB.A && P>AB.B) return true;
	else return false;
}


/*************************************************/

double Conector::distanciaEntreExtremosHermanos(Conector *pCon)
{
	Conector *hermanoCon;
	sirVector4d I(0,0,0,1),F(0,0,0,1),IC(0,0,0,1),FC(0,0,0,1);
	double distMin,aux;



	sirVector4d i(0,0,0,1),f(0,0,0,1),ih(0,0,0,1),fh(0,0,0,1);
	i=obtenerPuntoInicial();
	f=obtenerPuntoFinal();
	hermanoCon=obtenerHermano();
	ih=hermanoCon->obtenerPuntoInicial();
	fh=hermanoCon->obtenerPuntoFinal();


	I=obtenerPuntoInicial(); //Punto inicial del segmento en coordenadas de mundo.
	if(tengoHermano())
	{
		hermanoCon=obtenerHermano();
		F=hermanoCon->obtenerPuntoInicial();
	}
	else F=obtenerPuntoFinal();

	IC=pCon->obtenerPuntoInicial();
	if(pCon->tengoHermano())
	{
		hermanoCon=pCon->obtenerHermano();
		FC=hermanoCon->obtenerPuntoInicial();
	}
	else FC=pCon->obtenerPuntoFinal();

	distMin=distanciaPuntos(I[0],I[1],I[2],IC[0],IC[1],IC[2]); //Inicial-Inicial.
	aux=distanciaPuntos(I[0],I[1],I[2],FC[0],FC[1],FC[2]); //Inicial-Final.
	if(aux<distMin) distMin=aux;
	aux=distanciaPuntos(F[0],F[1],F[2],IC[0],IC[1],IC[2]); //Inicial-Final.
	if(aux<distMin) distMin=aux;
	aux=distanciaPuntos(F[0],F[1],F[2],FC[0],FC[1],FC[2]); //Final-Final.
	if(aux<distMin) distMin=aux;

	hermanoCon=NULL;
	return distMin;
}

double Conector::distanciaEntreExtremos(Conector *pCon)
{
	sirVector4d I(0,0,0,1),F(0,0,0,1),IC(0,0,0,1),FC(0,0,0,1);
	double distMin,aux;

	I=obtenerPuntoInicial(); //Punto inicial del segmento en coordenadas de mundo.
	F=obtenerPuntoFinal();

	IC=pCon->obtenerPuntoInicial();
	FC=pCon->obtenerPuntoFinal();

	distMin=distanciaPuntos(I[0],I[1],I[2],IC[0],IC[1],IC[2]); //Inicial-Inicial.
	aux=distanciaPuntos(I[0],I[1],I[2],FC[0],FC[1],FC[2]); //Inicial-Final.
	if(aux<distMin) distMin=aux;
	aux=distanciaPuntos(F[0],F[1],F[2],IC[0],IC[1],IC[2]); //Inicial-Final.
	if(aux<distMin) distMin=aux;
	aux=distanciaPuntos(F[0],F[1],F[2],FC[0],FC[1],FC[2]); //Final-Final.
	if(aux<distMin) distMin=aux;

	return distMin;
}

/*************************************************/

void Conector::conectadosColisionDeslizar(int direccion,Conector *conDeslizar,Lista<Conector*> *conColisiones)
{
	//Faltará mirar que los que se introduzcan en la EDF no estén conectados directa o
	//indirectamente al conector que se desliza.

	//SERIA:
	//	-La menor distancia de los que están conectados directa o indirectamente al conector
	//	 a deslizar con los que están en la dirección de deslizamiento.

	Conector *actual;
	ContenidoColision elemento;
	sirMat4d W2C;
	FRAN_SEGMENTO segmento;

	W2C=conDeslizar->obtenerC2W();
	W2C=W2C.inverse();

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();

		if(conDeslizar->tengoHermano())
		{
			if(actual!=conDeslizar && actual!=conDeslizar->obtenerHermano())
			{
				segmento=actual->obtenerSegmento(W2C);
				if(direccion>=0)
				{
					//if(segmento.A>=0 || segmento.B>=0) conColisiones->Introducir(actual);
					//Sinó está en la dirección no se introduce.
					if(segmento.A<0 && segmento.B<0)
					{
					}
					else if((iguales(segmento.A,0) && segmento.B<0) || (iguales(segmento.B,0) && segmento.A<0))
					{
					}
					else conColisiones->Introducir(actual);
				}
				else
				{
					//if(segmento.A<=0 || segmento.B<=0) conColisiones->Introducir(actual);
					if(segmento.A>0 && segmento.B>0)
					{
					}
					else if((iguales(segmento.A,0) && segmento.B>0) || (iguales(segmento.B,0) && segmento.A>0))
					{
					}
					else conColisiones->Introducir(actual);
				}
			}
		}
		else
		{
			//Mirar posición final!!!!!!!!!!!!!!!!!!!!-->NO!!!!!!!!!!!!!!!!

			if(actual!=conDeslizar)
			{
				segmento=actual->obtenerSegmento(W2C);
				if(direccion>=0)
				{
					//if(segmento.A>=0 || segmento.B>=0) conColisiones->Introducir(actual);
					//Sinó está en la dirección no se introduce.
					if(segmento.A<0 && segmento.B<0)
					{
					}
					else if((iguales(segmento.A,0) && segmento.B<0) || (iguales(segmento.B,0) && segmento.A<0))
					{
					}
					else conColisiones->Introducir(actual);
				}
				else
				{
					//if(segmento.A<=0 || segmento.B<=0) conColisiones->Introducir(actual);
					if(segmento.A>0 && segmento.B>0)
					{
					}
					else if((iguales(segmento.A,0) && segmento.B>0) || (iguales(segmento.B,0) && segmento.A>0))
					{
					}
					else conColisiones->Introducir(actual);
				}
			}
		}
		conectados.Siguiente();
	}

	actual=NULL;
}

/*************************************************/

bool Conector::caminoDeAssemblings(Conector *final,Lista<Conector*> conDeslizados)
{
	return madre->caminoDeAssemblings(final,conDeslizados);
}

/*************************************************/

bool Conector::caminoDeAssemblingsConector(Conector *final,Lista<Conector*> conDeslizados)
{
	//Teóricamente tanto el conector final y el inicial tienen que estar como ocupados.
	Conector *actual;
	bool camino=false;

	conectados.Primero();
	while((!conectados.Fin()) && (!camino))
	{
		actual=conectados.Actual();
		if(!conDeslizados.Existe(actual))
		{
			if(actual->caminoDeAssemblings(final,conDeslizados)) camino=true;
			else conectados.Siguiente();
		}
		else conectados.Siguiente();
	}
	return camino;
}

/*************************************************/

Lista<Conector*> Conector::listaConectadosPuedenDeslizar(void)
{
	//Devuelve una lista de los conectores conectados que pueden deslizar.
	Conector *actual,*hermanoActual;
	Lista<Conector*> lista;

	conectados.Primero();
	while(!conectados.Fin())
	{
		actual=conectados.Actual();
		//Para que no se metan un conector dos veces por si el conector que llama a
		//este método está cnectados a los dos hermanos.
		if((actual->puedeDeslizar()) && (!lista.Existe(actual))) lista.Introducir(actual);
		if(actual->tengoHermano())
		{
			hermanoActual=actual->obtenerHermano();
			if(!lista.Existe(hermanoActual)) lista.Introducir(hermanoActual);
		}
		conectados.Siguiente();
	}
	return lista;
}

/*************************************************/

bool Conector::rotarEjeZ(sirMat4d r)
{
	sirVector4d p1(0,0,0,0),p2(0,0,0,0),p3(0,0,0,0),p4(0,0,0,0);
	sirVector4d v1(0,0,0,0),v2(0,0,0,0);
	sirMat4d C2W,matMadre;


	v1[2]=obtenerLongitud();
	v2[2]=obtenerLongitud();

	//Hay que aplicarle la rotación a la matriz de la pieza y luego volver a calcular las coordenadas de los puntos y C2W.
	matMadre=madre->matrizPieza();
	C2W=matMadre*rotacion;

	v1=rotacion*v1;
	v1=matMadre*v1;

	p1[0]=C2W[0][3];
	p1[1]=C2W[1][3];
	p1[2]=C2W[2][3];

	p2[0]=C2W[0][3]+v1[0];
	p2[1]=C2W[1][3]+v1[1];
	p2[2]=C2W[2][3]+v1[2];


	matMadre=r*matMadre;
	C2W=matMadre*rotacion;

	v2=rotacion*v2;
	v2=matMadre*v2;

	p3[0]=C2W[0][3];
	p3[1]=C2W[1][3];
	p3[2]=C2W[2][3];

	p4[0]=C2W[0][3]+v2[0];
	p4[1]=C2W[1][3]+v2[1];
	p4[2]=C2W[2][3]+v2[2];

	//Por motivos de robustez.
	if(distanciaPuntos(p1[0],p1[1],p1[2],p3[0],p3[1],p3[2])<=DELTA_FRAN && distanciaPuntos(p2[0],p2[1],p2[2],p4[0],p4[1],p4[2])<=DELTA_FRAN) return true;
	else return false;
}

