/*
 * jugador.c
 *
 *  Created on: 26 oct. 2022
 *      Author: USUARIO
 */
#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include <string.h>
#include "jugador.h"
#include "operaciones.h"

static int buscarJugadorVacio(eJugador jugadores[], int tam);
static short cargarNombre(eJugador* jugador);
static short cargarPosicion(eJugador* jugador);
static short getPosicion(char* posicion, int tam, char* mensaje,char* mensajeError, int reintentos);
static short cargarCamiseta(eJugador* jugador);
static short cargarSalario(eJugador* jugador);
static short cargarConfederacion(eJugador* jugador,eConfederacion confederaciones[], int cantidadConfederaciones);
static short cargarAniosContrato(eJugador* jugador);
static int buscarJugadorPorId(eJugador jugadores[], int tam, int idABuscar);
static short modificarJugador(eJugador* jugador,int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
static void informarTotalYPromedioSalario(eJugador jugadores[], int tam);
static void informarConfederacionMayorAniosDeContrato(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
static int aniosContratoPorIdConfederacion(eJugador jugadores[], int tam, int id);
static void informarPorcentajeDeJugadoresPorConfederaciones(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
static float calcularPorcentajeDeJugadoresPorIdConfederacion(eJugador jugadores[],int tam, int id);
static int cantidadJugadoresPorIdConfederacion(eJugador jugadores[],int tam,int id);
static void mostrarJugadoresPorRegion(eJugador jugadores[],int tam, eConfederacion confederaciones[], int cantidadConfederaciones, int id);

void inicializarJugadores(eJugador jugadores[], int tam)
{
	int i;
	for(i=0; i < tam; i++)
	{
		jugadores[i].isEmpty = VACIO;
	}
}

short altaJugador(eJugador jugadores[],int* legajoJugadores,int tam, eConfederacion confederaciones[],int cantidadConfederaciones)
{
	int indice;
	short retorno = 0;

	indice = buscarJugadorVacio(jugadores, tam);

	printf("\n--Ingreso De Jugador--\n");
	if(indice != -1)
	{
		if(cargarNombre(&jugadores[indice]))
		{
			if(cargarPosicion(&jugadores[indice]))
			{
				if(cargarCamiseta(&jugadores[indice]))
				{
					if(cargarConfederacion(&jugadores[indice], confederaciones, cantidadConfederaciones))
					{
						if(cargarSalario(&jugadores[indice]))
						{
							if(cargarAniosContrato(&jugadores[indice]))
							{
								jugadores[indice].id = *legajoJugadores;
								jugadores[indice].isEmpty = LLENO;
								*legajoJugadores = *legajoJugadores + 1;
								retorno = 1;
							}
							else
							{
								printf("\nError al ingresar el anio\n");
							}
						}
						else
						{
							printf("\nError al ingresar el salario\n");
						}
					}
				}
				else
				{
					printf("\nError al ingresar la camiseta\n");
				}
			}
			else
			{
				printf("\nError al ingresar la posicion\n");
			}
		}
		else
		{
			printf("\nError al ingresar el nombre\n");
		}
	}
	else
	{
		printf("Error. Lista de jugadores llena");
	}

	return retorno;
}

static int buscarJugadorVacio(eJugador jugadores[], int tam)
{
	int retorno = -1;
	int i;
	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == VACIO)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

static short cargarNombre(eJugador* jugador)
{
	short retorno = 0;
	char nombre[50];
	if(utn_getNombre(nombre, 50,"Ingrese el nombre del jugador: ", "\nError. Nombre invalido\n", 3) == 0)
	{
		strcpy(jugador->nombre, nombre);
		retorno = 1;
	}
	return retorno;
}

static short cargarPosicion(eJugador* jugador)
{
	short retorno = 0;
	char posicion[50];
	if(getPosicion(posicion, 50,"Elija posicion del jugador: ", "\nError. Posicion invalida\n", 3))
	{
		strcpy(jugador->posicion, posicion);
		retorno = 1;
	}
	return retorno;
}

static short getPosicion(char* posicion, int tam, char* mensaje,char* mensajeError, int reintentos)
{
	int numeroIngresado;
	short retorno = 0;
	printf("\t|Posicion|\n"
					"1 - Arquero\n"
					"2 - Defensor\n"
					"3 - Mediocampista\n"
					"4 - Delantero\n");
	if(utn_getNumero(&numeroIngresado, mensaje, mensajeError, 1, 4, reintentos) == 0)
	{
		switch(numeroIngresado)
		{
			case 1:
				strcpy(posicion, "Arquero");
				break;

			case 2:
				strcpy(posicion, "Defensor");
				break;

			case 3:
				strcpy(posicion, "Mediocampista");
				break;

			case 4:
				strcpy(posicion, "Delantero");
				break;
		}
		retorno = 1;
	}
	return retorno;
}

static short cargarCamiseta(eJugador* jugador)
{
	short retorno = 0;
	int camiseta;
	if(utn_getNumero(&camiseta, "Ingrese el numero de camiseta del jugador: ", "\nError. Numero de camiseta invalido\n", 1, 99, 3) == 0)
	{
		jugador->numeroCamiseta = (short) camiseta;
		retorno = 1;
	}

	return retorno;
}

static short cargarConfederacion(eJugador* jugador,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	short retorno = 0;
	short contador = 0;
	int numeroIngresado;
	mostrarConfederaciones(confederaciones, cantidadConfederaciones);

	while(contador < 2)
	{
		if(utn_getNumero(&numeroIngresado, "Ingrese el id de la confederacion del jugador: ", "\nError. Confederacion invalida\n", 1, 3000, 3) == 0)
		{
			if(buscarConfederacionPorId(confederaciones, cantidadConfederaciones, numeroIngresado) != -1)//Verifica que exista la confederacion ingresada y que no este vacia
			{
				jugador->idConfederacion = numeroIngresado;
				retorno = 1;
				break;
			}
			else
			{
				printf("\nError. Confederacion inexistente\n");
				contador++;
			}
		}
	}
	return retorno;
}
static short cargarSalario(eJugador* jugador)
{
	short retorno = 0;
	float salario;
	if(utn_getNumeroFlotante(&salario, "Ingrese el salario del jugador del jugador: ", "\nError. Salario invalido\n", 1, 214748368, 3) == 0)
	{
		jugador->salario = salario;
		retorno = 1;
	}

	return retorno;
}

static short cargarAniosContrato(eJugador* jugador)
{
	short retorno = 0;
	int anios;
	if(utn_getNumero(&anios, "Ingrese los años de contrato del jugador: ", "\nError. Cantidad de años invalida\n", 1, 5, 3) == 0)
	{
		jugador->aniosContrato = (short) anios;
		retorno = 1;
	}

	return retorno;
}

short bajaJugador(eJugador jugadores[],int tam,eConfederacion confederaciones[],int cantidadConfederaciones)
{
	short retorno = 0;
	int indiceJugador;
	int numeroIngresado;
	ordenarJugadoresPorId(jugadores, tam);

	mostrarJugadores(jugadores, tam, confederaciones, cantidadConfederaciones);

	if(utn_getNumero(&numeroIngresado, "Ingrese el id del jugador que desea eliminar: ", "\nError. jugador invalido\n", 1, tam, 3) == 0)
	{
		indiceJugador = buscarJugadorPorId(jugadores, tam, numeroIngresado);
		if(indiceJugador != -1)
		{

			jugadores[indiceJugador].isEmpty = VACIO;
			retorno = 1;
		}
	}
	return retorno;
}

void ordenarJugadoresPorId(eJugador jugadores[],int tam)
{
	eJugador aux;
	int i;
	int j;
	for(i = 0; i < tam - 1; i++)
	{
		for(j = 0; j < tam; j++)
		{
			if(jugadores[i].isEmpty == LLENO && jugadores[j].isEmpty == LLENO)
			{
				if(jugadores[i].id < jugadores[j].id)
				{
					aux = jugadores[i];
					jugadores[i] = jugadores[j];
					jugadores[j] = aux;
				}
			}
		}
	}
}

void mostrarJugadores(eJugador jugadores[], int tam, eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int i;
	int indiceConfederacion;
	printf("=======================================================================================================\n"
			   "|%-5s|%-23s|%-13s|%-16s|%-11s|%-13s|%-16s|\n"
			"|-----|-----------------------|-------------|---------------|-----------|-------------|----------------|\n",
				 "ID","NOMBRE","POSICION" ,"Nº CAMISETA", "SUELDO", "CONFEDERACION","AÑOS DE CONTRATO");
	for(i = 0; i< tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO)
		{
			indiceConfederacion = buscarConfederacionPorId(confederaciones, cantidadConfederaciones, jugadores[i].idConfederacion);
			if(indiceConfederacion != -1)
			{

				printf("|%-5d|%-23s|%-13s|%-15d|$%-10.2f|%-13s|%-16d|\n",
						jugadores[i].id,
						jugadores[i].nombre,
						jugadores[i].posicion,
						jugadores[i].numeroCamiseta,
						jugadores[i].salario,
						confederaciones[indiceConfederacion].nombre,
						jugadores[i].aniosContrato);
			}
		}
	}
	printf("=======================================================================================================\n");
}
static int buscarJugadorPorId(eJugador jugadores[], int tam, int idABuscar)
{
	int retorno = -1;
	int i;
	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].id == idABuscar && jugadores[i].isEmpty == LLENO)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

short modificarJugadores(eJugador jugadores[],int tam,eConfederacion confederaciones[],int cantidadConfederaciones)
{
	int retorno = 0;
	int indiceJugador;
	int numeroIngresado;
	ordenarJugadoresPorId(jugadores, tam);

	mostrarJugadores(jugadores, tam, confederaciones, cantidadConfederaciones);

	if(utn_getNumero(&numeroIngresado, "Ingrese el id del jugador que desea modificar: ", "\nError. jugador invalido\n", 1, tam, 3) == 0)
	{
		indiceJugador = buscarJugadorPorId(jugadores, tam, numeroIngresado);
		if(indiceJugador != -1)
		{
			retorno = modificarJugador(&jugadores[indiceJugador], tam, confederaciones, cantidadConfederaciones);
		}
	}
	return retorno;
}
static short modificarJugador(eJugador* jugador,int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int retorno = 0;
	int numeroIngresado;
	do{
		printf("\t|SubMenu Modificacion|\n"
						"1 - Modificar Nombre\n"
						"2 - Modificar Posicion\n"
						"3 - Modificar Numero de camiseta\n"
						"4 - Modificar Confederacion\n"
						"5 - Modificar Salario\n"
						"6 - Modificar años de contrato\n"
						"7 - Salir\n");
		if(utn_getNumero(&numeroIngresado, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 7, 3)== 0)
		{
			switch(numeroIngresado)
			{
				case 1:
					if(cargarNombre(jugador))
					{
						printf("Nombre modificado exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;
				case 2:
					if(cargarPosicion(jugador))
					{
						printf("Posicion modificada exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;
				case 3:
					if(cargarCamiseta(jugador))
					{
						printf("Numero de camiseta modificado exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;

				case 4:
					if(cargarConfederacion(jugador, confederaciones, cantidadConfederaciones))
					{
						printf("Confederacion modificada exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;

				case 5:
					if(cargarSalario(jugador))
					{
						printf("Salario modificado exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;

				case 6:
					if(cargarAniosContrato(jugador))
					{
						printf("Años de contrato modificados exitosamente\n");
					}
					else
					{
						retorno = 0;
					}
					break;
			}
		}
	}while(numeroIngresado != 7);
	return retorno;
}

void informarDatos(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int numeroIngresado;
	do{
		printf("\t|SubMenu Informes|\n"
						"1 - Listado de los jugadores ordenados alfabéticamente por nombre de confederación y nombre de jugador.\n"
						"2 - Listado de confederaciones con sus jugadores\n"
						"3 - Total y promedio de todos los salarios y cuántos jugadores cobran más del salario promedio\n"
						"4 - Informar la confederación con mayor cantidad de años de contratos total\n"
						"5 - Informar porcentaje de jugadores por cada confederación\n"
						"6 - Informar cual es la región con más jugadores y el listado de los mismos\n"
						"7 - Salir\n");
		if(utn_getNumero(&numeroIngresado, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 7, 3)== 0)
		{
			switch(numeroIngresado)
			{
				case 1:
					ordenarAlfabeticamente(jugadores, tam, confederaciones, cantidadConfederaciones);
					mostrarJugadores(jugadores, tam, confederaciones, cantidadConfederaciones);
					break;

				case 2:
					listarJugadoresPorConfederaciones(jugadores, tam, confederaciones, cantidadConfederaciones);
					break;

				case 3:
					informarTotalYPromedioSalario(jugadores, tam);
					break;

				case 4:
					informarConfederacionMayorAniosDeContrato(jugadores, tam, confederaciones, cantidadConfederaciones);
					break;

				case 5:
					informarPorcentajeDeJugadoresPorConfederaciones(jugadores, tam, confederaciones, cantidadConfederaciones);
					break;
				case 6:
					informarRegionMasJugadores(jugadores, tam, confederaciones, cantidadConfederaciones);
					break;

			}
		}

	}while(numeroIngresado != 7);
}

void ordenarAlfabeticamente(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int i;
	int j;
	int indiceConfederacionI;
	int indiceConfederacionJ;
	eJugador aux;
	for(i = 0; i < tam- 1; i++)
	{
		for(j = 0; j < tam; j++)
		{
			if(jugadores[i].isEmpty == LLENO && jugadores[j].isEmpty == LLENO)
			{
				indiceConfederacionI = buscarConfederacionPorId(confederaciones, cantidadConfederaciones, jugadores[i].idConfederacion);
				indiceConfederacionJ = buscarConfederacionPorId(confederaciones, cantidadConfederaciones, jugadores[j].idConfederacion);
				if(indiceConfederacionI != -1 && indiceConfederacionJ != -1)
				{

					if(stricmp(confederaciones[indiceConfederacionI].nombre, confederaciones[indiceConfederacionJ].nombre) < 0)
					{
						aux = jugadores[i];
						jugadores[i] = jugadores[j];
						jugadores[j] = aux;
					}
					else
					{
						if(stricmp(jugadores[i].nombre, jugadores[j].nombre) < 0)
						{
							aux = jugadores[i];
							jugadores[i] = jugadores[j];
							jugadores[j] = aux;
						}
					}
				}
			}
		}
	}
}

void listarJugadoresPorConfederaciones(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int i;
	for(i = 0; i < cantidadConfederaciones; i++)
	{
		if(confederaciones[i].isEmpty == LLENO)
		{
			printf("==========================================================================================\n");
			printf("%42s\n", confederaciones[i].nombre);
			printf("------------------------------------------------------------------------------------------\n");
			listarJugadoresPorIdConfederacion(jugadores,tam, confederaciones[i].id);
			printf("==========================================================================================\n\n\n");
		}
	}
}

void listarJugadoresPorIdConfederacion(eJugador jugadores[],int tam,int id)
{
	int i;
	printf( "|%-5s|%-23s|%-13s|%-16s|%-11s|%-16s|\n"
			"|-----|-----------------------|-------------|---------------|-----------|----------------|\n",
			"ID","NOMBRE","POSICION" ,"Nº CAMISETA", "SUELDO","AÑOS DE CONTRATO");
	for(i = 0; i< tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO && jugadores[i].idConfederacion == id)
		{

				printf("|%-5d|%-23s|%-13s|%-15d|$%-10.2f|%-16d|\n",
						jugadores[i].id,
						jugadores[i].nombre,
						jugadores[i].posicion,
						jugadores[i].numeroCamiseta,
						jugadores[i].salario,
						jugadores[i].aniosContrato);
		}
	}
}

static void informarTotalYPromedioSalario(eJugador jugadores[], int tam)
{
	int contadorJugadores;
	float acumuladorSalarios;
	float promedioSalarios;
	int contadorMayorPromedio;
	int i;

	acumuladorSalarios = 0;
	contadorMayorPromedio= 0;
	contadorJugadores = 0;
	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO)
		{
			acumuladorSalarios += jugadores[i].salario;
			contadorJugadores++;
		}
	}
	promedioSalarios = calcularPromedio(acumuladorSalarios, contadorJugadores);

	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO && jugadores[i].salario > promedioSalarios)
		{
			contadorMayorPromedio++;
		}
	}

	printf("El total de jugadores es: %d\nEl Promedio de salarios es de: $%.2f\nLa cantidad de Jugadores que cobran mas que el promedio es: %d\n",
			contadorJugadores, promedioSalarios, contadorMayorPromedio);
}

static void informarConfederacionMayorAniosDeContrato(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	eConfederacion confederacionMax;
	int aniosDeContratoConfederacionActual;
	int aniosDeContratoMaxConfederacion;
	int i;

	if(cantidadConfederaciones > 0)
	{
		confederacionMax = confederaciones[0];
		if(confederacionMax.isEmpty == LLENO)
		{
			aniosDeContratoMaxConfederacion = aniosContratoPorIdConfederacion(jugadores, tam, confederaciones[0].id);
		}
		else
		{
			aniosDeContratoMaxConfederacion = -1;//los contadores son inicializados en 0 entonces cualquier confederacion que no esta vacia remplazara esta
		}
	}

	if(cantidadConfederaciones > 1)
	{
		for(i = 0; i < cantidadConfederaciones; i++)
		{
			if(confederaciones[i].isEmpty == LLENO)
			{
				aniosDeContratoConfederacionActual = aniosContratoPorIdConfederacion(jugadores, tam, confederaciones[i].id);
				if(aniosDeContratoConfederacionActual > aniosDeContratoMaxConfederacion)
				{
					aniosDeContratoMaxConfederacion = aniosDeContratoConfederacionActual;
					confederacionMax = confederaciones[i];
				}
			}
		}
	}

	if(cantidadConfederaciones > 0 && confederacionMax.isEmpty == LLENO)
	{
		printf("La confederacion con mayor cantidad de años de contrato es: %s\n", confederacionMax.nombre);
	}
	else
	{
		printf("No existe una confederacion valida\n");
	}
}

static int aniosContratoPorIdConfederacion(eJugador jugadores[], int tam, int id)
{
	int acumuladorAnios = 0;
	int i;

	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO && jugadores[i].idConfederacion == id)
		{
			acumuladorAnios += jugadores[i].aniosContrato;
		}
	}
	return acumuladorAnios;
}

static void informarPorcentajeDeJugadoresPorConfederaciones(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int i;
	float porcentajeActual;
	for(i = 0;i < cantidadConfederaciones; i++)
	{
		if(confederaciones[i].isEmpty == LLENO)
		{
			porcentajeActual = calcularPorcentajeDeJugadoresPorIdConfederacion(jugadores, tam, confederaciones[i].id);
			printf("El porcentaje de %s es: %.2f Porciento\n",confederaciones[i].nombre, porcentajeActual);
		}
	}
}

static float calcularPorcentajeDeJugadoresPorIdConfederacion(eJugador jugadores[],int tam, int id)
{
	int i;
	int contadorConfederacion = 0;
	int contadorJugadores = 0;
	float porcentaje;
	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO)
		{
			contadorJugadores++;
			if(jugadores[i].idConfederacion == id)
			{
				contadorConfederacion++;
			}
		}
	}

	porcentaje = calcularPorcentaje(contadorConfederacion, contadorJugadores);

	return porcentaje;
}

void informarRegionMasJugadores(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones)
{
	//comparo confederaciones dado que cada confederacion representa una region particular

	eConfederacion confederacionMax;
	int cantidadJugadoresConfederacionActual;
	int cantidadJugadoresMaxConfederacion;
	int i;

	if(cantidadConfederaciones > 0)
	{
		confederacionMax = confederaciones[0];
		if(confederacionMax.isEmpty == LLENO)
		{
			cantidadJugadoresMaxConfederacion = cantidadJugadoresPorIdConfederacion(jugadores, tam, confederaciones[0].id);
		}
		else
		{
			cantidadJugadoresMaxConfederacion = -1;//los contadores son inicializados en 0 entonces cualquier confederacion que no esta vacia remplazara esta
		}
	}

	if(cantidadConfederaciones > 1)
	{
		for(i = 0; i < cantidadConfederaciones; i++)
		{
			if(confederaciones[i].isEmpty == LLENO)
			{
				cantidadJugadoresConfederacionActual = cantidadJugadoresPorIdConfederacion(jugadores, tam, confederaciones[i].id);
				if(cantidadJugadoresConfederacionActual > cantidadJugadoresMaxConfederacion)
				{
					cantidadJugadoresMaxConfederacion = cantidadJugadoresConfederacionActual;
					confederacionMax = confederaciones[i];
				}
			}
		}
	}

	if(cantidadConfederaciones > 0 && confederacionMax.isEmpty == LLENO)
	{
		printf("\nLa Region con mayor cantidad de jugadores es: %s Con %d Jugadores\n", confederacionMax.region, cantidadJugadoresMaxConfederacion);
		mostrarJugadoresPorRegion(jugadores, tam, confederaciones, cantidadConfederaciones, confederacionMax.id);
	}
	else
	{
		printf("No existe una confederacion valida\n");
	}


}

static int cantidadJugadoresPorIdConfederacion(eJugador jugadores[],int tam,int id)
{
	int contador = 0;
	int i;

	for(i = 0; i < tam; i++)
	{
		if(jugadores[i].isEmpty == LLENO && jugadores[i].idConfederacion == id)
		{
			contador ++;
		}
	}
	return contador;
}

static void mostrarJugadoresPorRegion(eJugador jugadores[],int tam, eConfederacion confederaciones[], int cantidadConfederaciones, int id)
{
	int i;
	int indiceConfederacion;
	indiceConfederacion = buscarConfederacionPorId(confederaciones, cantidadConfederaciones, id);
	if(indiceConfederacion != -1)
	{
		printf("=======================================================================================================\n");
		printf("%42s\n", confederaciones[indiceConfederacion].region);
		printf("=======================================================================================================\n"
					   "|%-5s|%-23s|%-13s|%-16s|%-11s|%-13s|%-16s|\n"
					"|-----|-----------------------|-------------|---------------|-----------|-------------|----------------|\n",
						 "ID","NOMBRE","POSICION" ,"Nº CAMISETA", "SUELDO", "CONFEDERACION","AÑOS DE CONTRATO");
			for(i = 0; i< tam; i++)
			{
				if(jugadores[i].isEmpty == LLENO && jugadores[i].idConfederacion == id)
				{

						printf("|%-5d|%-23s|%-13s|%-15d|$%-10.2f|%-13s|%-16d|\n",
								jugadores[i].id,
								jugadores[i].nombre,
								jugadores[i].posicion,
								jugadores[i].numeroCamiseta,
								jugadores[i].salario,
								confederaciones[indiceConfederacion].nombre,
								jugadores[i].aniosContrato);
				}
			}
		printf("=======================================================================================================\n");
	}
}
