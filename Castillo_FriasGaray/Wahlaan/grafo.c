#include "Rii.h"


u32 pot(u32 x, u32 y) {
    u32 res = 1;

    while (y > 0) {
        if (y & 1)
            res = res * x;

        y = y >> 1;
        x = x * x;
    }
    return res;
}


u32 obtener_primo_para_hash(u32 cant_vertices) {
    // conjunto de primos útil para hash.
    // valores de primos obtenidos de;
    // https://planetmath.org/goodhashtableprimes
    u32 primos[31] = {
        2,
        3,
        5,
        7,
        23,
        53,
        97,
        193,
        389,
        769,
        1543,
        3079,
        6151,
        12289,
        24593,
        49157,
        98317,
        196613,
        393241,
        786433,
        1572869,
        3145739,
        6291469,
        12582917,
        25165843,
        50331653,
        100663319,
        201326611,
        402653189,
        805306457,
        1610612741
    };

    for (u32 i = 1; i < 30; i++) {
        if (cant_vertices >= pot(2, i) && cant_vertices <= pot(2, i+1)) {
            return primos[i-1];
        }
    }
    return primos[30];
}



void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; i++) {
        free(G->hash_table_vertices[i]);
    }
    free(G->hash_table_vertices);
    free(G->orden_actual);
    free(G);
    printf("Liberada toda la memoria\n");
}


Grafo ConstruccionDelGrafo() {
    Grafo grafo;
    u32 cant_vertices, cant_lados;
    char check_edge[4];

    // saltando los comentarios
    while ((c = getchar()) == 'c') {
        while ((c = getchar()) != '\n') {
            ;
        }
    }

    if (c != 'p') {
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    //if (scanf("%*s") != 0) return NULL;
    if (scanf("%s", check_edge) != 1) return NULL;
    if (strcmp(check_edge, "edge") != 0) {
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    if (scanf("%u", &cant_vertices) != 1) return NULL;
    if (scanf("%u", &cant_lados) != 1) return NULL;

    // allocando estructuras
    grafo = malloc(sizeof(grafo_t));
    // si falla allocando memoria
    if (grafo == NULL) return NULL;

    grafo->cant_vertices = cant_vertices;
    grafo->cant_lados = cant_lados;

    grafo->hash_table_vertices = (Vertice *)calloc(cant_vertices, sizeof(Vertice));
    if (grafo->hash_table_vertices == NULL) {
        printf("fallo al allocar memoria\n");
        free(grafo);
        return NULL;
    }
    for (u32 i = 0; i < grafo->cant_vertices; i++) {
        grafo->hash_table_vertices[i] = (Vertice)malloc(sizeof(vertice_t));

        // liberar toda la memoria ocupada
        if ((grafo->hash_table_vertices[i]) == NULL) {
            printf("fallo al allocar memoria\n");

            for (u32 j = 0; j < i; j++) {
                // liberar cada struct de vertice hasta el momento
                free(grafo->hash_table_vertices[j]);
            }
            free(grafo->hash_table_vertices);
            free(grafo);

            return NULL;
        }

        grafo->hash_table_vertices[i]->inicializado = false;
    }

    grafo->orden_actual = (Vertice *)malloc(grafo->cant_vertices * sizeof(Vertice));

    if (grafo->orden_actual == NULL) {
        // liberando toda la memoria
        for (u32 i = 0; i < grafo->cant_vertices; i++) {
            free(grafo->hash_table_vertices[i]);
        }
        free(grafo->hash_table_vertices);
        free(grafo);
        return NULL;
    }

    // una vez que terminó de allocar las estructuras empieza a tomar lados

    u32 vert_a, vert_b;
    // nombre de los vértices que conforman el lado
    for (u32 i = 0; i < grafo->cant_lados; i++) {
        if (scanf("%*s") != 0) {
            DestruccionDelGrafo(G);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }

        if (scanf("%u", &vert_a) != 1) {
            DestruccionDelGrafo(G);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }
        if (scanf("%u", &vert_b) != 1) {
            DestruccionDelGrafo(G);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }

        // obtener posicion vert_a()
        // obtener posicion vert_b()
        // poner a vert_a como vecino de vert_b
        // poner a vert_b como vecino de vert_a
    }

    // copiar hash table a dirección de orden

    // correr greedy



}