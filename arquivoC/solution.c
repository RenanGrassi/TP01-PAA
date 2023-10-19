#include "../headers/solution.h"

#include <sys/utsname.h>

int kbhit() {

    struct utsname os_info;
    uname(&os_info);

    if (strcmp(os_info.sysname, "Linux") != 0) 
        return 1;

    struct termios oldt, newt;
    int ch;
    int oldf;

    // Salva as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);

    // Desativa o modo canônico do terminal (leitura de linha por linha)
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Configura o descritor de arquivo STDIN_FILENO para não bloquear
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    // Restaura as configurações originais do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Restaura as configurações do descritor de arquivo
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    } 

    return 0;
}


// bool isSafe(char** map, int maxLinha, int maxColuna, int i, int j){
//     if(i >= 0 && i < maxLinha && j >= 0 && j < maxColuna && map[i][j] == 0)
//         return true;
//     return false;
// }

// bool solveMap(char** map, int maxLinha, int maxColuna, int i, int j, char** resolve){ // tem que salvar o menor caminho e mandar dps
//     // if (x, y is goal) return true
//     if (i == maxLinha - 1 && j == maxColuna - 1 && map[i][j] == 1) {
//         resolve[i][j] = 1;
//         return true;
//     }
//     // Check if maze[i][j] is valid
//     if (isSafe(map, maxLinha, maxColuna, i, j) == true) { /// verifica se realmente é seguro
//         // Check if the current block is alreadj part of
//         // resolveution path.// bool solveMaze(int maze[N][N])
// // {
// //     int sol[N][N] = { { 0, 0, 0, 0 },
// //                       { 0, 0, 0, 0 },
// //                       { 0, 0, 0, 0 },
// //                       { 0, 0, 0, 0 } };
// //     if (solveMazeUtil(maze, 0, 0, sol) == false) {
// //         printf("Solution doesn't exist");
// //         return false;
// //     }
// //     printSolution(sol);
// //     return true;
// // }
//         if (resolve[i][j] == 1)
//             return false;
//         // mark i, j as part of resolveution path
//         resolve[i][j] = 1;
//         /* Move forward in i direction */
//         if (solveMap(map, maxLinha, maxColuna, i + 1, j, resolve) == true)
//             return true;
//         // If moving in i direction doesn't give solution
//         // then Move down in j direction
//         if (solveMap(map, maxLinha, maxColuna,  i, j + 1, resolve) == true)
//             return true;

//         if (solveMap(map, maxLinha, maxColuna, i - 1, j, resolve) == true)
//             return true;
        
//         if (solveMap(map, maxLinha, maxColuna, i, j - 1, resolve) == true)
//             return true;
//         // If none of the above movements work then
//         // BACKTRACK: unmark i, j as part of solution path
//         resolve[i][j] = 0;
//         return false;
//     }
//     return false;
// }
