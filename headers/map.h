#include "include.h"

typedef struct TipoMap{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
}TipoMap;

void color(int n);  // selecionar a cor

void exitColor(int n);  // sair da cor selecionada

void grafic(char block);  // mostrar o mapa de forma bonita

void linha(int tam);  // mostrar a linha de cima e baixo

void showMap(TipoMap* map, bool movimento);  // mostrar o mapa

void atributos(FILE *f, TipoMap* map);  // adicionar os atributos do map.h

void printAtributos(TipoMap* map); // printar os atributos do map.h
TipoMap* generate_map(FILE* f);  // gerar o mapa

void copyMap(TipoMap* map); // copiar o mapa para o mapa de movimento

void freeMap(TipoMap* map);  // liberar o mapa
