
#include "..\archivos\archivos.h"
#include "datos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ------------ USO GENERAL

//	Se escargara de corroborar la palabra magica del archivo para asi
//	reconocer si reconocer si es algo mas o los datos se corrompieron...
//	(al menos los primeros 5 o 4)
bool checarArchivo( FILE *fichero)
{
	bool resultado = (ferror(fichero) == 0)? true : false;
	char magicWord[LARGO_PALABRA_MAGICA] = "";
	
	fread(magicWord, sizeof(char), LARGO_PALABRA_MAGICA, fichero);
	resultado &= (strncmp(magicWord, PALABRA_MAGICA, LARGO_PALABRA_MAGICA) == 0);
	
	return resultado;
}

//	Obtiene el numero de bloques que tiene el archivo, se tiene en mente que se llama
//	a la funcion despues de checarArchivo ya estando en posicion
int obtMaxDatos(FILE *fichero)
{
	int cantidad = 0;
	fread(&cantidad, sizeof(int), 1, fichero);
	return cantidad;
}

// Modifica el numero de boques que tiene el archivo, tambien se tiene
int modMaxDatos(FILE *fichero, int agregar)
{
	int cantidad;
	long int pos = ftell(fichero);

	fread(&cantidad, sizeof(int), 1, fichero);
	fseek(fichero, pos, SEEK_SET);
	cantidad += agregar;
	fwrite(&cantidad, sizeof(int), 1, fichero);
	
	return cantidad;
}

int maxDatos(int archivo)
{
	FILE *fichero = NULL;
	int datos = 0;
	
	switch(archivo)
	{
		case 0:
			fichero = abrirArchivo("administracion.bin", "rb");
			break;
		case 1:
			fichero = abrirArchivo("clientela.bin","rb");
			break;
		case 2:
			fichero = abrirArchivo("cuentas.bin", "rb");
			break;
		default:
			return -1;
	}
	
	if(fichero == NULL)
		return -1;
	else if (checarArchivo(fichero))
		datos = obtMaxDatos(fichero);
	
	cerrarArchivo(fichero);
	return datos;
}

// ------------------ ESCRIBIR LA INFO

void generarArchivo(FILE *fichero, char *archivo, char *magicWord, int numDatos)
{
	fichero = abrirArchivo(archivo, "wb");
	fwrite(magicWord, sizeof(char), LARGO_PALABRA_MAGICA, fichero);
	fwrite(&numDatos, sizeof(int), 1, fichero);
	
	cerrarArchivo(fichero);
}

void crearArchivos(void)
{
	FILE *fichero = 0;
	char *magicWord = PALABRA_MAGICA;
	int numDatos = -1; // -1 para indicar que no hay datos
	
	generarArchivo(fichero, "administracion.bin", magicWord, numDatos);
	generarArchivo(fichero, "clientela.bin", magicWord, numDatos);
	generarArchivo(fichero, "cuentas.bin", magicWord, numDatos);
}

void escribirNombre(nombreComp *persona, FILE *archivo)
{
	fwrite(persona->nombre, sizeof(char), 50, archivo);
	fwrite(persona->apPaterno, sizeof(char), 23, archivo);
	fwrite(persona->apMaterno, sizeof(char), 23, archivo);
}

void escribirAdmin(datosAdmin *admin)
{
	FILE *fichero = 0;
	int posicion = 0;
	long int bloquePos = 0;
	
	fichero = abrirArchivo("administracion.bin", "r+b");
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Porblemas con el archivo administracion.bin al escribir");
		cerrarArchivo(fichero);
		return;
	}
	posicion = obtMaxDatos(fichero);
	if( (posicion > -1) )
	{
		int maxDatos = posicion, id = 0;
		bool encontrado = false;
		do
		{
			fread(&posicion, sizeof(int), 1, fichero);
			bloquePos = ftell(fichero);
			fread(&id, sizeof(int), 1, fichero);
			fseek(fichero, bloquePos, SEEK_SET);
			if(id < 0)
			{
				escribirDatos(fichero, admin, LARGO_DATOS_GURADADO_ADMIN, 1);
				encontrado = true;
			}
			else
			{
				fseek(fichero, LARGO_DATOS_GURADADO_ADMIN, SEEK_CUR);
			}
			
		}while((posicion < maxDatos) && (encontrado == false));
		
		if( (posicion >= maxDatos) && (encontrado == false) )
		{
			fseek(fichero, sizeof(char) * 5, SEEK_SET);
			posicion = modMaxDatos(fichero, 1);
			fseek(fichero, 0, SEEK_END);

			escribirDatos(fichero, &posicion, sizeof(int), 1);
			escribirDatos(fichero, admin, LARGO_DATOS_GURADADO_ADMIN, 1);
		}
	}
	else
	{
		fseek(fichero, sizeof(char) * 5, SEEK_SET);
		posicion = modMaxDatos(fichero, 1);
		fseek(fichero, 0, SEEK_END);
	
		escribirDatos(fichero, &posicion, sizeof(int), 1);
		escribirDatos(fichero, admin, LARGO_DATOS_GURADADO_ADMIN, 1);
	}
	
	cerrarArchivo(fichero);
}

void escribirCliente(datosCliente *cliente)
{
	FILE *fichero = 0;
	int posicion = 0;
	long int bloquePos = 0;
	
	fichero = abrirArchivo("clientela.bin", "r+b");
	
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Problemas con el archivo");
		cerrarArchivo(fichero);
		return;
	}
	
	posicion = obtMaxDatos(fichero);
	if( (posicion > -1) )
	{
		int maxDatos = posicion, id = 0;
		bool encontrado = false;
		do
		{
			leerDatos(fichero, &posicion, sizeof(int), 1);
			bloquePos = ftell(fichero);
			fread(&id, sizeof(int), 1, fichero);
			fseek(fichero, bloquePos, SEEK_SET);
			if(id < 0)
			{
				escribirDatos(fichero, cliente, LARGO_DATOS_GURADADO_CLIENTE, 1);
				encontrado = true;
			}
			else
			{
				fseek(fichero, LARGO_DATOS_GURADADO_CLIENTE, SEEK_CUR);
				
			}
			
		}while( (posicion < maxDatos) && (encontrado == false) );
		
		if( (posicion >= maxDatos) && (encontrado == false) )
		{
			fseek(fichero, sizeof(char) * 5, SEEK_SET);
			posicion = modMaxDatos(fichero, 1);
			fseek(fichero, 0, SEEK_END);

			escribirDatos(fichero, &posicion, sizeof(int), 1);
			escribirDatos(fichero, cliente, LARGO_DATOS_GURADADO_CLIENTE, 1);
		}
	}
	else
	{
		fseek(fichero, sizeof(char) * 5, SEEK_SET);
		posicion = modMaxDatos(fichero, 1);
		fseek(fichero, 0, SEEK_END);
	
		escribirDatos(fichero, &posicion, sizeof(int), 1);
		escribirDatos(fichero, cliente, LARGO_DATOS_GURADADO_CLIENTE, 1);
	}
	
	cerrarArchivo(fichero);
}

// --------------- Borrar Usuarios (ya que es sobreescribir la info... va debajo de esto)

void modificarAdmin(int posicion, datosAdmin *escribir)
{
	FILE *fichero = 0;
	int posActual = 0;
	
	fichero = abrirArchivo("administracion.bin", "r+b");
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Problemas con el archivo");
		cerrarArchivo(fichero);
		return;
	}
	if(obtMaxDatos(fichero) < posicion)
	{
		fprintf(stderr, "Error: Posicion desfasada");
		cerrarArchivo(fichero);
		return;
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_ADMIN, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			return;
		}
	}
	
	if(feof(fichero) == 0)
	{
		long int bloquePos = ftell(fichero);
		
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_ADMIN, 1);
		fseek(fichero, bloquePos, SEEK_SET);
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_ADMIN, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return;
	}
	cerrarArchivo(fichero);
}

void borrarAdmin(int posicion)
{
	datosAdmin borrador = { -1, "-1", {"-1", "-1", "-1"} };
	modificarAdmin(posicion, &borrador);
}

void modificarCliente(int posicion, datosCliente *escribir)
{
	FILE *fichero = 0;
	int posActual = 0;
	
	fichero = abrirArchivo("clientela.bin", "r+b");
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Problemas con el archivo");
		cerrarArchivo(fichero);
		return;
	}
	if(obtMaxDatos(fichero) < posicion)
	{
		fprintf(stderr, "Error: Posicion desfasada");
		cerrarArchivo(fichero);
		return;
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_CLIENTE, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			return;
		}
	}
	
	if(feof(fichero) == 0)
	{	
		long int bloquePos = ftell(fichero);
		
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_CLIENTE, 1);
		fseek(fichero, bloquePos, SEEK_SET);
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_CLIENTE, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return;
	}
	cerrarArchivo(fichero);
}

void borrarCliente(int posicion)
{
	datosCliente borrador = { -1, "-1", {"-1", "-1", "-1"} };
	modificarCliente(posicion, &borrador);
}

// ----------------------- LEER LA INFO

void leerNombre(nombreComp *persona, FILE *archivo)
{
	fread(persona->nombre, sizeof(char), 50, archivo);
	fread(persona->apPaterno, sizeof(char), 23, archivo);
	fread(persona->apMaterno, sizeof(char), 23, archivo);
}

bool leerAdmin(datosAdmin *admin, int posicion)
{	
	int posActual = 0;
	FILE *fichero = abrirArchivo("administracion.bin", "rb");
	
	if (fichero == NULL)
	{
		perror("Error: Problemas con el archivo administracion.bin al abrir");
		return false;
	}
	else
	if (!checarArchivo(fichero))
	{
		perror("Error: Problemas con el archivo administracion.bin al checarlo");
		cerrarArchivo(fichero);
		return false;
	}
	else
	{
		if(obtMaxDatos(fichero) < posicion)
		{
			fprintf(stderr, "Error: Posicion desfasada");
			cerrarArchivo(fichero);
			return false;
		}
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_ADMIN, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			return false;
		}
	}
	
	if(feof(fichero) == 0)
	{
		//fread(&admin->id, sizeof(int), 1, fichero);
		//fread(&admin->clave, sizeof(char), 100, fichero);
		//leerNombre(&admin->nombre, fichero);
		leerDatos(fichero, admin, LARGO_DATOS_GURADADO_ADMIN, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return false;
	}
	cerrarArchivo(fichero);
	return true;
}

bool leerCliente(datosCliente *cliente, int posicion)
{
	int posActual = 0;
	FILE *fichero = abrirArchivo("clientela.bin", "rb");
	
	if (!checarArchivo(fichero))
	{
		perror("Error: Problemas con el archivo");
		cerrarArchivo(fichero);
		return false;
	}
	else
	{
		if(obtMaxDatos(fichero) < posicion)
		{
			fprintf(stderr, "Error: Posicion desfasada");
			cerrarArchivo(fichero);
			return false;
		}
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_CLIENTE, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			cerrarArchivo(fichero);
			return false;
		}
	}
	
	if(feof(fichero) == 0)
	{
		//fread(&cliente->id, sizeof(int), 1, fichero);
		//fread(&cliente->clave, sizeof(char), 100, fichero);
		//leerNombre(&cliente->nombre, fichero);
		leerDatos(fichero, cliente, LARGO_DATOS_GURADADO_CLIENTE, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return false;
	}
	cerrarArchivo(fichero);
	return true;
}

//	-----------------------------------------
//	|		Trabajar con las cuentas		|
//	-----------------------------------------

// Uso general

void escribirCuenta(nomCuenta *cuenta)
{
	FILE *fichero = 0;
	int posicion = 0;
	long int bloquePos = 0;
	
	fichero = abrirArchivo("cuentas.bin", "r+b");
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Problemas con cuentas.bin al escribir");
		cerrarArchivo(fichero);
		return;
	}
	posicion = obtMaxDatos(fichero);
	
	if( (posicion > -1) )
	{
		int maxDatos = posicion, id = 0;
		bool encontrado = false;
		do
		{
			leerDatos(fichero, &posicion, sizeof(int), 1);
			bloquePos = ftell(fichero);
			fread(&id, sizeof(int), 1, fichero);
			fseek(fichero, bloquePos, SEEK_SET);
			if(id < 0)
			{
				printf("\nPASE y sobreescribi\n");
				escribirDatos(fichero, cuenta, LARGO_DATOS_GURADADO_CUENTA, 1);
				encontrado = true;
			}
			else
			{
				fseek(fichero, LARGO_DATOS_GURADADO_CUENTA - sizeof(int), SEEK_CUR);
				fread(&posicion, sizeof(int), 1, fichero);
			}
			
		}while((posicion < maxDatos) && (encontrado == false));
		
		if( (posicion >= maxDatos) && (encontrado == false) )
		{
			fseek(fichero, sizeof(char) * 5, SEEK_SET);
			posicion = modMaxDatos(fichero, 1);
			fseek(fichero, 0, SEEK_END);

			escribirDatos(fichero, &posicion, sizeof(int), 1);
			escribirDatos(fichero, cuenta, LARGO_DATOS_GURADADO_CUENTA, 1);
		}
	}
	else
	{
		fseek(fichero, sizeof(char) * 5, SEEK_SET);
		posicion = modMaxDatos(fichero, 1);
		fseek(fichero, 0, SEEK_END);
		
		escribirDatos(fichero, &posicion, sizeof(int), 1);
		escribirDatos(fichero, cuenta, LARGO_DATOS_GURADADO_CUENTA, 1);
	}
	
	cerrarArchivo(fichero);
}

void modificarCuenta(int posicion, nomCuenta *escribir) // Modifica un dato
{	
	FILE *fichero = 0;
	int posActual = 0;
	
	fichero = abrirArchivo("cuentas.bin", "r+b");
	if(checarArchivo(fichero) == false)
	{
		perror("Error: Problemas con cuentas.bin al escribir");
		cerrarArchivo(fichero);
		return;
	}
	
	if(obtMaxDatos(fichero) < posicion)
	{
		fprintf(stderr, "Error: Posicion desfasada");
		cerrarArchivo(fichero);
		return;
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_CUENTA, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			return;
		}
	}
	
	if(feof(fichero) == 0)
	{
		long int bloquePos = ftell(fichero);
		
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_CUENTA, 1);
		fseek(fichero, bloquePos, SEEK_SET);
		escribirDatos(fichero, escribir, LARGO_DATOS_GURADADO_CUENTA, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return;
	}
	cerrarArchivo(fichero);
}

void borrarCuenta(int posicion) // Borra un dato
{
	nomCuenta borrador = { -1, -1, -1.0f, -1 };
	modificarCuenta(posicion, &borrador);
}

// LEER LA INFO DE LA CUENTA
bool leerCuenta(nomCuenta *admin, int posicion)
{	
	int posActual = 0;
	FILE *fichero = abrirArchivo("cuentas.bin", "rb");
	
	if (fichero == NULL)
	{
		perror("Error: Problemas con el archivo cuentas.bin al abrir");
		return false;
	}
	else
	if (!checarArchivo(fichero))
	{
		perror("Error: Problemas con el archivo cuentas.bin al checarlo");
		cerrarArchivo(fichero);
		return false;
	}
	else
	{
		if(obtMaxDatos(fichero) < posicion)
		{
			fprintf(stderr, "Error: Posicion desfasada");
			cerrarArchivo(fichero);
			return false;
		}
	}
	
	fread(&posActual, sizeof(int), 1, fichero);
	
	while(posActual < posicion)
	{
		fseek(fichero, LARGO_DATOS_GURADADO_CUENTA, SEEK_CUR);
		fread(&posActual, sizeof(int), 1, fichero);
		
		if(feof(fichero) != 0)
		{
			perror("Error: Se llego al final del archivo");
			return false;
		}
	}
	
	if(feof(fichero) == 0)
	{
		leerDatos(fichero, admin, LARGO_DATOS_GURADADO_CUENTA, 1);
	}
	else
	{
		perror("Error: Se llego al final del archivo");
		cerrarArchivo(fichero);
		return false;
	}
	cerrarArchivo(fichero);
	return true;
}
