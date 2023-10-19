#include "./headers/terminal.h"

// int main(){

//     // printf("\x1b[32m\x1b[41mEste texto tem fundo vermelho e texto verde.\x1b[0m\n");  // Define fundo vermelho e texto verde, depois restaura as cores padrão
//     // pausarTela();

//     // nc();

//     menu();
    
//     // endwin();  // Encerra a biblioteca ncurses
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit() {
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

int main() {
    printf("Pressione qualquer tecla (ou 'q' para sair):\n");

    while (1) {
        if (kbhit()) {
            int key = getchar();
            if (key == 'q') {
                break;  // Sai do loop se 'q' for pressionado
            }
            printf("Tecla pressionada: %c\n", key);
        }
    }

    return 0;
}
