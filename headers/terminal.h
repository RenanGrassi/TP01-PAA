#include "map.h"


void lerArquivo(FILE** f);
void identificarCaminhada(int* i, int* j, char ch);
char caminhar();
void menu();
void movimentacao(TipoMap* map, int atualI, int atualJ, bool** visited);

#ifdef __linux__
    void nc();
#endif