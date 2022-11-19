/*
 * menuMundial.h
 *
 *  Created on: 19 sep. 2022
 *      Author: USUARIO
 */

#ifndef MENUMUNDIAL_H_
#define MENUMUNDIAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ingresarCostosMantenimiento(float* costoHospedaje, float* costoComida, float* costoTransporte);
void cargarJugadores(int* pFormacionCargada, int* formacionEquipo, int* pJugadoresPorConfederacion);
void imprimirLinea(int tamanio);
void realizarCalculos(
		int* jugadoresPorConfederacion,
		float* pPromedioPorConfederacion,
		int costoMantenimiento,
		float* costoNeto,
		float* aumentoAplicado,
		float* porcentajeUefa,
		int cantidadJugadores);
void informarResultados(float* promedioPorConfederacion,float costoMantenimiento, float costoNeto, float aumentoAplicado);

#endif /* MENUMUNDIAL_H_ */
