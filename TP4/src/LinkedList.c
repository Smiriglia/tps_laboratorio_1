#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!= NULL)
    {
    	this-> pFirstNode = NULL;
		this-> size = 0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!= NULL)
    {
		returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* retorno = NULL;
    int i = 0;
    int tam;
    if(this!= NULL)
    {
		tam = ll_len(this);
    	if(nodeIndex > -1 && nodeIndex < tam)
    	{
    		retorno = this-> pFirstNode;
			while(i < nodeIndex)
			{
				retorno = retorno -> pNextNode;
				i++;
			}

    	}
    }
    return retorno;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int tam;
	Node* nodo = NULL;
	Node* nodoAux = NULL;

	if(this != NULL)
	{
		tam = ll_len(this);
		if(nodeIndex == 0 && tam == 0)
		{
			this->pFirstNode = (Node*) malloc(sizeof(Node));
			this->pFirstNode -> pElement = pElement;
			this->pFirstNode -> pNextNode = NULL;
			this->size = this->size + 1;
			returnAux = 0;
		}
		else
		{
			if(nodeIndex == 0)
			{
				nodoAux = this->pFirstNode;
				this->pFirstNode = (Node*) malloc(sizeof(Node));
				this->pFirstNode -> pElement = pElement;
				this->pFirstNode -> pNextNode = nodoAux;
				this->size = this->size + 1;
				returnAux = 0;
			}
			else
			{
				if(nodeIndex > -1 && nodeIndex <= tam)
				{
					nodo = getNode(this, nodeIndex);
					if(nodo == NULL && nodeIndex == tam)
					{
						nodoAux = getNode(this, nodeIndex - 1);
						if(nodoAux != NULL)
						{
							nodoAux-> pNextNode = (Node*) malloc(sizeof(Node));
							nodoAux -> pNextNode ->pElement = pElement;
							nodoAux -> pNextNode ->pNextNode = NULL;
							this->size = this->size + 1;
							returnAux = 0;
						}
					}
					else
					{
						nodoAux = nodo;
						nodo = getNode(this, nodeIndex-1);
						if(nodo != NULL)
						{
							nodo -> pNextNode = (Node*) malloc(sizeof(Node));
							nodo -> pNextNode-> pElement = pElement;
							nodo -> pNextNode -> pNextNode = nodoAux;
							returnAux = 0;
						}
					}
				}
			}
		}
	}
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(addNode(this,ll_len(this), pElement) == 0)
    {
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodo;
    nodo = getNode(this,index);
    if(nodo != NULL)
    {
    	returnAux = nodo->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* nodo;
	nodo = getNode(this,index);
	if(nodo != NULL)
	{
		nodo->pElement = pElement;
		returnAux = 0;
	}

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodo;
    Node* aux;
    Node* anterior;
	nodo = getNode(this,index);

	if(nodo != NULL)
	{
		aux = nodo-> pNextNode;
		if(index == 0 && ll_len(this) > 0)
		{
			this->pFirstNode = aux;
		}
		else
		{
			if(aux != NULL)
			{
				anterior= getNode(this,index - 1);
				if(anterior != NULL)
				{
					anterior -> pNextNode = aux;
				}
			}
		}
		free(nodo);
		this->size = this->size - 1;
		returnAux = 0;
	}
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
		while(ll_len(this) > 0)
		{
			ll_remove(this,0);
		}
		returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	free(this);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int tam;
    Node* nodo;
    if(this != NULL)
    {
    	tam = ll_len(this);
    	nodo = this -> pFirstNode;
    	for(i=0; i < tam; i++)
    	{
    		if(nodo->pElement == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    		nodo = nodo->pNextNode;
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(ll_len(this))
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(addNode(this,index,pElement)==0)
    {
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
	Node* nodo;
	Node* aux;
	Node* anterior;
	nodo = getNode(this,index);

	if(nodo != NULL)
	{
		returnAux = nodo->pElement;
		aux = nodo-> pNextNode;
		if(index == 0 && ll_len(this) > 0)
		{
			this->pFirstNode = aux;
		}
		else
		{
			if(aux != NULL)
			{

				anterior= getNode(this,index - 1);
				if(anterior != NULL)
				{
					anterior -> pNextNode = aux;
				}
			}
		}
		this->size = this->size - 1;
	}
	return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
		if(ll_indexOf(this,pElement) != -1)
		{
			returnAux = 1;
		}
		else
		{
			returnAux = 0;
		}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int contadorContenidos = 0;
    int tam;
    int i;
    void* auxElement = NULL;

    tam = ll_len(this2);
    if(this != NULL && this2 != NULL)
    {
    	for(i=0; i< tam; i++)
    	{
    		auxElement = ll_get(this, i);
			if(ll_contains(this,auxElement))
			{
				contadorContenidos++;
			}
    	}
    	if(i == contadorContenidos)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int tam;
    int i;
    void* auxElement;
    if(this != NULL)
    {
    	tam = ll_len(this);
    	if(tam >= to && tam >= from && from > -1 && to >= from)
    	{
			cloneArray = ll_newLinkedList();
			if(cloneArray != NULL)
			{
				for(i = from; i < to; i++)
				{
					auxElement = ll_get(this, i);
					ll_add(cloneArray, auxElement);
					this->size = this->size + 1;
				}
			}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
		cloneArray = ll_subList(this, 0, ll_len(this));

    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    int i;
    int j;
    int tam;
    void* element1 = NULL;
    void* element2 = NULL;
    void* aux = NULL;
    if(this != NULL && pFunc != NULL)
	{
    	tam = ll_len(this);
    	for(i=0; i < tam-1; i++)
    	{
    		for(j = i + 1; j < tam; j++)
    		{
    			element1 = ll_get(this,i);
    			element2 = ll_get(this,j);
    			switch(order)
    			{
    				case 0:
    					if((*pFunc)(element1,element2) == -1)
						{
    						aux = element1;
    						ll_set(this, i, element2);
    						ll_set(this, j, aux);
						}
    					returnAux = 0;
    					break;

    				case 1:
    					if((*pFunc)(element1,element2) == 1)
						{

    						aux = element1;
							ll_set(this, i, element2);
							ll_set(this, j, aux);
						}
    					returnAux = 0;
    					break;
    			}

    		}
    	}

	}

    return returnAux;

}
