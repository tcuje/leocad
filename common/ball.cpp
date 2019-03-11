/*************************************************/
/*                                               */
/*					  BALL.CPP  	             */
/*                                               */
/*************************************************/

#include "ball.h"


/*************************************************/

void Ball::Circulo(int inf,int sup,float r,float g,float b,float *xant,float *yant,float radio,float dis)
{
	int i;
	float alfa,xact,yact,dis1;

	for(i=inf;i<=sup;i++)
	{
		alfa=(2*M_PI*i)/16;

		xact=radio*cos(alfa);
		yact=radio*sin(alfa);

		glBegin(GL_LINES);
		glColor3f(r,g,b);
		glLineWidth(2);
		glVertex3f(*xant,*yant,dis);
		glVertex3f(xact,yact,dis);
		dis1=0-dis;
		glVertex3f(*xant,*yant,dis1);
		glVertex3f(xact,yact,dis1);

		glEnd();

		*xant=xact;
		*yant=yact;
	}
}

/*************************************************/

void Ball::dibujar(sirMat4d matriz,float r,float g,float b)
{
	float alfa,xant,yant;
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

	alfa=(2*M_PI)/16;

	xant=RADIO_CIRCULO*cos(alfa);
	yant=RADIO_CIRCULO*sin(alfa);

	Circulo(0,16,r,g,b,&xant,&yant,RADIO_CIRCULO,0);

	xant=RADIO_CIRCULO1*cos(alfa);
	yant=RADIO_CIRCULO1*sin(alfa);

	Circulo(0,16,r,g,b,&xant,&yant,RADIO_CIRCULO1,0.1);

	xant=RADIO_CIRCULO2*cos(alfa);
	yant=RADIO_CIRCULO2*sin(alfa);

	Circulo(0,16,r,g,b,&xant,&yant,RADIO_CIRCULO2,0.2);

	xant=RADIO_CIRCULO3*cos(alfa);
	yant=RADIO_CIRCULO3*sin(alfa);

	Circulo(0,16,r,g,b,&xant,&yant,RADIO_CIRCULO3,0.3);

	glPopMatrix();
}


