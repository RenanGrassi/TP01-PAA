#include "../headers/map.h"

void show_map(Map* map){
    int i, j;

    for(i = 0; i < map->tamI; i++) {
        for(j = 0; j < map->tamJ; j++) {
            printf("%c ", map->Matrix[i][j]);
        }
        puts("");
    }   
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