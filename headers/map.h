#include "solution.h"

typedef struct TipoMap{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
}TipoMap;

void grafic(char block);
void linha(int tam);
void showMap(TipoMap* map, bool movimento);
void atributos(FILE *f, TipoMap* map);
void printAtributos(TipoMap* map);
TipoMap* generate_map(FILE* f);
void copyMap(TipoMap* map);
void freeMap(TipoMap* map);
void teste();
