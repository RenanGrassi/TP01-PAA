#include "map.h"

void teste();  // so para testar onde esta o erro

bool checkingRoute(TipoMap *m, int x, int y);

void movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys);

void irProxCaminho(PCaminho caminho, int tam, TipoMap* map, int** routes);

void movimentacao(TipoMap* map, int atualI, int atualJ);

void reMovimentacao(TipoMap* map, int atualI, int atualJ);

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int *cont);

void procurarCaminho(TipoMap* map);  // procurar os caminhos possiveis
