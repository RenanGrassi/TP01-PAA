#include "../headers/solution.h"

void teste(){
    printw("\n\nteste\n\n");
    printf("\n\nteste\n\n");
    refresh();
}

// bool canMove(int x, int y, int ROWS, int COLS, char parede, bool** visited) {
//     printf("\nnewX = %d\nnewY = %d\n", x, y);
//     // printf("\n\n%c\n\n", map->Matrix[newX][newY]);
//     if (x >= 0 && x < ROWS && y >= 0 && y < COLS && parede != '1' && !visited[x][y])
//         printf("foi\n");
//     printf("\n%d\n", visited[x][y]);
//     return x >= 0 && x < ROWS && y >= 0 && y < COLS && parede != '1' && !visited[x][y];
// }

void mostrarSeguencia(int routes[][2], int *tam){

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
        // showMap(map, true);
        // ncPausar();

        return true;
    }
    else{
        return false;
    }
}

void movimentacaoShow(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = 'P';
        printw("\n");
        printf("\n");
        showMap(map, true);
        map->MatrixMovimento[atualI][atualJ] = 'p';
}

void movimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = 'P';
        // printw("\n");
        // printf("\n");
        // showMap(map, true);
        map->MatrixMovimento[atualI][atualJ] = 'p';
}

void reMovimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = map->Matrix[atualI][atualJ];
        // printw("\n");
        // printf("\n");
        // showMap(map, true);
        // map->MatrixMovimento[atualI][atualJ] = 'P';
}

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int routes[][2], int* tam) {

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        // *tam = 0;
        return true;
    }

    movimentacao(map, x, y);

    routes[(*tam)][0] = x; 
    routes[(*tam)][1] = y; // salva a posiçao sendo verificada agora
    (*tam)++;

    

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};  // seguencia de movimentos direta, baixo, esquerda, cima

    for (int i = 0; i < 4; i++) { // testa a sequencia
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (checkingRoute(map, newX, newY)) {
            
            if (map->Matrix[newX][newY] == 'C') {
                keys_collected++;
            }

            movimentacao(map, newX, newY);

            if (findShortestPath(newX, newY, keys_collected, map, routes, tam)) {
                return true;
            }

            reMovimentacao(map, newX, newY);

            if (map->Matrix[newX][newY] == 'C') {
                keys_collected--;
            }
        }
    }

    routes[(*tam)][0] = 0;
    routes[(*tam)][1] = 0;
    (*tam)--;

    return false;
}

void procurarCaminho(TipoMap* map, LPosicao* lista){

    int routes [map->tamI * map->tamJ][2];
    int* tam;
    copyMap(map);

    *tam = 0;

    if (findShortestPath(0, 0, 0, map, routes, tam)) {
        refresh();

        copyMap(map);
        int cont = 0;
        for (int i = 0; i < *tam; i++) {
            cont++;
            ncPausar();     
            movimentacaoShow(map, routes[i][0], routes[i][1]);       
        }
        printw("Indiana Jones consegue abrir o bau :)\n");
    } 

    else {
        printf("Indiana Jones nao consegue abrir o bau :(\n");
        printw("Indiana Jones nao consegue abrir o bau :(\n");
        refresh();
    
    }
}

