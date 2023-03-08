/***
 *	Proyecto Final.
 *	Integrantes:
 *		(1)
 *		(2)
 *		(3)
 *		PaikLC
 *		(4)
 *
 ***/

// Bibliotecas personalizadas por decirlo de alguna forma
#include ".\bibliotecas\datos\datos.h"
#include ".\bibliotecas\entrada\entrada.h"
#include ".\bibliotecas\menu\sistemaaadospunto.h"

// Biblioteca estadar o parte del entorno de desarrollo
#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

bool existe_file(char *str)
{
	FILE *tmp;
	tmp = fopen(str,"rb");
	if(tmp != NULL )
	{
		return checarArchivo(tmp);
	}
	else 
	{
		return false;
	}
}

void mostrarDatosAdmin(datosAdmin *persona)
{
	printf("ID: %d\n", persona->id);
	printf("Clave: %s\n", persona->clave);
	printf("Nombre: %s\n", persona->nombre.nombre);
	printf("Apellido Paterno: %s\n", persona->nombre.apPaterno);
	printf("Apellido Materno: %s\n", persona->nombre.apMaterno);
}

void mostrarDatosCliente(datosCliente *persona)
{
	printf("ID: %d\n", persona->id);
	printf("Clave: %s\n", persona->clave);
	printf("Nombre: %s\n", persona->nombre.nombre);
	printf("Apellido Paterno: %s\n", persona->nombre.apPaterno);
	printf("Apellido Materno: %s\n", persona->nombre.apMaterno);
}

void mostrarDatosCuenta(nomCuenta *cuenta)
{
	printf("ID: %d\n", cuenta->id);
	printf("Numero de cuenta: %d\n", cuenta->numCuenta);
	printf("Adeudo: %f\n", cuenta->adeudo);
	printf("Meses: %d\n", cuenta->meses);
}

// Calcula los intereses
void intereses(int *opcion, float *adeudo)
{
	float interes;
	
	switch(*opcion)
	{
		case 3: 
			interes = ((6.0f*(*adeudo))/100.0f);
			*adeudo += interes; 
		break;
		
		case 6: 
			interes = ((12.0f*(*adeudo))/100.0f);
			*adeudo += interes;
		break;
		
		case 9: 
			interes = ((18.0f*(*adeudo))/100.0f);
			*adeudo += interes;
		break;
	}
}

// Actualiza el adeudo
void restar_adeudo(float *adeudo, float monto)
{
	*adeudo -= monto;
	if(*adeudo < 0)
	{
		*adeudo = 0;
	}
}

int main( void )
{
	setlocale(0, "es-Mx");
	FILE *tmp = 0;
	int opcion = 0;
	
	
	if(existe_file("administracion.bin") == false)
	{
		generarArchivo(tmp,"administracion.bin",PALABRA_MAGICA,-1);
	}
	if(existe_file("clientela.bin") == false)
	{
		generarArchivo(tmp,"clientela.bin",PALABRA_MAGICA,-1);
	}
	if(existe_file("cuentas.bin") == false)
	{
		generarArchivo(tmp,"cuentas.bin",PALABRA_MAGICA,-1);
	}
	/********************************************/
	while(opcion != 3)
	{
		opcion = menu(); 
		if(opcion == 1 )
		{
			datosAdmin credencial = {0};
			int posMax = maxDatos(0);
			bool acceso = false;
			bool idEX = true; 
			
			if(posMax == -1)
			{
				acceso = true;
				regisCuent((datosCliente*) &credencial); //
				system("pause");
				escribirAdmin(&credencial);
			}
			else
			{
				credenciales info_admin = {0};
				inicioSesion(&info_admin,1);
				int i = -1;
				
				do
				{
					i++;
					if(leerAdmin(&credencial, i) == false )
					{
						fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo administracion");
						system("pause");
						return 1;
					}
					if(credencial.id == info_admin.id )
					{
						i = posMax +1; 
					}
					if(i == posMax)
					{
						idEX = false;
						i = posMax;
					}
				}while(i < posMax);
				
				if(strncmp(credencial.clave, info_admin.clave, 100) == 0 && idEX)
				{
					acceso = true;
				}
				else
				{
					printf("\nID o Clave Incorrecta");
					system("pause");
				}
				while(acceso && opcion != 5)
				{
					opcionu opU = {0};
					adminclient(&opU,1);
					opcion = opU.opcion;
					datosCliente clienT = {0};
					nomCuenta cuenta = {0};
					int posMax = maxDatos(1);
					
					switch(opcion)
					{
						case 1:
						{
							datosCliente existe_cliente = {0};
							regisCuent(&clienT);
							int i = -1;
							do
							{
								i++;
								if(posMax == -1) 
								{
									i = posMax;
									continue;
								}
								if(leerCliente(&existe_cliente, i) == false )
								{
									fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo clientela\n");
									system("pause");
									return 1;
								}
								if(clienT.id == existe_cliente.id )
								{
									fprintf(stderr,"ERROR: ID Duplicada");
									i = posMax + 1; 
									system("pause");
								}
							}while(i < posMax);
							if(i == posMax)
							{
								escribirCliente(&clienT);	
							}
						}
						break;
						
						case 2:
						{
							bool idEX = true, numcEX = true;
							credenciales clTE;
							inicioSesion(&clTE,2);
							int maxCUENTA =  maxDatos(2); 
							int i = -1, j = -1;

							do
							{
								i++;
								if(posMax == -1)
								{
									idEX = false;
									continue;
								}
								if(leerCliente(&clienT, i) == false )
								{
									fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo clientela");
									system("pause");
									return 1;
								}
								if(clienT.id == clTE.id )
								{
									i = posMax + 1; 
								}
								if(i == posMax)
								{
									idEX = false;
									i = posMax;
								}
							}while(i < posMax);
							
								do
								{
									j++;
									if(maxCUENTA == -1) continue;
									
									if(leerCuenta(&cuenta,j) == false)
									{
										fprintf(stderr,"ERROR: No se pudo leer el archivo cuentas");
										system("pause");
										return -1;
									}
									if(clTE.id == cuenta.id)
									{
										if(clTE.numCuenta == cuenta.numCuenta)
										{
											fprintf(stderr,"ERROR: Numero de Cuenta repetida");
											system("pause");
											numcEX = false;
										}
									}
								}while(j < maxCUENTA && idEX);
								
							if(strncmp(clienT.clave, clTE.clave, strlen(clienT.clave)) == 0 && idEX && numcEX)
							{
								
								acceso = true;
								cuenta.id = clTE.id;
								cuenta.adeudo = opU.cantidad;
								cuenta.numCuenta = clTE.numCuenta;
								cuenta.meses = opU.meses;
								intereses(&cuenta.meses,&cuenta.adeudo);
								escribirCuenta(&cuenta);
							}
							else
							{
								if(numcEX)
								{
									if(posMax != -1)
									{
										printf("\n");
										printf("ID o Clave Incorrecta\n");
										system("pause");	
									}
									else
									{
										printf("\n");
										printf("NO EXISTEN CLIENTES\n");
										system("pause");	
									}
								
								}
								break;
							}
						}
						break;
						
						case 3:
						{
							int posMax = maxDatos(1);
							datosCliente clientela = {0};
							int i = -1;
							do
							{
								i++;
								if(posMax == -1)
								{
									printf("\n");
									printf("NO HAY CLIENTES REGISTRADOS\n");
									continue;
								}
								if(leerCliente(&clientela, i) == false)
								{
									fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo clientela");
									system("pause");
									return 1;
								}
							mostrarDatosCliente(&clientela);
							}while(i < posMax);
							system("pause");
						}
						break;
						
						case 4:
						{
							int posMax = maxDatos(2);
							nomCuenta cuentas = {0};
							int i = -1;
							system("cls");
							do
							{
								i++;
								if(posMax == -1)
								{	
									system("cls");
									printf("\n");
									printf("NO HAY CUENTAS REGISTRADAS\n");
									continue;
								}
								if(leerCuenta(&cuentas, i) == false)
								{
									fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo cuentas");
									system("pause");
									return 1;
								}
								mostrarDatosCuenta(&cuentas);
							}while(i < posMax);
							system("pause");
						}
						break;
					}
				}
			}
		}
/********************************************/
		else if(opcion == 2 )
		{
			datosCliente Client_pass = {0};
			int posMax = maxDatos(1);
			bool acceso = false;
			bool idEX = true, numcEX = false;
			credenciales info_user = {0};
			int i = -1, j = -1;
			nomCuenta cuenta = {0};
			int maxCUENTA =  maxDatos(2);
			
			if(posMax == -1)
			{
				printf("\n");
				printf("No existen clientes registrados\n");
				system("pause");
			}
			else
			{
				inicioSesion(&info_user,2);
				int posicion;
				
				do
				{
					i++;
					if(leerCliente(&Client_pass, i) == false )
					{
						fprintf(stderr,"ERROR FATAL: No se pudo leer el archivo clientela");
						system("pause");
						return 1;
					}
					if(Client_pass.id == info_user.id)
					{
						i = posMax + 1; 
						posicion = i;
					}
					if(i == posMax)
					{
						idEX = false;
						i = posMax;
					}
				}while(i < posMax);
				do
					{
						j++;
						if(maxCUENTA == -1) continue;
						if(leerCuenta(&cuenta,j) == false)
						{
							fprintf(stderr,"ERROR: No se pudo leer el archivo cuentas");
							system("pause");
							return -1;
						}
						if(info_user.id == cuenta.id)
						{
							if(info_user.numCuenta == cuenta.numCuenta)
							{
								numcEX = true;
								j = maxCUENTA;
							}
						}
					}while(j < maxCUENTA && idEX);
				
				if(strncmp(Client_pass.clave, info_user.clave, strlen(Client_pass.clave)) == 0 && idEX && numcEX)
				{
					acceso = true;
				}
				else
				{
					if(numcEX)
					{
						printf("\nID o Clave Incorrecta");
						system("pause");
					}
					else
					{
						fprintf(stderr,"ERROR: Numero de Cuenta Inexistente");
						system("pause");
					}
				}
				while(acceso && opcion != 4)
				{
					opcionu opC = {0};
					adminclient(&opC,2);
					opcion = opC.opcion;
					posMax = maxDatos(2);
					nomCuenta Cuenta = {Client_pass.id, info_user.numCuenta, 0.0f, 0}, tmp = {0};
					int posicion = 0, j=-1;
					
					do
					{
						j++;
						if(leerCuenta(&tmp, j) == false)
						{
							printf("ERRO");
						}
						if(cuenta.id == tmp.id)
						{
							if(cuenta.numCuenta == tmp.numCuenta)
							{
								Cuenta.adeudo = tmp.adeudo;
								Cuenta.meses = tmp.meses;
								posicion = j;
								j = posMax;
							}
						}	
					}while(j < posMax);
					switch(opcion)
					{
						case 1:
							system("pause");
							restar_adeudo(&Cuenta.adeudo,opC.cantidad);
							modificarCuenta(posicion,&Cuenta);	
						break;
						
						case 2:
						
							intereses(&Cuenta.meses,&Cuenta.adeudo);
							restar_adeudo(&Cuenta.adeudo,opC.cantidad);
							modificarCuenta(posicion,&Cuenta);
						break;
						
						case 3:
						{
							int k = -1;
							bool existe_cuenta = false;
							
							do
							{
								k++;
								leerCuenta(&tmp, k);
								if(Cuenta.id == tmp.id)
								{
									mostrarDatosCuenta(&tmp);
									existe_cuenta = true;
								}
							}while(k < posMax);
							if(existe_cuenta == false)
							{
								fprintf(stdout," NO tiene una cuenta abierta\n");
							}
							system("pause");
						}
						break;
					}
				}
			}
		}	
	}
	return 0;
}