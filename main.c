#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

size_t longitud(Lista lista) {
	int tamano = 0; //Variable para ir actualizando el tamaño de la lista.
	Elemento* t = *lista; //Apunta al primer elemento de la lista.
	while(t != NULL) { //Se recorre la lista hasta que el elemento apuntado sea null.
		t = t -> siguiente; //En cada iteracion el apuntador apuntas ahora al siguiente elemento.
		tamano++; //En cada iteracion aumentamos en uno al tamano.
	}
	return tamano; //regresamos el tamaño de la lista;
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)) {
    int tamano = longitud(lista); //Variable que guarda el tamaño de la alista para saber hasta donde recorrerla.
    Elemento* t = *lista; //Apuntamos al primer elemento de la lista.
    int j;
    Elemento* arreglo = malloc(sizeof(Elemento) * tamano); //Se crea un arreglo de elementos para poder ordenarlos con qsort().
    for( j= 0; j < tamano; j++){
        arreglo[j]= *t; //En cada posición del arreglo metemos el Elemento.
        t = t -> siguiente; //En cada iteracion apuntamos al siguiente elemento.
    }
    int i;
    qsort(arreglo, tamano, sizeof(Elemento), *cmp);//Se manda a llamar qsort(). 
    Elemento* t2 = *lista; //Apuntamos nuevamente al primer elemento.
    for(i = 0; i < tamano; i++){
        t2 -> valor = arreglo[i].valor;  //
        t2 = t2 -> siguiente; //Recorremos la lista uno en cada iteracion.
    }
}

int cmp_int(const void* a, const void* b) {
	int a2 = *((int*) (((Elemento*) a)->valor));
	int b2 = *((int*) (((Elemento*) b)->valor));
	return a2 - b2;//Regresa un valor positivo si "a" es mayor, regresa 0 si son iguales o regresa un valor negativo si "b" es mayor.
}

Lista crea_lista() {
	Lista lista = malloc(sizeof(Lista)); //Reservamos la memoria y asignamos el apuntador a la variable.
	return lista; //Devolvemos el apuntador a la función.
}

int inserta_elemento(Lista lista, void *valor) {
	if (valor == NULL) {//Verifica si el valor es un elemento nulo.
		return longitud(lista); //Si el valor es nulo solo regresamos la longitud de la lista
	}
	Elemento* nuevo = malloc(sizeof(Elemento)); //Reservamos memoria para el nuevo elemento.
	nuevo -> valor = valor; //A el elemento le asignamos el valor que se recibe como parametro.
	nuevo -> siguiente = *lista; //Lo que va despues del nuevo elemento es la lista original.
	*lista = nuevo; //La lista apunta al nuevo elemento.
}

void imprime_lista_int(Lista lista) {
	int i;
	int tamano = longitud(lista); //Calculamos el tamaño de la lista para saber hasta donde recorrerla.
	Elemento* t = *lista; //Apuntamos al primer elemento de la lista.
	printf("("); //Se imprime el inicio de la lista
	for(i = 0; i < tamano; i++){ //Iteramos la lista de Elementos.
			printf("[%d] ", *(int*)t -> valor);//Para todos los elementos de la lista casteamos su valor que es un apuntador a void y lo imprimimos. 
			t = t -> siguiente; //En cada iteracion vamos apuntando al siguiente.
	}
	printf("%s\n\n", ")"); //Imprime el final de la lista.
}

Elemento *quita_elemento(Lista lista, size_t posicion) {
	int tamano = longitud(lista);//Guardamos el tamaño de la lista.
	if(*lista == NULL || posicion < 0 || posicion >= longitud(lista)){//Verificamos que la longitud de la lista no sea cero o que la posicion sea mayor al numero de elementos.
		return NULL;//Regrasamos null.
	}
	if(posicion == 0) {//Si recibimos la posicion igual a cero quitamos al primer elemento de la lista.
		Elemento* t = *lista; //Apunta al inicio de la lista(el primer elemento).
		Elemento* auxi = t->siguiente; //Ahora apuntamos al segundo elemento.
		*lista = auxi; //El primer elemento ahora apunta al segundo.
		return t; //Se regresa el elemento eliminado que fue el primer elemento.		
	}
	else if(posicion == tamano-1){//Checa si la posicion es igual al tamaño menos uno(osea el ultimo elemento).
	Elemento *y = *lista;
	int i;//Se crea una variable para recorrer la lista.
		for(i = 0; i < tamano-2; i++){ //Recorremos hasta el peniltimo elemento.
			y = y-> siguiente;//Apunta al siguiente.
		}
	Elemento *aux = y -> siguiente; //Apuntamos a el ultimo elemento.
	Elemento *aux2 = aux; //Almacenamos el elemento que se va a eliminar.
	y -> siguiente = NULL; //Se le asigna el valor de null ahora al siguiente del penultimo de la lista.
	return aux2; //Regresamos el elemente eliminado que en este acaso es el ultimo.
	}
}


void borra_lista(Lista lista) {
	int tamano = longitud(lista);//Guardamos la longitud de la lista en un a variable.
	int i;//Se crea para la iteracion de la lista.
	for(i = 0; i < tamano; i++){ 
		Elemento* t = quita_elemento(lista, 0); //Borramos el primer elemento hasta que se termine de eleiminar la lista completa..
		if (t != NULL){ //Se revisa si el elemento al que apunta t no es nulo.
			free(t -> valor); //Liberamos la memoria que ocupa su valor.
			free(t); //Por ultimo eliminamos al elemento(esto se hace en cada iteracion).
		}
	}
	free(lista); //Liberamos la memoria que ocupaba la lista.
}


void inserta_datos_de_prueba(Lista lista) {
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}
