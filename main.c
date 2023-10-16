#include "headers/map.h"

int main(){

    FILE *f;
    char stay_running;
    char file_path[250];

    Map *map;

    // ler o arquivo e mandar para a funçao generate_map

    do{
        printf("Digite o caminho do arquivo: ");

        strcpy(file_path, "./mapGenerator/map0.txt");
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

    // mandar para uma funçao o file e criar o map

    map = generate_map(f);

    // printar o mapa

    printAtributos(map);

    show_map(map);    

    pausar_tela(); // pausa para ser limpo depois
    return 0;
}