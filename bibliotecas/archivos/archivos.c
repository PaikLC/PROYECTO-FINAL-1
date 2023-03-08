// Codigo ccentrado en la E/S a un archivo

#include "archivos.h"


#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>


FILE *abrirArchivo( char *archivo, char *modo)
{
	FILE *ptr = NULL;
	
	ptr = fopen(archivo, modo);
	
	if(ptr == NULL)
	{
		perror("Error al intentar abrir o crear el archivo");
	}
	return ptr;
}

int verificarError(FILE *ptr)
{
	int codigo = 0;
	codigo = ferror(ptr);
	
	if(codigo != 0)
	{
		perror("Error");
		clearerr(ptr);
		return true;
	}
	return false;
}

bool escribirDatos(FILE *ptr, void *info, size_t tamD, size_t cantidad)
{
	bool resultado = true;
	size_t escrito = 0;
	
	escrito = fwrite(info, tamD, cantidad, ptr);
	if(escrito < tamD)
	{
		resultado = false;
	}
	
	return resultado;
}

bool leerDatos(FILE *ptr, void *info, size_t tamD, size_t cantidad)
{
	bool resultado = true;
	size_t leido = 0;
	
	leido = fread(info, tamD, cantidad, ptr);
	if(leido < tamD && cantidad > 0)
	{
		resultado = false;
	}
	
	return resultado;
}

void cerrarArchivo(FILE *ptr)
{
	fclose(ptr);
}