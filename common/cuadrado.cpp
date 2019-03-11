/*************************************************/
/*                                               */
/*					CUADRADO.CPP	             */
/*                                               */
/*************************************************/

#include "cuadrado.h"
#include "utilidades.h"

/*************************************************/

void Cuadrado::lado(float r,float g,float b)
{
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);

	glVertex3f((float)ANCHURA_CUADRADO,-ANCHURA_CUADRADO,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,0);
	glVertex3f((float)ANCHURA_CUADRADO,-ANCHURA_CUADRADO,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,(float)ALTURA_CUADRADO);

	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,0);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,(float)ALTURA_CUADRADO);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,(float)ALTURA_CUADRADO);

	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,0);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,(float)ALTURA_CUADRADO);

	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,0);
	glVertex3f((float)ANCHURA_CUADRADO,ANCHURA_CUADRADO,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,(float)ANCHURA_CUADRADO,(float)ALTURA_CUADRADO);

	glEnd();

}
void Cuadrado::lado(float r,float g,float b,float radio)
{
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);

	glVertex3f((float)ANCHURA_CUADRADO,-radio,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,0);
	glVertex3f((float)ANCHURA_CUADRADO,-radio,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,(float)ALTURA_CUADRADO);

	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,0);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)-0.10,(float)ALTURA_CUADRADO);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,(float)ALTURA_CUADRADO);


	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,0);
	glVertex3f((float)(ANCHURA_CUADRADO-0.10),0,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,(float)ALTURA_CUADRADO);

	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,0);
	glVertex3f((float)ANCHURA_CUADRADO,radio,0);
	glVertex3f((float)ANCHURA_CUADRADO,(float)0.10,(float)ALTURA_CUADRADO);
	glVertex3f((float)ANCHURA_CUADRADO,radio,(float)ALTURA_CUADRADO);

	glEnd();

}

void Cuadrado::ladoc(float r,float g,float b,float radio)
{
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);

	glVertex3f(radio,-ANCHURA_CUADRADO,0);
	glVertex3f(radio,(float)-0.10,0);
	glVertex3f(radio,-ANCHURA_CUADRADO,(float)ALTURA_CUADRADO);
	glVertex3f(radio,(float)-0.10,(float)ALTURA_CUADRADO);

	glVertex3f(radio,(float)-0.10,0);
	glVertex3f((float)(radio-0.10),0,0);
	glVertex3f(radio,(float)-0.10,(float)ALTURA_CUADRADO);
	glVertex3f((float)(radio-0.10),0,(float)ALTURA_CUADRADO);

	glVertex3f((float)(radio-0.10),0,0);
	glVertex3f(radio,(float)0.10,0);
	glVertex3f((float)(radio-0.10),0,(float)ALTURA_CUADRADO);
	glVertex3f(radio,(float)0.10,(float)ALTURA_CUADRADO);

	glVertex3f(radio,(float)0.10,0);
	glVertex3f(radio,ANCHURA_CUADRADO,0);
	glVertex3f(radio,(float)0.10,(float)ALTURA_CUADRADO);
	glVertex3f(radio,ANCHURA_CUADRADO,(float)ALTURA_CUADRADO);

	glEnd();

}
/*************************************************/

void Cuadrado::dibujar(sirMat4d matriz,float r,float g,float b)
{
	float pos[3],rot[4];//aux[16];
	Matrix m;

	//Areglo
	double aux[16];

	matriz.obtenerMatriz(aux);
	m.crear(aux);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	//Tengo que aplicarle la rotación correspondiente para que si se rota se haga respecto al centro de la pieza!!!!!!!!

	lado(r,g,b);
	//glPushMatrix();
	glRotatef(90,0,0,1);
	lado(r,g,b);
	glRotatef(90,0,0,1);
	lado(r,g,b);
	glRotatef(90,0,0,1);
	lado(r,g,b);
	//glPopMatrix();

	glPopMatrix();

}

/*************************************************/

void Cuadrado::dibujar(sirMat4d matriz,float r,float g,float b,float radio)
{
	float pos[3],rot[4];//aux[16];
	sirMat4d ma;
	sirVector4d normal(0,1,0,0);
	sirVector3d auxi;
	Matrix m;

	//Areglo
	double aux[16];

	auxi[0]=matriz[0][3];
	auxi[1]=matriz[1][3];
	auxi[2]=matriz[2][3];

	normal=matriz*normal;
	m.Rotate(90,(float)normal[0],(float)normal[1],(float)normal[2]);
	ma.introducir(m.m);
	matriz=ma*matriz;

	matriz[0][3]=auxi[0];
	matriz[1][3]=auxi[1];
	matriz[2][3]=auxi[2];

	matriz.obtenerMatriz(aux);
	m.crear(aux);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	//Tengo que aplicarle la rotación correspondiente para que si se rota se haga respecto al centro de la pieza!!!!!!!!

	ladoc(r,g,b,radio);
	//glPushMatrix();
	glRotatef(90,0,0,1);
	lado(r,g,b,radio);
	glRotatef(90,0,0,1);
	ladoc(r,g,b,radio);
	glRotatef(90,0,0,1);
	lado(r,g,b,radio);
	//glPopMatrix();

	glPopMatrix();

}