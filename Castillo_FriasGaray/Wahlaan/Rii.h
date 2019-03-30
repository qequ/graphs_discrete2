/*
    Integrantes

    Castillo Luciano - email: lucianocastillo22@gmail.com

    Frias Garay Alvaro - email:

*/

#ifndef _RII_H
#define _RII_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef uint32_t u32;


/* Estructura de datos para Vértice y operaciones */

typedef struct vertice vertice_t;

typedef vertice_t * Vertice;

struct vertice {
    // info del vértice
    bool inicializado;
    bool coloreado;
    u32 nombre;
    u32 color_actual;

    // info útil cuando tengamos que añadir vecinos
    u32 cant_vecinos;
    u32 tam_array_vecinos;

    // array de vecinos
    Vertice * vecinos;
};

void init_vertice(Vertice vertice, u32 nombre);

void destruir_vertice(Vertice vertice);

void agregar_vecino(Vertice A, Vertice B);

void optimizar_memoria(Vertice A);

void imprimirVecinos(Vertice vertice);


/* Estructura de datos para Grafo y operaciones */

struct GrafoSt {
    u32 cant_vertices;
    u32 cant_lados;
    u32 coloreo_actual; // cantidad de colores del coloreo actual

    Vertice * hash_table_vertices; // útil para cargar lados
    Vertice * orden_actual; // orden actual de vértices

};

typedef struct GrafoSt grafo_t;

typedef struct GrafoSt * Grafo;

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);

Grafo CopiarGrafo(Grafo G);

void dumpear_hash_table(Grafo g);

/* Estructura de Cola y operaciones. Útil para Bipartito */

struct ColaSt{
    Vertice *elems;
    u32 first;
    u32 size;
    u32 n;
};

typedef struct ColaSt cola_t;

typedef struct ColaSt * Cola;

Cola crear_cola(u32 n);

void encolar(Cola q, Vertice elem);

Vertice decolar(Cola q);

u32 cola_vacia(Cola q);

void destruir_cola(Cola q);


// Funciones para extraer información de los grafos

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeLados(Grafo G);

u32 NumeroDeColores(Grafo G);

// Funciones para extraer información de los vértices

u32 NombreDelVertice(Grafo G, u32 i);

u32 ColorDelVertice(Grafo G, u32 i);

u32 GradoDelVertice(Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);

/* Funciones útiles para hashtable */

u32 obtener_primo_para_hash(u32 cant_vertices);

u32 hash_1(Grafo graf, u32 nombre_vert);

u32 hash_2(u32 nombre_vert, u32 primo);

u32 obtener_posicion_vertice(Grafo graf, u32 nombre_vert);

/* Funciones de ordenación*/

char OrdenNatural(Grafo G);

char OrdenWelshPowell(Grafo G);

/* Algoritmos principales */

u32 Greedy(Grafo G);

int Bipartito(Grafo G);

#endif
