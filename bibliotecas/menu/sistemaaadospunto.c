#include<stdio.h>
#include<stdlib.h>
#include"..\entrada\entrada.h"
#include"sistemaaadospunto.h"   

int menu()
{
	int op;	
 		do{
 			system("cls");
			printf("****************************************************************************\n");
			printf("****************************************************************************\n");
			printf("                        Sistema bancario BANAMEMEX\n");
			printf("****************************************************************************\n\n");
			printf("****************************************************************************\n\n");
			printf("\t%cQuien esta utilizando la terminal?\n",168);
			printf("1.-Administracion ");
			printf("\n2.-Cliente ");
			printf("\n3.-Salir\n");	
			datoDecimal( "Opcion: ", &op);                            
																
			if(op < 1 || op > 3 ){
				system("cls");
				printf("Ingrese un numero del 1 al 3");
				system("timeout /t 2");                    		
			}
		}while(op < 1 || op > 3 );
	return op;
}


void adminclient(opcionu *datusuar,int op)
{ 
	if(op == 1)
	{
		do{
			system("cls");
				
			printf("\n**************Usted selecciono administraccion************** \n");
			printf(" Selecione una opcion\n\n ");
			printf("\n1.-Registrar una cuenta \n");
			printf("\n2.-Registrar una cuenta de credito \n");
			printf("\n3.-Ver clientes \n");
			printf("\n4.-Ver cuentas \n");
			printf("\n5.-Salir \n");
			datoDecimal( "Opcion: ", &datusuar->opcion);  
			if(datusuar->opcion < 1 ||  datusuar->opcion> 5 )
			{
				system("cls");
				printf("Ingrese un numero del 1 al 5");
				system("timeout /t 2");                    		
			}
			
		}while(datusuar->opcion < 1 ||  datusuar->opcion> 5);
		
		switch(datusuar->opcion)
		{
			
			case 1:
				system("cls");
				return;
			break;	
				 
			case 2:
				system("cls");
				datoFlotante( "Indicar el prestamo: ", &datusuar->cantidad);
				do{
					datoDecimal( "Meses de interes: ", &datusuar->meses);
					if(datusuar->meses != 3 && datusuar->meses != 6 && datusuar->meses !=9)
					{					
						system("cls");
						printf("Introduzca 3, 6 o 9\n");	
						system("pause");
					}
				}while(datusuar->meses != 3 && datusuar->meses != 6 && datusuar->meses !=9);
				return;
				
			break;	
			
			case 3:
				system("cls");
				return;
			break;	
			
			case 4:
				return;
			break;	
			
			case 5:
				return;
			break;	
		}	
	}
	else
	{
		do{
		system("cls");
		printf("\n1.-Registrar un deposito");
		printf("\n2.-Registrar una compra");
		printf("\n3.-Ver saldo cuentas de credito");
		printf("\n4.-Salir");
		datoDecimal( "Opcion: ", &datusuar->opcion);  
			if(datusuar->opcion < 1 ||  datusuar->opcion > 4 ){
				system("cls");
				printf("Ingrese un numero del 1 al 4");
				system("timeout /t 2");                    		
			}
		}while(datusuar->opcion < 1 ||  datusuar->opcion > 4);
		
		switch(datusuar->opcion)
		{
		case 1:
			system("cls");
			datoFlotante( "Introduzca su deposito: ", &datusuar->cantidad );
			if((datusuar->cantidad)<0){
			
			 datusuar->cantidad *= -1;
			}
		break;	
			 
		case 2:
			system("cls");
			datoFlotante( "Agregar adeudo = ", &datusuar->cantidad);
			if((datusuar->cantidad)>0)
			{
			datusuar->cantidad *= -1;	
			}
			return;
		break;	
		
		case 3:
			system("cls");
			return;
		break;	
		
		case 4:
			system("cls");
			return;
		break;	
		}
	}
}
	
void inicioSesion(credenciales *datos, int op)
{
	system("cls");		
	datoDecimal( "Digite su ID: ", &datos->id); 		
	entradaCaracteres("Digite su clave: ", datos->clave , 100); 
	if(op == 2 )
	{

		datoDecimal( "Digite su numero de cuenta: ", &datos->numCuenta); 	
		
	}
}
	
void regisCuent(datosCliente *datosC)
{
	
   	 system("cls");
	 datoDecimal( "Introduzca la ID: ", &datosC->id );		
	 entradaCaracteres("Introduzca la clave: ", datosC->clave, 100);
	 entradaCaracteres("Introduzca el nombre: ", datosC->nombre.nombre, 50);
	 entradaCaracteres("Introduzca el apellido paterno: ", datosC->nombre.apPaterno, 23);
	 entradaCaracteres("Introduzca el apellido Materno: ", datosC->nombre.apMaterno, 23);
	 
}	