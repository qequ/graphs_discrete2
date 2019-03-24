#include "Rii.h"

// Función para calcular la potencia x^y
u32 pot(u32 x, u32 y) {
    u32 res = 1;

    while (y > 0) {
        if (y & 1)
            res = res * x;

        y = y >> 1;
        x = x * x;
    }
    return res;
}


// Función para obtener un primo para el hash_2 de acuerdo a la cantidad
// de vértices que tiene el grafo
u32 obtener_primo_para_hash(u32 cant_vertices) {
    // Conjunto de primos útil para hash.
    // Valores de primos obtenidos de;
    // https://planetmath.org/goodhashtableprimes
    u32 primos[31] = {
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
        if (cant_vertices >= pot(2, i) && cant_vertices <= pot(2, i+1)) {
            return primos[i-1];
        }
    }
    return primos[30];
}

/* Funciones de Hash */
u32 hash_1(Grafo graf, u32 nombre_vert) {
    return (nombre_vert % graf->cant_vertices);
}

u32 hash_2(u32 nombre_vert, u32 primo) {
    return (primo - (nombre_vert % primo));
}


// Función para encontrar el índice de un vértice en la hash table.
u32 obtener_posicion_vertice(Grafo graf, u32 nombre_vert) {
    // calculando las funciones de hash
    /*
    u32 h1 = hash_1(graf, nombre_vert);
    u32 h2 = hash_2(nombre_vert, primo_hash);
    u32 i = 0;

    while (1) {
        // Calculando el índice de acuerdo a los hash
        u32 indice = (h1 + i * h2) % graf->cant_vertices;

        // Si el vértice en dicha posición no estaba inicializado
        // quiere decir que el vértice con nombre_vert todavía no estaba
        // en la hash table; se lo inicializa.
        if (!graf->hash_table_vertices[indice]->inicializado) {
            
            Vertice vert = graf->hash_table_vertices[indice];
            init_vertice(vert, nombre_vert);
            return indice;
        }
        // Si no, si el vértice está inicializado y el nombre del vértice
        // en dicha posición es nombre_vert
        else if (graf->hash_table_vertices[indice]->nombre == nombre_vert) {
            return indice;
        }
        // Si llegó acá significa que el vértice en dicha posición está
        // inicializado y no es el vértice que buscamos
        i++;
    }
    */

    // testeando con linear probing
    u32 busquedas = 0;
    u32 indice = hash_1(graf, nombre_vert);

    while(busquedas < graf->cant_vertices) {
        if (!graf->hash_table_vertices[indice]->inicializado) {
            Vertice vertice = graf->hash_table_vertices[indice];
            init_vertice(vertice, nombre_vert);
            return indice;
        }
        else if(graf->hash_table_vertices[indice]->nombre == nombre_vert) {
            return indice;
        }
        else indice = (hash_1(graf, nombre_vert) + busquedas) % graf->cant_vertices;
        busquedas++;
    }

    return indice;
}

