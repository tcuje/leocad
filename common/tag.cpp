/*************************************************/
/*                                               */
/*					  TAG.CPP                    */
/*                                               */
/*************************************************/

#include "tag.h"

/*************************************************/

//Constructor por defecto
Tag::Tag(void)
{
	tag=new char[1];
	strcpy(tag,"");
}

/*************************************************/

//Constructor con parámetros
Tag::Tag(char *t)
{
	tag=new char[strlen(t)+1];
	strcpy(tag,t);
}

/*************************************************/

//Constructor de copia
Tag::Tag(Tag &t)
{
	tag=new char[strlen(t.tag)+1];
	strcpy(tag,t.tag);
}

/*************************************************/

//Destructor de la clase
Tag::~Tag(void)
{
	delete [] tag;
}

/*************************************************/

//Operador de assignación
Tag& Tag::operator =(Tag &t)
{
	if(*this!=t)
	{
		delete [] tag;
		tag=new char[strlen(t.tag)+1];
		strcpy(tag,t.tag);
	}
	return *this;
}

/*************************************************/

//Sobrecarga de operadores
bool Tag::operator ==(Tag t)
{
	if(!strcmp(tag,t.tag)) return true;
	else return false;
}

/*************************************************/

bool Tag::operator !=(Tag t)
{
	if(!strcmp(tag,t.tag)) return false;
	else return true;
}

/*************************************************/

int Tag::convertirEntero(char *c)
{
	int i=0,l,contador=0;

	l=strlen(c);
	while(i<l)
	{
		contador=contador+(int)c[i]; //Transformamos a entero el carácter actual.
		i=i+1;
	}

	return contador;
}

/*************************************************/

bool Tag::operator <(Tag t)
{
	int a,b;

	a=convertirEntero(tag);
	b=convertirEntero(t.tag);

	return (convertirEntero(tag)<convertirEntero(t.tag));
}

/*************************************************/

bool Tag::operator >(Tag t)
{
	int a,b;

	a=convertirEntero(tag);
	b=convertirEntero(t.tag);

	return (convertirEntero(tag)>convertirEntero(t.tag));
}

/*************************************************/

void Tag::introducirTag(char *t)
{
	delete [] tag;
	tag=new char[strlen(t)+1];
	strcpy(tag,t);
}

