#include "Rii.h"


// init_vertice no construye el vértice dado que todos los vértices
// fueron construidos, pero no inicializados por el grafo (grafo_init)
void init_vertice(Vertice vertice, u32 nombre) {
    vertice->inicializado = true;
    vertice->nombre = nombre;
    // este color es solo temporal, cuando termine ConstrucciónDelGrafo
    // el mismo será distinto
    vertice->color_actual = 0;
    vertice->tam_array_vecinos = 1;

    // Tendrá a lo sumo 1 vecino, luego iremos agregando más vecinos
    vertice->vecinos = (Vertice *)malloc(sizeof(Vertice));
}


// Liberando memoria del vértice
void destruir_vertice(Vertice vertice) {
    free(vertice->vecinos);
    free(vertice);
}

// agregar el vecino B al vertice A (al final del array)
void agregar_vecino(Vertice A, Vertice B) {
    u32 posicion = A->cant_vecinos;

    if (posicion >= A->tam_array_vecinos) {
        // si el nuevo vecino se sale del array, expandirlo
        Vertice * vecinos;
        A->tam_array_vecinos += 4;
        vecinos = realloc(A->vecinos, A->tam_array_vecinos * sizeof(*A->vecinos));
        A->vecinos = vecinos;
    }

    A->vecinos[posicion] = B;
    A->cant_vecinos++;
}

// Útil para cuando se haya terminado de cargar los lados del vértice.
// por si quedó espacio asignado sin usar, i.e tam_array_vecinos > cant_vecinos.
// Se reallocara esa memoria sin usar
void optimizar_memoria(Vertice A) {
    Vertice * vecinos;
    vecinos = realloc(A->vecinos, A->cant_vecinos * sizeof(*A->vecinos));
    A->vecinos = vecinos;
}

void imprimirVecinos(Vertice vertice) {
    printf("Los vecinos del vertice %u son:\n", vertice->nombre);
    //Recorrer el arreglo de vecinos linealmente e imprimir los valores
    for (u32 i = 0; i < vertice->cant_vecinos; i++)
        printf("%u ", vertice->vecinos[i]->nombre);
    printf("\n");
}


int main() {
    // testing Vertice TAD  y sus operaciones
    Vertice v_A = (Vertice)malloc(sizeof(vertice_t));
    Vertice v_B = (Vertice)malloc(sizeof(vertice_t));
    Vertice v_C = (Vertice)malloc(sizeof(vertice_t));

    init_vertice(v_A, 232);
    init_vertice(v_B, 11);
    init_vertice(v_C, 33);

    agregar_vecino(v_A, v_B);
    agregar_vecino(v_A, v_C);

    agregar_vecino(v_B, v_A);
    agregar_vecino(v_C, v_B);


    imprimirVecinos(v_A);
    imprimirVecinos(v_B);
    imprimirVecinos(v_C);

    optimizar_memoria(v_A);

    destruir_vertice(v_A);
    destruir_vertice(v_B);
    destruir_vertice(v_C);

    // corriendo con valgrind, no tienen memory leaks las funciones

    return 0;
}

