typedef struct {
    bool                inicializado;
    bool                coloreado;
    u32                 nombre;
    u32                 color_actual;
    u32                 grado;
    u32                 cant_bloque;
    u32                 pos_ultimo_vecino;

    // Arreglo de indices a vértices vecinos
    u32*                indices_vecinos;
} VerticeSt;

typedef VerticeSt * Vertice;


Vertice ConstruirVertice(u32 nombre, u32 grado);

void DestruirVertice(Vertice V);
