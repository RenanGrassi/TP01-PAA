#include "../headers/map.h"

void teste(){ // so para testar onde esta o erro
    printw("\n\nteste\n\n");
    printf("\n\nteste\n\n");
    refresh();
}

#ifdef __linux__
    void color(int n){
        attron(COLOR_PAIR(n));  // Define a cor do te
    }

    void exitColor(int n){
        attroff(COLOR_PAIR(n));  // Desfaz a cor do texto
    }

#else
    void color(int n){    }

    void exitColor(int n){    }

#endif

void grafic(char block){
    switch (block){

    case '0':
        printw("  ");
        printf("  ");
        break;

    case '1':
        color(1);
        printw("  ");
        printf("\033[41m  \033[0m");
        exitColor(1);
        break;

    case 'C':
        color(2);
        printw("0-");
        printf("\033[32m0-\033[0m");
        exitColor(2);
        break;
    
    case 'X':
        color(3);
        printw("[]");
        printf("\033[33m[]\033[0m");
        exitColor(3);
        break;
    
    //desenahr um personagem
    case 'P':

        color(4);
        printw("o-");
        printf("\033[36mo-\033[0m");
        exitColor(4);
        break;
    
    case 'p':
        color(5);
        printw("  ");
        printf("\033[47m  \033[0m");
        exitColor(5);
        break;

    // case 'A':
    //     color(6);
    //     printw("  ");
    //     printf("  ");
    //     exitColor(6);
    //     break;

    default:
        break;
    }
}

void linha(int tam){
    for (int i = 0; i < tam+2; i++) {
        color(7);
        printw("  ");
        printf("\033[41m  \033[0m");
        exitColor(7);
        refresh();
    }
    printw("\n");
    printf("\n");
    refresh();
}

void coluna(int tam){

    color(7);
    printw("  ");
    printf("\033[41m  \033[0m");
    exitColor(7);
    refresh();

}

void showMap(TipoMap* map, bool movimento){
    int i, j;
    
    linha(map->tamJ);

    for(i = 0; i < map->tamI; i++) {
        for(j = 0; j < map->tamJ; j++) {
            if (j == 0) {
                coluna(map->tamJ);
            }

            // printw("%c ", map->Matrix[i][j]);
            if (movimento)
                grafic(map->MatrixMovimento[i][j]);
            
            else 
                grafic(map->Matrix[i][j]);
            
            refresh();


            if (j == map->tamJ - 1) {
                coluna(map->tamJ);
            }
        }
        printw("\n");
        printf("\n");
        refresh();
    }

    
    linha(map->tamJ); 

}

void atributos(FILE *f, TipoMap* map){ //adiciona os atributos do map.h
    
    fscanf(f, "%d %d", &(map->tamI), &(map->tamJ));
    
    fscanf(f, "%d", &(map->keys));

    fscanf(f, "%d %d", &(map->chestI), &(map->chestJ));
}

void printAtributos(TipoMap* map){
    printw("tamI: %d, tamJ: %d\n", map->tamI, map->tamJ);
    printf("tamI: %d, tamJ: %d\n", map->tamI, map->tamJ);
    refresh();  

    printw("keys: %d\n", map->keys);
    printf("keys: %d\n", map->keys);
    refresh();  

    printw("chestI: %d, chestJ: %d\n", map->chestI, map->chestJ);
    printf("chestI: %d, chestJ: %d\n", map->chestI, map->chestJ);
    refresh(); 

    printw("\n");
    printf("\n");
    refresh();     

}

TipoMap* generateMap(FILE* f){
    int i, j;
    char read;
    
    TipoMap* map = (TipoMap*) malloc(sizeof(TipoMap));
    map->caminhosPossiveis = malloc(sizeof(Caminho));
    map->caminhosPossiveis->proxCaminho = NULL;
    map->caminhosPossiveis->tamanho = 0;

    // receber os atributos do mapa
    atributos(f, map);

    map->Matrix = (char**) malloc(sizeof(char*) * map->tamI);

    for (int i = 0; i < map->tamI; i++) {
        map->Matrix[i] = (char*) malloc(sizeof(char) * map->tamJ);
    }
    
    i = 0;
    j = 0;

    while (i < map->tamI) {
        while (j < map->tamJ) {
            fscanf(f, "%c", &read);


            if (read >= 48 && read <= 122) {
                    // printw("%c", read);
                    map->Matrix[i][j] = read;
                    j++;
            }
        }
        i++;
        j = 0;
    }

    return map;
}

TipoMap* generateMapAleatorio(){
    int i, j;
    
    srand(time(NULL));

    TipoMap* map = (TipoMap*) malloc(sizeof(TipoMap));
    map->caminhosPossiveis = malloc(sizeof(Caminho));
    map->caminhosPossiveis->proxCaminho = NULL;
    map->caminhosPossiveis->tamanho = 0;


    // receber os atributos do mapa
    map->tamI = 10;
    map->tamJ = 10;
    map->chestI = rand() % 10;
    map->chestJ = rand() % 10;

    if(map-> chestI == 0 && map->chestJ == 0)
        map-> chestI = rand() % map->tamI + 1;

    map->keys = rand() % 6;
    int paredes = 30;

    int keysPostas = 0;
    int paredesPostas = 0;


    map->Matrix = (char**) malloc(sizeof(char*) * map->tamI);

    for (int i = 0; i < map->tamI; i++) {
        map->Matrix[i] = (char*) malloc(sizeof(char) * map->tamJ);

        for (int j = 0; j < map->tamJ; j++) {
            map->Matrix[i][j] = '0';
        }
    }

    map->Matrix[map->chestI][map->chestJ] = 'X';

    int paredeX = 0;
    int paredeY = 0;

    int keysX = 0;
    int keysY = 0;

    while (paredesPostas != paredes || keysPostas != map->keys) {
        if (paredesPostas != paredes){
            paredeX = rand() % map->tamI;
            paredeY = rand() % map->tamJ;
            
            if (paredeX==0 && paredeY==0)
                paredeX = rand() % (map->tamI-1) + 1;
            
            if(map->Matrix[paredeX][paredeY] != 'X' && map->Matrix[paredeX][paredeY] != '1' && map->Matrix[paredeX][paredeY] != 'C'){
                map->Matrix[paredeX][paredeY] = '1';
                paredesPostas++;
            }
        }

        if (keysPostas != map->keys){
            keysX = rand() % map->tamI;
            keysY = rand() % map->tamJ;

            if (keysX==0 && keysY==0)
                keysX = rand() % (map->tamI-1) + 1;

            if(map->Matrix[keysX][keysY] != 'X' && map->Matrix[keysX][keysY] != '1' && map->Matrix[keysX][keysY] != 'C'){
                map->Matrix[keysX][keysY] = 'C';
                keysPostas++;
            }
        }
    }

    return map;
}

void copyMap(TipoMap* map) {
    int i, j;

    map->MatrixMovimento = (char**) malloc(map->tamI * sizeof(char*));

    for (i = 0; i < map->tamI; i++) {
        map->MatrixMovimento[i] = (char*) malloc(map->tamJ * sizeof(char));

        for (j = 0; j < map->tamJ; j++) {

            map->MatrixMovimento[i][j] = map->Matrix[i][j];
            
        }
    }
}

void freeMap(TipoMap* map){
    int i;
    copyMap(map);

    for (i = 0; i < map->tamI; i++) {
        free(map->Matrix[i]);
        free(map->MatrixMovimento[i]);
    }

    free(map->Matrix);
    free(map->MatrixMovimento);
    free(map);
}

void freeCaminhos(PCaminho caminhos){
    if(caminhos == NULL){
        return;
    }

    freeCaminhos(caminhos->proxCaminho);

    for(int i = 0; i < caminhos->tamanho; i++){
        free(caminhos->vetCaminho[i]);
    }

    free(caminhos->vetCaminho);

    free(caminhos);
}