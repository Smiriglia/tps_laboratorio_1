/*
 ============================================================================
 Name        : TP1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_getNumero.h"
//aaa
int main(void) {
	int respuesta;
	int numeroIngresado;

	setbuf(stdout, NULL);

	respuesta = utn_getNumero(&numeroIngresado, "Ingrese un numero: ", "ERROR\n", 0, 10, 3);

	printf("retorno: %d \nnumero ingresado: %d",respuesta,numeroIngresado);
	return 0;
}
