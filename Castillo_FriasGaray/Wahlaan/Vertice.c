#include "Rii.h"


Vertice ConstruirVertice(u32 nombre, u32 grado)
{
    Vertice V = malloc(sizeof(struct VerticeSt));

    V->inicializado = true;
    V->coloreado = false;
    V->nombre = nombre;
    V->color_actual = 0;
    V->cant_bloque = 0;
    V->pos_ultimo_vecino = 0;
    V->grado = grado;
    V->indices_vecinos = (u32*) malloc(sizeof(u32) * grado);

    return V;
}

Vertice CopiarVertice(Vertice V) {
    Vertice copia = malloc(sizeof(struct VerticeSt));
    memcpy(copia, V, sizeof(struct VerticeSt));
    copia->indices_vecinos = malloc(sizeof(V->indices_vecinos));
    memcpy(copia->indices_vecinos, V->indices_vecinos, sizeof(u32) * V->grado);
    return copia;
}

void DestruirVertice(Vertice V) {
    free(V->indices_vecinos);
    free(V);
}
