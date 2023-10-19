#include "../headers/map.h"

void teste(){
    printf("\n\nteste\n\n");
}


void grafic(char block){
    switch (block){

    case '0':
        printf("  ");
        break;

    case '1':
        printf("\x1b[41m  \x1b[0m"); // vermelho
        break;
    case 'C':
        printf("\x1b[32m0-\x1b[0m"); // verde
        break;
    
    case 'X':
        printf("\x1b[33m[]\x1b[0m"); // amarelo
        break;
    
    //desenahr um personagem
    case 'P':
        printf("\x1b[36mo-\x1b[0m"); // ciano
        break;
    
    case 'p':
        printf("\x1b[47m  \x1b[0m"); // branco
        break;

    default:
        break;
    }
}


void linha(int tam){
    for (int i = 0; i < tam+2; i++) {
        printf("\x1b[41m  \x1b[0m");
    }
    printf("\n");
}

void coluna(int tam){

    printf("\x1b[41m  \x1b[0m");

}

void showMap(TipoMap* map, bool movimento){
    int i, j;
    
    linha(map->tamJ);

    for(i = 0; i < map->tamI; i++) {
        for(j = 0; j < map->tamJ; j++) {
            if (j == 0) {
                coluna(map->tamJ);
            }

            // printf("%c ", map->Matrix[i][j]);
            if (movimento)
                grafic(map->MatrixMovimento[i][j]);
            
            else 
                grafic(map->Matrix[i][j]);
            


            if (j == map->tamJ - 1) {
                coluna(map->tamJ);
            }
        }
        printf("\n");
    }

    
    linha(map->tamJ); 
}

void atributos(FILE *f, TipoMap* map){ //adiciona os atributos do map.h
    
    fscanf(f, "%d %d", &(map->tamI), &(map->tamJ));
    
    fscanf(f, "%d", &(map->keys));

    fscanf(f, "%d %d", &(map->chestI), &(map->chestJ));
}

void printAtributos(TipoMap* map){
    printf("tamI: %d, tamJ: %d\n", map->tamI, map->tamJ);  

    printf("keys: %d\n", map->keys);  

    printf("chestI: %d, chestJ: %d\n", map->chestI, map->chestJ); 

    printf("\n");     

}

TipoMap* generate_map(FILE* f){
    int i, j;
    char read;
    
    TipoMap* map = (TipoMap*) malloc(sizeof(TipoMap));

    // receber os atributos do mapa
    atributos(f, map);

    map->Matrix = (char**) calloc(sizeof(char*), map->tamI);

    for (int i = 0; i < map->tamI; i++) {
        map->Matrix[i] = (char*) calloc(sizeof(char), map->chestJ);
    }
    
    i = 0;
    j = 0;

    while (i < map->tamI) {
        while (j < map->tamJ) {
            fscanf(f, "%c", &read);


            if (read >= 48 && read <= 122) {
                    // printf("%c", read);
                    map->Matrix[i][j] = read;
                    j++;
            }
        }
        i++;
        j = 0;
    }

    copyMap(map);
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

    for (i = 0; i < map->tamI; i++) {
        free(map->Matrix[i]);
        free(map->MatrixMovimento[i]);
    }

    free(map->Matrix);
    free(map->MatrixMovimento);
    free(map);
}
