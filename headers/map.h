#include "solution.h"

void grafic(char block);
void linha(int tam);
void showMap(TipoMap* map, bool movimento);
void atributos(FILE *f, TipoMap* map);
void printAtributos(TipoMap* map);
TipoMap* generate_map(FILE* f);
void copyMap(TipoMap* map);
void freeMap(TipoMap* map);
void procurarCaminho(TipoMap* map);
