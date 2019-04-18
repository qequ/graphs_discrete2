typedef struct {
    u32 cant_vertices;
    u32 cant_lados;
    u32 cant_colores;

    Vertice* vertices;
} GrafoSt;

typedef GrafoSt * Grafo;


/* Construye un grafo a partir de stdin */
Grafo ConstruccionDelGrafo();

/* Destruye el grafo, liberando la memoria utilizada */
void DestruccionDelGrafo(Grafo G);

/* Crea una copia del grafo */
Grafo CopiarGrafo(Grafo G);

u32 AgregarVertice(Grafo G, u32 nombre_vertice, u32 grado);

int BuscarVertice(Grafo G, u32 nombre_vert);
