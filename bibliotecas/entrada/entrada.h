
#ifndef _ENTRADA_H_
#define _ENTRADA_H_

#include <stddef.h>

//	Verifica que lo introducido por la consola sea
//	correcto.
//	Argumentos:
//		mensaje: 	El mensaje con el que pedira el dato
//		str:		En donde se guardara los caracteres leidos.
//		limite:		Cantidad que va a guardar.
//	return: El numero de caracteres leidos.
int entradaCaracteres(char *mensaje, char *str, unsigned int limite);

//	Verifica que lo ingresado sea del tipo correcto
//	Argumentos:
//		mensaje:	El mensaje a mostrar cuando se pida el dato
//		ptr:		El puntero a la variable donde se guardara el
//						dato leido
void datoDecimal( char *mensaje, int* ptr );

//	Verifica lo ingresado sea del tipo flotante
//	Argumentos:
//		mensaje:	El mensaje a mostrar cuando se pida el dato.
//		ptr:		El puntero a la variable donde se va a guardar
//					el dato leido
void datoFlotante( char *mensaje, float *ptr );

#endif