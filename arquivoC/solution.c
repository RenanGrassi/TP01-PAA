#include "../headers/solution.h"

void mostrarSequencia(int** routes, int tam){

    for (int i = 0; i < tam; i++) {

        printf("[%d,%d]", routes[i][0], routes[i][1]);
        printw("[%d,%d]", routes[i][0], routes[i][1]);
        refresh();

        if (i < tam - 1){
            printf(",");
            printw(",");
            refresh();
        }
    }
    printf("\n");
    printw("\n");
}

bool checkingRoute(TipoMap *map, int* x, int* y, bool poder) {
    
    if (poder){
        if(*x == -1)
            *x = map->tamI - 1;
        else if(*x == map->tamI)
            *x = 0;
        else if(*y == -1)
            *y = map->tamJ - 1;
        else if (*y == map->tamJ)
            *y = 0;
    }

    if(*x >= 0 && *x < map->tamI && *y >= 0 && *y < map->tamJ && map->MatrixMovimento[*x][*y] != '1' && map->MatrixMovimento[*x][*y] != 'p'){
        return true;
    }


    else{
        return false;
    }
}

bool movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys, bool poder){

    int abriu = false;

    if(map->MatrixMovimento[atualI][atualJ] == 'C')
        (*keys)++;

    if(map->MatrixMovimento[atualI][atualJ] == 'X' && *keys == map->keys){
        printf("Indiana Jones conseguiu abrir o bau :)\n");
        printw("Indiana Jones conseguiu abrir o bau :)\n");
        abriu = true;
    }

    map->MatrixMovimento[atualI][atualJ] = 'P';
    printw("\n");
    printf("\n");
    showMap(map, true, poder);
    printw("\n Indiana Jones pegou %d chaves\n", *keys);
    printf("\n Indiana Jones pegou %d chaves\n", *keys);
    refresh();
    map->MatrixMovimento[atualI][atualJ] = 'p';

    return abriu;
}

void movimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = 'p';
}

void reMovimentacao(TipoMap* map, int atualI, int atualJ){
        map->MatrixMovimento[atualI][atualJ] = map->Matrix[atualI][atualJ];
}

void irProxCaminho(PCaminho caminho, int tam, TipoMap* map, int** routes){

    if(caminho->proxCaminho == NULL){

        caminho->proxCaminho = (PCaminho)malloc(sizeof(Caminho));
        caminho->proxCaminho->tamanho = tam;
        caminho->proxCaminho->vetCaminho = (int**) malloc(sizeof(int*) * (tam));

        for (int i = 0; i < tam; i++) {
                caminho->proxCaminho->vetCaminho[i] = (int*) malloc(sizeof(int) * 2);
                caminho->proxCaminho->vetCaminho[i][0] = routes[i][0];
                caminho->proxCaminho->vetCaminho[i][1] = routes[i][1];
        }

        caminho->proxCaminho->proxCaminho = NULL;

    }

    else if(tam <= caminho->proxCaminho->tamanho ){
        PCaminho prox = caminho->proxCaminho;

        caminho->proxCaminho = (PCaminho)malloc(sizeof(Caminho));
        caminho->proxCaminho->tamanho = tam;
        caminho->proxCaminho->vetCaminho = (int**) malloc(sizeof(int*) * (tam));

        for (int i = 0; i < tam; i++) {
                caminho->proxCaminho->vetCaminho[i] = (int*) malloc(sizeof(int) * 2);
                caminho->proxCaminho->vetCaminho[i][0] = routes[i][0];
                caminho->proxCaminho->vetCaminho[i][1] = routes[i][1];
        }
           
        caminho->proxCaminho->proxCaminho = prox;
    }

    else{
        irProxCaminho(caminho->proxCaminho, tam, map, routes);
        return;
    }
           
}

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int* caminhosJaVistos, int recursividade, TipoRecursividade* rec) {

    movimentacao(map, x, y);

    routes[(tam)][0] = x; 
    routes[(tam)][1] = y; // salva a posiçao sendo verificada agora
    (tam)++;

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        // onde coloca o caminho percorrido
        irProxCaminho(map->caminhosPossiveis, tam, map, routes);
        (*caminhosJaVistos)++;

        if (*caminhosJaVistos > 40000)
            return true;
        
    }


    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};  // seguencia de movimentos cima, esquerda, baixo, direita

    for (int i = 0; i < 4; i++) { // testa a sequencia
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (checkingRoute(map, &newX, &newY, false)) {
            
            if (map->Matrix[newX][newY] == 'C') {
                keys_collected++;
            }

            movimentacao(map, newX, newY);

            rec->Recursividade++; 
            recursividade++;

            if (recursividade > rec->maiorRecursividade)
                rec->maiorRecursividade = recursividade;
            // conta a recursividade sempre que entra na funcao findShortestPath

            if (findShortestPath(newX, newY, keys_collected, map, routes, tam, caminhosJaVistos, recursividade, rec)) {
                return true;
            }

            reMovimentacao(map, newX, newY);

            if (map->Matrix[newX][newY] == 'C') {
                keys_collected--;
            }
        }
    }

    routes[(tam)][0] = 0;
    routes[(tam)][1] = 0;
    (tam)--;


    return false;
}

void mostragemCaminho(TipoMap* map, PCaminho caminho, int* rotaN){
    int keys = 0;

    copyMap(map);

    if (caminho == NULL) {
        limparTela();
        printf("\n\nIndiana Jones correu muito!! Mas acabou\n\n");
        printw("\n\nIndiana Jones correu muito!! Mas acabou\n\n");
        refresh();
        return;
    }
    (*rotaN) ++;
    

    for (int i = 0; i < caminho->tamanho; i++) {
        limparTela();
        printf("\nmostragem: %d\n", *rotaN);
        printw("\nmostragem: %d\n", *rotaN);
        printf("\ntamanho: %d\n", caminho->tamanho);
        printw("\ntamanho: %d\n", caminho->tamanho);

        movimentacaoShow(map, caminho->vetCaminho[i][0], caminho->vetCaminho[i][1], &keys, false);     
        refresh(); 
        timePause();
    }
    printw("\nSe desejar parar de mostrar aperte 0");
    printw("\nOu pressione outra tecla para continuar...");
    printf("\nSe desejar parar de mostrar aperte 0");
    printf("\nOu pressione outra tecla para continuar...");
    refresh();
    int opcao = getch();
    
    if(opcao == '0')
        return;

    mostragemCaminho(map, caminho->proxCaminho, rotaN);

}

void mostraRecursividade(TipoRecursividade* rec){
    printf("Nivel maximo recursividade: %d\n", rec->maiorRecursividade);
    printf("Recursividade: %ld\n", rec->Recursividade);

    printw("Nivel maximo recursividade: %d\n", rec->maiorRecursividade);
    printw("Recursividade: %ld\n", rec->Recursividade);
    refresh();
}

void generateRec(TipoRecursividade* rec){
    rec->maiorRecursividade = 0;
    rec->Recursividade = 0;
}

void procurarCaminho(TipoMap* map, int* caminhosJaVistos, TipoRecursividade* rec){

    int** routes = (int**) malloc(sizeof(int*) * (map->tamI * map->tamJ));
    for (int i = 0; i < map->tamI * map->tamJ; i++) {
        routes[i] = (int*) malloc(sizeof(int) * 2);
    }

    int tam = 0;
    int recursividade = 0;

    copyMap(map);
    if (map->caminhosPossiveis->proxCaminho == NULL){
        rec->Recursividade++; 
        recursividade++;

        if (recursividade > rec->maiorRecursividade)
            rec->maiorRecursividade = recursividade;
        // conta a primeira chamada da funçao findShortestPath
        findShortestPath(0, 0, 0, map, routes, tam, caminhosJaVistos, recursividade, rec);
    }
    
    
    if(*caminhosJaVistos){
        int opcao = -1  ;

        while (opcao != 0){
            int keys = 0;
            int rotaN = 0;

            copyMap(map);
            
            printf("Foram encontrados %d caminhos possiveis\n", *caminhosJaVistos);
            printf("Escolha uma opcao:\n");
            printf("1 - Mostrar o menor caminho\n");
            printf("2 - Mostrar todos os caminhos\n");
            printf("3 - Mostrar como solicitado na especificacao do TP\n");
            printf("4 - Mostrar recursividade\n");
            printf("0 - Sair\n");

            printw("Foram encontrados %d caminhos possiveis\n", *caminhosJaVistos);
            printw("Escolha uma opcao:\n");
            printw("1 - Mostrar o menor caminho\n");
            printw("2 - Mostrar todos os caminhos\n");
            printw("3 - Mostrar como solicitado na especificacao do TP\n");
            printw("4 - Mostrar recursividade\n");
            printw("0 - Sair\n");

            refresh();

            opcao = getch();
            opcao -= 48;
            
            if(opcao != 0)
                limparTela();
            
            switch(opcao){
                case 1:
                    if (*caminhosJaVistos == 40001){
                        printw("Indiana Jones talvez nao encontrou o menor caminho, mas eh o melhor dos 40001 percorridos\n");
                        printf("Indiana Jones talvez nao encontrou o menor caminho, mas eh o melhor dos 40001 percorridos\n");
                        refresh();
                        ncPausar();
                    }

                    for(int i = 0; i < map->caminhosPossiveis->proxCaminho->tamanho; i++){
                        limparTela();
                        printw("tamanho = %d\n", map->caminhosPossiveis->proxCaminho->tamanho);
                        printf("tamanho = %d\n", map->caminhosPossiveis->proxCaminho->tamanho);
                        movimentacaoShow(map, map->caminhosPossiveis->proxCaminho->vetCaminho[i][0], map->caminhosPossiveis->proxCaminho->vetCaminho[i][1], &keys, false);
                        timePause();
                    }
                    break;

                case 2:
                    if (*caminhosJaVistos == 40001){
                            printw("Indiana Jones talvez nao encontrou o menor caminho, mas eh o melhor dos 40001 percorridos\n");
                            printf("Indiana Jones talvez nao encontrou o menor caminho, mas eh o melhor dos 40001 percorridos\n");
                            refresh();
                            ncPausar();
                        }
                    mostragemCaminho(map, map->caminhosPossiveis->proxCaminho, &rotaN);
                    break;

                case 3:
                    mostrarSequencia(map->caminhosPossiveis->proxCaminho->vetCaminho, map->caminhosPossiveis->proxCaminho->tamanho);
                    break;
                
                case 4:
                    mostraRecursividade(rec);
                    break;
                case 0:
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    printw("Opcao invalida. Tente novamente.\n");
            }
            if(opcao != 0){
                ncPausar();
            }

        }
    }

    else{
        printf("Indiana Jones nao consegue abrir o bau :(\n");
        printw("Indiana Jones nao consegue abrir o bau :(\n");
    }

    refresh();
}
