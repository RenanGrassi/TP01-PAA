#include "include.h"

#ifndef MAP
#define MAP

typedef struct Map{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
}Map;

void show_map(Map* map);
void atributos(FILE *f, Map *map);
void printAtributos(Map *map);
Map *generate_map(FILE* f);

#endif // MAP