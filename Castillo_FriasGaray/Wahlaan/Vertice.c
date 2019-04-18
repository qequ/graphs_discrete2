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
    V->vecinos = (Vertice*) malloc(sizeof(Vertice) * grado);

    return V;
}

void DestruirVertice(Vertice V) {
    free(V->vecinos);
    free(V);
}

void AgregarVecino(Vertice V, Vertice vecino) {
    V->vecinos[V->pos_ultimo_vecino] = vecino;
    ++V->pos_ultimo_vecino;
}
