
#define COMANDO_BORRADO "CLS"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "entrada.h"

int entradaCaracteres(char *mensaje, char *str, unsigned int limite)
{
	int leidos= 0;
	
	fflush(stdin);
	printf("\n%s", mensaje);
	leidos = scanf("%s", str);
	while (leidos == 0)
	{
		printf("\t\tColoque algo mas peque%co\n", 164);
		printf("%s", mensaje);
		fflush(stdin);
		leidos = scanf("%s", str);
	}
	
	return strlen(str);
}

void datoDecimal( char *mensaje, int* ptr )
{
	fflush(stdin);
	printf("\n%s", mensaje);
	while ((scanf("%d", ptr) == 0))
	{
		printf("\t\tColoque un numero valido!");
		printf("%s", mensaje);
		fflush(stdin);
	}
}

void datoFlotante( char *mensaje, float *ptr )
{
	fflush(stdin);
	printf("\n%s", mensaje);
	while ((scanf("%f", ptr) == 0))
	{
		printf("\t\tColoque un numero valido!");
		printf("%s", mensaje);
		fflush(stdin);
	}
}