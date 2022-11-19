/*
 * operaciones.c
 *
 *  Created on: 22 sep. 2022
 *      Author: USUARIO
 */
#include "operaciones.h"

/**
 * \fn int sumaIntArray(int*, int)
 * \brief Sumara el contenido del array dado
 *
 * \param pArray array a sumar
 * \param size tamaño del array
 * \return la suma de todos los elementos del array dado
 */
int sumaIntArray(int* pArray, int size)
{
	int suma;
	suma = 0;
	for(int i = 0; i < size; i++)
	{
		suma += pArray[i];
	}
	return suma;
}
/**
 * \fn float calcularPorcentaje(int, int)
 * \brief calcula que porcentaje representa un numero sobre el total
 *
 * \param cantidad el numero a saber que porcentaje representa
 * \param total el total que va a ser utilizado como divisor
 * \return el porcentaje que representa la cantidad ingresada sobre el total
 */
float calcularPorcentaje(int cantidad, int total)
{
	float porcentaje = 0;
	if(total != 0)
	{
		porcentaje = (float) cantidad * 100 / total;
	}
	return porcentaje;
}
/**
 * \fn float porcientoeDe(float, float)
 * \brief calcula el porciento dado del total dado
 *
 * \param porcentaje el porcentaje a calcular del total
 * \param total el total a ser calculado
 * \return el numero que representa el porcentaje dado sobre el total
 */
float porcientoeDe(float porcentaje, float total)
{
	float retorno;

	retorno = total * porcentaje / 100;

	return retorno;
}

/**
 * \fn int calcularPromedio(float, int)
 * \brief Calcula el promedio dividiendo el total sobre la cantidad
 *
 * \param total es el dividendo
 * \param cantidad es el divisor
 * \return el promedio calculado o 0 si la cantidad es 0
 */
float calcularPromedio(float total, int cantidad)
{
	float promedio;
	if(cantidad != 0)
	{
		promedio = total / cantidad;
	}
	else
	{
		promedio = 0;
	}
	return promedio;
}
