#include "Rii.h"


typedef struct HTableSt {
    u32      size;
    Vertice* elems;
} htable_t;

typedef htable_t * HTable;

/* Inicializa una hash table y devuelve un puntero. */
HTable htable_init(u32 size);

/* Agrega un elemento a la hash table. */
void htable_insert(HTable ht, u32 key, Vertice vert);

/* Obtiene un elemento de la hash table. */
Vertice htable_get(HTable ht, u32 key);

/* Destruye la hash table. */
void htable_destroy(HTable ht);

/* Imprime una representación de la hash table. */
void htable_print(HTable ht);
