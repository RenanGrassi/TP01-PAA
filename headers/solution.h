#include "include.h"

// typedef struct Posicao PPosicao;
// typedef struct Posicao{
    
//     union {

//         struct{
//             PPosicao posicaoFinal;
//         } primeraPosicao;

//         struct {
//             int tam;
//         } ultimaPosicao;

//         int linha;
//         int coluna;
//         PPosicao proxPosicao;
//     };

// } TipoPosicao;


// typedef struct ListaPosicao{

//     PPosicao* primeiro;
//     PPosicao* ultimo;
//     int tamanho;

// } TipoListaPosicao;


int kbhit();

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
