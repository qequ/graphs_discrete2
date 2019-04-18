#include "Rii.h"


int comparar_nombres_creciente(const void * v1, const void * v2) {
    if (((*(Vertice*)v1)->nombre) > ((*(Vertice*)v2)->nombre)) {
        return 1;
    }
    else {
        return 0;
    }
}


char OrdenNatural(Grafo G) {
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_nombres_creciente);
    return 0;
}

int comparar_grados_decreciente(const void * v1, const void * v2) {
    if (((*(Vertice*)v1)->grado) < ((*(Vertice*)v2)->grado)) {
        return 1;
    }
    else if (((*(Vertice*)v1)->grado) > ((*(Vertice*)v2)->grado)) {
        return -1;
    }
    else {
        return 0;
    }
}


char OrdenWelshPowell(Grafo G) {
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_grados_decreciente);
    return 0;
}


char SwitchVertices(Grafo G,u32 i,u32 j) {
    if (i >= G->cant_vertices || j >= G->cant_vertices) return 1;

    // Swap vertices
    Vertice tmp = G->vertices[i];
    G->vertices[i] = G->vertices[j];
    G->vertices[j] = tmp;
    return 0;
}

char SwitchColores(Grafo G,u32 i,u32 j) {
    if (i >= G->cant_colores || j >= G->cant_colores) return 1;

    for (u32 k = 0; k < G->cant_vertices; ++k) {
        if (G->vertices[k]->color_actual == i)
            G->vertices[k]->color_actual = j;
        else if (G->vertices[k]->color_actual == j)
            G->vertices[k]->color_actual = i;
    }
    return 0;
}

int comparar_colores_creciente(const void * v1, const void * v2) {
    if (((*(Vertice*)v1)->color_actual) > ((*(Vertice*)v2)->color_actual))
        return 1;
    else
        return 0;
}

int comparar_colores_decreciente(const void * v1, const void * v2) {
    if (((*(Vertice*)v1)->color_actual) < ((*(Vertice*)v2)->color_actual))
        return 1;
    else
        return 0;
}

char RMBCnormal(Grafo G) {
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_colores_creciente);
    return 0;
}

char RMBCrevierte(Grafo G) {
    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_colores_decreciente);
    return 0;
}

int comparar_cant_bloque_creciente(const void * a, const void * b) {
    Vertice v1 = (*(Vertice*)a);
    Vertice v2 = (*(Vertice*)b);

    if (v1->color_actual == v2->color_actual)
        return 0;

    return v2->cant_bloque - v1->cant_bloque;
}

char RMBCchicogrande(Grafo G) {
    u32 *cantidad_por_color = calloc(G->cant_colores, sizeof(u32));
    if (cantidad_por_color == NULL) return 1;

    for (u32 k = 0; k < G->cant_vertices; ++k)
        cantidad_por_color[G->vertices[k]->color_actual]++;

    for (u32 k = 0; k < G->cant_vertices; ++k)
        G->vertices[k]->cant_bloque = cantidad_por_color[G->vertices[k]->color_actual];

    free(cantidad_por_color);

    qsort(G->vertices, G->cant_vertices, sizeof(Vertice), comparar_cant_bloque_creciente);
    return 0;
}


// TODO: agregar test para ordenamientos
