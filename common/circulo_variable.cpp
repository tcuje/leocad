/*************************************************/
/*                                               */
/*				CIRCULO_VARIABLE.CPP             */
/*                                               */
/*************************************************/

#include "circulo_variable.h"


/*************************************************/

void Circulo_Variable::semiCirculo(int inf,int sup,float r,float g,float b,float *xant,float *yant,float radio)
{
	int i;
	float alfa,xact,yact;

	for(i=inf;i<=sup;i++)
	{
		alfa=(float)(2*M_PI*i)/16;

		xact=(float)(radio*cos(alfa));
		yact=(float)(radio*sin(alfa));

		glBegin(GL_LINES);
		glColor3f(r,g,b);
		glLineWidth(2);
		glVertex3f(*xant,*yant,0);
		glVertex3f(xact,yact,0);
		glVertex3f(*xant,*yant,(float)ALTURA_CIRCULO);
		glVertex3f(xact,yact,(float)ALTURA_CIRCULO);
		glEnd();

		*xant=xact;
		*yant=yact;
	}
}

/*************************************************/

void Circulo_Variable::dibujar(sirMat4d matriz,float r,float g,float b)
{
	float alfa,xant,yant,xact,yact;
	float pos[3],rot[4];//aux[16];
	Matrix m;

	//Areglo
	double aux[16];

	//El círculo se dibuja alrededor del eje Z.

	//matriz es la matriz del objeto sobre el que hay que dibujar la geometría en coordenadas de mundo.
	matriz.obtenerMatriz(aux);
	m.crear(aux);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	xant=(float)RADIO_CIRCULO;
	yant=0;

	alfa=(float)((2*M_PI)/16);

	xact=(float)(RADIO_CIRCULO*cos(alfa));
	yact=(float)(RADIO_CIRCULO*sin(alfa));

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f((float)(xant-0.10),yant,0);
	glVertex3f(xact,yact,0);
	glVertex3f((float)(xant-0.10),yant,(float)ALTURA_CIRCULO);
	glVertex3f(xact,yact,(float)ALTURA_CIRCULO);
	glEnd();

	xant=xact;
	yant=yact;

	semiCirculo(1,7,r,g,b,&xant,&yant,(float)RADIO_CIRCULO);

	alfa=(float)((2*M_PI*8)/16);

	xact=(float)(RADIO_CIRCULO*cos(alfa));
	yact=(float)(RADIO_CIRCULO*sin(alfa));
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f((float)(xact+0.10),yact,0);
	glVertex3f(xant,yant,(float)ALTURA_CIRCULO);
	glVertex3f((float)(xact+0.10),yact,(float)ALTURA_CIRCULO);

	glEnd();

	xant=(float)(xact+0.10);
	yant=yact;

	semiCirculo(9,15,r,g,b,&xant,&yant,(float)RADIO_CIRCULO);

	alfa=(float)(2*M_PI);

	xact=(float)(RADIO_CIRCULO*cos(alfa));
	yact=(float)(RADIO_CIRCULO*sin(alfa));

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f((float)(xact-0.10),yact,0);
	glVertex3f(xant,yant,(float)ALTURA_CIRCULO);
	glVertex3f((float)(xact-0.10),yact,(float)ALTURA_CIRCULO);
	glEnd();

	glPopMatrix();

}

void Circulo_Variable::dibujar(sirMat4d matriz,float r,float g,float b,float radio)
{
	float alfa,xant,yant,xact,yact;
	float pos[3],rot[4];//aux[16];
	Matrix m;

	//Areglo
	double aux[16];

	//El círculo se dibuja alrededor del eje Z.

	//matriz es la matriz del objeto sobre el que hay que dibujar la geometría en coordenadas de mundo.
	matriz.obtenerMatriz(aux);
	m.crear(aux);
	m.GetTranslation(pos);
	m.ToAxisAngle(rot);

	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glRotatef(rot[3],rot[0],rot[1],rot[2]);

	xant=radio;
	yant=0;

	alfa=(float)((2*M_PI)/16);

	xact=(float)(radio*cos(alfa));
	yact=(float)(radio*sin(alfa));

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f((float)(xant-0.10),yant,0);
	glVertex3f(xact,yact,0);
	glVertex3f((float)(xant-0.10),yant,(float)ALTURA_CIRCULO);
	glVertex3f(xact,yact,(float)ALTURA_CIRCULO);
	glEnd();

	xant=xact;
	yant=yact;

	semiCirculo(1,7,r,g,b,&xant,&yant,radio);

	alfa=(float)((2*M_PI*8)/16);

	xact=(float)(radio*cos(alfa));
	yact=(float)(radio*sin(alfa));
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f((float)(xact+0.10),yact,0);
	glVertex3f(xant,yant,(float)ALTURA_CIRCULO);
	glVertex3f((float)(xact+0.10),yact,(float)ALTURA_CIRCULO);

	glEnd();

	xant=(float)(xact+0.10);
	yant=yact;

	semiCirculo(9,15,r,g,b,&xant,&yant,radio);

	alfa=(float)(2*M_PI);

	xact=(float)(radio*cos(alfa));
	yact=(float)(radio*sin(alfa));

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f((float)(xact-0.10),yact,0);
	glVertex3f(xant,yant,(float)ALTURA_CIRCULO);
	glVertex3f((float)(xact-0.10),yact,(float)ALTURA_CIRCULO);
	glEnd();

	glPopMatrix();

}

