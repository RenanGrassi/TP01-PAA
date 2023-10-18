#include "include.h"

bool isSafe(char** map, int maxLinha, int maxColuna, int i, int j);

// bool solveMaze(int maze[N][N])
// {
//     int sol[N][N] = { { 0, 0, 0, 0 },
//                       { 0, 0, 0, 0 },
//                       { 0, 0, 0, 0 },
//                       { 0, 0, 0, 0 } };
//     if (solveMazeUtil(maze, 0, 0, sol) == false) {
//         printf("Solution doesn't exist");
//         return false;
//     }
//     printSolution(sol);
//     return true;
// }
 
bool solveMap(char** map, int maxLinha, int maxColuna, int i, int j, char** resolve);
