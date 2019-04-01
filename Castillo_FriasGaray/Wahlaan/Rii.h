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
struct VerticeSt {
    bool                inicializado;
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


/* Estructura de datos para Grafo y operaciones */

typedef struct {
    u32 cant_vertices;
    u32 cant_lados;
    u32 cant_colores;

    Vertice* vertices;
} GrafoSt;

typedef GrafoSt * Grafo;


/* Construye un grafo a partir de stdin */
Grafo ConstruccionDelGrafo();

/* Destruye el grafo, liberando la memoria utilizada */
void DestruccionDelGrafo(Grafo G);

/* Crea una copia del grafo */
Grafo CopiarGrafo(Grafo G);

/* Devuelve la cantidad de vértices de un grafo G */
u32 NumeroDeVertices(Grafo G);

/* Devuelve la cantidad de lados de un grafo G */
u32 NumeroDeLados(Grafo G);

/* Devuelve la cantidad de colores presentes en un grafo G */
u32 NumeroDeColores(Grafo G);


Vertice ConstruirVertice(u32 nombre, u32 grado);

void DestruirVertice(Vertice V);

u32 AgregarVertice(Grafo G, u32 nombre_vertice, u32 grado);

int CompararU32(const void * a, const void * b);

void AgregarVecino(Vertice V, Vertice vecino);

int BuscarVertice(Grafo G, u32 nombre_vert);


#endif
