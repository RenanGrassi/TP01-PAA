#include "../headers/solution.h"

void teste(){
    printw("\n\nteste\n\n");
    printf("\n\nteste\n\n");
    refresh();
}

typedef struct {
    int x;
    int y;
} Posicao; //Tentativa de corrigir.


void mostrarSequencia(int routes[][2], int *tam){

    for (int i = 0; i < *tam; i++) {

            printf("[%d,%d]", routes[i][0], routes[i][1]);
            printw("[%d,%d]", routes[i][0], routes[i][1]);
            refresh();

            if (i < *tam - 1)
                printf(",");
                printw(",");
                refresh();
        }
}

bool checkingRoute(TipoMap *map, int i, int j) {

    if(i >= 0 && i < map->tamI && j >= 0 && j < map->tamJ && map->MatrixMovimento[i][j] != '1' && map->MatrixMovimento[i][j] != 'p'){
            //         showMap(map, true);
            // ncPausar();
        return true;
    }
    else{
        return false;
    }
}

void movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys){

    if(map->MatrixMovimento[atualI][atualJ] == 'C')
        (*keys)++;

    map->MatrixMovimento[atualI][atualJ] = 'P';
    printw("\n");
    printf("\n");
    showMap(map, true);
    printw("\n Indiana Jones pegou %d chaves\n", *keys);
    printf("\n Indiana Jones pegou %d chaves\n", *keys);
    refresh();
    map->MatrixMovimento[atualI][atualJ] = 'p';
}

void movimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = 'P';
        map->MatrixMovimento[atualI][atualJ] = 'p';
}

void reMovimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = map->Matrix[atualI][atualJ];
}


bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int routes[][2], int tam) {

    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};

    Posicao caminho[map->tamI * map->tamJ];
    int caminhoTam = 0;
    
    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        // onde eu coloco o caminho percorrido
        // while(map->caminhosPossiveis->proxCaminho != NULL){
        //     if(map->caminhosPossiveis->proxCaminho->tamanho > tam || map->caminhosPossiveis->proxCaminho == NULL){

        //         PCaminho prox = map->caminhosPossiveis->proxCaminho;

        //         map->caminhosPossiveis->proxCaminho = malloc(sizeof(Caminho));
        //         map->caminhosPossiveis->proxCaminho->tamanho = tam;
        //         map->caminhosPossiveis->proxCaminho->vetCaminho = (int**) malloc(sizeof(int*) * (tam));

        //         for (int i = 0; i < tam; i++) {
        //             map->caminhosPossiveis->proxCaminho->vetCaminho[i] = (int*) malloc(sizeof(int) * 2);
        //             map->caminhosPossiveis->proxCaminho->vetCaminho[i][0] = routes[i][0];
        //             map->caminhosPossiveis->proxCaminho->vetCaminho[i][1] = routes[i][1];
        //         }

        //         map->caminhosPossiveis->proxCaminho->proxCaminho = prox;
        //     }

        //     map->caminhosPossiveis = map->caminhosPossiveis->proxCaminho;
        // }
        // return true;
        map->caminhosPossiveis->proxCaminho = malloc(sizeof(Caminho));
        map->caminhosPossiveis->proxCaminho->tamanho = tam;
        map->caminhosPossiveis->proxCaminho->vetCaminho = (int**) malloc(sizeof(int*) * (tam));

        for (int i = 0; i < tam; i++) {
            map->caminhosPossiveis->proxCaminho->vetCaminho[i] = (int*) malloc(sizeof(int) * 2);
            map->caminhosPossiveis->proxCaminho->vetCaminho[i][0] = routes[i][0];
            map->caminhosPossiveis->proxCaminho->vetCaminho[i][1] = routes[i][1];
        }
    }

    movimentacao(map, x, y);

    // Continuar com a busca em largura
    Posicao fila[map->tamI * map->tamJ];
    int inicio = 0;
    int fim = 0;
    // Inicializar a fila com a posição inicial
    fila[fim++] = (Posicao){x, y};

    while (inicio < fim) {
        Posicao atual = fila[inicio++];
        x = atual.x;
        y = atual.y;

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < map->tamI && newY >= 0 && newY < map->tamJ &&
                map->MatrixMovimento[newX][newY] != '1' && map->MatrixMovimento[newX][newY] != 'p') {
                caminho[caminhoTam++] = (Posicao){newX, newY};

                if (map->Matrix[newX][newY] == 'C') {
                    keys_collected++;
                }

                if (newX == map->chestI && newY == map->chestJ && keys_collected == map->keys) {
                    // Caminho encontrado
                    return true;
                }

                // Marque a posição como visitada para evitar visitá-la novamente
                map->MatrixMovimento[newX][newY] = 'p';

                // Adicione a próxima posição à fila
                fila[fim++] = (Posicao){newX, newY};
            }
        }
    }

    // Se chegou aqui, nenhum caminho foi encontrado
    return false;
}

void procurarCaminho(TipoMap* map){

    int routes [map->tamI * map->tamJ][2];
    int tam = 0;

    copyMap(map);


    if (findShortestPath(0, 0, 0, map, routes, tam)) {
        refresh();

        copyMap(map);

        int cont = 0;
        int keys = 0;

        for (int i = 0; i < map->caminhosPossiveis->proxCaminho->tamanho; i++) {
            cont++;
            ncPausar();
            movimentacaoShow(map, map->caminhosPossiveis->proxCaminho->vetCaminho[i][0], map->caminhosPossiveis->proxCaminho->vetCaminho[i][1], &keys);     
            refresh(); 
        }
        printw("Indiana Jones consegue abrir o bau :)\n");
        printf("Indiana Jones consegue abrir o bau :)\n");
    } 

    else {
        printf("Indiana Jones nao consegue abrir o bau :(\n");
        printw("Indiana Jones nao consegue abrir o bau :(\n");
        
    
    }
    refresh();
}

