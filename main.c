#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 10
#define MAX_COLS 10

char maze[MAX_ROWS][MAX_COLS];
bool visited[MAX_ROWS][MAX_COLS];
int keys_needed;

int ROWS, COLS;

int startX, startY;
int endX, endY;

int shortestPath[MAX_ROWS * MAX_COLS][2];
int pathLength = 0;

bool canMove(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != '1' && !visited[x][y];
}

bool findShortestPath(int x, int y, int keys_collected) {
    if (x == endX && y == endY && keys_collected == keys_needed) {
        pathLength = 0;
        return true;
    }
    visited[x][y] = true;
    shortestPath[pathLength][0] = x;
    shortestPath[pathLength][1] = y;
    pathLength++;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (canMove(newX, newY)) {
            if (maze[newX][newY] == 'C') {
                keys_collected++;
            }

            if (findShortestPath(newX, newY, keys_collected)) {
                return true;
            }

            if (maze[newX][newY] == 'C') {
                keys_collected--;
            }
        }
    }

    pathLength--;
    visited[x][y] = false;
    return false;
}

int main() {
    FILE *inputFile = fopen("C:\\Users\\matto\\.vscode\\TP01-PAA\\map0.txt", "r");

    if (inputFile == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(inputFile, "%d %d", &ROWS, &COLS);
    fscanf(inputFile, "%d", &keys_needed);
    fscanf(inputFile, "%d %d", &endX, &endY);
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fscanf(inputFile, " %c", &maze[i][j]);
        }
    }

    fclose(inputFile);

    if (findShortestPath(startX, startY, 0)) {
    for (int i = 0; i < pathLength; i++) {
        printf("[%d,%d]", shortestPath[i][0], shortestPath[i][1]);
        if (i < pathLength - 1) {
            printf(",");
        }
    }
} else {
    printf("Indiana Jones nao consegue abrir o bau :(");
}

    return 0;
}
