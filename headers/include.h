#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>



#if defined(__MINGW32__) || defined(_MSC_VER)
#include <conio.h>
#define limparInput() fflush(stdin)
#define limparTela() system("cls");
#define pausarTela() system("pause");
#define ncPausar() printf("\nPressione alguma tecla para continuar..."); limparInput(); getch(); limparTela();
#define refresh() ;
#define initscr() ;
#define printw ;
#define getch() _getch();
#define nc() ;
#define endwin();


#else
#include <stdio_ext.h>
#include <ncurses.h>
#define limparInput() __fpurge(stdin)
#define limparTela() clear();
#define pausarTela() printf("\nPress any key to continue..."); limparInput(); getchar();
#define ncPausar() printw("\nPressione alguma tecla para continuar..."); refresh(); limparInput(); getch(); clear(); refresh();
#define printf ;

#endif
