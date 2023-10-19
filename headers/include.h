#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <ncurses.h>


#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_input() fflush(stdin)
#define limpar_tela() cls();
#define pausar_tela() system("pause")
#define ncPausar() printw("\nPressione alguma tecla para continuar..."); refresh(); getch(); cls(); refresh();

#else
#include <stdio_ext.h>
#define limpar_input() __fpurge(stdin)
#define limpar_tela() clear();
#define pausar_tela() printf("\nPress any key to continue..."); limpar_input(); getchar();
#define ncPausar() printw("\nPressione alguma tecla para continuar..."); refresh(); getch(); clear(); refresh();

#endif