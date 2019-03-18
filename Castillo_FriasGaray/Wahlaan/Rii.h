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

typedef uint32_t u32;


/* Estructura de datos para Vértice y operaciones*/

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


/* Estructura de datos para Grafo y operaciones*/

struct GrafoSt {
    u32 cant_vertices;
    u32 cant_lados;
    u32 coloreo_actual; // numero máximo de coloreo actual

    Vertice * hash_table_vertices; // útil para cargar lados
    Vertice * orden_actual; // orden actual de vértices

};


#endif