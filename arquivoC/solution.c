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

bool checkingRoute(TipoMap *map, int i, int j) {
    
    // // printar as variaveis dentro do if
    // printw("\n\ni = %d\nj = %d\ntem uma parede? %c\nJa fui nessa posicao? %c\n\n", i, j, map->MatrixMovimento[i][j], map->MatrixMovimento[i][j]);
    // refresh();

    if(i >= 0 && i < map->tamI && j >= 0 && j < map->tamJ && map->MatrixMovimento[i][j] != '1' && map->MatrixMovimento[i][j] != 'p'){
        // printw("\n\ni = %d\nj = %d\ntem uma parede? %c\nJa fui nessa posicao? %c\n\n", i+2, j, map->MatrixMovimento[i][j], map->MatrixMovimento[i][j]);
        // refresh();
        // ncPausar();
        showMap(map, true);
        ncPausar();

        return true;
    }
    else{
        return false;
    }
}

void movimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = 'P';
        printw("\n");
        printf("\n");
        // showMap(map, true);
        map->MatrixMovimento[atualI][atualJ] = 'p';
}

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int routes[][2], int* tam) {

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        *tam = 0;
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

        // printw("\nnewX = %d\nnewY = %d", newX, newY);
        // refresh();
        // printw("\n\n%c\n\n", map->Matrix[newX][newY]);
        // refresh();

        if (checkingRoute(map, newX, newY)) {
            
            if (map->Matrix[newX][newY] == 'C') {
                keys_collected++;
            }

            movimentacao(map, newX, newY);

            if (findShortestPath(newX, newY, keys_collected, map, routes, tam)) {
                return true;
            }

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
        printw("Indiana Jones consegue abrir o bau :)\n");
        refresh();

        showMap(map, true);

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

    else 
        printf("Indiana Jones nao consegue abrir o bau :(");
        
}

