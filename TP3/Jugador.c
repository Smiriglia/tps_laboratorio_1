#include "jugador.h"
#include "inputs.h"

/**
 * \fn Jugador jug_newParametros*(char*, char*, char*, char*, char*, char*)
 * \brief Crea un nuevo jugador parseando, validando y asignandole los datos dados
 *
 * \param idStr
 * \param nombreCompletoStr
 * \param edadStr
 * \param posicionStr
 * \param nacionalidadStr
 * \param idSelccionStr
 * \return puntero al jugador creado
 */
Jugador* jug_newParametros(char* idStr,char* nombreCompletoStr,char* edadStr, char* posicionStr, char* nacionalidadStr, char* idSelccionStr)
{
	Jugador* pJugador;
	int id;
	int edad;
	int idSeleccion;
	pJugador = jug_new();

	if(pJugador != NULL)
	{
		if((esNumerica(idStr, 30) == 1) && (esNumerica(edadStr, 30) == 1) && (esNumerica(idSelccionStr, 30) == 1))
		{

			id = atoi(idStr);
			edad = atoi(edadStr);
			idSeleccion = atoi(idSelccionStr);

			jug_setId(pJugador, id);
			jug_setNombreCompleto(pJugador, nombreCompletoStr);
			jug_setEdad(pJugador, edad);
			jug_setPosicion(pJugador, posicionStr);
			jug_setNacionalidad(pJugador, nacionalidadStr);
			jug_setIdSeleccion(pJugador, idSeleccion);
		}
		else
		{
			pJugador = NULL;
		}
	}
	return pJugador;
}
/**
 * \fn Jugador jug_new*()
 * \brief Reserva espacio en memoria para un nuevo jugador
 *
 * \return El puntero a ese nuevo jugador
 */
Jugador* jug_new()
{
	Jugador* pJugador;

	pJugador = (Jugador*) malloc(sizeof(Jugador));

	return pJugador;
}
/**
 * \fn int jug_setId(Jugador*, int)
 * \brief Asigna el valor dado al id del puntero del jugador dado
 *
 * \param this
 * \param id
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int jug_setId(Jugador* this,int id)
{
	int retorno = 0;
	if(this != NULL && id > 0)
	{
		this->id = id;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getId(Jugador*, int*)
 * \brief Asigna la id del puntero del jugador dado en el puntero dado
 *
 * \param this
 * \param id
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int jug_getId(Jugador* this,int* id)
{
	int retorno = 0;

	if(this !=  NULL && id !=NULL)
	{
		*id = this->id;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_setNombreCompleto(Jugador*, char*)
 * \brief Asigna la cadena de caracteres dada en el el nombre completo del puntero a jugador dado
 *
 * \param this
 * \param nombreCompleto
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int jug_setNombreCompleto(Jugador* this,char* nombreCompleto)
{
	int retorno = 0;
	if(this != NULL && nombreCompleto != NULL)
	{
		strcpy(this->nombreCompleto, nombreCompleto);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getNombreCompleto(Jugador*, char*)
 * \brief Asigana el nombre completo del puntero a jugador dado en la cadena de caracteres dada
 *
 * \param this
 * \param nombreCompleto
 * \return
 */
int jug_getNombreCompleto(Jugador* this,char* nombreCompleto)
{
	int retorno = 0;

	if(this !=  NULL && nombreCompleto != NULL)
	{
		strcpy(nombreCompleto, this->nombreCompleto);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_setPosicion(Jugador*, char*)
 * \brief Asigna la cadena de caracteres dada en la posicion del puntero a jugador dado
 *
 * \param this
 * \param posicion
 * \return 1 si fue exitoso, 0 si no fue exitoso
 */
int jug_setPosicion(Jugador* this,char* posicion)
{
	int retorno = 0;
	if(this != NULL && posicion != NULL)
	{
		strcpy(this->posicion, posicion);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getPosicion(Jugador*, char*)
 * \brief Asigna la posicion del puntero a jugador dado en la cadena de caracteres dada
 *
 * \param this
 * \param posicion
 * \return
 */
int jug_getPosicion(Jugador* this,char* posicion)
{
	int retorno = 0;

	if(this !=  NULL && posicion != NULL)
	{
		strcpy(posicion, this->posicion);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_setNacionalidad(Jugador*, char*)
 * \brief  Asigna la cadena de caracteres dada en la posicion del puntero a jugador dado
 *
 * \param this
 * \param nacionalidad
 * \return
 */
int jug_setNacionalidad(Jugador* this,char* nacionalidad)
{
	int retorno = 0;
	if(this != NULL && nacionalidad != NULL)
	{
		strcpy(this->nacionalidad, nacionalidad);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getNacionalidad(Jugador*, char*)
 * \brief Asigna la nacionalidad del puntero a jugador dado en la cadena de caracteres dada
 *
 * \param this
 * \param nacionalidad
 * \return 1 si fue exitoso, 0 sino fue exitoso
 */
int jug_getNacionalidad(Jugador* this,char* nacionalidad)
{
	int retorno = 0;

	if(this !=  NULL && nacionalidad != NULL)
	{
		strcpy(nacionalidad, this->nacionalidad);
		retorno = 1;
	}

	return retorno;
}

/**
 * \fn int jug_setEdad(Jugador*, int)
 * \brief Asigna el int dado en la edad del puntero a jugador dado
 *
 * \param this
 * \param edad
 * \return 1 si fue exitoso, 0 si no fue exitoso
 */
int jug_setEdad(Jugador* this,int edad)
{
	int retorno = 0;
	if(this != NULL && edad > 0)
	{
		this->edad = edad;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getEdad(Jugador*, int*)
 * \brief Asigna la edad del puntero a jugador dado en el puntero a int dado
 *
 * \param this
 * \param edad
 * \return 1 si fue exitoso, 0 si no lo fue
 */
int jug_getEdad(Jugador* this,int* edad)
{
	int retorno = 0;

	if(this !=  NULL && edad !=NULL)
	{
		*edad = this->edad;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_setIdSeleccion(Jugador*, int)
 * \brief Asigna el int dado en la idSeleccion del puntero a jugador dado
 *
 * \param this
 * \param idSeleccion
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int jug_setIdSeleccion(Jugador* this,int idSeleccion)
{
	int retorno = 0;
	if(this != NULL && idSeleccion > -1)
	{
		this->idSeleccion = idSeleccion;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getIdSeleccion(Jugador*, int*)
 * \brief Asigna el idSeleccion del puntero a jugador dado en el puntero a entero dado
 *
 * \param this
 * \param idSeleccion
 * \return 1 si fue exitoso, 0 si no lo fue
 */
int jug_getIdSeleccion(Jugador* this,int* idSeleccion)
{
	int retorno = 0;

	if(this !=  NULL && idSeleccion !=NULL)
	{
		*idSeleccion = this->idSeleccion;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int jug_getLastId(char[])
 * \brief Devuelve el numero binario escrito en el path dado
 *
 * \param path
 * \return El numero entero escrito en el path dado
 */
int jug_getLastId(char path[])
{
	int id = 0;
	FILE* archivo = NULL;
	archivo = fopen(path,"rb");
	if(archivo != NULL)
	{
		fread(&id, sizeof(id), 1, archivo);
	}
	else
	{
		printf("Error de archivo\n");
	}
	fclose(archivo);
	return id;
}

/**
 * \fn int jug_sumarLastId(char[])
 * \brief Suma 1 al numero escrito en el camino dado
 *
 * \param path
 * \return 1 si fue exitoso, 0 si no fue exitoso
 */
int jug_sumarLastId(char path[])
{
	int id = jug_getLastId(path);
	int retorno = 0;
	id++;
	FILE* archivo = NULL;
	archivo = fopen(path,"wb");
	if(archivo != NULL)
	{
		fwrite(&id,sizeof(id),1,archivo);
		retorno = 1;
	}
	fclose(archivo);
	return retorno;
}
/**
 * \fn void jug_delete(Jugador*)
 * \brief Libera el espacio en memoria de un jugador
 *
 * \param this
 */
void jug_delete(Jugador* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/**
 * \fn int jug_SortByEdad(void*, void*)
 * \brief Criterio de ordenamiento numerico por edad
 *
 * \param jug1
 * \param jug2
 * \return int
 */
int jug_SortByEdad(void* jug1,void* jug2)
{
	Jugador* jugador1 = (Jugador*)jug1;
	Jugador* jugador2  = (Jugador*)jug2;
	int edad1;
	int edad2;
	int retorno = 0;
	if(jugador1 != NULL && jugador2 != NULL && jug_getEdad(jugador1,&edad1) && jug_getEdad(jugador2,&edad2))
	{
		if(edad1 > edad2)
		{
			retorno = 1;
		}
		else
		{
			if(edad1 < edad2)
			{
				retorno = -1;
			}
		}
	}

	return retorno;
}
/**
 * \fn int jug_SortByNacionalidad(void*, void*)
 * \brief Criterio de ordenamiento alfabetico por nacionalidad
 *
 * \param jug1
 * \param jug2
 * \return int
 */
int jug_SortByNacionalidad(void* jug1,void* jug2)
{
	Jugador* jugador1 = (Jugador*)jug1;
	Jugador* jugador2  = (Jugador*)jug2;
	char nacionalidad1[30];
	char nacionalidad2[30];
	int retorno = 0;
	if(jugador1 != NULL && jugador2 != NULL && jug_getNacionalidad(jugador1,nacionalidad1) && jug_getNacionalidad(jugador2,nacionalidad2))
	{
		if(stricmp(nacionalidad1, nacionalidad2) > 0)
		{
			retorno = 1;
		}
		else
		{
			if(stricmp(nacionalidad1, nacionalidad2) < 0)
			{
				retorno = -1;
			}
		}
	}

	return retorno;
}
/**
 * \fn int jug_SortByNombre(void*, void*)
 * \brief Criterio de ordenamiento alfabetico por nombre
 *
 * \param jug1
 * \param jug2
 * \return int
 */
int jug_SortByNombre(void* jug1,void* jug2)
{
	Jugador* jugador1 = (Jugador*)jug1;
	Jugador* jugador2  = (Jugador*)jug2;
	char nombre1[100];
	char nombre2[100];
	int retorno = 0;
	if(jugador1 != NULL && jugador2 != NULL && jug_getNombreCompleto(jugador1,nombre1) && jug_getNombreCompleto(jugador2,nombre2))
	{
		if(stricmp(nombre1, nombre2) > 0)
		{
			retorno = 1;
		}
		else
		{
			if(stricmp(nombre1, nombre2) < 0)
			{
				retorno = -1;
			}
		}
	}

	return retorno;
}

