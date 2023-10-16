#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map/map.h"

int main(){

    FILE *f;
    char stay_running;
    char file_path[250];
    int tamI, tamJ;
    int keys;
    int chestI, chestJ;

    Map *map;

    // ler o arquivo e mandar para a funçao generate_map

    do{
        printf("Digite o caminho do arquivo: ");

        strcpy(file_path, "./mapGenerator/map.txt");
        //scanf("%s", file_path);

        printf("Arquivo: %s\n", file_path);

        f = fopen(file_path, "r");

        if(f == NULL){
            printf("Arquivo nao encontrado\n");
        }
        else{
            printf("Arquivo encontrado\n");
        }
    }

    while(f == NULL);

    //ler a primeira linha da matriz e mandar para a funçao generate_map

    fscanf(f, "%d %d", &tamI, &tamJ);


    return 0;
}