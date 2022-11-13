#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Jugador.h"
#include "Seleccion.h"

/** \brief Parsea los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int parser_JugadorFromText(FILE* pFile , LinkedList* pArrayListJugador)
{
	Jugador* pJugador;
	char id[30];
	char nombre[100];
	char edad[30];
	char posicion[30];
	char nacionalidad[30];
	char idSeleccion[30];
	int retornoFscanf;
	int retorno;
	int i = 0;


	if(pFile != NULL)
	{
		fscanf(pFile,"%s\n",nombre);//FALSA LECTURA
		// feof nos devuelve 1 SI LLEGO AL FINAL DEL ARCHIVO y sino nos devuelve 0
		while(feof(pFile) == 0)
		{
			retornoFscanf = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,edad,posicion,nacionalidad,idSeleccion);
			if(retornoFscanf == 6)
			{
				pJugador = jug_newParametros(id,nombre,edad,posicion,nacionalidad,idSeleccion);
				if(pJugador != NULL && pArrayListJugador != NULL)
				{
					ll_add(pArrayListJugador, pJugador);
				}
				i++;
			}
		}
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}
    return retorno;
}

/** \brief Parsea los datos de los jugadores desde el archivo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int parser_JugadorFromBinary(FILE* pFile , LinkedList* pArrayListJugador)
{
	Jugador* pJugador = NULL;
	Jugador* aux = jug_new();
	int retorno;

	if(pFile != NULL && pArrayListJugador != NULL)
	{
		while(fread(aux,sizeof(Jugador), 1, pFile) != 0)
		{
				if(aux != NULL)
				{
					pJugador = jug_new();
					*pJugador = *aux;
					ll_add(pArrayListJugador, pJugador);
					retorno = 1;
				}
		}
	}
	else
	{
		retorno = 0;
	}

	jug_delete(aux);
	return retorno;
}


/** \brief Parsea los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int parser_SeleccionFromText(FILE* pFile , LinkedList* pArrayListSeleccion)
{
	Seleccion* pSeleccion;
	char id[30];
	char pais[30];
	char confederacion[30];
	char convocados[30];
	int retornoFscanf;
	int retorno = 0;

	if(pFile != NULL)
	{
		fscanf(pFile,"%s\n",pais);//FALSA LECTURA
		// feof nos devuelve 1 SI LLEGO AL FINAL DEL ARCHIVO y sino nos devuelve 0
		while(feof(pFile) == 0)
		{
			retornoFscanf = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id, pais, confederacion, convocados);
			if(retornoFscanf == 4)
			{
				pSeleccion = selec_newParametros(id, pais, confederacion, convocados);
				if(pSeleccion != NULL && pArrayListSeleccion != NULL)
				{
					ll_add(pArrayListSeleccion, pSeleccion);
				}
				else
				{
					printf("Error null\n");
				}
			}
			else
			{
				printf("Error Retorno\n");
			}
		}
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}
	return retorno;
    return 1;
}

