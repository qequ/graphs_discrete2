#include "Rii.h"


Cola crear_cola(u32 n) {
    Cola q = malloc(sizeof(cola_t));
    q->elems = malloc(n * sizeof(Vertice));
    q->first = 0;
    q->size = 0;
    q->n = n;
    return q;
}

void encolar(Cola q, Vertice elem) {
    q->elems[(q->first + q->size) % q->n] = elem;
    q->size += 1;
}

Vertice decolar(Cola q) {
    q->first = (q->first + 1) % q->n;
    q->size = q->size - 1;
    return q->elems[(q->first? q->first - 1 : q->n - 1)];
}


u32 cola_vacia(Cola q) {
    return (q->size == 0);
}

void destruir_cola(Cola q) {
    free(q->elems);
    free(q);
}
