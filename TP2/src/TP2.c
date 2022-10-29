/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "jugador.h"
#include "confederacion.h"

#define MAX_JUGADORES 3000
/**
 * \fn int main(void)
 * \brief El programa que administra los jugadores de cada confederación de fútbol.
 * contando con un menu  de 4 opciones Ingresar Jugador, Eliminar jugador, Modificar Jugador y informar los datos
 *
 * \return 0
 */
int main(void) {
	setbuf(stdout,NULL);
	int respuesta;
	int legajoJugadores = 1;
	short flagIngresoJugador;
	int cantidadConfederaciones;
	eJugador jugadores[MAX_JUGADORES];
	eConfederacion confederaciones[] = {
			{100, "CONMEBOL", "SUDAMERICA", 1916, LLENO},
			{101, "UEFA", "EUROPA", 1954, LLENO},
			{102, "AFC", "ASIA", 1954, LLENO},
			{103, "CAF", "AFRICA", 1957, LLENO},
			{104, "CONCACAF", "NORTE Y CENTRO AMERICA", 1961, LLENO},
			{105, "OFC", "OCEANIA", 1966, LLENO}};//hardcodeo las confederaciones
	cantidadConfederaciones = 6;
	flagIngresoJugador = 0;

	inicializarJugadores(jugadores, MAX_JUGADORES);
	do
	{
		printf("\t|Menu Principal|\n"
				"1 - Ingresar jugador\n"
				"2 - Eliminar jugador\n"
				"3 - Modificar jugador\n"
				"4 - Informar todos los resultados\n"
				"5 - Salir\n");

		if(utn_getNumero(&respuesta, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 5, 3)== 0)
		{
			switch(respuesta)
			{
				case 1:
					if(altaJugador(jugadores, &legajoJugadores, MAX_JUGADORES, confederaciones, cantidadConfederaciones))
					{
						printf("Jugador Ingresado correctamente\n");
						flagIngresoJugador = 1;
					}
					else
					{
						printf("ERROR. al ingresar Jugador\n");
					}
					break;

				case 2:
					if(flagIngresoJugador)
					{
						if(bajaJugador(jugadores, MAX_JUGADORES, confederaciones, cantidadConfederaciones))
						{
							printf("\nJugador eliminado correctamente\n\n");
						}
						else
						{
							printf("\nError al eliminar un jugador\n\n");
						}
					}
					else
					{
						printf("\nError. Debes ingresar al menos un jugador antes de poder eliminar\n\n");
					}
					break;

				case 3:
					if(flagIngresoJugador)
					{
						if(modificarJugadores(jugadores,MAX_JUGADORES, confederaciones, cantidadConfederaciones))
						{
							printf("\nModificacion de jugador exitosa\n\n");
						}
						else
						{
							printf("\nError al modificar un jugador\n\n");
						}
					}
					else
					{
						printf("\nError. Debes ingresar al menos un jugador antes de poder modificar\n\n");
					}
					break;

				case 4:
					if(flagIngresoJugador)
					{
						informarDatos(jugadores, MAX_JUGADORES, confederaciones, cantidadConfederaciones);
					}
					else
					{
						printf("\nError. Debes ingresar al menos un jugador antes de poder informar datos\n\n");
					}
					break;
			}
		}
	}while(respuesta != 5);
	return 0;
}
