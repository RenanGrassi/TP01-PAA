#include "../headers/solution.h"

bool isSafe(int** map, int maxLinha, int maxColuna, int i, int j){
    if(i >= 0 && i < maxLinha && j >= 0 && j < maxColuna && map[i][j] == 0)
        return true;
    return false;
}

bool solveMap(int** map, int maxLinha, int maxColuna, int i, int j, int** resolve){
    // if (x, y is goal) return true
    if (i == maxLinha - 1 && j == maxColuna - 1 && map[i][j] == 1) {
        resolve[i][j] = 1;
        return true;
    }
    // Check if maze[i][j] is valid
    if (isSafe(map, i, j) == true) {
        // Check if the current block is alreadj part of
        // resolveution path.
        if (resolve[i][j] == 1)
            return false;
        // mark i, j as part of resolveution path
        resolve[i][j] = 1;
        /* Move forward in i direction */
        if (solveMap(map, maxLinha, maxColuna, i + 1, j, resolve) == true)
            return true;
        // If moving in i direction doesn't give solution
        // then Move down in j direction
        if (solveMap(map, maxLinha, maxColuna,  i, j + 1, resolve) == true)
            return true;
        // If none of the above movements work then
        // BACKTRACK: unmark i, j as part of solution path
        resolve[i][j] = 0;
        return false;
    }
    return false;
}
