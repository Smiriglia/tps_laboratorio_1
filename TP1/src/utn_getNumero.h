/*
 * utn_getNumero.h
 *
 *  Created on: 19 sep. 2022
 *      Author: USUARIO
 */

#ifndef UTN_GETNUMERO_H_
#define UTN_GETNUMERO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int utn_getNumero(int* pResultado,
char* mensaje,
char* mensajeError,
int minimo,
int maximo,
int reintentos);

#endif /* UTN_GETNUMERO_H_ */
