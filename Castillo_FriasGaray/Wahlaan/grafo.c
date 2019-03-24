#include "Rii.h"


void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; i++) {
        // Si está inicializado hay que utilizar la función destruir_vertice
        // ya que init_vertice usa un malloc para el array de vecinos
        if (G->hash_table_vertices[i]->inicializado) {
            destruir_vertice(G->hash_table_vertices[i]);
        }
        else {
        free(G->hash_table_vertices[i]);
        }
    }
    free(G->hash_table_vertices);
    free(G->orden_actual);
    free(G);
    printf("Liberada toda la memoria\n");
}


void agregar_lado(Grafo graf, u32 nombre_vert_a, u32 nombre_vert_b) {
    // Buscando las posiciones de los vértices en la hash table
    u32 posicion_vert_a = obtener_posicion_vertice(graf, nombre_vert_a);
    u32 posicion_vert_b = obtener_posicion_vertice(graf, nombre_vert_b);

    // Recuperando los vértices
    Vertice vert_a = graf->hash_table_vertices[posicion_vert_a];
    Vertice vert_b = graf->hash_table_vertices[posicion_vert_b];

    // agregar vértices como vecinos entre si(dado que es grafo no dirigido)
    agregar_vecino(vert_a, vert_b);
    agregar_vecino(vert_b, vert_a);
}


bool hay_vertices_no_inicializados(Grafo graf) {
    for (u32 i = 0; i < graf->cant_vertices; i++) {
        if (!graf->hash_table_vertices[i]->inicializado) {
            return true;
        }
    }
    return false;
}


void optimizar_hash_table(Grafo graf) {
    for (u32 i = 0; i < graf->cant_vertices; i++) {
        optimizar_memoria(graf->hash_table_vertices[i]);
    }
}

void dumpear_hash_table(Grafo g) {
    for (u32 i = 0; i < g->cant_vertices; i++) {
        printf("en posicion %u del hash table:\n", i);
        printf("nombre vertice: %u\n", g->hash_table_vertices[i]->nombre);
        printf("Vecinos:\n");
        imprimirVecinos(g->hash_table_vertices[i]);
    }
}



Grafo ConstruccionDelGrafo() {
    Grafo grafo;
    u32 cant_vertices, cant_lados;
    char check_edge[4];
    char c;

    // Saltando los comentarios
    while ((c = getchar()) == 'c') {
        while ((c = getchar()) != '\n') {
            ;
        }
    }

    // Chequeando la línea "p edge x y"
    if (c != 'p') {
        printf("error en primera linea sin comentario\n");
        return NULL;
    }
    if (scanf("%s", check_edge) != 1) return NULL;
    if (strcmp(check_edge, "edge") != 0) {
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    if (scanf("%u", &cant_vertices) != 1) return NULL;
    if (scanf("%u", &cant_lados) != 1) return NULL;

    // Allocando grafo
    grafo = malloc(sizeof(grafo_t));
    // Si falla allocando memoria
    if (grafo == NULL) return NULL;

    grafo->cant_vertices = cant_vertices;
    grafo->cant_lados = cant_lados;
    grafo->hash_table_vertices = (Vertice *)calloc(cant_vertices, sizeof(Vertice));

    if (grafo->hash_table_vertices == NULL) {
        printf("fallo al allocar memoria\n");
        free(grafo);
        return NULL;
    }

    // Añadiendo vértices sin inicializar a la hash table
    for (u32 i = 0; i < grafo->cant_vertices; i++) {
        grafo->hash_table_vertices[i] = (Vertice)malloc(sizeof(vertice_t));

        // Liberar toda la memoria ocupada si falla al allocar
        if ((grafo->hash_table_vertices[i]) == NULL) {
            printf("fallo al allocar memoria\n");

            for (u32 j = 0; j < i; j++) {
                // Liberar cada struct de vertice hasta el momento
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
        // Liberando toda la memoria
        for (u32 i = 0; i < grafo->cant_vertices; i++) {
            free(grafo->hash_table_vertices[i]);
        }
        free(grafo->hash_table_vertices);
        free(grafo);
        return NULL;
    }

    // Una vez que terminó de allocar las estructuras empieza a tomar lados

    // Nombre de los vértices que conforman el lado
    u32 nombre_vert_a, nombre_vert_b;

    // Calcular el primo para la hash_table(se hace acá para no tener que
    // calcularlo cada vez que buscamos un lado)
    //u32 primo_hash = obtener_primo_para_hash(grafo->cant_vertices);

    for (u32 i = 0; i < grafo->cant_lados; i++) {
        if (scanf("%*s") != 0) {
            DestruccionDelGrafo(grafo);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }

        if (scanf("%u", &nombre_vert_a) != 1) {
            DestruccionDelGrafo(grafo);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }
        if (scanf("%u", &nombre_vert_b) != 1) {
            DestruccionDelGrafo(grafo);
            printf("Error de lectura en %u\n", i+1);
            return NULL;
        }

        agregar_lado(grafo, nombre_vert_a, nombre_vert_b);
    }


    // chequeando que el total de vértices extraido es n
    if (hay_vertices_no_inicializados(grafo)) {
        printf("cantidad de vertices leidos no es la declarada\n");
        return NULL;
    }

    // liberando espacio sin usar(si quedó) de array de vecinos de cada vértice
    optimizar_hash_table(grafo);

    // Copiando punteros de hash_table a array de orden
    // memcpy(grafo->orden, grafo->hashTable, grafo->cantVertices * sizeof(Vertice));
    if (memcpy(grafo->orden_actual, grafo->hash_table_vertices, grafo->cant_vertices * sizeof(Vertice)) == NULL) {
        printf("fallo al copiar hash table\n");
        return NULL;
    }


    // Correr greedy

    return grafo;
}


Grafo CopiarGrafo(Grafo G) {

    Grafo grafo = malloc(sizeof(grafo_t));
    memcpy(grafo, G, sizeof(grafo_t));

    return grafo;
}


u32 NumeroDeVertices(Grafo G) {
    return (G->cant_vertices);
}


u32 NumeroDeLados(Grafo G) {
    return (G->cant_lados);
}


u32 NumeroDeColores(Grafo G) {
    return (G->coloreo_actual);
}


u32 NombreDelVertice(Grafo G, u32 i) {
    return (G->orden_actual[i]->nombre);
}

u32 ColorDelVertice(Grafo G, u32 i) {
    if (i >= G->cant_vertices) {
        return (pow(2, 32) - 1);
    }

    return (G->orden_actual[i]->color_actual);
}


u32 GradoDelVertice(Grafo G, u32 i) {
    if (i >= G->cant_vertices) {
        return (pow(2, 32) - 1);
    }

    return (G->orden_actual[i]->cant_vecinos);
}


u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j) {
    if (i >= G->cant_vertices) {
        return (pow(2, 32) - 1);
    }

    if (j >= GradoDelVertice(G, i)) {
        return (pow(2, 32) - 1);
    }

    return (G->orden_actual[i]->vecinos[j]->color_actual);
}


u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j) {
    return (G->orden_actual[i]->vecinos[j]->nombre);
}