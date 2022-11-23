/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"
#include "../inc/inputs.h"


int main(void)
{
	setbuf(stdout,NULL);
	int option;

	/*startTesting(1);  // ll_newLinkedList
	startTesting(2);  // ll_len
	startTesting(3);  // getNode - test_getNode
	startTesting(4);  // addNode - test_addNode
	startTesting(5);  // ll_add
  	startTesting(6);  // ll_get
	startTesting(7);  // ll_set
	startTesting(8);  // ll_remove
	startTesting(9);  // ll_clear
	startTesting(10); // ll_deleteLinkedList
	startTesting(11); // ll_indexOf
	startTesting(12); // ll_isEmpty
	startTesting(13); // ll_push
	startTesting(14); // ll_pop
	startTesting(15); // ll_contains
	startTesting(16); // ll_containsAll
	startTesting(17); // ll_subList
	startTesting(18); // ll_clone
	startTesting(19); // ll_sort*/
	do{
	    	printf("\t|Menu Principal|\n"
	    					"1  - Cargar Archivos\n"
	    					"2  - Ingresar Jugador\n"
	    					"3  - Modificar jugador\n"
	    					"4  - Eliminar Jugador\n"
	    					"5  - Listar\n"
	    					"6  - Convocar y Desconvocar Jugadores\n"
	    					"7 - Salir\n");

			if(utn_getNumero(&option, "Eliga su opcion: ","\nERROR, OPCION INVALIDA\n", 1, 7, 3)== 0)
	        switch(option)
	        {
	        	case 1:
	        		break;

	        	case 2:
	        		break;

	        	case 3:
	        		break;

	        	case 4:
	        		break;

	        	case 5:
	        		break;

	        	case 6:
	        		break;
	        }
		}while(option != 7);
    return 0;
}

































