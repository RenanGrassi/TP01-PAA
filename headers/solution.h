#include "map.h"

void teste();  // so para testar onde esta o erro

void mostraSequencia(int** routes, int tam);

bool checkingRoute(TipoMap *m, int* x, int* y, bool poder);

bool movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys);

void movimentacao(TipoMap* map, int atualI, int atualJ);

void reMovimentacao(TipoMap* map, int atualI, int atualJ);

void irProxCaminho(PCaminho caminho, int tam, TipoMap* map, int** routes);

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int *caminhosJaVIstos);

void mostragemCaminho(TipoMap* map, PCaminho caminho, int* rotaN);

void procurarCaminho(TipoMap* map, int* caminhosJaVistos);  // procurar os caminhos possiveis


