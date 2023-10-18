#include "../headers/terminal.h"

void nc(){

    initscr();  // Inicializa a biblioteca ncurses
    cbreak();   // Habilita entrada de teclado em modo "raw" (sem buffer)
    noecho();   // Não exibe os caracteres digitados
    keypad(stdscr, TRUE);  // Habilita teclas especiais (setas, F1, etc.)
    
    start_color();

    init_color(9, 339, 269, 219);
    init_pair(1, 0, 9);

    init_pair(2, COLOR_GREEN, 0);
    init_pair(3, COLOR_YELLOW, 0);
    init_pair(4, COLOR_CYAN, 0);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_color(8, 647, 0, 0);
    init_pair(6, 0, 8);
}

void lerArquivo(FILE** f){
    
    char file_path[250];
    
    do{
        printf("\nDigite o caminho do arquivo: \n");

        strcpy(file_path, "./mapGenerator/");
        //scanf("%s", file_path);
        strcat(file_path, "map0.txt");

        printf("\nArquivo: %s\n", file_path);

        *f = fopen(file_path, "r");

        if(*f == NULL){
            printf("\nArquivo nao encontrado\n\n");
        }
        else{
            printf("\nArquivo encontrado!!!\n\n");
        }
    }

    while(*f == NULL);

}

char chaminhar (){
    nc();

    printw("Pressione uma tecla (sem Enter):\n");
    refresh();

    int ch = getch();  // Lê um caractere


    printw("Você pressionou: %c\n", ch);
    refresh();
    pausar_tela();

    endwin();  // Encerra a biblioteca ncurses
    return 'a';
}

void menu(){

    FILE* f;
    Map *map;
    Map *mapMovimento;
    int a;
    
    lerArquivo(&f);

    map = generate_map(f);
    fclose(f);

    printAtributos(map);
    puts("\n");

    nc();
    show_map(map);
    endwin();

    // pausar_limpar();
    // endwin();
    // chaminhar();
    // nc();

    // mapMovimento = map;
    // movimentacao(mapMovimento, 0, 0);
    // pausar_limpar();

    // mapMovimento = map;
    // movimentacao(mapMovimento, 0, 1);
    // pausar_limpar();

    // mapMovimento = map;
    // movimentacao(mapMovimento, 0, 2);
    // pausar_limpar();

}

void movimentacao(Map* map, int atualI, int atualJ){
    
    map->Matrix[atualI][atualJ] = 'P';
    
    show_map(map);

    map->Matrix[atualI][atualJ] = 'p';
    
}

