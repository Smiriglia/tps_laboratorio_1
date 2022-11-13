#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Jugador.h"
#include "inputs.h"
/**
 * \fn int main()
 * \brief Ejecuta un menu con diversas opciones para gestion de jugadores y selecciones del mundial
 *
 * \return 0
 */
int main()
{
	setbuf(stdout,NULL);
    int option = 0;
    LinkedList* listaJugadores = ll_newLinkedList();
    LinkedList* listaSelecciones = ll_newLinkedList();
    LinkedList* listaJugadoresConfederacion = ll_newLinkedList();
    int flagCargaDatos = 0;
    do{
    	printf("\t|Menu Principal|\n"
    					"1  - Cargar Archivos\n"
    					"2  - Ingresar Jugador\n"
    					"3  - Modificar jugador\n"
    					"4  - Eliminar Jugador\n"
    					"5  - Listar\n"
    					"6  - Convocar y Desconvocar Jugadores\n"
    					"7  - Ordenar y Listar\n"
    					"8  - Generar Archivo Binario\n"
    					"9  - Cargar Archivo Binario\n"
    					"10 - Guardar Archivo csv\n"
    					"11 - Salir\n");

		if(utn_getNumero(&option, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 11, 3)== 0)
        switch(option)
        {
            case 1:
            	if(!flagCargaDatos && controller_cargarJugadoresDesdeTexto("jugadores.csv",listaJugadores) &&
            			controller_cargarSeleccionesDesdeTexto("selecciones.csv", listaSelecciones) &&
						!ll_isEmpty(listaJugadores) && !ll_isEmpty(listaSelecciones))
            	{

            		printf("Carga Exitosa\n");
            		flagCargaDatos = 1;
            	}
            	else
            	{
            		printf("Ha habido un error al cargar los jugadores\n");
            	}
            	break;
            case 2:
            	if(flagCargaDatos)
            	{
					if(controller_agregarJugador(listaJugadores))
					{
						printf("Jugador Agregado Exitosamente\n");
					}
					else
					{
						printf("Error, al Agregar Jugador\n");
					}
            	}
            	else
				{
					printf("Debes cargar los archivos antes de agregar\n");
				}

            	break;

            case 3:
            	if(flagCargaDatos)
				{
					if(controller_editarJugador(listaJugadores, listaSelecciones))
					{
						printf("Modificacion de jugador exitosa\n");
					}
					else
					{
						printf("Error, al Modificar Jugador\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de editar\n");
				}
            	break;

            case 4:
            	if(flagCargaDatos)
				{
					if(controller_removerJugador(listaJugadores, listaSelecciones))
					{
						printf("Eliminacion de jugador exitosa\n");
					}
					else
					{
						printf("Error, al eliminar Jugador\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de remover\n");
				}
            	break;
            case 5:
            	if(flagCargaDatos)
            	{
					if(controller_subMenuListar(listaJugadores, listaSelecciones))
					{
						printf("Listado exitoso\n");
					}
					else
					{
						printf("Error al listar\n");
					}
            	}
            	else
            	{
            		printf("Debes cargar los archivos antes de listar\n");
            	}
            	break;

            case 6:
				if(flagCargaDatos)
				{
					if(controller_convocarJugadores(listaJugadores, listaSelecciones))
					{
						printf("Convocacion exitosa\n");
					}
					else
					{
						printf("Error al convocar\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de Convocar\n");
				}
            	break;

            case 7:
            	if(flagCargaDatos)
				{
					if(controller_ordenarYListar(listaJugadores, listaSelecciones))
					{
						printf("Orden y Listado exitosa\n");
					}
					else
					{
						printf("Error al Ordenar\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de Convocar\n");
				}
            	break;

            case 8:
            	if(flagCargaDatos)
				{
            		ll_clear(listaJugadoresConfederacion);
					if(controller_crearListaJugadoresConfederacion(listaJugadores,listaSelecciones, listaJugadoresConfederacion) &&
							!ll_isEmpty(listaJugadoresConfederacion) &&
							controller_guardarJugadoresModoBinario("jugadoresBin.bin", listaJugadoresConfederacion))
					{
						printf("Guardado en binario exitoso\n");
					}
					else
					{
						printf("Error al guardar en binario\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de guardar\n");
				}
            	break;

            case 9:
            	if(flagCargaDatos)
				{
					ll_clear(listaJugadoresConfederacion);
					if(controller_cargarJugadoresDesdeBinario("jugadoresBin.bin" , listaJugadoresConfederacion) && !ll_isEmpty(listaJugadoresConfederacion))
					{
						controller_listarJugadores(listaJugadoresConfederacion, listaSelecciones);
					}
					else
					{
						printf("Error al cargar en binario\n");
					}
				}
            	else
            	{
            		printf("Debes cargar los archivos antes de cargar los binarios\n");
            	}
            	break;

            case 10:
            	if(flagCargaDatos)
				{
					ll_clear(listaJugadoresConfederacion);
					if(!ll_isEmpty(listaJugadores) && !ll_isEmpty(listaSelecciones) &&
						controller_guardarJugadoresModoTexto("jugadores.csv", listaJugadores) &&
						controller_guardarSeleccionesModoTexto("selecciones.csv",listaSelecciones))
					{
						printf("Guardado en csv exitoso\n");
					}
					else
					{
						printf("Error al guardar en csv\n");
					}
				}
				else
				{
					printf("Debes cargar los archivos antes de guardar\n");
				}
				break;
		}
    }while(option != 11);

    ll_clear(listaJugadores);
    ll_deleteLinkedList(listaJugadores);
    ll_clear(listaSelecciones);
    ll_deleteLinkedList(listaSelecciones);
    return 0;
}

