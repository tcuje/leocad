#ifndef PRACTICA_TAB_H
# define PRACTICA_TAB_H

int parser(char *path);

typedef union{
	char *nombre;
	int numero;
} YYSTYPE;
# define	NUM	257
# define	IDENTIFICADOR	258
# define	NAME	259
# define	MATRIX	260
# define	CONNECTOR	261
# define	PARAMETERS	262
# define	LENGHT	263
# define	ID	264
# define	BROTHER	265
# define	RADIUS	266
# define	TOOTH	267


extern YYSTYPE yylval;

#endif /* not PRACTICA_TAB_H */