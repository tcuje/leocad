/*************************************************/
/*                                               */
/*                UTILIDADES.CPP                 */
/*                                               */
/*************************************************/


#include "utilidades.h"

void nada()
{
}


bool ajuste(double a,double b)
{
	double aux=0.002;
	return ((a-b<aux)&&(a-b>(-1)*aux));
}

/*************************************************/

char * buscarfin(char aux2[])
{
	int i;
	bool trobat=false;
	char *aux;
	for (i=0;!trobat && i<50;i++)
	{
		if(aux2[i]=='<')
		{
			trobat=true;
			aux2[i]='\0';
		}
	}
	aux=aux2;
	return aux;
}

/*************************************************/

double angulo(double opp,double adj)
{
	//Función que alculo el ángulo con la tangente opp/adj
	//El valor que devulve se encuentra entre PI y -PI

	double angulo;
	char aux[3];
	int aux2;

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

/***********************************************************/

void imprimirMatriz(Matrix m)
{
	char cadena[500];
	char r1[30],r2[30],r3[30],r4[30],r5[30],r6[30],r7[30],r8[30],r9[30],r10[30],r11[30],r12[30],r13[30],r14[30],r15[30],r16[30];

	_gcvt(m.m[0],7,r1);
	_gcvt(m.m[1],7,r2);
	_gcvt(m.m[2],7,r3);
	_gcvt(m.m[3],7,r4);
	_gcvt(m.m[4],7,r5);
	_gcvt(m.m[5],7,r6);
	_gcvt(m.m[6],7,r7);
	_gcvt(m.m[7],7,r8);
	_gcvt(m.m[8],7,r9);
	_gcvt(m.m[9],7,r10);
	_gcvt(m.m[10],7,r11);
	_gcvt(m.m[11],7,r12);
	_gcvt(m.m[12],7,r13);
	_gcvt(m.m[13],7,r14);
	_gcvt(m.m[14],7,r15);
	_gcvt(m.m[15],7,r16);
	strcpy(cadena,"1 vector-->");
	strcat(cadena,"(");
	strcat(cadena,r1);
	strcat(cadena,",");
	strcat(cadena,r2);
	strcat(cadena,",");
	strcat(cadena,r3);
	strcat(cadena,",");
	strcat(cadena,r4);
	strcat(cadena,")");
	strcat(cadena,"2 vector-->");
	strcat(cadena,"(");
	strcat(cadena,r5);
	strcat(cadena,",");
	strcat(cadena,r6);
	strcat(cadena,",");
	strcat(cadena,r7);
	strcat(cadena,",");
	strcat(cadena,r8);
	strcat(cadena,")");
	strcat(cadena,"3 vector-->");
	strcat(cadena,"(");
	strcat(cadena,r9);
	strcat(cadena,",");
	strcat(cadena,r10);
	strcat(cadena,",");
	strcat(cadena,r11);
	strcat(cadena,",");
	strcat(cadena,r12);
	strcat(cadena,")");
	strcat(cadena,"4 vector-->");
	strcat(cadena,"(");
	strcat(cadena,r13);
	strcat(cadena,",");
	strcat(cadena,r14);
	strcat(cadena,",");
	strcat(cadena,r15);
	strcat(cadena,",");
	strcat(cadena,r16);
	strcat(cadena,")");
	AfxMessageBox(cadena);
}

/***********************************************************/

void imprimirMatriz(sirMat4d m)
{
	char cadena[500];
	char r1[30],r2[30],r3[30],r4[30],r5[30],r6[30],r7[30],r8[30],r9[30],r10[30],r11[30],r12[30],r13[30],r14[30],r15[30],r16[30];

	_gcvt(m[0][0],7,r1);
	_gcvt(m[1][0],7,r2);
	_gcvt(m[2][0],7,r3);
	_gcvt(m[3][0],7,r4);
	_gcvt(m[0][1],7,r5);
	_gcvt(m[1][1],7,r6);
	_gcvt(m[2][1],7,r7);
	_gcvt(m[3][1],7,r8);
	_gcvt(m[0][2],7,r9);
	_gcvt(m[1][2],7,r10);
	_gcvt(m[2][2],7,r11);
	_gcvt(m[3][2],7,r12);
	_gcvt(m[0][3],7,r13);
	_gcvt(m[1][3],7,r14);
	_gcvt(m[2][3],7,r15);
	_gcvt(m[3][3],7,r16);
	strcpy(cadena,"1 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r1);
	strcat(cadena,",");
	strcat(cadena,r2);
	strcat(cadena,",");
	strcat(cadena,r3);
	strcat(cadena,",");
	strcat(cadena,r4);
	strcat(cadena,")");
	strcat(cadena,"2 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r5);
	strcat(cadena,",");
	strcat(cadena,r6);
	strcat(cadena,",");
	strcat(cadena,r7);
	strcat(cadena,",");
	strcat(cadena,r8);
	strcat(cadena,")");
	strcat(cadena,"3 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r9);
	strcat(cadena,",");
	strcat(cadena,r10);
	strcat(cadena,",");
	strcat(cadena,r11);
	strcat(cadena,",");
	strcat(cadena,r12);
	strcat(cadena,")");
	strcat(cadena,"4 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r13);
	strcat(cadena,",");
	strcat(cadena,r14);
	strcat(cadena,",");
	strcat(cadena,r15);
	strcat(cadena,",");
	strcat(cadena,r16);
	strcat(cadena,")");
	AfxMessageBox(cadena);
}

void cadenamatriz(sirMat4d m,char cad[])
{
	char cadena[500];
	char r1[30],r2[30],r3[30],r4[30],r5[30],r6[30],r7[30],r8[30],r9[30],r10[30],r11[30],r12[30],r13[30],r14[30],r15[30],r16[30];

	_gcvt(m[0][0],7,r1);
	_gcvt(m[1][0],7,r2);
	_gcvt(m[2][0],7,r3);
	_gcvt(m[3][0],7,r4);
	_gcvt(m[0][1],7,r5);
	_gcvt(m[1][1],7,r6);
	_gcvt(m[2][1],7,r7);
	_gcvt(m[3][1],7,r8);
	_gcvt(m[0][2],7,r9);
	_gcvt(m[1][2],7,r10);
	_gcvt(m[2][2],7,r11);
	_gcvt(m[3][2],7,r12);
	_gcvt(m[0][3],7,r13);
	_gcvt(m[1][3],7,r14);
	_gcvt(m[2][3],7,r15);
	_gcvt(m[3][3],7,r16);
	strcpy(cadena,"1 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r1);
	strcat(cadena,",");
	strcat(cadena,r2);
	strcat(cadena,",");
	strcat(cadena,r3);
	strcat(cadena,",");
	strcat(cadena,r4);
	strcat(cadena,")");
	strcat(cadena,"2 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r5);
	strcat(cadena,",");
	strcat(cadena,r6);
	strcat(cadena,",");
	strcat(cadena,r7);
	strcat(cadena,",");
	strcat(cadena,r8);
	strcat(cadena,")");
	strcat(cadena,"3 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r9);
	strcat(cadena,",");
	strcat(cadena,r10);
	strcat(cadena,",");
	strcat(cadena,r11);
	strcat(cadena,",");
	strcat(cadena,r12);
	strcat(cadena,")");
	strcat(cadena,"4 vcol-->");
	strcat(cadena,"(");
	strcat(cadena,r13);
	strcat(cadena,",");
	strcat(cadena,r14);
	strcat(cadena,",");
	strcat(cadena,r15);
	strcat(cadena,",");
	strcat(cadena,r16);
	strcat(cadena,")");

	strcpy(cad,cadena);
}

/***********************************************************/

void imprimirVector(sirVector3d v)
{
	char cadena[500];
	char r1[30],r2[30],r3[30];

	_gcvt(v[0],7,r1);
	_gcvt(v[1],7,r2);
	_gcvt(v[2],7,r3);
	strcpy(cadena,"vector-->");
	strcat(cadena,"(");
	strcat(cadena,r1);
	strcat(cadena,",");
	strcat(cadena,r2);
	strcat(cadena,",");
	strcat(cadena,r3);
	strcat(cadena,")");

	AfxMessageBox(cadena);
}

/***********************************************************/

void imprimirVector(sirVector4d v)
{
	char a[100];
	char n1[30],n2[30],n3[30],n4[30];

	_gcvt(v[0],7,n1);
	_gcvt(v[1],7,n2);
	_gcvt(v[2],7,n3);
	_gcvt(v[3],7,n4);
	strcpy(a,"(");
	strcat(a,n1);
	strcat(a,",");
	strcat(a,n2);
	strcat(a,",");
	strcat(a,n3);
	strcat(a,",");
	strcat(a,n4);
	strcat(a,")");
	AfxMessageBox(a);
}

void imprimirVector(float *v)
{
	char a[100];
	char n1[30],n2[30],n3[30],n4[30];

	_gcvt(v[0],7,n1);
	_gcvt(v[1],7,n2);
	_gcvt(v[2],7,n3);
	_gcvt(v[3],7,n4);
	strcpy(a,"(");
	strcat(a,n1);
	strcat(a,",");
	strcat(a,n2);
	strcat(a,",");
	strcat(a,n3);
	strcat(a,",");
	strcat(a,n4);
	strcat(a,")");
	AfxMessageBox(a);
}
void cadenavector(sirVector4d v,char cad[])
{
	char a[100];
	char n1[30],n2[30],n3[30],n4[30];

	_gcvt(v[0],7,n1);
	_gcvt(v[1],7,n2);
	_gcvt(v[2],7,n3);
	_gcvt(v[3],7,n4);
	strcpy(a,"(");
	strcat(a,n1);
	strcat(a,",");
	strcat(a,n2);
	strcat(a,",");
	strcat(a,n3);
	strcat(a,",");
	strcat(a,n4);
	strcat(a,")");

	strcpy(cad,a);
}
/***********************************************************/

void imprimirEntero(int n)
{
	char a[40];
	char s[5];
	_itoa(n,s,10);
	strcpy(a,"Conector seleccionado: ");
	strcat(a,s);
	AfxMessageBox(a);
}

/***********************************************************/

void imprimirFloat(float n)
{
	char s[30];
	_gcvt(n,7,s);
	AfxMessageBox(s);
}

/***********************************************************/

void imprimirDouble(double n)
{
	char s[30];
	_gcvt(n,7,s);
	AfxMessageBox(s);
}

/***********************************************************/

void pasarEspacios(char *linea,int *ind)
{
	while(linea[(*ind)]==' ' && linea[(*ind)]!='\0') (*ind)=(*ind)+1; //Por si acaso se hubiera puesto más de un espacio entre números.
}

/***********************************************************/

bool lineaVacia(char *linea)
{
	int i=0;
	bool trobat=false;

	while(/*linea[i]!='\n'*/linea[i]!='\0' && !trobat)
	{
		if(linea[i]!=' ') trobat=true;
		else i=i+1;
	}

	if(trobat) return false; //Hem trobat un caràcter que no es espai
	else return true;
}

/***********************************************************/


char *leerContenido(char *linea,int *indice)
{

	char *resultado=new char[strlen(linea)+1]; //strlen(linea)+1-longitudTag;
	int i=0,longitud;

	pasarEspacios(linea,indice); //Pasamos los posibles espacios en blanco iniciales
	longitud=strlen(linea);

	//Por si el tag no está en la misma línea que el contenido!!!
	while((linea[(*indice)]!='<') && ((*indice)<longitud))
	{
		resultado[i]=linea[(*indice)];
		(*indice)=(*indice)+1;
		i=i+1;
	}

	resultado[i]='\0'; //Marca de final de string.

	return resultado;
}


/***********************************************************/

bool restoLineaVacia(char *linea,int *indice)
{
	int i;
	bool trobat=false;

	i=(*indice);
	while(/*i<strlen(linea)---linea[i]!='\n'*/linea[i]!='\0' && !trobat)
	{
		if(linea[i]!=' ') trobat=true;
		else i=i+1;
	}


	if(!trobat)
	{
		(*indice)=0;
		return true;
	}
	else return false;
}

/***********************************************************/

bool compararTag(char *linea,int *indice,char *tag)
{
	char aux[20];
	int i=0;

	pasarEspacios(linea,indice); //Pasamos los posibles espacios en blanco iniciales
	while(linea[(*indice)]!='>')
	{
		aux[i]=linea[(*indice)];
		(*indice)=(*indice)+1;
		i=i+1;
		pasarEspacios(linea,indice);
	}

	aux[i]=linea[(*indice)];
	aux[i+1]='\0';
	(*indice)=(*indice)+1; //Al final "ind" apunta al primer carácter de la "linea".

	if(!strcmp(aux,tag)) return true;
	else return false;
}

char *obtenerTag(char *linea,int *indice)
{
	char aux[20],*resultat;
	int i=0;

	pasarEspacios(linea,indice); //Pasamos los posibles espacios en blanco iniciales
	while(linea[(*indice)]!='>')
	{
		aux[i]=linea[(*indice)];
		(*indice)=(*indice)+1;
		i=i+1;
		pasarEspacios(linea,indice);
	}

	aux[i]=linea[(*indice)];
	aux[i+1]='\0';
	(*indice)=(*indice)+1; //Al final "ind" apunta al primer carácter de la "linea".
	resultat=new char[strlen(aux)+1];
	strcpy(resultat,aux);
	return resultat;
}


/***********************************************************/

bool pasarLineasVacias(ifstream *f,char *linea,int *indice)
{
	//Método que pasa las líneas vacías del fichero f y devuelve cierto
	//en caso de que sigan habiendo más líneas por leer. En caso de que
	//llegáramos al final del mismo devolvería falso.

	while(lineaVacia(linea))
	{
		if(!f->eof()) f->getline(linea,200); //Mientras hayan líneas vacías las saltamos
		else return false;
	}

	(*indice)=0;

	return true;
}

/***********************************************************/

bool obtenerLineaConInformacion(ifstream *f,char *linea,int *indice)
{
	f->getline(linea,200); //Cogemos la línea actual
	if(!pasarLineasVacias(f,linea,indice))
	{
		f->close();
		return false;
	}
	return true;
}

