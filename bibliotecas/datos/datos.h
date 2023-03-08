
#ifndef _DATOS_H_
#define _DATOS_H_

#include <stdbool.h>
#include <stdio.h>

// Esto esta en bytes
#define LARGO_DATOS_GURADADO_ADMIN		200
#define LARGO_DATOS_GURADADO_CLIENTE	200
#define LARGO_DATOS_GURADADO_CUENTA		16
// PALABRA CLAVE
#define PALABRA_MAGICA	"DBPY"
#define LARGO_PALABRA_MAGICA 5

// Estructura para guardar el nombre
typedef struct
{
	char	nombre[50];
	char	apPaterno[23]; 
	char	apMaterno[23];
}nombreComp;

// Estructura para guardar la informacion de los administradores
typedef struct
{
	int 		id;
	char		clave[100];
	nombreComp	nombre;
}datosAdmin;

// Estructura para guardar la informacion de los clientes
typedef struct
{
	int			id;
	char		clave[100];
	nombreComp	nombre;
}datosCliente;

// Estructura para guardar la informacion de una cuenta
typedef struct
{
	int				id;
	unsigned int	numCuenta;
	float			adeudo;
	int				meses;
}nomCuenta;

// ----------------------- Cosas utiles

//	Se escargara de corroborar la palabra magica del archivo para asi
//	reconocer si reconocer si es algo mas o los datos se corrompieron...
//	(al menos los primeros 5 o 4)
bool checarArchivo( FILE *fichero);

//	Obtiene la cantidad de datos que estan contenidos en
//	el archivo.
//	Argumentos:
//		archivo: Numero que establece que archivo se va a leer
//		(0 = Admin, 1 = Cliente, 2 = Cuentas)
//	return: cantidad de datos que estan en el archivo, -1 en caso de error.
int maxDatos(int archivo);

// ----------------------- Trabajar con los propios archivos

// Genera el archivo con un formato valido
// Argumentos:
// 		fichero: Apuntador del archivo(innecesario)
// 		archivo: La ruta del archivo a crear
// 		magicWord: Cadena de caracteres con la palabra magica(DBPY)
//		numDatos: Numero de bloques en el archivo
void generarArchivo(FILE *fichero, char *archivo, char *magicWord, int numDatos);

//	Crea los archivos en donde se guardaran la informacion
void crearArchivos(void);

//	Agrega un administrador
//	Argumentos:
//		admin:	la estructura con los datos del administrador
void escribirAdmin(datosAdmin *admin);

//	Agrega un cliente
//	Argumentos:
//		cliente:	La estructura con los datos del cliente
void escribirCliente(datosCliente *cliente);

//	Obtiene la informacion de un administrador
//	Argumentos:
//		admin:		La estructura con los datos del administrador
//		posicion:	La posicion en el archivo del administrador a leer.
//	return:	True si no hay problemas al momento de leer el archivo.
bool leerAdmin(datosAdmin *admin, int posicion);

//	Obtiene la informacion de un cliente
//	Argumentos:
//		admin:		La estructura con los datos del cliente
//		posicion:	La posicion en el archivo del cliente a leer.
//	return:	True si no hay problemas al momento de leer el archivo.
bool leerCliente(datosCliente *cliente, int posicion);

//	-------------- Borrar datos

//	Modifica la informacion de ese administrador
//	Argumentos:
//		posicion:	El numero indicador de ese bloque de datos
//					con la informacion
//		escribir:	Datos con los que se sobreescribira ese bloque
void modificarAdmin(int posicion, datosAdmin *escribir);

//	Borra la informacion de ese administrador
//	Argumentos:
//		posicion:	El numero indicador de ese bloque de datos
//					con la informacion
void borrarAdmin(int posicion);

//	Modifica la informacion de ese cliente
//	Argumentos:
//		posicion:	El numero indicador de ese bloque de datos
//					con la informacion
//		escribir:	Datos con los que se sobreescribira ese bloque
void modificarCliente(int posicion, datosCliente *escribir);

//	Borra la informacion de ese cliente
//	Argumentos:
//		posicion:	El numero indicando el bloque donde
//					se encuentra esa informacion 
void borrarCliente(int posicion);

// TRABAJAR CON LAS CUENTAS

//	Escribe una cuenta nueva
//	Argumentos:
//		cuenta:	Escribe una nueva cuenta
void escribirCuenta(nomCuenta *cuenta);

//	Sobreescribe la informacion de una cuenta
//	Argumentos:
//		posicion:	El numero del bloque a modificar
//		escribir:	La informacion con la que se reemplazara esa parte
void modificarCuenta(int posicion, nomCuenta *escribir);

//	Borra una cuenta
//	Argumentos:
//		posicion:	El bloque a borrar
void borrarCuenta(int posicion);

//	Lee un bloque y obtiene la informacion de este
//	Argumentos:
//		admin:		La estructura en donde se guardara lo leido
//		posicion:	La posicion del bloque de datos a leer
bool leerCuenta(nomCuenta *admin, int posicion);

#endif