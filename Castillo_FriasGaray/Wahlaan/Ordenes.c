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
