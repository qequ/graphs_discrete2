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
        vertices_repetidos[2 * i] = vert_1;
        vertices_repetidos[2 * i + 1] = vert_2;
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
            // Cuando agrego un vértice ya se el grado
            AgregarVertice(G, vertices_repetidos[i], cant_vecinos);

            if (cant_vecinos > G->mayor_grado) G->mayor_grado = cant_vecinos;

            cant_vecinos = 1;
        } else
            cant_vecinos++;
    }
    AgregarVertice(G, vertices_repetidos[i], cant_vecinos);

    // Libero el arreglo auxiliar
    free(vertices_repetidos);

    Vertice vecino, vert;

    // Agrego los vecinos
    for (u32 i = 0; i < cant_lados; ++i) {
        vert = G->vertices[BuscarVertice(G, lados[2 * i])];
        vecino = G->vertices[BuscarVertice(G, lados[2 * i + 1])];

        AgregarVecino(vert, vecino);
        AgregarVecino(vecino, vert);
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
    Grafo G2 = malloc(sizeof(GrafoSt));
    memcpy(G2, G, sizeof(GrafoSt));
    G2->vertices = malloc(sizeof(G->vertices));
    memcpy(G2->vertices, G->vertices, sizeof(u32) * G->cant_vertices);
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


u32 AgregarVertice(Grafo G, u32 nombre_vertice, u32 grado) {
    u32 i_vertice;

    G->vertices[G->cant_vertices] = ConstruirVertice(nombre_vertice, grado);
    i_vertice = G->cant_vertices;
    ++G->cant_vertices;
    return i_vertice;
}

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
