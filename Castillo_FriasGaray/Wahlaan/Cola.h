typedef struct {
    Vertice *elems;
    u32 first;
    u32 size;
    u32 n;
} cola_t;

typedef cola_t * Cola;


Cola crear_cola(u32 n);

void encolar(Cola q, Vertice elem);

Vertice decolar(Cola q);

u32 cola_vacia(Cola q);

void destruir_cola(Cola q);
