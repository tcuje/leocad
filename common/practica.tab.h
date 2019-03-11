#ifndef PRACTICA_TAB_H
# define PRACTICA_TAB_H


int parser(char *path);

typedef union{
	char *cadena;
} YYSTYPE;
# define	NUM	257
# define	NAME	258
# define	MATRIX	259
# define	IDENTIFICADOR	260
# define	CONNECTOR	261
# define	PARAMETERS	262
# define	LENGHT	263
# define	ID	264
# define	BROTHER	265
# define	RADIUS	266
# define	TOOTH	267
# define	CONNECTI	268
# define	CONA	269
# define	ASSEMBLING	270
# define	VERIFICATION	271


extern YYSTYPE yylval;

#endif /* not PRACTICA_TAB_H */
