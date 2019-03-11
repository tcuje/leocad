/*************************************************/
/*                                               */
/*					  CRUZ.CPP  	             */
/*                                               */
/*************************************************/

#include "cruz.h"

/*************************************************/

void Cruz::cruz(float r,float g,float b,float altura)
{
	//Se dibuja respecto al centro del conector
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(-DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ,altura);
	glVertex3f(-DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ-DISTANCIA2_CRUZ,altura);
	glVertex3f(-DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ-DISTANCIA2_CRUZ,altura);
	glVertex3f(DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ-DISTANCIA2_CRUZ,altura);
	glVertex3f(DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ-DISTANCIA2_CRUZ,altura);
	glVertex3f(DISTANCIA1_CRUZ,-DISTANCIA1_CRUZ,altura);
	glEnd();
}

/*************************************************/

void Cruz::dibujar(sirMat4d matriz,float r,float g,float b)
{
	float pos[3],rot[4];//aux[16];
	Matrix m;

	//Areglo
	double aux[16];

	//p'=matConector*matPieza*p-->El punt estará en coordenadas de mundo!!!!!!

	matriz.obtenerMatriz(aux);
	m.crear(aux);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	cruz(r,g,b,-0.10);
	cruz(r,g,b,0.10);
	glRotatef(90,0,0,1);
	cruz(r,g,b,-0.10);
	cruz(r,g,b,0.10);
	glRotatef(90,0,0,1);
	cruz(r,g,b,-0.10);
	cruz(r,g,b,0.10);
	glRotatef(90,0,0,1);
	cruz(r,g,b,-0.10);
	cruz(r,g,b,0.10);

	/*//Dibujo su normal!!!
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glLineWidth(2);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glEnd();*/

	glPopMatrix();
}

