#include <stdio.h>
#include <stdlib.h>

#ifndef MAP
#define MAP

typedef struct Map{
    unsigned int X;
    unsigned int Y;
    char **Matrix;
}Map;

void show_map(Map*);
Map *generate_map(FILE*, int, int);

#endif // MAP