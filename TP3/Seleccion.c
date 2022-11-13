#include "Seleccion.h"
#include "inputs.h"
/**
 * \fn Seleccion selec_newParametros*(char*, char*, char*, char*)
 * \brief Crea una nueva seleccion parseando y validando los datos dados
 *
 * \param idStr
 * \param paisStr
 * \param confederacionStr
 * \param convocadosStr
 * \return El puntero a la seleccion creada
 */
Seleccion* selec_newParametros(char* idStr,char* paisStr,char* confederacionStr, char* convocadosStr)
{
	int id;
	int convocados;
	Seleccion* seleccion = NULL;
	seleccion = selec_new();
	if(seleccion != NULL)
	{
		if((esNumerica(idStr, 30) == 1) && (esNumerica(convocadosStr, 30) == 1) && paisStr != NULL && confederacionStr != NULL)
		{
			id = atoi(idStr);
			convocados = atoi(convocadosStr);
			seleccion->id = id;
			strcpy(seleccion->pais, paisStr);
			strcpy(seleccion->confederacion, confederacionStr);
			seleccion->convocados = convocados;
		}
		else
		{
			seleccion = NULL;
		}
	}
	return seleccion;
}
/**
 * \fn Seleccion selec_new*()
 * \brief Reserva espacio en memoria para una seleccion
 *
 * \return puntero a ese espacio en memoria
 */
Seleccion* selec_new()
{
	Seleccion* pSeleccion;

	pSeleccion = (Seleccion*) malloc(sizeof(Seleccion));

	return pSeleccion;
}

int selec_getId(Seleccion* this,int* id)
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
 * \fn int selec_getPais(Seleccion*, char*)
 * \brief Obtiene el pais del puntero a seleccion dado y se lo asigna al puntero dado
 *
 * \param this
 * \param pais
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int selec_getPais(Seleccion* this,char* pais)
{
	int retorno = 0;
	if(this != NULL && pais != NULL)
	{
		strcpy(pais, this->pais);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int selec_getConfederacion(Seleccion*, char*)
 * \brief Obtiene la confederacion del puntero a seleccion dado y se lo asigna al puntero dado
 *
 * \param this
 * \param confederacion
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int selec_getConfederacion(Seleccion* this,char* confederacion)
{
	int retorno = 0;
	if(this != NULL && confederacion != NULL)
	{
		strcpy(confederacion, this->confederacion);
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int selec_getConvocados(Seleccion*, int*)
 * \brief Obtiene los convocados del puntero a seleccion dado y se lo asigna al puntero dado
 *
 * \param this
 * \param convocados
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int selec_getConvocados(Seleccion* this,int* convocados)
{
	int retorno = 0;

	if(this !=  NULL && convocados !=NULL)
	{
		*convocados = this->convocados;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int selec_setConvocados(Seleccion*, int)
 * \brief Asigna los convocados dados al puntero dado
 *
 * \param this
 * \param convocados
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int selec_setConvocados(Seleccion* this,int convocados)
{
	int retorno = 0;

	if(this !=  NULL && convocados > -1)
	{
		 this->convocados = convocados;
		retorno = 1;
	}

	return retorno;
}
/**
 * \fn int selec_restarConvocado(Seleccion*)
 * \brief resta uno al contador de convocados de la seleccion dada
 *
 * \param this
 * \return 1 si fue exitoso, 0 si no fue exitoso
 */
int selec_restarConvocado(Seleccion* this)
{
	int convocados;
	int retorno = 0;
	if(selec_getConvocados(this, &convocados))
	{
		convocados--;
		retorno = selec_setConvocados(this, convocados);
	}
	return retorno;
}

/**
 * \fn int selec_SortByConfederacion(void*, void*)
 * \brief Criterio de ordenamiento alfabetico por confederacion
 *
 * \param sel1
 * \param sel2
 * \return int
 */
int selec_SortByConfederacion(void* sel1,void* sel2)
{
	Seleccion* seleccion1 = (Seleccion*)sel1;
	Seleccion* seleccion2  = (Seleccion*)sel2;
	char confederacion1[30];
	char confederacion2[30];
	int retorno = 0;
	if(seleccion1 != NULL && seleccion2 != NULL && selec_getConfederacion(seleccion1,confederacion1) && selec_getConfederacion(seleccion2,confederacion2))
	{
		if(stricmp(confederacion1, confederacion2) > 0)
		{
			retorno = 1;
		}
		else
		{
			if(stricmp(confederacion1, confederacion2) < 0)
			{
				retorno = -1;
			}
		}
	}

	return retorno;
}
