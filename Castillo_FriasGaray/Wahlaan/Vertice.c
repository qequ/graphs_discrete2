#include "Rii.h"


Vertice ConstruirVertice(u32 nombre, u32 grado)
{
    Vertice V = malloc(sizeof(VerticeSt));

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

void DestruirVertice(Vertice V) {
    free(V->indices_vecinos);
    free(V);
}
