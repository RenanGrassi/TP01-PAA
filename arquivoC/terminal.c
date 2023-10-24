#include "../headers/terminal.h"

#ifdef __linux__
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

        init_color(10, 0, 0, 570);
        init_pair(7, 0, 10);
    }
#endif

void lerArquivo(FILE** f){
    
    char file_path[250];
    char ch[2];
    
    do{
        printw("\nDigite o caminho do arquivo: (apenas o numero do mapa)\n");
        printf("\nDigite o caminho do arquivo: (apenas o numero do mapa)\n");
        refresh();

        strcpy(file_path, "./mapGenerator/");
        strcat(file_path, "map");

        scanw("%s", ch);
        scanf("%s", ch);
        
        strcat(file_path, ch);
        strcat(file_path, ".txt");

        printw("\nArquivo: %s\n", file_path);
        printf("\nArquivo: %s\n", file_path);
        refresh();

        *f = fopen(file_path, "r");

        if(*f == NULL){
            printw("\nArquivo nao encontrado\n\n");
            printf("\nArquivo nao encontrado\n\n");
            refresh();
            ncPausar();
        }
        else{
            printw("\nArquivo encontrado!!!\n\n");
            printf("\nArquivo encontrado!!!\n\n");
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

void chaminharUsuario (TipoMap* map){

    printw("Voce esta no modo de caminhada!!\n\nNesse modo voce pode se movimentar pelo mapa usando o 'WASD' ou as setas do teclado\nPara sair do modo de caminhada aperte '0' ou quando voce ficar preso por 5 rodadas sera reiniciado o modo\n\nATENCAO AS REGRAS DO JOGO SE MATEM ENTRETANTO VOCE TEM O PODER DE TRANSFORMAR O MAPA EM GLOBO\n\n");

    printf("Voce esta no modo de caminhada!!\n\nNesse modo voce pode se movimentar pelo mapa usando o 'WASD' do teclado\nPara sair do modo de caminhada aperte '0' ou quando voce ficar preso por 5 rodadas sera reiniciado o modo\n\nATENCAO AS REGRAS DO JOGO SE MATEM\n\n");
    ncPausar();
    int newX = 0, newY = 0;
    int x = 0, y = 0;
    int tentativas = 0;
    int keys = 0;

    copyMap(map);
    movimentacaoShow(map, x, y, &keys);
    

    while (true){
        
        if (tentativas == 5){
            printf("O Indiana Jones bateu a cabeca no caminho errado muitas vezes seguidas, infelizmente ele nao aguentou ;-;");
            printw("O Indiana Jones bateu a cabeca no caminho errado muitas vezes seguidas, infelizmente ele nao aguentou ;-;");
            refresh();
            return;
        }

        int ch = getch();  // Lê um caractere
        limparTela();

        if (ch == '0'){
            break;
        }

        identificarCaminhada(&newX, &newY, ch);

        if (checkingRoute(map, &newX, &newY, true)){
            if(movimentacaoShow(map, newX, newY, &keys))
                return;
            x = newX;
            y = newY;
            tentativas = 0;
        }

        else{
            movimentacaoShow(map, x, y, &keys);
            newX = x;
            newY = y;
            tentativas++;
            
        }
            
    }

}

void menu(){

    FILE* f;
    TipoMap* map;
    TipoRecursividade rec;

    int opcao = -1;
    int mapCriado = 0;
    int caminhosJaVistos = 0;

    while (opcao){

        // printar menu
        printw("\n1 - Ler arquivo e gerar mapa\n2 - Gerar mapa aleatorio\n3 - Printar atributos do mapa\n4 - Printar mapa\n5 - Achar o menor caminho\n6 - Tentar achar algum caminho possivel sozinho\n0 - Sair\n");
        refresh();

        printf("\n1 - Ler arquivo e gerar mapa\n2 - Gerar mapa aleatorio\n3 - Printar atributos do mapa\n4 - Printar mapa\n5 - Achar o menor caminho\n6 - Tentar achar algum caminho possivel sozinho\n0 - Sair\n");
        
        opcao = getch();
        opcao -= 48;

        limparTela();

        switch (opcao){

            case 1:
                if (caminhosJaVistos)
                    freeCaminhos(map->caminhosPossiveis->proxCaminho);

                if (mapCriado)
                    freeMap(map);
                
                endwin();
                lerArquivo(&f);
                nc();

                map = generateMap(f);
                generateRec(&rec);

                fclose(f);
                
                mapCriado = 1;
                caminhosJaVistos = 0;
                break;
            
            case 2:
                limparInput();
                
                if (caminhosJaVistos)
                    freeCaminhos(map->caminhosPossiveis->proxCaminho);

                if (mapCriado)
                    freeMap(map);
        
                map = generateMapAleatorio();
                generateRec(&rec);
                printf("\nMapa aleatorio foi gerado, para ver seus atributos selecione 3\n");
                printw("\nMapa aleatorio foi gerado, para ver seus atributos selecione 3\n");
                mapCriado = 1;
                caminhosJaVistos = 0;
                break;

            case 3:
                if(mapCriado){
                    printAtributos(map);
                    break;
                }

            case 4:
                if(mapCriado){
                    showMap(map, false);
                    break;
                }

            case 5:
                if(mapCriado){
                    procurarCaminho(map, &caminhosJaVistos, &rec);
                    break;
                }

            case 6:
                if(mapCriado){
                    chaminharUsuario(map);
                    break;
                }

            default:
                printf("Opcao invalida. Tente novamente.\n");
                printw("Opcao invalida. Tente novamente.\n");
                break;

            case 0:
                if (caminhosJaVistos)
                    freeCaminhos(map->caminhosPossiveis->proxCaminho);

                if (mapCriado)
                    freeMap(map);
                
                endwin();

                exit(0);
                    
            
        }
        ncPausar();
    }
    
}
