#include "include.h"

typedef struct Caminho* PCaminho;
typedef struct Caminho{

    int ** vetCaminho;
    int tamanho;
    PCaminho proxCaminho;

} Caminho;


typedef struct TipoMap{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
    PCaminho caminhosPossiveis;
}TipoMap;

void teste(); // para facilitar identificar os erros

void timePause(); // pausar o tempo por 

void color(int n);  // selecionar a cor

void exitColor(int n);  // sair da cor selecionada

void grafic(char block);  // mostrar o mapa de forma bonita

void linha(int tam, bool poder);  // mostrar a linha de cima e baixo

void coluna(int tam, bool poder);  // mostrar a coluna da esquerda e direita

void showMap(TipoMap* map, bool movimento, bool poder);  // mostrar o mapa true = movimento, false = mapa normal

void atributos(FILE *f, TipoMap* map);  // adicionar os atributos do map.h

void printAtributos(TipoMap* map); // printar os atributos do map.h

TipoMap* generateMap(FILE* f);  // gerar o mapa por meio do arquivo

TipoMap* generateMapAleatorio(); // gerar o mapa aleatoriamente

void copyMap(TipoMap* map); // copiar o mapa para o mapa de movimento

void freeMap(TipoMap* map);  // liberar o mapa

void freeCaminhos(PCaminho caminhos);// libera o caminho
