#include "Rii.h"

u32 max(u32 a, u32 b) {
    if (a > b) {
        return a;
    }
    return b;
}

void decolorear(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; i++) {
        G->vertices[i]->coloreado = false;
        G->vertices[i]->color_actual = 0;
    }
    G->cant_colores = 0;
}

void colorear(Vertice V, u32 color) {
    V->coloreado = true;
    V->color_actual = color;
}


u32 Greedy(Grafo G) {
    decolorear(G);

    // cota superior de cantidad de vértices + 1 colores
    bool colores_usados[G->mayor_grado + 1];
    memset(colores_usados, false, (G->mayor_grado + 1) * sizeof(bool));

    // Coloreo el primer vértice con 0
    colorear(G->vertices[0], 0);
    u32 max_color = 0;

    for (u32 i = 1; i < G->cant_vertices; i++) {
        Vertice x = G->vertices[i];
        u32 color_x = 0;
        u32 max_color_usado = 0;

        // Recorriendo todos los vecinos de X
        for (u32 j = 0; j < x->grado; j++) {
            // x e y son vecinos
            Vertice y = x->vecinos[j];

            // Descartando posibles colores de x ya usados por vecinos
            if (y->coloreado) {
                if (y->color_actual > max_color_usado)
                    max_color_usado = y->color_actual;
                colores_usados[y->color_actual] = true;
            }
        }

        // Buscar el mínimo color no usado
        for (u32 color_vert = 0; color_vert < G->mayor_grado + 1; color_vert++) {
            if (!colores_usados[color_vert]) {
                color_x = color_vert;
                break;
            }
        }

        // Colorear al vértice
        colorear(x, color_x);
        // Actualizar si es que hay un nuevo color máximo
        max_color = max(max_color, color_x);

        // resetear el array de colores usados para el siguiente vértice
        memset(colores_usados, false, (max_color_usado + 1) * sizeof(bool));
    }

    G->cant_colores = (max_color + 1);
    // Como se empieza contando de cero la cantidad de colores es max_color + 1
    return (max_color + 1);
}

int Bipartito(Grafo G) {
    decolorear(G);

    // Variables útiles para el coloreo
    Cola q;
    Vertice x, p, vecino;
    // Comenzamos suponiendo que es bipartito
    G->cant_colores = 2;

    for (u32 j = 0; j < G->cant_vertices; j++) {
        x = G->vertices[j];

        // Si el vértice ya está coloreado no nos importa
        if (x->coloreado)
            continue;

        // Los colores van a ser 0 y 1
        colorear(x, 0);
        // Cola útil para BFS
        q = crear_cola(G->cant_vertices);

        if (q == NULL) {
            printf("Error al intentar alocar memoria!\n");
            return NULL;
        }

        encolar(q, x);

        while (!cola_vacia(q)) {
            // Obteniendo el primero de la cola
            p = decolar(q);

            // Recorriendo los vecinos del vértice decolado
            for (u32 i = 0; i < p->grado; i++) {
                vecino = p->vecinos[i];

                if (!vecino->coloreado) {
                    encolar(q, vecino);

                    // Coloreamos al vecino con el color opuesto a p
                    if (p->color_actual == 0)
                        colorear(vecino, 1);
                    else
                        colorear(vecino, 0);
                }
                else if (vecino->color_actual == p->color_actual) {
                    // El vértice p y su vecino tienen el mismo color
                    // i.e. el grafo no es bipartito
                    destruir_cola(q);
                    // Colorea al grafo con el orden actual
                    Greedy(G);
                    return 0;
                }
            }
        }
        // Termina con una componente conexa, destruimos la cola
        destruir_cola(q);
    }
    // Si llegó acá significa que el grafo fue coloreado con 2 colores
    // i.e. es bipartito
    return 1;
}
