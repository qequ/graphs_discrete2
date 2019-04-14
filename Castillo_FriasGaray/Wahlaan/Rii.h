/*
    Integrantes

    Castillo Luciano    - email: lucianocastillo22@gmail.com

    Frias Garay Alvaro  - email: alvarofriasgaray@gmail.com

*/

#ifndef _RII_H
#define _RII_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_U32      4294967295  // 2^32 - 1


typedef uint32_t u32;

/*
    Estructura de datos para Vértice y operaciones.
*/
#include "Vertice.h"

/*
    Estructura de datos para Grafo y operaciones.
*/
#include "Grafo.h"

/*
    Estructura de Cola y operaciones.
    Útil para Bipartito.
*/
#include "Cola.h"


// Funciones para extraer información de los grafos

/* Devuelve la cantidad de vértices de un grafo G */
u32 NumeroDeVertices(Grafo G);

/* Devuelve la cantidad de lados de un grafo G */
u32 NumeroDeLados(Grafo G);

/* Devuelve la cantidad de colores presentes en un grafo G */
u32 NumeroDeColores(Grafo G);


Vertice ConstruirVertice(u32 nombre, u32 grado);

void DestruirVertice(Vertice V);

u32 NombreDelVertice(Grafo G, u32 i);

u32 ColorDelVertice(Grafo G, u32 i);

u32 GradoDelVertice(Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 AgregarVertice(Grafo G, u32 nombre_vertice, u32 grado);

int CompararU32(const void * a, const void * b);

void AgregarVecino(Vertice V, Vertice vecino);

int BuscarVertice(Grafo G, u32 nombre_vert);


/* Funciones de ordenación*/

char OrdenNatural(Grafo G);

char OrdenWelshPowell(Grafo G);

/* Algoritmos principales */

u32 Greedy(Grafo G);

int Bipartito(Grafo G);

#endif
