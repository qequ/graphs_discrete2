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

int BuscarVertice(Grafo G, u32 nombre_vert);
