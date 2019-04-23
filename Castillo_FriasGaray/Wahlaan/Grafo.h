typedef struct {
    u32 cant_vertices;
    u32 cant_lados;
    u32 cant_colores;
    u32 mayor_grado;

    Vertice* vertices;
} GrafoSt;

typedef GrafoSt * Grafo;


/* Construye un grafo a partir de stdin */
Grafo ConstruccionDelGrafo();

/* Destruye el grafo, liberando la memoria utilizada */
void DestruccionDelGrafo(Grafo G);

/* Crea una copia del grafo */
Grafo CopiarGrafo(Grafo G);


// Funciones para extraer información de los grafos

/* Devuelve la cantidad de vértices de un grafo G */
u32 NumeroDeVertices(Grafo G);

/* Devuelve la cantidad de lados de un grafo G */
u32 NumeroDeLados(Grafo G);

/* Devuelve la cantidad de colores presentes en un grafo G */
u32 NumeroDeColores(Grafo G);


u32 NombreDelVertice(Grafo G, u32 i);

u32 ColorDelVertice(Grafo G, u32 i);

u32 GradoDelVertice(Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);


int CompararU32(const void * a, const void * b);

int BuscarVertice(Grafo G, u32 nombre_vert);

