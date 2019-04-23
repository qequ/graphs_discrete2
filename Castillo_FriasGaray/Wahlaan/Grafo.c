#include "Rii.h"


/* Construye un grafo a partir de stdin */
Grafo ConstruccionDelGrafo() {
    u32 vert_1, vert_2, cant_vertices, cant_lados;
    u32 *vertices_repetidos, *lados;
    Grafo G;
    char c;

    // Se ignoran los comentarios iniciales
    while((c = getchar()) == 'c')
        while (getchar() != '\n')
            ;

    if (c != 'p'){
        printf("Formato incorrecto!\n");
        return NULL;
    }

    // Ya tenemos la p, buscamos una línea de la forma: `p edge x y`
    if(scanf(" edge %u %u\n", &cant_vertices, &cant_lados) <= 0){
        printf("Formato incorrecto!\n");
        return NULL;
    }
    printf("Cantidad de vertices: %u\nCantidad de lados: %u\n", cant_vertices, cant_lados);

    // Pedimos memoria para guardar la estructura de grafo.
    // Calloc rellena con ceros la estructura.
    G = calloc(1, sizeof(GrafoSt));

    if(G == NULL){
        printf("Error al intentar alocar memoria!\n");
        return NULL;
    }

    // Pedimos memoria para cargar los vértices
    G->vertices = (Vertice*) malloc(sizeof(Vertice) * cant_vertices);

    // Pedimos memoria para el auxiliar de vértices con repeticiones
    vertices_repetidos = (u32*) malloc(sizeof(u32) * cant_lados * 2);

    if(G->vertices == NULL || vertices_repetidos == NULL){
        printf("Error al intentar alocar memoria!\n");
        free(vertices_repetidos);
        free(G->vertices);
        free(G);
        return NULL;
    }

    for (u32 i = 0; i < cant_lados; ++i) {
        // Leemos líneas de la forma: `e vertice1 vertice2`
        if (scanf("e %u %u\n", &vert_1, &vert_2) <= 0) {
            printf("Formato incorrecto!\n");
            free(vertices_repetidos);
            free(G->vertices);
            free(G);
            return NULL;
        }

        // Se guardan todos los nombres de vértices en el arreglo auxiliar
        // de manera que queden pares [ |x1 y1|  |x2 y2|  ...  |xn yn| ]
        vertices_repetidos[2*i] = vert_1;
        vertices_repetidos[2*i + 1] = vert_2;
    }

    // Pedimos memoria para arreglo auxiliar de lados
    lados = (u32*) malloc(sizeof(u32) * cant_lados * 2);

    if (lados == NULL) {
        printf("Error al intentar alocar memoria!\n");
        free(vertices_repetidos);
        free(G->vertices);
        free(G);
        return NULL;
    }
    // Copio el arreglo
    for (u32 i = 0; i < cant_lados * 2; ++i)
        lados[i] = vertices_repetidos[i];

    // Ordenamiento de vértices
    qsort(vertices_repetidos, cant_lados * 2, sizeof(u32), CompararU32);

    G->mayor_grado = 1;

    u32 cant_vecinos = 1;
    u32 i = 0;

    // Se agregan los demás vértices sin repeticiones
    for (; i < (cant_lados * 2) - 1; ++i) {
        if (vertices_repetidos[i] != vertices_repetidos[i + 1]) {
            // Cuando agrego un vértice ya conozco el grado,
            // construyo un nuevo vertice con su respectiva cantidad de vecinos
            // y utilizando la cantidad de vertices del grafo como contador,
            // a medida que voy creando mas vertices.
            G->vertices[G->cant_vertices] = ConstruirVertice(vertices_repetidos[i], cant_vecinos, G->cant_vertices);

            // Libero memoria si hay error
            if (G->vertices[G->cant_vertices] == NULL){
                printf("Error al intentar alocar memoria!\n");
                free(lados);
                free(vertices_repetidos);
                DestruccionDelGrafo(G);
                return NULL;
            }
            // Aumento el contador de vertices
            ++G->cant_vertices;

            // Actualizo delta (el mayor grado del grafo) si es necesario
            if (cant_vecinos > G->mayor_grado) G->mayor_grado = cant_vecinos;
            // Reseteo la cantidad de vecinos
            cant_vecinos = 1;
        } else
            cant_vecinos++;
    }
    // Repito lo anterior para el último:
    // Construyo el último vertice.
    G->vertices[G->cant_vertices] = ConstruirVertice(vertices_repetidos[i], cant_vecinos, G->cant_vertices);

    if (G->vertices[G->cant_vertices] == NULL) {
        printf("Error al intentar alocar memoria!\n");
        free(lados);
        free(vertices_repetidos);
        DestruccionDelGrafo(G);
        return NULL;
    }
    ++G->cant_vertices;

    // Libero el arreglo auxiliar
    free(vertices_repetidos);

    Vertice v1, v2;
    u32 indice1, indice2;

    // Agrego los vecinos
    for (u32 i = 0; i < cant_lados; ++i) {
        indice1 = BuscarVertice(G, lados[2*i]);
        indice2 = BuscarVertice(G, lados[2*i + 1]);

        v1 = G->vertices[indice1];
        v2 = G->vertices[indice2];

        v1->vecinos[v1->pos_ultimo_vecino] = v2;
        ++v1->pos_ultimo_vecino;

        v2->vecinos[v2->pos_ultimo_vecino] = v1;
        ++v2->pos_ultimo_vecino;
    }

    // Libero el arreglo auxiliar de lados
    free(lados);

    G->cant_lados = cant_lados;

    // Coloreo G usando Greedy
    printf("Coloreando con Greedy...\n");
    G->cant_colores = Greedy(G);
    printf("Coloreado con %u colores\n", G->cant_colores);
    return G;
}

/* Destruye el grafo, liberando la memoria utilizada */
void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->cant_vertices; ++i)
        DestruirVertice(G->vertices[i]);

    free(G->vertices);
    free(G);
}

Grafo CopiarGrafo(Grafo G) {
    // Pido memoria para un grafo
    Grafo G2 = malloc(sizeof(GrafoSt));
    if (G2 == NULL) {
        printf("Error al intentar alocar memoria!\n");
        return NULL;
    }
    // Copio la estructura del grafo
    memcpy(G2, G, sizeof(GrafoSt));

    // Pido memoria para el arreglo de vertices
    G2->vertices = malloc(sizeof(Vertice) * G->cant_vertices);
    if (G2->vertices == NULL) {
        printf("Error al intentar alocar memoria!\n");
        free(G2);
        return NULL;
    }
    // Copio todos los vertices
    memcpy(G2->vertices, G->vertices, sizeof(Vertice) * G->cant_vertices);

    for (u32 i = 0; i < G->cant_vertices; ++i) {
        // Pido memoria para un nuevo vertice
        G2->vertices[i] = malloc(sizeof(struct VerticeSt));

        if (G2->vertices[i] == NULL) {
            printf("Error al intentar alocar memoria!\n");
            // Libero la memoria
            for (u32 k = 0; k < i; ++k)
                DestruirVertice(G2->vertices[k]);
            free(G2->vertices);
            free(G2);
            return NULL;
        }
        // Copio la estructura de vertice
        memcpy(G2->vertices[i], G->vertices[i], sizeof(struct VerticeSt));

        // Pido memoria para el arreglo de vecinos
        G2->vertices[i]->vecinos = malloc(sizeof(Vertice) * G->vertices[i]->grado);

        if (G2->vertices[i]->vecinos == NULL) {
            printf("Error al intentar alocar memoria!\n");
            // Libero la memoria
            for (u32 k = 0; k <= i; ++k)
                DestruirVertice(G2->vertices[k]);
            free(G2->vertices);
            free(G2);
            return NULL;
        }
        // Copio el arreglo de punteros a vecinos
        memcpy(G2->vertices[i]->vecinos, G->vertices[i]->vecinos, sizeof(Vertice) * G->vertices[i]->grado);

    }
    // En este punto, todos los vecinos apuntan a los vertices de G,
    // Cambiemos esos punteros
    for (u32 i = 0; i < G->cant_vertices; ++i)
        for (u32 j = 0; j < G2->vertices[i]->grado; ++j) {
            Vertice vecino = G->vertices[i]->vecinos[j];

            G2->vertices[i]->vecinos[j] = G2->vertices[vecino->indice];
        }

    return G2;
}

int CompararU32(const void * a, const void * b) {
    u32 primero = *(u32*) a;
    u32 segundo = *(u32*) b;
    return primero >= segundo;
}

// ----------Funciones para extraer info de los grafos----//

/* Devuelve la cantidad de vértices de un grafo G */
u32 NumeroDeVertices(Grafo G) {
    return G->cant_vertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->cant_lados;
}

u32 NumeroDeColores(Grafo G) {
    return G->cant_colores;
}

// ----------Funciones para extraer info de los vértices----//

u32 NombreDelVertice(Grafo G, u32 i) {
    return G->vertices[i]->nombre;
}

u32 ColorDelVertice(Grafo G, u32 i) {
    if (i >= G->cant_vertices) {
        return (MAX_U32);
    }

    return (G->vertices[i]->color_actual);
}


u32 GradoDelVertice(Grafo G, u32 i) {
    if (i >= G->cant_vertices) {
        return (MAX_U32);
    }

    return (G->vertices[i]->grado);
}

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j) {
    if (i >= G->cant_vertices) {
        return (MAX_U32);
    }

    if (j >= GradoDelVertice(G, i)) {
        return (MAX_U32);
    }

    return (G->vertices[i]->vecinos[j]->color_actual);
}

u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j) {
    return G->vertices[i]->vecinos[j]->nombre;
}

u32 GradoJotaesimoVecino(Grafo G, u32 i, u32 j) {
    return G->vertices[i]->vecinos[j]->grado;
}

/*
Busqueda binaria en arreglo de vertices del grafo
Asume que el mismo está ordenado.
*/
int BuscarVertice(Grafo G, u32 nombre_vert) {
    int bajo;
    int alto;
    int mitad = 0;
    bool encontrado = false;

    bajo = 0;
    alto = G->cant_vertices - 1;

    while (bajo <= alto && !encontrado) {
        mitad = (alto + bajo) / 2;

        if (nombre_vert == G->vertices[mitad]->nombre)
            encontrado = 1;
        else if (nombre_vert < G->vertices[mitad]->nombre)
            alto = mitad - 1;
        else
            bajo = mitad + 1;
    }

    if (encontrado)
        return mitad;
    else
        return -1;
}
