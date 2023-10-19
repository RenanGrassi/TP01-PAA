#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <ncurses.h>


#if defined(__MINGW32__) || defined(_MSC_VER)
#define limparInput() fflush(stdin)
#define limparTela() system("cls");
#define pausarTela() system("pause");
#define ncPausar() printw("\nPressione alguma tecla para continuar..."); refresh(); limparInput(); getch(); limparTela();refresh();

#else
#include <stdio_ext.h>
#define limparInput() __fpurge(stdin)
#define limparTela() system("clear");
#define pausarTela() printf("\nPress any key to continue..."); limparInput(); getchar(); limparInput(); 
#define ncPausar() printw("\nPressione alguma tecla para continuar..."); refresh(); limparInput(); getch(); limparTela();refresh();

#endif
