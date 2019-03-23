#include "Rii.h"

// función para inicializar la estructura con info básica del grafo
Grafo init_grafo(u32 cant_vertices, u32 cant_lados) {
    Grafo grafo = NULL;

    grafo = malloc(sizeof(grafo_t));
    grafo->cant_vertices = cant_vertices;
    grafo->cant_lados = cant_lados;

    // allocando memoria para los vértices y sus punteros
    grafo->hash_table_vertices = (Vertice *)calloc(cant_vertices, sizeof(Vertice));
    for (u32 i = 0; i < grafo->cant_vertices; i++) {
        grafo->hash_table_vertices[i] = (Vertice)malloc(sizeof(vertice_t));
        grafo->hash_table_vertices[i]->inicializado = false;
    }

    grafo->orden_actual = (Vertice *)malloc(grafo->cant_vertices * sizeof(Vertice));

    return grafo;
}
