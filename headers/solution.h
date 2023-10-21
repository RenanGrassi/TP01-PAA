#include "map.h"


typedef struct Posicao* PPosicao;
typedef struct Posicao{

        int** vetCaminho;

} TipoPosicao;


typedef struct LPosicao{

    PPosicao caminho;
    PPosicao proxCaminho;
    int tamanho;

} LPosicao;

void teste();  // so para testar onde esta o erro

bool checkingRoute(TipoMap *m, int x, int y);

void movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys);

void movimentacao(TipoMap* map, int atualI, int atualJ);

void reMovimentacao(TipoMap* map, int atualI, int atualJ);

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int routes[][2], int* tam);

void procurarCaminho(TipoMap* map,  LPosicao* lista);  // procurar os caminhos possiveis
