struct VerticeSt {
    bool                inicializado;
    bool                coloreado;
    u32                 nombre;
    u32                 color_actual;
    u32                 grado;
    u32                 ultvecino_i;

    // Arreglo de punteros a vértices vecinos
    struct VerticeSt**  vecinos;
};

typedef struct VerticeSt * Vertice;


void init_vertice(Vertice vertice, u32 nombre);

void destruir_vertice(Vertice vertice);

void agregar_vecino(Vertice A, Vertice B);

void optimizar_memoria(Vertice A);

void imprimirVecinos(Vertice vertice);
