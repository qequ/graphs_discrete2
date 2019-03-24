/*
    Integrantes

    Castillo Luciano - email:

    Frias Garay Alvaro - email:

*/

#ifndef _RII_H
#define _RII_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint32_t u32;


/* Estructura de datos para Vértice y operaciones */

typedef struct vertice vertice_t;

typedef vertice_t * Vertice;

struct vertice {
    // info del vértice
    bool inicializado;
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
    u32 coloreo_actual; // numero máximo de coloreo actual

    Vertice * hash_table_vertices; // útil para cargar lados
    Vertice * orden_actual; // orden actual de vértices

};

typedef struct GrafoSt grafo_t;

typedef struct GrafoSt * Grafo;

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);

Grafo CopiarGrafo(Grafo G);


/* Funciones útiles para hashtable */

u32 pot(u32 x, u32 y);

u32 obtener_primo_para_hash(u32 cant_vertices);

u32 hash_1(Grafo graf, u32 nombre_vert);

u32 hash_2(u32 nombre_vert, u32 primo);

u32 obtener_posicion_vertice(Grafo graf, u32 nombre_vert);

#endif