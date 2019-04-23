#include "Rii.h"

/*
Construye un nuevo vertice y devuelve un puntero al mismo.
*/
Vertice ConstruirVertice(u32 nombre, u32 grado, u32 indice) {
    Vertice V = malloc(sizeof(struct VerticeSt));
    if (V == NULL) return NULL;

    // Inicializo la estructura
    V->inicializado = true;
    V->coloreado = false;
    V->nombre = nombre;
    V->color_actual = 0;
    V->cant_bloque = 0;
    V->pos_ultimo_vecino = 0;
    V->grado = grado;
    V->indice = indice;
    V->vecinos = (Vertice*) malloc(sizeof(Vertice) * grado);

    // Libero memoria si hay error
    if (V->vecinos == NULL) {
        free(V);
        return NULL;
    }
    return V;
}

void DestruirVertice(Vertice V) {
    // Libero la memoria
    free(V->vecinos);
    free(V);
}
