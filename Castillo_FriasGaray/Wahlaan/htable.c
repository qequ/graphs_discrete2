#include "Rii.h"
#include "htable.h"


/* Obtiene un primo de acuerdo a la cantidad de vértices que tiene el grafo */
u32 get_prime(u32 size) {
    // Conjunto de primos útil para hash.
    // Valores de primos obtenidos de;
    // https://planetmath.org/goodhashtableprimes
    u32 primes[31] = {
        2,
        3,
        5,
        7,
        23,
        53,
        97,
        193,
        389,
        769,
        1543,
        3079,
        6151,
        12289,
        24593,
        49157,
        98317,
        196613,
        393241,
        786433,
        1572869,
        3145739,
        6291469,
        12582917,
        25165843,
        50331653,
        100663319,
        201326611,
        402653189,
        805306457,
        1610612741
    };

    for (u32 i = 1; i < 30; i++) {
        if (size >= pow(2, i) && size <= pow(2, i+1)) {
            return primes[i-1];
        }
    }
    return primes[30];
}

/* Función hash principal */
u32 hash(u32 key) {
    return (key);
}

/* Función hash usando un número primo */
u32 hash2(u32 key, u32 size) {
    u32 prime = get_prime(size);
    return (prime - (key % prime));
}

u32 module(u32 n, u32 size) {
    return n % size;
}

HTable htable_init(u32 size) {
    // Pido memoria para guardar la hash table
    HTable ht = malloc(sizeof(htable_t));

    ht->size = size;
    // Pido memoria para guardar un arreglo de elementos
    ht->elems = (Vertice *)calloc(size, sizeof(Vertice));
    return ht;
}

void htable_insert(HTable ht, u32 key, Vertice vert) {
    u32 i = 1;
    // Intento con un hash simple tomando el módulo para no salir del array
    u32 hashed_key = module(hash(key), ht->size);

    while (ht->elems[hashed_key] != NULL) {
        // El lugar está ocupado, así que armamos otro hash usando
        // ambas funciones `hash` y `hash2` (double hashing),
        // y tomamos el módulo en base `ht->size` para no salir del array.
        hashed_key = module(hashed_key + i * hash2(key, ht->size), ht->size);
        // Aumento `i` por si necesito generar otro hash
        ++i;
    }
    // No hay elemento en esta posición, entonces la uso
    ht->elems[hashed_key] = vert;
    // return hashed_key;
}

Vertice htable_get(HTable ht, u32 key) {
    u32 i = 1;
    u32 hashed_key = module(hash(key), ht->size);

    while (ht->elems[hashed_key] == NULL || ht->elems[hashed_key]->nombre != key) {
        hashed_key = module(hashed_key + i * hash2(key, ht->size), ht->size);
        ++i;
    }
    return ht->elems[hashed_key];
}

void htable_destroy(HTable ht) {
    // Libero la memoria de cada elemento en la hash table
    for (u32 i = 0; i < ht->size; ++i)
        free(ht->elems[i]);

    free(ht->elems);
    free(ht);
}

void htable_print(HTable ht) {
    u32 n = 0;

    for (u32 i = 0; i < ht->size; ++i) {
        if (ht->elems[i] != NULL) {
            // Imprimo información de los elementos no nulos de la hash table
            printf("%u %u %p\n", ht->elems[i]->nombre, ht->elems[i]->inicializado, &ht->elems[i]);
            ++n;
        }
    }
    printf("Printed %u elements of %u\n", n, ht->size);
}
