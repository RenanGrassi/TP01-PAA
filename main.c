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
#include <conio.h>

int main() {
    printf("Pressione qualquer tecla (ou 'q' para sair):\n");

    int ch;
    while (1) {
        ch = _getch();  // Lê uma tecla pressionada
        if (ch == 'q') {
            break;  // Sai do loop se 'q' for pressionado
        }
        printf("Tecla pressionada: %c\n", ch);
    }

    return 0;
}

