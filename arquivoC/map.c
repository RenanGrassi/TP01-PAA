#include "../headers/map.h"

void teste(){
    printf("\n\nteste\n\n");
    // refresh();
}


void grafic(char block){
    switch (block){

    case '0':
        printf("  ");
        break;

    case '1':
        // attron(COLOR_PAIR(1));  // Define a cor do texto
        printf("  ");
        // attroff(COLOR_PAIR(1));  // Desfaz a cor do texto
        break;

    case 'C':
        // attron(COLOR_PAIR(2));  // Define a cor do texto
        printf("0-");
        // attroff(COLOR_PAIR(2));  // Desfaz a cor do texto
        break;
    
    case 'X':
        // attron(COLOR_PAIR(3));  // Define a cor do texto
        printf("[]");
        // attroff(COLOR_PAIR(3));  // Desfaz a cor do texto
        break;
    
    //desenahr um personagem
    case 'P':

        // attron(COLOR_PAIR(4));  // Define a cor do texto
        printf("o-");
        // attroff(COLOR_PAIR(4));  // Desfaz a cor do texto
        break;
    
    case 'p':
        // attron(COLOR_PAIR(5));  // Define a cor do texto
        printf("  ");
        // attroff(COLOR_PAIR(5));  // Desfaz a cor do texto
        break;

    case 'A':
        // attron(COLOR_PAIR(6));  // Define a cor do texto
        printf("  ");
        // attroff(COLOR_PAIR(6));  // Desfaz a cor do texto
        break;

    default:
        break;
    }
}


void linha(int tam){
    for (int i = 0; i < tam+2; i++) {
        // attron(COLOR_PAIR(1));  // Define a cor do texto
        printf("  ");
        // attroff(COLOR_PAIR(1));  // Desfaz a cor do texto
        // refresh();
    }
    printf("\n");
    // refresh();
}

void coluna(int tam){

    // attron(COLOR_PAIR(1));  // Define a cor do texto
    printf("  ");
    // attroff(COLOR_PAIR(1));  // Desfaz a cor do texto
    // refresh();

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
            
            // refresh();


            if (j == map->tamJ - 1) {
                coluna(map->tamJ);
            }
        }
        printf("\n");
        // refresh();
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
    // refresh();  

    printf("keys: %d\n", map->keys);
    // refresh();  

    printf("chestI: %d, chestJ: %d\n", map->chestI, map->chestJ);
    // refresh(); 

    printf("\n");
    // refresh();     

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
