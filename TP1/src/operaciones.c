/*
 * operaciones.c
 *
 *  Created on: 22 sep. 2022
 *      Author: USUARIO
 */

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
	return cantidad * 100 / total;
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
	return total * porcentaje / 100;
}
