#include <stdio.h>
#include <stdlib.h>

#include "Jugador.h"
#include "Seleccion.h"
#include "LinkedList.h"
#include "controller.h"
#include "parser.h"
#include "inputs.h"

static void imprimirSeleccion(Seleccion* seleccion);
static void imprimirJugador(Jugador* jugador,  LinkedList* selecciones);
static int buscarSeleccionPorId(LinkedList* selecciones, int id);
static int listarJugadoresConvocados(LinkedList* pArrayListJugador, LinkedList* selecciones);
static int buscarJugadorPorId(LinkedList* pArrayListJugador, int id);
static int modificarJugador(Jugador* jugador);
static int convocarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones);
static int convocarJugador(Jugador* jugador, Seleccion* seleccion);
static int desconvocarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones);
static int desconvocarJugador(Jugador* jugador, Seleccion* seleccion);
static int jug_esConfederacion(Jugador* jugador, LinkedList* pArrayListSelecciones, char confederacion[]);

/** \brief Carga los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeTexto(char* path , LinkedList* pArrayListJugador)
{
	FILE * archivo;
	int retorno = 0;
	archivo = fopen(path,"r");
	if(archivo != NULL)
	{
		retorno = parser_JugadorFromText(archivo , pArrayListJugador);
		fclose(archivo);
	}
    return retorno;
}

/** \brief Carga los datos de los jugadores desde el archivo generado en modo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeBinario(char* path , LinkedList* pArrayListJugador)
{
	FILE * archivo;
	int retorno = 0;
	archivo = fopen(path,"rb");
	if(archivo != NULL)
	{
		retorno = parser_JugadorFromBinary(archivo , pArrayListJugador);
		fclose(archivo);
	}
	return retorno;
}

/** \brief Alta de jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_agregarJugador(LinkedList* pArrayListJugador)
{
	int idAux;
	char idStr[30];
	char nombreCompleto[100];
	int edadAux;
	char edadStr[30];
	char posicion[30];
	char nacionalidad[30];
	int retorno = 0;
	Jugador * jugador = NULL;

	if((utn_getDescripcion(nombreCompleto,100,"Ingrese el nombre completo del jugador: ", "\nError. Nombre Invalido\n", 3) == 0) &&
			(utn_getNumero(&edadAux,"Ingrese la edad del jugador: ", "\nError. Edad Invalida\n", 18, 120,3) == 0) &&
			(utn_getDescripcion(posicion,30,"Ingrese la posicion del jugador: ", "\nError. posicion Invalido\n", 3) == 0) &&
			(utn_getDescripcion(nacionalidad,30,"Ingrese la nacionalidad del jugador: ", "\nError. nacionalidad Invalido\n", 3) == 0))
	{
		idAux = jug_getLastId("lastId.bin");
		if(idAux != 0)
		{
			sprintf(idStr, "%d", idAux);
			sprintf(edadStr, "%d", edadAux);

			jugador = jug_newParametros(idStr, nombreCompleto, edadStr, posicion, nacionalidad, "0");
			if(jugador != NULL && pArrayListJugador != NULL)
			{
				ll_add(pArrayListJugador, jugador);
				jug_sumarLastId("lastId.bin");
				retorno = 1;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_editarJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int mayorId;
	int retorno = 0;
	int idElegido;
	int indiceJugador;
	Jugador* jugador = NULL;
	mayorId = jug_getLastId("lastId.bin");
	if(mayorId > 0 && pArrayListJugador != NULL)
	{
		controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);
		if((utn_getNumero(&idElegido,"Ingrese la id del jugador a modificar: ", "\nError. Id Invalida\n", 1, mayorId,3) == 0))
		{
			indiceJugador = buscarJugadorPorId(pArrayListJugador, idElegido);
			if(indiceJugador != -1)
			{
				jugador = (Jugador*) ll_get(pArrayListJugador, indiceJugador);
				retorno = modificarJugador(jugador);
			}
		}
	}
    return retorno;
}

/** \brief Baja del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_removerJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{

	int mayorId;
	int retorno = 0;
	int idElegido;
	int indiceJugador;
	int idSeleccion;
	int indiceSeleccion;
	Jugador* jugador = NULL;
	Seleccion* seleccion = NULL;
	mayorId = jug_getLastId("lastId.bin");
	if(mayorId > 0 && pArrayListJugador != NULL)
	{
		controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);//para ver mas tarde
		if((utn_getNumero(&idElegido,"Ingrese la id del jugador: ", "\nError. Id Invalida\n", 1, mayorId,3) == 0))
		{
			indiceJugador = buscarJugadorPorId(pArrayListJugador, idElegido);
			if(indiceJugador != -1)
			{
				jugador = (Jugador*) ll_get(pArrayListJugador, indiceJugador);
				if(jug_getIdSeleccion(jugador, &idSeleccion) &&  idSeleccion > 0)
				{
					indiceSeleccion = buscarSeleccionPorId(pArrayListSelecciones, idSeleccion);
					if(indiceSeleccion != -1)
					{
						seleccion = (Seleccion*) ll_get(pArrayListSelecciones, indiceSeleccion);
						selec_restarConvocado(seleccion);
					}
				}

				int selec_restarConvocado(Seleccion* this);
				ll_remove(pArrayListJugador, indiceJugador);
				jug_delete(jugador);
				retorno = 1;
			}
		}
	}
	return retorno;
}

/** \brief Listar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_listarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int retorno = 0;
	int tam;
	int i;
	Jugador* jugador = NULL;
	if(pArrayListJugador != NULL)
	{
		tam = ll_len(pArrayListJugador);
		retorno = 1;
		printf("=======================================================================================================================\n"
				"|%-5s|%-35s|%-13s|%-20s|%-20s|%-20s|\n"
				"|-----|-----------------------------------|-------------|--------------------|--------------------|--------------------|\n",
				 "ID","NOMBRE COMPLETO","EDAD" ,"POSICION", "NACIONALIDAD","SELECCION");
		for(i = 0; i < tam; i++)
		{
			jugador = (Jugador*) ll_get(pArrayListJugador, i);
			imprimirJugador(jugador, pArrayListSelecciones);
		}
		printf("=======================================================================================================================\n");
	}
	return retorno;
}

/** \brief Ordenar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_ordenarJugadores(LinkedList* pArrayListJugador)
{
    return 1;
}

/** \brief Guarda los datos de los jugadores en el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoTexto(char* path , LinkedList* pArrayListJugador)
{
	int retorno = 0;
	FILE* archivoBinario;
	Jugador* jugador = NULL;
	int id;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	int idSeleccion;
	int i;

	archivoBinario = fopen(path,"wb");

	if(archivoBinario != NULL)
	{
		fprintf(archivoBinario, "id,nombreCompleto,edad,posicion,nacionalidad,idSelecion\n");
		for(i = 0; i < ll_len(pArrayListJugador); i++)
		{
			jugador = (Jugador*) ll_get(pArrayListJugador, i);
			if(jugador != NULL)
			{
				if(jug_getId(jugador,&id) && jug_getNombreCompleto(jugador,nombreCompleto) && jug_getEdad(jugador, &edad) &&
					jug_getPosicion(jugador,posicion) && jug_getNacionalidad(jugador, nacionalidad) && jug_getIdSeleccion(jugador, &idSeleccion))
				{
					fprintf(archivoBinario, "%d,%s,%d,%s,%s,%d\n",id,nombreCompleto,edad,posicion,nacionalidad,idSeleccion);
				}
			}
		}
		fclose(archivoBinario);
		retorno = 1;
	}
	return retorno;
}

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListJugador)
{
	int retorno = 0;
	FILE* archivoBinario;
	Jugador* jugador = NULL;
	int i;

	archivoBinario = fopen(path,"wb");

	if(archivoBinario != NULL)
	{
		for(i = 0; i < ll_len(pArrayListJugador); i++)
		{
			jugador = (Jugador*) ll_get(pArrayListJugador, i);
			if(jugador != NULL)
			{
				fwrite(jugador,sizeof(Jugador),1,archivoBinario);
			}
		}
		fclose(archivoBinario);
		retorno = 1;
	}
    return retorno;
}



/** \brief Carga los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_cargarSeleccionesDesdeTexto(char* path , LinkedList* pArrayListSeleccion)
{
	FILE * archivo;
	int retorno = 0;
	archivo = fopen(path,"r");
	retorno = parser_SeleccionFromText(archivo , pArrayListSeleccion);
	fclose(archivo);
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_editarSeleccion(LinkedList* pArrayListSeleccion)
{
    return 1;
}


/** \brief Listar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_listarSelecciones(LinkedList* pArrayListSeleccion)
{
	int tam;
	int retorno = 0;
	Seleccion* seleccion = NULL;
	if(pArrayListSeleccion != NULL)
	{
		tam = ll_len(pArrayListSeleccion);
		retorno = 1;
		printf("=============================================================\n"
					   "|%-5s|%-23s|%-13s|%-15s|\n"
					"|-----|-----------------------|-------------|---------------|\n",
						 "ID","PAIS","CONFEDERACION" ,"CONVOCADOS");
		for(int i = 0; i < tam; i++)
		{
			seleccion = (Seleccion*) ll_get(pArrayListSeleccion, i);
			imprimirSeleccion(seleccion);
		}
		printf("=============================================================\n");
	}
	return retorno;
}

/** \brief Ordenar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_ordenarSelecciones(LinkedList* pArrayListSeleccion)
{
    return 1;
}

/** \brief Guarda los datos de los selecciones en el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarSeleccionesModoTexto(char* path , LinkedList* pArrayListSeleccion)
{
	int id;
	char pais[30];
	char confederacion[30];
	int convocados;
	int i;
	Seleccion* seleccion = NULL;
	FILE* archivoBinario;
	int retorno;
	archivoBinario = fopen(path,"wb");

	if(archivoBinario != NULL)
	{
		fprintf(archivoBinario, "id,pais,confederacion,convocados\n");
		for(i = 0; i < ll_len(pArrayListSeleccion); i++)
		{
			seleccion = (Seleccion*) ll_get(pArrayListSeleccion, i);
			if(seleccion != NULL)
			{
				if(seleccion != NULL && selec_getId(seleccion,&id) && selec_getPais(seleccion,pais) &&
					selec_getConfederacion(seleccion, confederacion) && selec_getConvocados(seleccion, &convocados))
				{
					fprintf(archivoBinario, "%d,%s,%s,%d\n",id,pais,confederacion,convocados);
				}
			}
		}
		fclose(archivoBinario);
		retorno = 1;
	}
	return retorno;
}
/**
 * \fn void imprimirSeleccion(Seleccion*)
 * \brief Imprime todas los datos de una seleccion
 *
 * \param seleccion
 */
static void imprimirSeleccion(Seleccion* seleccion)
{
	int id;
	char pais[30];
	char confederacion[30];
	int convocados;

	if(seleccion != NULL && selec_getId(seleccion,&id) && selec_getPais(seleccion,pais) &&
			selec_getConfederacion(seleccion, confederacion)&& selec_getConvocados(seleccion, &convocados))
	{
		printf("|%-5d|%-23s|%-13s|%-15d|\n",
								id,pais,confederacion,convocados);
	}
}
/**
 * \fn int controller_subMenuListar(LinkedList*, LinkedList*)
 * \brief El usuario puede elgir distintas opciones de listado
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int controller_subMenuListar(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int retorno = 0;
	int respuesta;
	do
	{
		printf("\t|Menu Listado|\n"
				"1 - Todos Los Jugadores\n"
				"2 - Todas Las Selecciones\n"
				"3 - Jugadores Convocados\n"
				"4 - Salir\n");

		if(utn_getNumero(&respuesta, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 4, 3)== 0)
		{
			switch(respuesta)
			{
				case 1:
					retorno =  controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);
					break;

				case 2:
					retorno = controller_listarSelecciones(pArrayListSelecciones);
					break;

				case 3:
					listarJugadoresConvocados(pArrayListJugador, pArrayListSelecciones);
					break;
			}
		}
	}while(respuesta != 4);
	return retorno;
}

/**
 * \fn void imprimirJugador(Jugador*, LinkedList*)
 * \brief Imprime todos los datos de un jugador
 *
 * \param jugador
 * \param selecciones
 */
static void imprimirJugador(Jugador* jugador,  LinkedList* selecciones)
{
	int indiceSeleccion;
	int id;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	Seleccion* seleccion = NULL;
	char paisSeleccion[30] = "No convocado";
	int idSeleccion;
	if(jugador != NULL && selecciones != NULL)
	{
		if(jug_getIdSeleccion(jugador, &idSeleccion))
		{
			indiceSeleccion = buscarSeleccionPorId(selecciones, idSeleccion);
			if(indiceSeleccion != -1 || idSeleccion == 0)
			{
				seleccion = ll_get(selecciones, indiceSeleccion);
				if(jug_getId(jugador, &id) && jug_getNombreCompleto(jugador, nombreCompleto) &&
					jug_getEdad(jugador,&edad) && jug_getPosicion(jugador, posicion) &&
					jug_getNacionalidad(jugador,nacionalidad) && (idSeleccion == 0 ||selec_getPais(seleccion, paisSeleccion)))
				{
					printf("|%-5d|%-35s|%-13d|%-20s|%-20s|%-20s|\n",id,nombreCompleto, edad, posicion, nacionalidad, paisSeleccion);
				}
			}
		}
	}
}
/**
 * \fn int buscarSeleccionPorId(LinkedList*, int)
 * \brief recorre la lista dada hasta encontrar la coincidencia de id
 *
 * \param selecciones
 * \param id
 * \return el indice de coincidencia en caso de haberlo encontrado, -1 si no fue encontrado
 */
static int buscarSeleccionPorId(LinkedList* selecciones, int id)
{
	int indice = -1;
	int i ;
	int tam;
	Seleccion* seleccion;
	int idAux;
	if(selecciones != NULL && id > 0)
	{
			tam = ll_len(selecciones);
			for(i = 0; i < tam; i++)
			{
				seleccion = ll_get(selecciones, i);
				if(selec_getId(seleccion,&idAux) && idAux == id)
				{
					indice = i;
					break;
				}
			}
	}
	return indice;
}
/**
 * \fn int listarJugadoresConvocados(LinkedList*, LinkedList*)
 * \brief Lista a los jugadores convocados
 *
 * \param pArrayListJugador
 * \param selecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int listarJugadoresConvocados(LinkedList* pArrayListJugador, LinkedList* selecciones)
{
	int retorno = 0;
	int tam;
	int i;
	int idSeleccion;
	Jugador* jugador = NULL;
	if(pArrayListJugador != NULL)
	{
		tam = ll_len(pArrayListJugador);
		retorno = 1;
		printf("=======================================================================================================================\n"
				"|%-5s|%-35s|%-13s|%-20s|%-20s|%-20s|\n"
				"|-----|-----------------------------------|-------------|--------------------|--------------------|--------------------|\n",
				 "ID","NOMBRE COMPLETO","EDAD" ,"POSICION", "NACIONALIDAD","SELECCION");
		for(i = 0; i < tam; i++)
		{
			jugador = (Jugador*) ll_get(pArrayListJugador, i);

			if(jug_getIdSeleccion(jugador, &idSeleccion) && (idSeleccion > 0))
			{
				imprimirJugador(jugador, selecciones);
			}
		}
		printf("=======================================================================================================================\n");
	}
	return retorno;
}

static int buscarJugadorPorId(LinkedList* pArrayListJugador, int id)
{
	int indice = -1;
	int i;
	int tam;
	Jugador* jugador;
	int idAux;
	if(pArrayListJugador != NULL && id > 0)
	{
			tam = ll_len(pArrayListJugador);
			for(i = 0; i < tam; i++)
			{
				jugador = ll_get(pArrayListJugador, i);
				if(jug_getId(jugador,&idAux) && idAux == id)
				{
					indice = i;
					break;
				}
			}
	}
	return indice;
}
/**
 * \fn int modificarJugador(Jugador*)
 * \brief El jugador puede elgir y modificar a un jugador
 *
 * \param jugador
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int modificarJugador(Jugador* jugador)
{
	int retorno = 0;
	int option;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	if(jugador != NULL)
	{
		do{
			printf("\t|Menu Modificacion|\n"
					"1  - Modificar Nombre Completo\n"
					"2  - Modificar Edad\n"
					"3  - Modificar Posicion\n"
					"4  - Modificar Nacionalidad\n"
					"5  - Salir\n");

			if(utn_getNumero(&option, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 5, 3)== 0)
				switch(option)
				{
					case 1:
						if(utn_getDescripcion(nombreCompleto,100,"Ingrese el nombre completo del jugador: ", "\nError. Nombre Invalido\n", 3) == 0)
						{
							retorno = jug_setNombreCompleto(jugador, nombreCompleto);
						}
						break;

					case 2:
						if(utn_getNumero(&edad,"Ingrese la edad del jugador: ", "\nError. Edad Invalida\n", 18, 120,3) == 0)
						{
							retorno = jug_setEdad(jugador, edad);
						}
						break;

					case 3:
						if(utn_getDescripcion(posicion,30,"Ingrese la posicion del jugador: ", "\nError. posicion Invalido\n", 3) == 0)
						{
							retorno = jug_setPosicion(jugador, posicion);
						}
						break;

					case 4:
						if(utn_getDescripcion(nacionalidad,30,"Ingrese la nacionalidad del jugador: ", "\nError. nacionalidad Invalido\n", 3) == 0)
						{
							retorno = jug_setNacionalidad(jugador, nacionalidad);
						}
						break;
				}
		}while(option != 5);
	}

	return retorno;
}
/**
 * \fn int controller_convocarJugadores(LinkedList*, LinkedList*)
 * \brief le da a elegir al usuario si quiere convocar o desconvocar jugadores
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int controller_convocarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int option;
	int retorno = 0;
	do{
		printf("\t|Menu Convocacion|\n"
				"1  - Convocar jugador\n"
				"2  - Desconvocar jugador\n"
				"3  - Salir\n");

		if(utn_getNumero(&option, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 5, 3)== 0)
		{
			switch(option)
			{
				case 1:
					retorno = convocarJugadores(pArrayListJugador, pArrayListSelecciones);
					break;

				case 2:
					retorno = desconvocarJugadores(pArrayListJugador, pArrayListSelecciones);
					break;
			}
		}
	}while(option != 3);

	return retorno;
}
/**
 * \fn int convocarJugadores(LinkedList*, LinkedList*)
 * \brief El jugador puede elegir a un jugador no convocado para convocarlo en una seleccion
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int convocarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int mayorId;
	int retorno = 0;
	int idElegido;
	int idSeleccion;
	int indiceJugador;
	int indiceSeleccion;
	int idSeleccionJugador;
	Jugador* jugador = NULL;
	Seleccion* seleccion = NULL;
	mayorId = jug_getLastId("lastId.bin");
	if(mayorId > 0 && pArrayListJugador != NULL)
	{
		controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);//para ver mas tarde
		if((utn_getNumero(&idElegido,"Ingrese la id del jugador a convocar: ", "\nError. Id Invalida\n", 1, mayorId,3) == 0))
		{
			indiceJugador = buscarJugadorPorId(pArrayListJugador, idElegido);
			if(indiceJugador != -1)
			{
				jugador = (Jugador*) ll_get(pArrayListJugador, indiceJugador);
				jug_getIdSeleccion(jugador, &idSeleccionJugador);
				if(idSeleccionJugador == 0)
				{
					controller_listarSelecciones(pArrayListSelecciones);
					if((utn_getNumero(&idSeleccion,"Ingrese la id de la seleccion la cual convocara al jugador: ", "\nError. Id Invalida\n", 1, 31,3) == 0))
					{
						indiceSeleccion = buscarSeleccionPorId(pArrayListSelecciones, idSeleccion);
						if(indiceSeleccion != -1)
						{
							seleccion = (Seleccion*) ll_get(pArrayListSelecciones, indiceSeleccion);
							retorno = convocarJugador(jugador, seleccion);
						}
					}
				}
				else
				{
					printf("No puedes convocar un jugador que ya ha sido convocado\n");
				}
			}
		}
	}
	return retorno;
}
/**
 * \fn int convocarJugador(Jugador*, Seleccion*)
 * \brief Verifica si la seleccion no esta llena y convoca al jugador dado
 *
 * \param jugador
 * \param seleccion
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int convocarJugador(Jugador* jugador, Seleccion* seleccion)
{
	int idSeleccion;
	int convocados;
	int retorno = 0;

	if(selec_getConvocados(seleccion , &convocados) && convocados < MAX_CONVOCADOS && selec_getId(seleccion , &idSeleccion) &&jug_setIdSeleccion(jugador, idSeleccion))
	{
		convocados++;
		retorno = selec_setConvocados(seleccion , convocados);
	}
	return retorno;
}
/**
 * \fn int desconvocarJugadores(LinkedList*, LinkedList*)
 * \brief El jugador elige a uno de los jugadores convocados para desconvocarlo
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int desconvocarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int mayorId;
	int retorno = 0;
	int idElegido;
	int indiceJugador;
	int indiceSeleccion;
	int idSeleccionJugador;
	Jugador* jugador = NULL;
	Seleccion* seleccion = NULL;
	mayorId = jug_getLastId("lastId.bin");
	if(mayorId > 0 && pArrayListJugador != NULL)
	{
		listarJugadoresConvocados(pArrayListJugador, pArrayListSelecciones);
		if((utn_getNumero(&idElegido,"Ingrese la id del jugador a desconvocar: ", "\nError. Id Invalida\n", 1, mayorId,3) == 0))
		{
			indiceJugador = buscarJugadorPorId(pArrayListJugador, idElegido);
			if(indiceJugador != -1)
			{
				jugador = (Jugador*) ll_get(pArrayListJugador, indiceJugador);
				jug_getIdSeleccion(jugador, &idSeleccionJugador);
				if(idSeleccionJugador > 0)
				{
					indiceSeleccion = buscarSeleccionPorId(pArrayListSelecciones, idSeleccionJugador);
					if(indiceSeleccion != -1)
					{
						seleccion = (Seleccion*) ll_get(pArrayListSelecciones, indiceSeleccion);
						retorno = desconvocarJugador(jugador, seleccion);
					}
				}
				else
				{
					printf("No puedes desconvocar a un jugador que no ha sido convocado\n");
				}
			}
		}
	}
	return retorno;
}
/**
 * \fn int desconvocarJugador(Jugador*, Seleccion*)
 * \brief Desconvoca al jugador y resta 1 al contador de convocados de la seleccion
 *
 * \param jugador
 * \param seleccion
 * \return 1 si fue exitoso, 0 sino lo fue
 */
static int desconvocarJugador(Jugador* jugador, Seleccion* seleccion)
{
	int retorno = 0;

	if(jug_setIdSeleccion(jugador, 0))
	{
		retorno = selec_restarConvocado(seleccion);
	}
	return retorno;
}
/**
 * \fn int controller_ordenarYListar(LinkedList*, LinkedList*)
 * \brief Ordena y lista dependiendo de la opcion que elija el usuario
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \return 1 si fue exitoso, 0 sino lo fue
 */
int controller_ordenarYListar(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int retorno = 0;
	int option;
	do{
		printf("\t|Menu Ordenar Y Listar|\n"
						"1  - Ordenar Jugadores Por Nacionalidad\n"
						"2  - Ordenar Selecciones por confederacion\n"
						"3  - Ordenar Jugadores Por Edad\n"
						"4  - Ordenar Jugadores Por Nombre\n"
						"5  - Salir\n");

		if(utn_getNumero(&option, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 11, 3)== 0)
		{
			switch(option)
			{
				case 1:
					ll_sort(pArrayListJugador, jug_SortByNacionalidad, 1);
					controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);
					retorno = 1;
					break;

				case 2:
					ll_sort(pArrayListSelecciones, selec_SortByConfederacion, 1);
					controller_listarSelecciones(pArrayListSelecciones);
					retorno = 1;
					break;

				case 3:
					ll_sort(pArrayListJugador, jug_SortByEdad, 1);
					controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);
					retorno = 1;
					break;

				case 4:
					ll_sort(pArrayListJugador, jug_SortByNombre, 1);
					controller_listarJugadores(pArrayListJugador, pArrayListSelecciones);
					retorno = 1;
					break;
			}
		}
	}while(option != 5);

	return retorno;
}
/**
 * \fn int controller_crearListaJugadoresConfederacion(LinkedList*, LinkedList*, LinkedList*)
 * \brief Crea una lista de jugadores que pertenezcan a la confederacion ingresada por el usuario
 *
 * \param pArrayListJugador
 * \param pArrayListSelecciones
 * \param pArrayNewList
 * \return 1 si fue exitoso y 0 si no fue exitoso
 */
int controller_crearListaJugadoresConfederacion(LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones, LinkedList* pArrayNewList)
{
	int retorno = 0;
	int i;
	char confederacion[30];
	Jugador* jugador;
	if(pArrayListJugador != NULL && pArrayListJugador != NULL && pArrayNewList != NULL)
	{
		if(utn_getNombre(confederacion,30,"Ingrese la confederacion del jugador: ", "\nError. confederacion Invalida\n", 3) == 0)
		{
			for(i = 0; i < ll_len(pArrayListJugador); i++)
			{
				jugador = (Jugador*) ll_get(pArrayListJugador, i);
				if(jug_esConfederacion(jugador, pArrayListSelecciones, confederacion))
				{
					ll_add(pArrayNewList, jugador);
				}
			}
			retorno = 1;
		}
	}
	return retorno;
}
/**
 * \fn int jug_esConfederacion(Jugador*, LinkedList*, char[])
 * \brief Verifica si el jugador coincide con la confederacion dada
 *
 * \param jugador
 * \param pArrayListSelecciones
 * \param confederacion
 * \return 1 si coincide, 0 si no coincide
 */
int jug_esConfederacion(Jugador* jugador, LinkedList* pArrayListSelecciones, char confederacion[])
{
	int retorno = 0;
	int idSeleccion;
	int indiceSeleccion;
	Seleccion* seleccion;
	char confederacionJugador[30];

	if(jugador != NULL && pArrayListSelecciones != NULL && jug_getIdSeleccion(jugador, &idSeleccion))
	{
		indiceSeleccion = buscarSeleccionPorId(pArrayListSelecciones, idSeleccion);
		if(indiceSeleccion != -1)
		{
			seleccion = (Seleccion*) ll_get(pArrayListSelecciones, indiceSeleccion);
			if(seleccion != NULL && selec_getConfederacion(seleccion, confederacionJugador) && stricmp(confederacion, confederacionJugador) == 0)
			{
				retorno = 1;
			}
		}
	}

	return retorno;
}
