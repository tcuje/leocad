//
// Global variables common to all platforms.
//


#include "globales.h"


void insertafichero (char *nombre)
{
	ifstream *fichero=new ifstream();

	fichero->open("C:\temp\auxi.bison");

	if(fichero->fail())
	{
		//Si el fichero no existe deber�a ir aqu� pero crea un fichero totalmente vac�o
		fichero->close();
	}
	else
	{
		while(!fichero->eof())
		{
		}

		fichero->close();
	}
}






