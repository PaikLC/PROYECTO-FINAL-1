#ifndef LIBRERIAMENU
#define LIBRERIAMENU
#include "..\datos\datos.h"

	//Guarda los datos del usuario/administrador
typedef struct
{
	
	int id;
	char clave[100];
	unsigned int numCuenta;
}credenciales;  
     
     //Guarda los datos del usuario
typedef struct
{
	
	int opcion;
	unsigned int numeroCuenta;
	float cantidad;
	int meses;
}opcionu;

	//	Llama al menu principal 
	//  return: int que indica la opcion seleccionada 
	//  administrador = 1, cliente = 2, salida = 3
    int menu(); 
     
	//Muestra los menus de cliente/administrador
	//Argumentos:
	//	opcionu *datusuar: da los datos del usuario
	//	int op: la opciones seleccionada respecto a administrador (1) y cliente (2)   
	void adminclient(opcionu *datusuar,int op);

	//Valida la ID y la contraseña, de ser un usuario validara su numCuenta
	//Argumentos: 
	//	datos: Un puntero de una estrutura donde se va a guardar lo leido 
	//	op: De ser un usuario pedira su numero de cuenta mediante un if (op = 2)
    void inicioSesion(credenciales *datos, int op);
    
    //Registra los datos del usuario
    //argumentos:
    //	datosC: Estrutura del cliente
    void regisCuent(datosCliente *datosC);
    
#endif
