/*
 * jugador.h
 *
 *  Created on: 26 oct. 2022
 *      Author: USUARIO
 */
#ifndef JUGADOR_H_
#include "confederacion.h"
#define LLENO 0
#define VACIO 1
typedef struct
{
	int id;
	char nombre[50];
	char posicion[50];
	short numeroCamiseta;
	int idConfederacion;
	float salario;
	short aniosContrato;
	short isEmpty;
}eJugador;

void inicializarJugadores(eJugador jugadores[], int tam);
short altaJugador(eJugador jugadores[],int* legajoJugadores,int MAX_JUGADORES, eConfederacion confederaciones[],int cantidadConfederaciones);
short bajaJugador(eJugador jugadores[],int tam,eConfederacion confederaciones[],int cantidadConfederaciones);
void ordenarJugadoresPorId(eJugador jugadores[],int tam);
void mostrarJugadores(eJugador jugadores[], int tam, eConfederacion confederaciones[], int cantidadConfederaciones);
short modificarJugadores(eJugador jugadores[],int tam,eConfederacion confederaciones[],int cantidadConfederaciones);
void informarDatos(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
void ordenarAlfabeticamente(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
void listarJugadoresPorConfederaciones(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
void listarJugadoresPorIdConfederacion(eJugador jugadores[],int tam,int id);
void informarRegionMasJugadores(eJugador jugadores[],int tam,eConfederacion confederaciones[], int cantidadConfederaciones);
#define JUGADOR_H_



#endif /* JUGADOR_H_ */
