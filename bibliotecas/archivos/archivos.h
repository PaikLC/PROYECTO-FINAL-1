// Definiciones de la biblioteca archivos.c

#ifndef _ARCHIVOS_H_
#define _ARCHIVOS_H_

#include <stdio.h>
#include <stdbool.h>

// Abre crea, edita un archivo.
//	archivo: Cadena de caracteres con la ruta del archivo a abrir
//	modo: Como va a abrir el archivo
//			r: Intenta abrir un archivo para leer
//			w: Intenta abrir un archivo para escribir
//			a: Añade informacion al final, si no existe lo crea
//			r+: Abre un archivo para leer y escribir. DEBE EXISTIR
//			w+: Abre una archivo para leer y escribir. Si no existe
//				se crea y si existe se borra el contenido
//			a+: Abre un archivo para leer y escribir. Si no existe
//					se crea
// 		Se puede añadir a estas una t o b para modificar como se
//			leera y escribira en el archivo. Recomiendo usar b
//			para evitar problemas con fseek
FILE *abrirArchivo( char *archivo, char *modo);

// Verifica si es que no ocurrio un error al momento
// de trabajar con el archivo
//	ptr: Puntero de la estructura FILE a evaluar
//	return: True en caso de error. Ademas manda un
//				mensaje de error por stderr con mas
//				detalles del error
int verificarError(FILE *ptr);

//	Escribe un dato al archivo respectivo
//	Argumentos:
//		ptr:		Puntero a la estructura conteniendo el archivo abierto.
//		info:		Puntero a la informacion a escribir.
//		tamD:		El tamaño de la informacion a escribir. (el tipo de dato o tamaño de la estructura)
//		cantidad:	El numero de datos a escribir.
//	return:	false en caso de error.
bool escribirDatos(FILE *ptr, void *info, size_t tamD, size_t cantidad);

//	Lee la informacion de un archivo
//	Argumentos:
//		ptr:		Puntero a la estructura conteniendo el archivo abiierto.
//		info:		Puntero a la memnoria donde se va a guardar lo leido.
//		tamD:		El tamaño de la informacion a leer. (el tipo de dato o el tamaño de la estructura)
//		cantidad:	El numero de datos a escribir.
//	return:	false en caso de error.
bool leerDatos(FILE *ptr, void *info, size_t tamD, size_t cantidad);

// Cierra un archivo
//	ptr: Puntero de la estructura FILE a cerrar
void cerrarArchivo(FILE *ptr);

#endif