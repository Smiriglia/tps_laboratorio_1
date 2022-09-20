/*
 * menuMundial.c
 *
 *  Created on: 19 sep. 2022
 *      Author: USUARIO
 */

#include "menuMundial.h"
#include "utn.h"

static void cambiarCosto(float* costoACambiar, char* tipoDeCosto);

void ingresarCostosMantenimiento(float* costoHospedaje, float* costoComida, float* costoTransporte)
{
	int respuesta;
	int retornoIngreso;
	do
	{
		printf("-El costo de hospedaje es: %.2f$\n-El costo de comida es: %.2f$\n-El costo de transporte es: %.2f$\n",costoHospedaje[0], costoComida[0], costoTransporte[0]);
		retornoIngreso = utn_getNumero(&respuesta, "\t|Submenu Costo de Mantenimiento|\n1 - Ingreso del costo de hospedaje\n2 - Ingreso costo de comida\n3 - Ingreso costo de transporte\n4 - Volver al menu principal\nEliga su opcion: ", "ERROR, OPCION INVALIDA\n", 0, 4, 3);

		if(retornoIngreso == 0);
		{
			switch(respuesta)
			{
				case 1:
					cambiarCosto(costoHospedaje, "Hospedaje");
					break;
				case 2:
					cambiarCosto(costoComida, "Comida");
					break;
				case 3:
					cambiarCosto(costoTransporte, "Transporte");
					break;
			}
		}
	}while(respuesta != 4);
}

static void cambiarCosto(float* costoACambiar, char* tipoDeCosto)
{
	float costoIngresado;
	float retornoIngreso;
	char mensajeIngreso[] = "Ingrese el costo de ";

	strcat(mensajeIngreso, tipoDeCosto);
	strcat(mensajeIngreso, ": ");

	retornoIngreso = utn_getNumeroFloat(&costoIngresado, mensajeIngreso,"ERROR, ingrese un costo positivo\n",0, 1000000,3);
	if(retornoIngreso != 0)
	{
		printf("No se ha podido cambiar el costo deseado\n");
	}
	else
	{
		*costoACambiar = costoIngresado;
	}
}
