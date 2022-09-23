/*
 * menuMundial.c
 *
 *  Created on: 19 sep. 2022
 *      Author: USUARIO
 */

#include "menuMundial.h"
#include "utn.h"
#include "operaciones.h"

static void cambiarCosto(float* costoACambiar, char* tipoDeCosto);

void imprimirLinea(int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("-");
	}
	printf("\n");
}
void ingresarCostosMantenimiento(float* costoHospedaje, float* costoComida, float* costoTransporte)
{
	int respuesta;
	int retornoIngreso;
	do
	{
		printf("-El costo de hospedaje es: %.2f$\n"
				"-El costo de comida es: %.2f$\n"
				"-El costo de transporte es: %.2f$\n",
				costoHospedaje[0],
				costoComida[0],
				costoTransporte[0]);
		retornoIngreso = utn_getNumero(&respuesta, "\t|Submenu Costo de Mantenimiento|\n"
				"1 - Ingreso del costo de hospedaje\n"
				"2 - Ingreso costo de comida\n3 - Ingreso costo de transporte\n"
				"4 - Volver al menu principal\n"
				"Eliga su opcion: ",
				"\nERROR, OPCION INVALIDA\n", 0, 4, 3);

		if(retornoIngreso == 0)
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
		imprimirLinea(35);

	}while(respuesta != 4);
}

static void cambiarCosto(float* costoACambiar, char* tipoDeCosto)
{
	float costoIngresado;
	int retornoIngreso;
	char mensajeIngreso[] = "Ingrese el costo de ";

	strcat(mensajeIngreso, tipoDeCosto);
	strcat(mensajeIngreso, ": ");

	retornoIngreso = utn_getNumeroFloat(&costoIngresado, mensajeIngreso,"\nERROR, ingrese un costo positivo\n",1, 1000000,3);
	if(retornoIngreso == 0)
	{
		*costoACambiar = costoIngresado;
	}
	else
	{
		printf("\n¡No se ha podido cambiar el costo deseado!\n");
	}
}

void cargarJugadores(int* pFormacionCargada, int* formacionEquipo, int* pJugadoresPorConfederacion)
{
	int posicionIngresada;
	int retornoPosicion;

	int confederacionIngresada;
	int retornoConfederacion;

	int numeroCamisetaIngresado;
	int retornoNumeroCamisetaIngresado;

	do
	{

		if(sumaIntArray(pFormacionCargada, 4) < 22)//22 = maximo de jugadores
		{

			retornoPosicion = utn_getNumero(&posicionIngresada, "\t|Submenu Carga de Jugadores|\n"
							"Posicion:\n"
							"0 - Arquero\n"
							"1 - Defensor\n"
							"2 - Mediocampista\n"
							"3 - Delantero\n"
							"Eliga su opcion: ",
							"\nERROR, OPCION INVALIDA\n", 0, 3, 3);
			if(retornoPosicion == 0)
			{
				imprimirLinea(35);
				if(pFormacionCargada[posicionIngresada] < formacionEquipo[posicionIngresada] * 2)
				{
					//[0]AFC, [1]CAF, [2]CONCACAF, [3]CONMEBOL, [4]UEFA, [5]OFC;
					retornoConfederacion = retornoPosicion = utn_getNumero(&confederacionIngresada, "\t|Submenu Carga de Jugadores|\n"
							"Confederacion:\n"
							"0 - AFC\n"
							"1 - CAF\n"
							"2 - CONCACAF\n"
							"3 - CONMEBOL\n"
							"4 - UEFA\n"
							"5 - OFC\n"
							"Eliga su opcion: ",
							"\nERROR, OPCION INVALIDA\n", 0, 5, 3);
					if(retornoConfederacion == 0)
					{
						imprimirLinea(35);
						retornoNumeroCamisetaIngresado = utn_getNumero(&numeroCamisetaIngresado, "\t|Submenu Carga de Jugadores|\n"
								"Numero de camiseta:\n"
								"Ingrese el numero de camiseta: ",
								"\nERROR, NUMERO INVALIDA\n", 1, 99, 3);
						if(retornoNumeroCamisetaIngresado == 0)
						{
							pFormacionCargada[posicionIngresada] = pFormacionCargada[posicionIngresada] + 1;
							pJugadoresPorConfederacion[confederacionIngresada] = pJugadoresPorConfederacion[confederacionIngresada] +1;
							printf("Jugador cargado correctamente\n");
						}
						else
						{
							printf("ERROR. No se pudo cargar el numero de camiseta del jugador");
						}

					}
					else
					{
						printf("ERROR. No se ha podido cargar la confederacion\n");
					}

				}
				else
				{
					printf("ERROR. Ya hay demasiados jugadores en esa posicion\n");
				}

			}
		}
		else
		{
			printf("ERROR. Ya se han ingresado todos los jugadores\n");
		}
		imprimirLinea(35);
		printf("¿Desea seguir ingresando jugadores?");
	}while(verifica());
	imprimirLinea(35);
}
void realizarCalculos(
		int* jugadoresPorConfederacion,
		float* pPromedioPorConfederacion,
		int costoMantenimiento,
		float* costoNeto,
		float* aumentoAplicado,
		float* porcentajeUefa)
{
	for(int i = 0; i < 6; i++)
	{
		pPromedioPorConfederacion[i] = (float) jugadoresPorConfederacion[i] / 22;
	}
	*porcentajeUefa = calcularPorcentaje(jugadoresPorConfederacion[4],22);//[4] jugadores de la uefa | 22 numero maximo de jugadores

	if(porcentajeUefa[0] > 50)
	{
		*aumentoAplicado = porcientoeDe(35, costoMantenimiento);
		*costoNeto = costoMantenimiento + aumentoAplicado[0];
	}
}
