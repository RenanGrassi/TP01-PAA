#include "solution.h"

#ifndef MAP
#define MAP

typedef struct Map{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
}Map;

void grafic(char block);
void linha(int tam);
void show_map(Map* map, bool movimento);
void atributos(FILE *f, Map *map);
void printAtributos(Map *map);
Map* generate_map(FILE* f);
void copyMap(Map* map);
void teste();
void pausar_limpar();

#endif // MAP