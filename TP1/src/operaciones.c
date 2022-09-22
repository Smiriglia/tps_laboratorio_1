/*
 * operaciones.c
 *
 *  Created on: 22 sep. 2022
 *      Author: USUARIO
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
