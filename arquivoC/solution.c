#include "../headers/solution.h"

void teste(){
    printw("\n\nteste\n\n");
    printf("\n\nteste\n\n");
    refresh();
}

bool canMove(int x, int y, int ROWS, int COLS, char parede, bool** visited) {
    printf("\nnewX = %d\nnewY = %d\n", x, y);
    // printf("\n\n%c\n\n", map->Matrix[newX][newY]);
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS && parede != '1' && !visited[x][y])
        printf("foi\n");
    printf("\n%d\n", visited[x][y]);
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && parede != '1' && !visited[x][y];
}

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, bool** visited, int* pathLength, int shortestPath[][2]) {

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        *pathLength = 0;
        return true;
    }

    visited[x][y] = true;
    shortestPath[(*pathLength)][0] = x;
    shortestPath[(*pathLength)][1] = y;
    (*pathLength)++;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        printf("\nnewX = %d\nnewY = %d", newX, newY);
        printf("\n\n%c\n\n", map->Matrix[newX][newY]);

        if (canMove(newX, newY, map->tamI, map->tamJ, map->Matrix[newX][newY], visited)) {
            
            if (map->Matrix[newX][newY] == 'C') {
                keys_collected++;
            }

            if (findShortestPath(newX, newY, keys_collected, map, visited, pathLength, shortestPath)) {
                return true;
            }

            if (map->Matrix[newX][newY] == 'C') {
                keys_collected--;
            }
        }
    }

    *pathLength--;
    visited[x][y] = false;
    return false;
}
