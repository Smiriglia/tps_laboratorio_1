/*
 * confederacion.h
 *
 *  Created on: 26 oct. 2022
 *      Author: USUARIO
 */

#ifndef CONFEDERACION_H_
typedef struct
{
	int id;
	char nombre[50];
	char region[50];
	int anioCreacion;
	short isEmpty;
}eConfederacion;

void mostrarConfederaciones(eConfederacion confederaciones[], int cantidadConfederaciones);
int buscarConfederacionPorId(eConfederacion confederaciones[],int cantidadConfederaciones,int idABuscar);
short altaConfederacion(eConfederacion confederaciones[],int* legajoConfederaciones, int tam);
short bajaConfederacion(eConfederacion confederaciones[], int tam);
short modificarConfederaciones(eConfederacion confederaciones[], int tam);
#define CONFEDERACION_H_



#endif /* CONFEDERACION_H_ */
