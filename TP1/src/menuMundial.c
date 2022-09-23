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

/**
 * \fn void imprimirLinea(int)
 * \brief Imprime una linea de guiones del tamaño ingresado
 *
 * \param size el tamaño que tendra la linea a imprimir
 */
void imprimirLinea(int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("-");
	}
	printf("\n");
}
/**
 * \fn void ingresarCostosMantenimiento(float*, float*, float*)
 * \brief Se ejecuta un menu para ingresar alguno de los 3 costos o volver al menu principal
 *
 * \param costoHospedaje el puntero del costo a cambiar
 * \param costoComida el puntero del costo a cambiar
 * \param costoTransporte el puntero del costo a cambiar
 */
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

/**
 * \fn void cambiarCosto(float*, char*)
 * \brief Se pide un numero positivo para asignarle el valor al puntero ingresado
 *
 * \param costoACambiar puntero del valor a cambiar
 * \param tipoDeCosto se utilizara para informarle al usuario el tipo de costo que cambiara
 */
static void cambiarCosto(float* costoACambiar, char* tipoDeCosto)
{
	float costoIngresado;
	int retornoIngreso;
	char mensajeIngreso[] = "Ingrese el costo de ";

	strcat(mensajeIngreso, tipoDeCosto);
	strcat(mensajeIngreso, ": ");

	retornoIngreso = utn_getNumeroFloat(&costoIngresado, mensajeIngreso,"\nERROR, ingrese un costo positivo\n",1, 214748368,3);
	if(retornoIngreso == 0)
	{
		*costoACambiar = costoIngresado;
	}
	else
	{
		printf("\n¡No se ha podido cambiar el costo deseado!\n");
	}
}

/**
 * \fn void cargarJugadores(int*, int*, int*)
 * \brief se cargara jugadores por posicion, confederacion y camiseta mientra que no se hayan cargado anteriormente estos o el usuario quiera parar
 *
 * \param pFormacionCargada formacion que el usuario ya ha cargado
 * \param formacionEquipo formacion a la que se desea llegar (sin incluir los suplentes)
 * \param pJugadoresPorConfederacion contador de jugadores cargados en cada confederacion
 */
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
			break;
		}
		imprimirLinea(35);
		printf("¿Desea seguir ingresando jugadores?");
	}while(verifica());
	imprimirLinea(35);
}

/**
 * \fn void realizarCalculos(int*, float*, int, float*, float*, float*)
 * \brief Se calculara el promedio de jugadores por confederacion, y el porcentaje en la liga europea para
 * saber si tenemos que hacer un aumento del 35% a los costos
 *
 * \param jugadoresPorConfederacion se dividira por el total para sacar el promedio
 * \param pPromedioPorConfederacion se guardara el valor del promedio de cada confederacion
 * \param costoMantenimiento se le aplicara un aumento en caso de ser necesario
 * \param costoNeto costo con el aumento incluido
 * \param aumentoAplicado se guardara el aumento a aplicar
 * \param porcentajeUefa se almacenara el porcentaje de jugadores que son de la liga europea
 */
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
/**
 * \fn void informarResultados(float*, float, float, float)
 * \brief Se imprimira el promedio de jugadores por confederacion y el costo de mantenimiento
 * en caso que se haya aplicado un aumento se informara el aumento y el valor neto
 *
 * \param promedioPorConfederacion promedio a imprimir
 * \param costoMantenimiento costo a imprimir
 * \param costoNeto costo a imprimir en caso que haya aumento
 * \param aumentoAplicado aumento a verificar y imprimir si es mayor de 0
 */
void informarResultados(float* promedioPorConfederacion,float costoMantenimiento, float costoNeto, float aumentoAplicado)
{
	//[0]promedio de AFC, [1]promedio de CAF, [2]promedio de CONCACAF, [3]promedio de CONMEBOL, [4]promedio de UEFA, [5]promedio de OFC
	printf("\tInformar Resultados\n\n"
			"Promedio AFC: %.2f\n"
			"Promedio CAF: %.2f\n"
			"Promedio CONCACAF: %.2f\n"
			"Promedio CONMEBOL: %.2f\n"
			"Promedio UEFA: %.2f\n"
			"Promedio OFC: %.2f\n",
			promedioPorConfederacion[0],
			promedioPorConfederacion[1],
			promedioPorConfederacion[2],
			promedioPorConfederacion[3],
			promedioPorConfederacion[4],
			promedioPorConfederacion[5]);
	if(aumentoAplicado > 0)
	{
		printf("El costo de mantenimiento era de: %.2f$ y recibio un aumento de: %.2f$, su nuevo valor es de: %.2f$\n",
				costoMantenimiento,
				aumentoAplicado,
				costoNeto);
	}
	else
	{
		printf("El costo de mantenimiento es: %.2f$\n",costoMantenimiento);
	}
}
