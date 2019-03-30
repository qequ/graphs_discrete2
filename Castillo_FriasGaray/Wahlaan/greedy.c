#include "Rii.h"

u32 max(u32 a, u32 b) {
    if (a > b) {
        return a;
    }
    return b;
}

void decolorear(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; i++) {
        G->hash_table_vertices[i]->coloreado = false;
        G->hash_table_vertices[i]->color_actual = 0;
    }
    G->coloreo_actual = 0;
}

void colorear(Vertice V, u32 color) {
    V->coloreado = true;
    V->color_actual = color;
}

u32 Greedy(Grafo G) {
    decolorear(G);

    // cota superior de cantidad de vértices + 1 colores
    bool colores_usados[G->cant_vertices + 1];
    memset(colores_usados, false, (G->cant_vertices + 1)*sizeof(bool));

    colorear(G->orden_actual[0], 0);
    u32 max_color = 0;

    for (u32 i = 1; i < G->cant_vertices; i++) {
        Vertice x = G->orden_actual[i];
        u32 color_x = 0;

        // Recorriendo todos los vecinos de X
        for (u32 j = 0; j < x->cant_vecinos; j++) {
            // x e y son vecinos
            Vertice y = x->vecinos[j];

            // Descartando posibles colores de x ya usados por vecinos
            if (y->coloreado) {
                colores_usados[y->color_actual] = true;
            }
        }

        // Buscar el mínimo color no usado
        for (u32 color_vert = 0; color_vert < G->cant_vertices + 1; color_vert++) {
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
        memset(colores_usados, false, (G->cant_vertices + 1)*sizeof(bool));
    }

    G->coloreo_actual = (max_color + 1);
    // Como se empieza contando de cero la cantidad de colores es max_color + 1
    return (max_color + 1);
}


int main() {
    Grafo g = ConstruccionDelGrafo();
    //dumpear_hash_table(g);
    u32 coloreo;

    coloreo = Greedy(g);

    if (coloreo > g->cant_vertices + 1) {
        printf("Esto no debería pasar\n");
    }
    else printf("coloreo razonable\n");

    printf("cant vertices: %u\n",g->cant_vertices );

    return 0;
}