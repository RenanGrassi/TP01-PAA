#include "include.h"

typedef struct TipoMap{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
}TipoMap;

typedef struct Posicao PPosicao;
typedef struct Posicao{

        int linha;
        int coluna;
        PPosicao proxPosicao;

} TipoPosicao;


typedef struct LPosicao{

    PPosicao caminho;
    PPosicao proxCaminho;
    int tamanho;

} LPosicao;

void teste();

bool canMove(int x, int y, int ROWS, int COLS, char parede, bool** visited);

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, bool** visited, int* pathLength, int shortestPath[][2]);
