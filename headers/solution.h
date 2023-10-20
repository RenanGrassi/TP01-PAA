#include "include.h"

typedef struct TipoMap{
    unsigned int tamI, tamJ;
    unsigned int keys;
    unsigned int chestI, chestJ;
    char **Matrix;
    char **MatrixMovimento;
}TipoMap;

// typedef struct Posicao PPosicao;
// typedef struct Posicao{
    
//     union {

//         struct{
//             PPosicao posicaoFinal;
//         } primeraPosicao;

//         struct {
//             int tam;
//         } ultimaPosicao;

//         int linha;
//         int coluna;
//         PPosicao proxPosicao;
//     };

// } TipoPosicao;


// typedef struct ListaPosicao{

//     PPosicao* primeiro;
//     PPosicao* ultimo;
//     int tamanho;

// } TipoListaPosicao;

void teste();

bool canMove(int x, int y, int ROWS, int COLS, char parede, bool** visited);

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, bool** visited, int* pathLength, int shortestPath[][2]);
