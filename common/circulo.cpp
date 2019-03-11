/*************************************************/
/*                                               */
/*				CIRCULO_VARIABLE.CPP             */
/*                                               */
/*************************************************/

#include "circulo.h"


/*************************************************/

void Circulo::semiCirculo(int inf,int sup,float r,float g,float b,float *xant,float *yant)
{
	int i;
	float alfa,xact,yact;

	for(i=inf;i<=sup;i++)
	{
		alfa=(2*M_PI*i)/16;

		xact=RADIO_CIRCULO*cos(alfa);
		yact=RADIO_CIRCULO*sin(alfa);

		glBegin(GL_LINES);
		glColor3f(r,g,b);
		glLineWidth(2);
		glVertex3f(*xant,*yant,0);
		glVertex3f(xact,yact,0);
		glVertex3f(*xant,*yant,ALTURA_CIRCULO);
		glVertex3f(xact,yact,ALTURA_CIRCULO);
		glEnd();

		*xant=xact;
		*yant=yact;
	}
}

/*************************************************/

void Circulo::dibujar(sirMat4d matriz,float r,float g,float b)
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

	xant=RADIO_CIRCULO;
	yant=0;

	alfa=(2*M_PI)/16;

	xact=RADIO_CIRCULO*cos(alfa);
	yact=RADIO_CIRCULO*sin(alfa);

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant-0.10,yant,0);
	glVertex3f(xact,yact,0);
	glVertex3f(xant-0.10,yant,ALTURA_CIRCULO);
	glVertex3f(xact,yact,ALTURA_CIRCULO);
	glEnd();

	xant=xact;
	yant=yact;

	semiCirculo(1,7,r,g,b,&xant,&yant);

	alfa=(2*M_PI*8)/16;

	xact=RADIO_CIRCULO*cos(alfa);
	yact=RADIO_CIRCULO*sin(alfa);
	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f(xact+0.10,yact,0);
	glVertex3f(xant,yant,ALTURA_CIRCULO);
	glVertex3f(xact+0.10,yact,ALTURA_CIRCULO);

	glEnd();

	xant=xact+0.10;
	yant=yact;

	semiCirculo(9,15,r,g,b,&xant,&yant);

	alfa=2*M_PI;

	xact=RADIO_CIRCULO*cos(alfa);
	yact=RADIO_CIRCULO*sin(alfa);

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glLineWidth(2);
	glVertex3f(xant,yant,0);
	glVertex3f(xact-0.10,yact,0);
	glVertex3f(xant,yant,ALTURA_CIRCULO);
	glVertex3f(xact-0.10,yact,ALTURA_CIRCULO);
	glEnd();

	glPopMatrix();
}

