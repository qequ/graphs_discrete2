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


int Bipartito(Grafo G) {
    decolorear(G);

    // Variables útiles para el coloreo
    Cola q;
    Vertice x, p, vecino;
    // Comenzamos suponiendo que es bipartito
    G->coloreo_actual = 2;

    for (u32 j = 0; j < G->cant_vertices; j++) {
        x = G->orden_actual[j];

        // Si el vértice ya está coloreado no nos importa
        if (x->coloreado) {
            continue;
        }

        // Los colores van a ser 0 y 1
        colorear(x, 0);
        // Cola útil para BFS
        q = crear_cola(G->cant_vertices);
        encolar(q, x);

        while (!cola_vacia(q)) {
            // Obteniendo el primero de la cola
            p = decolar(q);

            // Recorriendo los vecinos del vértice decolado
            for (u32 i = 0; i < p->cant_vecinos; i++) {
                vecino = p->vecinos[i];

                if (!vecino->coloreado) {
                    encolar(q, vecino);

                    // Coloreamos al vecino con el color opuesto a p
                    if (p->color_actual == 0) {
                        colorear(vecino, 1);
                    }
                    else {
                        colorear(vecino, 0);
                    }
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


int main() {
    Grafo G = ConstruccionDelGrafo();

/*
    int bip = Bipartito(G);
    if (bip == 1) {
        printf("Es bipartito\n");
    }
    else {
        printf("No es bipartito\n");
    }
*/

    OrdenNatural(G);
    printf("Orden natural según nombre\n");
    for (u32 i = 0; i < G->cant_vertices - 1; i++) {
        if (G->orden_actual[i]->nombre > G->orden_actual[i+1]->nombre) {
            printf("mal ordenado\n");
        }
    }

    printf("all right\n");

    u32 coloreo_orden_nat = Greedy(G);
    printf("Cantidad de colores en orden natural: %u\n", coloreo_orden_nat);

    OrdenWelshPowell(G);

    printf("Orden WelshPowell\n");
    for (u32 i = 0; i < G->cant_vertices - 1; i++) {
        if (G->orden_actual[i]->cant_vecinos < G->orden_actual[i+1]->cant_vecinos) {
            printf("mal ordenado\n");
        }
    }
    printf("all right wp\n");

    u32 coloreo_wp = Greedy(G);

    printf("Cantidad de colores en WelshPowell: %u\n", coloreo_wp);

    return 0;
}