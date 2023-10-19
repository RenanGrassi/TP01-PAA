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
        printw("\nDigite o caminho do arquivo: \n");
        refresh();

        strcpy(file_path, "./mapGenerator/");
        //scanf("%s", file_path);
        strcat(file_path, "map0.txt");

        printw("\nArquivo: %s\n", file_path);
        refresh();

        *f = fopen(file_path, "r");

        if(*f == NULL){
            printw("\nArquivo nao encontrado\n\n");
        refresh();
        }
        else{
            printw("\nArquivo encontrado!!!\n\n");
        refresh();
        }
    }

    while(*f == NULL);

}

void identificarCaminhada(int* i, int* j, char ch){


    switch (ch){
        
        case 'w':
            (*i)--;
            break;
        
        case 3:
            (*i)--;
            break;
        
        case 's':
            (*i)++;
            break;
        
        case 2:
            (*i)++;
            break;
        
        case 'a':
            (*j)--;
            break;
        
        case 4: 
            (*j)--;
            break;
        
        case 'd':
            (*j)++;
            break;
        
        case 5: 
            (*j)++;
            break;

        default:
            break;
    }
}

void chaminhar (Map* map){

    int i = 0, j = 0;

    movimentacao(map, i, j);

    while (true){

        int ch = getch();  // Lê um caractere
        limpar_tela();

        identificarCaminhada(&i, &j, ch);
        movimentacao(map, i, j);
    }

}

void menu(){

    FILE* f;
    Map *map;
    int opcao = 1;

    //fazer um swtich case com as opçoes do menu
    //1 - ler arquivo / gerar mapa
    //2 - print atributos
    //3 - printar o mapa
    //4 - Achar o menor caminho
    //5 - Tentar achar o menor caminho sozinho
    //0 - sair

    //faça o menu que pedi acima

    // while (opcao){

    //     // printar menu
    //     // printw()
        
    //     scanf("%d", &opcao);

    //     switch (opcao)
    //     {
    //     case 1:
    //         lerArquivo(&f);

    //         map = generate_map(f);
    //         fclose(f);
    //         break;
        
    //     case 2:
    //         printAtributos(map);
    //         break;

    //     case 3:
    //         show_map(map, false);
    //         break;
        
    //     case 5:
    //         chaminhar(map);
    //         break;
                
    //     default:
    //         break;
    //     }
    // }
    
    
    lerArquivo(&f);

    map = generate_map(f);
    fclose(f);

    printAtributos(map);
    printw("\n");
    refresh();

    show_map(map, false);
    ncPausar();

    chaminhar(map);

    freeMap(map);
}

void movimentacao(Map* map, int atualI, int atualJ){
    
    map->MatrixMovimento[atualI][atualJ] = 'P';
    printw("\n");
    show_map(map, true);

    map->MatrixMovimento[atualI][atualJ] = 'p';
    
}

