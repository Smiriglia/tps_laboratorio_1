/*
 ============================================================================
 Name        : TP1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

int main(void) {
	int retornoIngreso;
	int respuesta;

	setbuf(stdout, NULL);


	do
	{

		retornoIngreso = utn_getNumero(&respuesta, "\t|Menu Principal|\n1 - Ingreso de los costos de Mantenimiento\n2 - Carga de jugadores\n3 - Realizar todos los cálculos\n4 - Informar todos los resultados\n5 - Salir\nEliga su opcion: ", "ERROR, OPCION INVALIDA\n", 0, 5, 3);


		if(retornoIngreso == 0)
		{
			switch(respuesta)
			{
				case 1:

					break;

				case 2:

					break;

				case 3:

					break;
				case 4:

					break;
				case 5:
				{
					printf("SALIR");
				}
			}
		}
	}while(respuesta != 5);

	return 0;
}
