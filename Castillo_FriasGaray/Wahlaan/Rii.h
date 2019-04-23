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


/* Funciones de ordenación*/

char OrdenNatural(Grafo G);

char OrdenWelshPowell(Grafo G);

char SwitchVertices(Grafo G,u32 i,u32 j);

char SwitchColores(Grafo G,u32 i,u32 j);

char RMBCnormal(Grafo G);

char RMBCrevierte(Grafo G);

char RMBCchicogrande(Grafo G);


/* Algoritmos principales */

u32 Greedy(Grafo G);

int Bipartito(Grafo G);


void ActualizarIndicesDeVertices(Grafo G);

#endif
