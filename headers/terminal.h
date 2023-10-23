#include "solution.h"

#ifdef __linux__
    void nc();
#endif

void lerArquivo(FILE** f); // abre o arquivo para leitura

void identificarCaminhada(int* i, int* j, char ch); // identifica se o usuario quer ir para cima, baixo, esquerda ou direita

char caminharUsuario(); // modo de jogo que o usuario controla o Indiana Jones

void menu(); // menu que chama as funcoes e deixa o usuario escolher as opcoes
