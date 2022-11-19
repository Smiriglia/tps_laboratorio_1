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
#include "operaciones.h"

/**
 * \fn int main(void)
 * \brief Se ejecuta un menu con opciones para la carga de jugadores y costos del mundial.
 *
 * \return 0 si la ejecucion fue exitosa
 */
int main(void) {
	int respuesta;
	int retornoIngreso;
	float costoHospedaje;
	float costoComida;
	float costoTransporte;

	int formacionEquipo[] = {1, 4, 4, 2};//Si cambiamos estos numeros va a afectar a la formacion seleccionada
	int formacionCargada[] = {0, 0, 0, 0};//[0]Arqueros, [1] Defensores, [2] Mediocampistas, [3] Delanteros
	int jugadoresPorConfederacion[] = {0, 0, 0, 0, 0, 0};//[0]AFC, [1]CAF, [2]CONCACAF, [3]CONMEBOL, [4]UEFA, [5]OFC
	float promedioPorConfederacion[6];//[0]promedio de AFC, [1]promedio de CAF, [2]promedio de CONCACAF, [3]promedio de CONMEBOL, [4]promedio de UEFA, [5]promedio de OFC
	float costoMantenimiento;
	float costoNeto;
	float aumentoAplicado;
	float porcentajeUefa;



	int flagDatosCalculados;

	flagDatosCalculados = 0;
	costoHospedaje = 0;
	costoComida = 0;
	costoTransporte = 0;
	aumentoAplicado = 0;

	setbuf(stdout, NULL);


	do
	{
		printf("\t|Menu Principal|\n"
				"1 - Ingreso de los costos de Mantenimiento\n"
				"   * El costo de hospedaje es: %.2f$\n"
				"   * El costo de comida es: %.2f$\n"
				"   * El costo de transporte es: %.2f$\n\n"
				"2 - Carga de jugadores\n"
				"   * Arqueros -> %d\n"
				"   * Defensores -> %d\n"
				"   * Mediocampistas -> %d\n"
				"   * Delanteros -> %d\n\n"
				"3 - Realizar todos los cálculos\n"
				"4 - Informar todos los resultados\n"
				"5 - Salir\n",
				costoHospedaje,
				costoComida,
				costoTransporte,
				formacionCargada[0],
				formacionCargada[1],
				formacionCargada[2],
				formacionCargada[3]);

		retornoIngreso = utn_getNumero(&respuesta, "Eliga su opcion: ",
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
					if(sumaIntArray(formacionCargada, 4) < 1 || costoHospedaje == 0 || costoComida == 0 || costoTransporte == 0)//22 es el numero maximo de jugadores
					{
						printf("ERROR. No se han ingresado todos los datos\n");
					}
					else
					{
						costoMantenimiento = costoHospedaje + costoComida + costoTransporte;

						realizarCalculos(jugadoresPorConfederacion,
									promedioPorConfederacion,
									costoMantenimiento,
									&costoNeto,
									&aumentoAplicado,
									&porcentajeUefa,
									sumaIntArray(formacionCargada, 4));
						printf("Todos los calculos se han realizado correctamente\n");
						flagDatosCalculados = 1;
					}
					imprimirLinea(35);
					break;
				case 4:
					if(flagDatosCalculados)
					{
						informarResultados(promedioPorConfederacion, costoMantenimiento, costoNeto, aumentoAplicado);
					}
					else
					{
						printf("ERROR. No se pueden mostrar los datos sin haberlos calculado\n");
					}
					imprimirLinea(35);
					break;
				case 5:
					printf("SALIR");
					break;
			}
		}
	}while(respuesta != 5);

	return 0;
}
