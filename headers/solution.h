#include "map.h"

void mostraSequencia(int** routes, int tam); // mostra a sequencia da forma pedida no TP [0,0],[0,1]...

bool checkingRoute(TipoMap *m, int* x, int* y, bool poder); // verifica se a rota eh valida, poder: true = pode passar pelas paredes, false = não pode passar pelas paredes

bool movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys); // mostra o mapa movimentacao adicionando a posicao atualI e atualJ

void movimentacao(TipoMap* map, int atualI, int atualJ); // movimentacao do indiana jones

void reMovimentacao(TipoMap* map, int atualI, int atualJ); // volta a movimentacao do indiana jones

void irProxCaminho(PCaminho caminho, int tam, TipoMap* map, int** routes); // adiciona na lista encadeada de forma ordenada

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int *caminhosJaVIstos); // achar o um caminho possivel recursivamente

void mostragemCaminho(TipoMap* map, PCaminho caminho, int* rotaN); // mostra todos os caminhos de forma recursiva

void procurarCaminho(TipoMap* map, int* caminhosJaVistos);  // procurar os caminhos possiveis


