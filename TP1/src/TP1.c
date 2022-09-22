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
#include <conio.h>
#include <ctype.h>
#include "utn.h"
#include "menuMundial.h"

int main(void) {
	int respuesta;
	int retornoIngreso;
	float costoHospedaje;
	float costoComida;
	float costoTransporte;

	int formacionEquipo[] = {1, 4, 4, 2};//Si cambiamos estos numeros va a afectar a la formacion seleccionada
	int formacionCargada[] = {0, 0, 0, 0};//[0]Arqueros, [1] Defensores, [2] Mediocampistas, [3] Delanteros
	int jugadoresPorConfederacion[] = {0, 0, 0, 0, 0, 0};//[0]AFC, [1]CAF, [2]CONCACAF, [3]CONMEBOL, [4]UEFA, [5]OFC;
	costoHospedaje = 0;
	costoComida = 0;
	costoTransporte = 0;


	setbuf(stdout, NULL);


	do
	{

		retornoIngreso = utn_getNumero(&respuesta, "\t|Menu Principal|\n"
				"1 - Ingreso de los costos de Mantenimiento\n"
				"2 - Carga de jugadores\n"
				"3 - Realizar todos los cálculos\n"
				"4 - Informar todos los resultados\n"
				"5 - Salir\nEliga su opcion: ",
				"\nERROR, OPCION INVALIDA\n", 0, 5, 3);
		imprimirLinea(35);

		if(retornoIngreso == 0)
		{
			switch(respuesta)
			{
				case 1:
					ingresarCostosMantenimiento(&costoHospedaje, &costoComida, &costoTransporte);
					break;

				case 2:
					cargarJugadores(formacionCargada, formacionEquipo, jugadoresPorConfederacion);
					break;

				case 3:

					break;
				case 4:

					break;
				case 5:
					printf("SALIR");
					break;
			}
		}
	}while(respuesta != 5);

	return 0;
}
