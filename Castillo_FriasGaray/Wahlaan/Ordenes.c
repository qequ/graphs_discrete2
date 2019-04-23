#include "Rii.h"


int comparar_nombres_creciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v1->nombre > v2->nombre)
        return 1;
    else if (v1->nombre < v2->nombre)
        return -1;
    else
        return 0;
}

char OrdenNatural(Grafo G) {
    // Ordeno el arreglo de vértices en base al nombre creciente
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_nombres_creciente);

    // Actualizo los indices
    ActualizarIndicesDeVertices(G);
    return 0;
}

int comparar_grados_decreciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v2->grado > v1->grado)
        return 1;
    else if (v2->grado > v1->grado)
        return -1;
    else
        return 0;
}


char OrdenWelshPowell(Grafo G) {
    // Ordeno el arreglo de vértices en base al grado decreciente
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_grados_decreciente);

    // Actualizo los indices
    ActualizarIndicesDeVertices(G);
    return 0;
}


char SwitchVertices(Grafo G, u32 i, u32 j) {
    if (i >= G->cant_vertices || j >= G->cant_vertices) return 1;

    // Swap vertices
    Vertice tmp = G->vertices[i];
    G->vertices[i] = G->vertices[j];
    G->vertices[j] = tmp;

    // Actualizo índices
    G->vertices[i]->indice = i;
    G->vertices[j]->indice = j;

    return 0;
}

char SwitchColores(Grafo G, u32 i, u32 j) {
    if (i >= G->cant_colores || j >= G->cant_colores) return 1;

    for (u32 k = 0; k < G->cant_vertices; ++k) {
        if (G->vertices[k]->color_actual == i)
            G->vertices[k]->color_actual = j;
        else if (G->vertices[k]->color_actual == j)
            G->vertices[k]->color_actual = i;
    }
    return 0;
}

int comparar_colores_creciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v1->color_actual > v2->color_actual)
        return 1;
    else if (v1->color_actual < v2->color_actual)
        return -1;
    else
        return 0;
}

int comparar_colores_decreciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v2->color_actual > v1->color_actual)
        return 1;
    else if (v2->color_actual < v1->color_actual)
        return -1;
    else
        return 0;
}

char RMBCnormal(Grafo G) {
    // Ordeno el arreglo de vértices en base al color creciente
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_colores_creciente);

    // Actualizo los indices
    ActualizarIndicesDeVertices(G);
    return 0;
}

char RMBCrevierte(Grafo G) {
    // Ordeno el arreglo de vértices en base al color decreciente
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_colores_decreciente);

    // Actualizo los indices
    ActualizarIndicesDeVertices(G);
    return 0;
}

int comparar_cant_bloque_creciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v1->cant_bloque > v2->cant_bloque) return 1;
    if (v1->cant_bloque < v2->cant_bloque) return -1;

    if (v1->color_actual > v2->color_actual)
        return 1;
    else if (v1->color_actual < v2->color_actual)
        return -1;
    else
        return 0;
}

char RMBCchicogrande(Grafo G) {
    // Pido memoria para un arreglo auxiliar de cantidad de vertices por colores
    u32 *cantidad_por_color = calloc(G->cant_colores, sizeof(u32));

    if (cantidad_por_color == NULL) {
        printf("Error al intentar alocar memoria!\n");
        return 1;
    }

    for (u32 k = 0; k < G->cant_vertices; ++k)
        cantidad_por_color[G->vertices[k]->color_actual]++;

    for (u32 k = 0; k < G->cant_vertices; ++k)
        G->vertices[k]->cant_bloque = cantidad_por_color[G->vertices[k]->color_actual];

    // Libero arreglo auxiliar
    free(cantidad_por_color);

    // Ordeno el arreglo de vértices en base a bloques de colores con cardinalidad creciente
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_cant_bloque_creciente);

    // Actualizo los indices
    ActualizarIndicesDeVertices(G);
    return 0;
}


void ActualizarIndicesDeVertices(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; ++i)
        G->vertices[i]->indice = i;
}
