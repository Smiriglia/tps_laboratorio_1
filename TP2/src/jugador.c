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


/**
 * \fn void inicializarJugadores(eJugador[], int)
 * \brief cambia el estado de todos los jugadores de un array a vacio
 *
 * \param jugadores array de jugadores a inicializar
 * \param tam tamaño del array de jugadores
 */
void inicializarJugadores(eJugador jugadores[], int tam)
{
	int i;
	for(i=0; i < tam; i++)
	{
		jugadores[i].isEmpty = VACIO;
	}
}

/**
 * \fn short altaJugador(eJugador[], int*, int, eConfederacion[], int)
 * \brief Pide el ingreso de cada uno de los datos necesarios para cargar a un jugador en el sistema y los valida
 *
 * \param jugadores El array de jugadores donde sera cargado el jugador
 * \param legajoJugadores el puntero del id unico del jugador
 * \param tam el tamaño del array de jugadores
 * \param confederaciones el array de confederaciones a las que puede pertenecer el jugador
 * \param cantidadConfederaciones el tamaño del array de confederaciones
 *
 * \return Devuelve 1 en caso de carga exitosa y 0 en caso contrario
 */
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
/**
 * \fn int buscarJugadorVacio(eJugador[], int)
 * \brief Busca un jugador con estado vacio en un array de jugadores
 *
 * \param jugadores array de jugadores a recorrer
 * \param tam tamaño del array de jugadores
 * \return el indice del jugador vacio en caso de encontrarlo o -1 en caso de no encontrar un jugador vacio
 */
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

/**
 * \fn short cargarNombre(eJugador*)
 * \brief Pide al jugador que ingrese un nombre el cual se le asignara al jugador despues de validarlo
 *
 * \param jugador puntero del jugador a cargar
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
static short cargarNombre(eJugador* jugador)
{
	short retorno = 0;
	char nombre[50];
	if(utn_getDescripcion(nombre, 50,"Ingrese el nombre del jugador: ", "\nError. Nombre invalido\n", 3) == 0)
	{
		strcpy(jugador->nombre, nombre);
		retorno = 1;
	}
	return retorno;
}
/**
 * \fn short cargarPosicion(eJugador*)
 * \brief Pide al jugador que ingrese la posicion la cual se le asignara al jugador despues de validarlo
 *
 * \param jugador puntero del jugador a cargar
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
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

/**
 * \fn short getPosicion(char*, int, char*, char*, int)
 * \brief Se le da a elegir al jugador entre las 4 opciones de posiciones que puede tomar
 *  un jugador y lo guarda en un array de caracteres
 *
 * \param posicion array de caracteres donde se guardara la posicion elegida
 * \param tam el tamaño del array de caracteres
 * \param mensaje El mensaje que se mostrara a la hora de ingresar
 * \param mensajeError El mensaje que se mostrara en caso de error
 * \param reintentos La cantidad de reintentos que tendra el usuario
 *
 * \return 1 si se ingreso una pocision valida o 0 en caso contrario
 */
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

/**
 * \fn short cargarCamiseta(eJugador*)
 * \brief El usuario ingresa un numero de camiseta el cual sera validado y asignado al jugador
 *
 * \param jugador el puntero del jugador al cual se le asignara el numero de camiseta
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
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

/**
 * \fn short cargarConfederacion(eJugador*, eConfederacion[], int)
 * \brief Muestra la lista de confederaciones y se le pide al usuario que ingrese el id de la confederacion a asignarle al jugador
 * despues de validarlo
 *
 * \param jugador El puntero del jugador al cual sera asignada la id de la confederacion elegida
 * \param confederaciones El array de las confederaciones a elegir
 * \param cantidadConfederaciones El tamaño del array de las confederaciones
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
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

/**
 * \fn short cargarSalario(eJugador*)
 * \brief Se le pide al usuario el ingreso del salario de un jugador, se valida y luego se asigna en el jugador
 *
 * \param jugador El puntero del jugador al cual se le asignara el salario
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
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


/**
 * \fn short cargarAniosContrato(eJugador*)
 * \brief Se le pide al usuario el ingreso de los años de contrato de un jugador, se valida y luego se asigna en el jugador
 *
 * \param jugador  jugador El puntero del jugador al cual se le asignara los años de contrato
 *
 * \return 1 si la carga fue exitosa o 0 si la carga no fue exitosa
 */
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

/**
 * \fn short bajaJugador(eJugador[], int, eConfederacion[], int)
 * \brief Se muestra la lista de jugadores cargados ordenados por id y se le pide
 *  al usuario que ingrese el id del usuario que desea eliminar realizando una baja logica
 *
 * \param jugadores Array de jugadores a mostrar y eliminar jugador del mismo
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a la que puede pertenecer el jugador
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 *
 * \return 1 Si la baja fue exitosa o 0 Si la baja no fue exitosa
 */
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


/**
 * \fn void ordenarJugadoresPorId(eJugador[], int)
 * \brief Ordena un array de jugadores ascendentemente por id
 *
 * \param jugadores Array de jugadores a ordenar
 * \param tam tamaño del array de jugadores
 */
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

/**
 * \fn void mostrarJugadores(eJugador[], int, eConfederacion[], int)
 * \brief Muestra todos los jugadores que no esten vacios en un array de jugadores
 * mostrando los datos ID, NOMBRE, POSICION , Nº CAMISETA, SUELDO, CONFEDERACION, AÑOS DE CONTRATO
 *
 * \param jugadores array de jugadores a mostrar
 * \param tam tamaño del array de jugadores
 * \param confederaciones array de confederaciones a las que puede pertenecer el jugador
 * \param cantidadConfederaciones tamaño del array de confederaciones
 */
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

/**
 * \fn int buscarJugadorPorId(eJugador[], int, int)
 * \brief Busca el jugador que tenga la id dada en el array de jugadores dado
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param idABuscar Id a buscar en el array de jugadores
 *
 * \return El indice del jugador con la id dada o -1 en caso de no encontrarlo
 */
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

/**
 * \fn short modificarJugadores(eJugador[], int, eConfederacion[], int)
 * \brief Muestra a todos los jugadores y se le pide al jugador la id del jugador al cual quiere modificar
 *
 * \param jugadores Array de jugadores a modificar
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a la cual pueden pertenecer los jugadores
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 *
 * \return 1 si la modificacion fue exitosa o 0 si no lo fue
 */
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

/**
 * \fn short modificarJugador(eJugador*, int, eConfederacion[], int)
 * \brief Se muestra un submenu de modificacion en el cual el usuario puede elegir que dato del jugador modificara
 *
 * \param jugador Puntero del jugador a modificar
 * \param tam Tamaño del jugador a modificar
 * \param confederaciones Array de confederaciones a las que el jugador puede pertenecer
 * \param cantidadConfederaciones Tamaño del array de las confederaciones
 *
 * \return 1 si la modificacion fue exitosa o 0 si no lo fue
 */
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
						retorno = 1;
					}
					break;
				case 2:
					if(cargarPosicion(jugador))
					{
						printf("Posicion modificada exitosamente\n");
					}
					else
					{
						retorno = 1;
					}
					break;
				case 3:
					if(cargarCamiseta(jugador))
					{
						printf("Numero de camiseta modificado exitosamente\n");
					}
					else
					{
						retorno = 1;
					}
					break;

				case 4:
					if(cargarConfederacion(jugador, confederaciones, cantidadConfederaciones))
					{
						printf("Confederacion modificada exitosamente\n");
					}
					else
					{
						retorno = 1;
					}
					break;

				case 5:
					if(cargarSalario(jugador))
					{
						printf("Salario modificado exitosamente\n");
					}
					else
					{
						retorno = 1;
					}
					break;

				case 6:
					if(cargarAniosContrato(jugador))
					{
						printf("Años de contrato modificados exitosamente\n");
					}
					else
					{
						retorno = 1;
					}
					break;
			}
		}
	}while(numeroIngresado != 7);
	return retorno;
}


/**
 * \fn void informarDatos(eJugador[], int, eConfederacion[], int)
 * \brief Se le muestra al usuario un submenu de informes el cual podra elegir la opcion que desee
 * dependiendo de los datos que quiere que sean informados
 *
 * \param jugadores Array de jugadores del cual se informaran los datos
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a las cuales pueden pertenecer los jugadores
 * \param cantidadConfederaciones
 */
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

/**
 * \fn void ordenarAlfabeticamente(eJugador[], int, eConfederacion[], int)
 * \brief Ordena un array alfabeticamente por el nombre de la confederacion y como segundo criterio por
 * el nombre del jugador
 *
 * \param jugadores Array de jugadores a ordenar
 * \param tam Tamaño del array de jugadores a ordenar
 * \param confederaciones Array de confederaciones a las cuales pueden pertenecer los jugadores
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 */
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
						if(stricmp(jugadores[i].nombre, jugadores[j].nombre) == 0)
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
}

/**
 * \fn void listarJugadoresPorConfederaciones(eJugador[], int, eConfederacion[], int)
 * \brief Muestra el listado de confederaciones con sus jugadores
 *
 * \param jugadores Array de jugadores a mostrar
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a mostrar sus jugadores
 * \param cantidadConfederaciones Tamaño de jugadores
 */
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

/**
 * \fn void listarJugadoresPorIdConfederacion(eJugador[], int, int)
 * \brief Muestra dado si su id confederacion coincide con la id dada
 *
 * \param jugadores El array de jugadores a mostrar si coinciden
 * \param tam El tamaño del array de jugadores
 * \param id El id a verificar si coincide
 */
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

/**
 * \fn void informarTotalYPromedioSalario(eJugador[], int)
 * \brief Calcula e Informa el total de jugadores,  el promedio de salario y la cantidad de jugadores que superan ese promedio
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 */
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

/**
 * \fn void informarConfederacionMayorAniosDeContrato(eJugador[], int, eConfederacion[], int)
 * \brief Informa cual es la confederacion con mas años de contrato
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a recorrer
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 */
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

/**
 * \fn int aniosContratoPorIdConfederacion(eJugador[], int, int)
 * \brief Calcula la suma de años de contrato de todos los jugadores de un array dado que no esten vacios y
 * coincidan con la idConfederacion dada
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param id Id a verificar
 *
 * \return La suma total de años de contrato de los jugadores que coinciden con la id
 */
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

/**
 * \fn void informarPorcentajeDeJugadoresPorConfederaciones(eJugador[], int, eConfederacion[], int)
 * \brief Calcula e informa el porcentaje jugadores de un array de jugadores dado que pertenecen a cada una de las confederaciones
 * que no esten vacias en un array de confederaciones dado
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a recorrer
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 */
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

/**
 * \fn float calcularPorcentajeDeJugadoresPorIdConfederacion(eJugador[], int, int)
 * \brief Calcula el porcentaje que representan los jugadores del array dado que su idConfederacion
 * coincide con el id dado
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param id Id a verificar
 *
 * \return El porcentaje que representan los jugadores que coinciden con el id dado
 */
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

/**
 * \fn void informarRegionMasJugadores(eJugador[], int, eConfederacion[], int)
 * \brief Informa cual es la region con mas jugadores y imprime la lista de jugadores pertenecientes a esta region
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a recorrer
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 */
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

/**
 * \fn int cantidadJugadoresPorIdConfederacion(eJugador[], int, int)
 * \brief Recorre el array de jugadores y contando la cantidad de jugadores que su idConfederacion coincide
 * con el id dado
 *
 * \param jugadores Array de jugadores
 * \param tam Tamaño del array de jugadores
 * \param id Id a verificar
 * \return La cala cantidad de jugadores que su idConfederacion coincide con el id dado
 */
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

/**
 * \fn void mostrarJugadoresPorRegion(eJugador[], int, eConfederacion[], int, int)
 * \brief Muestra la lista de jugadores que su idConfederacion coincida con el id dado
 * Y muestra en la parte superior la region a la que pertenecen los mismos
 *
 * \param jugadores Array de jugadores a recorrer
 * \param tam Tamaño del array de jugadores
 * \param confederaciones Array de confederaciones a las que pueden pertenecer los jugadores
 * \param cantidadConfederaciones Tamaño del array de confederaciones
 * \param id Id a verificar
 */
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
