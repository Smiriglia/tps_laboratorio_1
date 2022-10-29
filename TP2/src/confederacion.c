/*
 * confederacion.c
 *
 *  Created on: 26 oct. 2022
 *      Author: USUARIO
 */
#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include <string.h>
#include "jugador.h"
#include "confederacion.h"

static short buscarConfederacionVacia(eConfederacion confederaciones[], int tam);
static short cargarNombre(eConfederacion* pConfederacion);
static short cargarRegion(eConfederacion* pConfederacion);
static short cargarAnio(eConfederacion* pConfederacion);
static short modificarConfederacion(eConfederacion* pConfederacion);

void mostrarConfederaciones(eConfederacion confederaciones[], int cantidadConfederaciones)
{
	int i;
	printf("=================================================================\n"
			   "|%-5s|%-10s|%-30s|%-15s|\n"
			   "|-----|----------|------------------------------|---------------|\n",
			     "ID","Nombre", "Region", "Año de creacion");
	for(i = 0; i< cantidadConfederaciones; i++)
	{
		if(confederaciones[i].isEmpty == LLENO)
		{
			printf("|%-5d|%-10s|%-30s|%-15d|\n",confederaciones[i].id,confederaciones[i].nombre,confederaciones[i].region,confederaciones[i].anioCreacion);
		}
	}
	printf("=================================================================\n");
}

int buscarConfederacionPorId(eConfederacion confederaciones[],int cantidadConfederaciones,int idABuscar)
{
	int retorno = -1;
	int i;
	for(i = 0; i < cantidadConfederaciones; i++)
	{
		if(confederaciones[i].id == idABuscar && confederaciones[i].isEmpty == LLENO)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

short altaConfederacion(eConfederacion confederaciones[],int* legajoConfederaciones, int tam)
{
	int indice;
	short retorno = 0;

	indice = buscarConfederacionVacia(confederaciones, tam);
	printf("\n--Ingreso De Jugador--\n");
	if(indice != -1)
	{
		if(cargarNombre(&confederaciones[indice]))
		{
			if(cargarRegion(&confederaciones[indice]))
			{
				if(cargarAnio(&confederaciones[indice]))
				{
					confederaciones[indice].id = *legajoConfederaciones;
					confederaciones[indice].isEmpty = LLENO;
					*legajoConfederaciones = *legajoConfederaciones + 1;
					retorno = 1;
				}
				else
				{
					printf("Error al cargar el año\n");
				}
			}
			else
			{
				printf("Error al cargar la region\n");
			}
		}
		else
		{
			printf("Error al cargar el nombre\n");
		}
	}
	else
	{
		printf("Error. Lista de confederaciones llena");
	}
	return retorno;
}

static short buscarConfederacionVacia(eConfederacion confederaciones[], int tam)
{
	int retorno = -1;
	int i;
	for(i = 0; i < tam; i++)
	{
		if(confederaciones[i].isEmpty == VACIO)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}
static short cargarNombre(eConfederacion* pConfederacion)
{
	short retorno = 0;
	char nombre[50];
	if(utn_getNombre(nombre, 50,"Ingrese el nombre de la confederacion: ", "\nError. Nombre invalido\n", 3) == 0)
	{
		strcpy(pConfederacion->nombre, nombre);
		retorno = 1;
	}
	return retorno;
}

static short cargarRegion(eConfederacion* pConfederacion)
{
	short retorno = 0;
	char region[50];
	if(utn_getDescripcion(region, 50,"Ingrese la region de la confederacion: ", "\nError. region invalido\n", 3) == 0)
	{
		strcpy(pConfederacion->region, region);
		retorno = 1;
	}
	return retorno;
}

static short cargarAnio(eConfederacion* pConfederacion)
{

	short retorno = 0;
	int anio;
	if(utn_getNumero(&anio, "Ingrese el año de creacion de la confederacion: ", "\nError. Año invalido\n", 1857, 2022, 3) == 0)
	{
		pConfederacion->anioCreacion = anio;
		retorno = 1;
	}

	return retorno;
}

short bajaConfederacion(eConfederacion confederaciones[], int tam)
{
	short retorno = 0;
	int indiceConfederacion;
	int numeroIngresado;

	mostrarConfederaciones(confederaciones, tam);

	if(utn_getNumero(&numeroIngresado, "Ingrese el id de la confederacion que desea eliminar: ", "\nError. id invalido\n", 1, tam, 3) == 0)
	{
		indiceConfederacion = buscarConfederacionPorId(confederaciones, tam, numeroIngresado);
		if(indiceConfederacion != -1)
		{

			confederaciones[indiceConfederacion].isEmpty = VACIO;
			retorno = 1;
		}
	}
	return retorno;
}

short modificarConfederaciones(eConfederacion confederaciones[], int tam)
{
	short retorno = 0;
	int indiceConfederacion;
	int numeroIngresado;

	mostrarConfederaciones(confederaciones, tam);

	if(utn_getNumero(&numeroIngresado, "Ingrese el id de la confederacion que desea eliminar: ", "\nError. id invalido\n", 1, tam, 3) == 0)
	{
		indiceConfederacion = buscarConfederacionPorId(confederaciones, tam, numeroIngresado);
		if(indiceConfederacion != -1)
		{
			retorno = modificarConfederacion(&confederaciones[indiceConfederacion]);
		}
	}
	return retorno;
}

static short modificarConfederacion(eConfederacion* pConfederacion)
{
	int retorno = 0;
	int numeroIngresado;
	do{
		printf("\t|SubMenu Modificacion|\n"
						"1 - Modificar Nombre\n"
						"2 - Modificar Region\n"
						"3 - Modificar Año de creacion\n"
						"4 - Salir\n");
		if(utn_getNumero(&numeroIngresado, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 4, 3)== 0)
		{
			switch(numeroIngresado)
			{
				case 1:
					if (cargarNombre(pConfederacion))
					{
						retorno = 1;
					}
					else
					{
						printf("Error al modificar el nombre");
					}
					break;

				case 2:
					if (cargarRegion(pConfederacion))
					{
						retorno = 1;
					}
					else
					{
						printf("Error al modificar la Region");
					}
					break;

				case 3:
					if (cargarAnio(pConfederacion))
					{
						retorno = 1;
					}
					else
					{
						printf("Error al modificar el año de creacion");
					}
					break;
			}
		}
	}while(numeroIngresado != 4);

	return retorno;
}


