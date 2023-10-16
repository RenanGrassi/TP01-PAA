#include "headers/map.h"

int main(){

    FILE *f;
    char stay_running;
    char file_path[250];

    Map *map;

    // ler o arquivo e mandar para a funçao generate_map

    do{
        printf("\nDigite o caminho do arquivo: \n");

        strcpy(file_path, "./mapGenerator/map0.txt");
        //scanf("%s", file_path);

        printf("\nArquivo: %s\n", file_path);

        f = fopen(file_path, "r");

        if(f == NULL){
            printf("\nArquivo nao encontrado\n\n");
        }
        else{
            printf("\nArquivo encontrado!!!\n\n");
        }
    }

    while(f == NULL);

    // mandar para uma funçao o file e criar o map

    map = generate_map(f);

    // printar o mapa

    printAtributos(map);

    puts("\n");

    show_map(map);    

    pausar_tela(); // pausa para ser limpo depois
    return 0;
}