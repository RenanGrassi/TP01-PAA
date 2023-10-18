#include "../headers/map.h"

void grafic(char block){
    switch (block){
    case '0':
        printf("  ");
        break;

    case '1':
        //cor marrom printf("[]");
        printf("\033[0;38;5;94m[]\033[0m");
        break;

    case 'C':
        printf("\033[0;32m0-\033[0m");
        break;
    
    case 'X':
        printf("\033[0;33mXX\033[0m");
        break;
    
    //desenahr um personagem
    case 'P':
        printf("\033[0;34mo-\033[0m");
        break;

    case 'A':
        //print fogo
        printf("\033[0;31m{}\033[0m");
        break;

    default:
        break;
    }
}

void linha(int tam){
    for (int i = 0; i < (tam*2)+2; i++) {
        printf("-");
    }
    puts("");
}

void coluna(int tam){

    printf("|");

}

void show_map(Map* map){
    int i, j;
    
    linha(map->tamJ);
    
    for(i = 0; i < map->tamI; i++) {
        for(j = 0; j < map->tamJ; j++) {
            if (j == 0) {
                coluna(map->tamJ);
            }

            // printf("%c", map->Matrix[i][j]);
            grafic(map->Matrix[i][j]);

            if (j == map->tamJ - 1) {
                coluna(map->tamJ);
            }
        }
        puts("");
    }

    linha(map->tamJ); 
}

void atributos(FILE *f, Map *map){ //adiciona os atributos do map.h

    fscanf(f, "%d %d", &(map->tamI), &(map->tamJ));

    fscanf(f, "%d", &(map->keys));

    fscanf(f, "%d %d", &(map->chestI), &(map->chestJ));
}

void printAtributos(Map *map){
    printf("tamI: %d, tamJ: %d\n", map->tamI, map->tamJ);
    printf("keys: %d\n", map->keys);
    printf("chestI: %d, chestJ: %d\n", map->chestI, map->chestJ);
}

Map *generate_map(FILE *f){
    int i, j;
    char read;
    
    Map *map = (Map*) malloc(sizeof(Map));

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

            // se for um numero ou uma letra

            if (read >= 48 && read <= 122) {
                    // printf("%c", read);
                    map->Matrix[i][j] = read;
                    j++;
            }
        }
        i++;
        j = 0;
    }

    return map;
}
