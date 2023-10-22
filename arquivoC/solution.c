#include "../headers/solution.h"

void teste(){
    printw("\n\nteste\n\n");
    printf("\n\nteste\n\n");
    refresh();
}

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

bool checkingRoute(TipoMap *map, int i, int j) {

    if(i >= 0 && i < map->tamI && j >= 0 && j < map->tamJ && map->MatrixMovimento[i][j] != '1' && map->MatrixMovimento[i][j] != 'p'){
        return true;
    }
    else{
        return false;
    }
}

void movimentacaoShow(TipoMap* map, int atualI, int atualJ, int* keys){

    if(map->MatrixMovimento[atualI][atualJ] == 'C')
        (*keys)++;

    map->MatrixMovimento[atualI][atualJ] = 'P';
    printw("\n");
    printf("\n");
    showMap(map, true);
    printw("\n Indiana Jones pegou %d chaves\n", *keys);
    printf("\n Indiana Jones pegou %d chaves\n", *keys);
    refresh();
    map->MatrixMovimento[atualI][atualJ] = 'p';
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

    else if(tam <= caminho->tamanho ){
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

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int* caminhosJaVistos) {
    
    movimentacao(map, x, y);

    routes[(tam)][0] = x; 
    routes[(tam)][1] = y; // salva a posiçao sendo verificada agora
    (tam)++;

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        // onde eu coloco o caminho percorrido
        irProxCaminho(map->caminhosPossiveis, tam, map, routes);
        (*caminhosJaVistos)++;
        
    }


    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};  // seguencia de movimentos cima, esquerda, baixo, direita

    for (int i = 0; i < 4; i++) { // testa a sequencia
        int newX = x + dx[i];
        int newY = y + dy[i];

        

        if (checkingRoute(map, newX, newY)) {
            
            if (map->Matrix[newX][newY] == 'C') {
                keys_collected++;
            }

            movimentacao(map, newX, newY);


            if (findShortestPath(newX, newY, keys_collected, map, routes, tam, caminhosJaVistos)) {
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
        printf("\n\nIndiana Jones correu muito!! Mas acabou\n\n");
        printw("\n\nIndiana Jones correu muito!! Mas acabou\n\n");
        refresh();
        return;
    }
    (*rotaN) ++;
    

    for (int i = 0; i < caminho->tamanho; i++) {
        printf("\nmostragem: %d\n", *rotaN);
        printw("\nmostragem: %d\n", *rotaN);
        movimentacaoShow(map, caminho->vetCaminho[i][0], caminho->vetCaminho[i][1], &keys);     
        refresh(); 
        ncPausar();
    }

    printw("Indiana Jones conseguiu abrir o bau :)\n");
    printf("Indiana Jones conseguiu abrir o bau :)\n");
    mostragemCaminho(map, caminho->proxCaminho, rotaN);

}

void procurarCaminho(TipoMap* map, int* caminhosJaVistos){

    int** routes = (int**) malloc(sizeof(int*) * (map->tamI * map->tamJ));
    for (int i = 0; i < map->tamI * map->tamJ; i++) {
        routes[i] = (int*) malloc(sizeof(int) * 2);
    }

    int keys = 0;
    int tam = 0;
    int rotaN = 0;


    copyMap(map);
    if (map->caminhosPossiveis->proxCaminho == NULL)
        findShortestPath(0, 0, 0, map, routes, tam, caminhosJaVistos);
    
    if(*caminhosJaVistos){
        int opcao = -1;

        while (opcao != 0){
            printf("Escolha uma opcao:\n");
            printw("Escolha uma opcao:\n");
            printf("1 - Mostrar o menor caminho\n");
            printw("1 - Mostrar o menor caminho\n");
            printf("2 - Mostrar todos os caminhos\n");
            printw("2 - Mostrar todos os caminhos\n");
            printf("3 - Mostrar por meio de tuplas\n");
            printw("3 - Mostrar por meio de tuplas\n");
            printf("0 - Sair\n");
            printw("0 - Sair\n");

            scanf("%d", &opcao);

            switch(opcao){
                case 1:
                    movimentacaoShow(map, map->caminhosPossiveis->proxCaminho->vetCaminho[0][0], map->caminhosPossiveis->proxCaminho->vetCaminho[0][1], &keys);
                    printf("Indiana Jones conseguiu abrir o bau :)\n");
                    printw("Indiana Jones conseguiu abrir o bau :)\n");
                    break;
                case 2:
                    mostragemCaminho(map, map->caminhosPossiveis->proxCaminho, &rotaN);
                    break;
                case 3:
                    mostrarSequencia(map->caminhosPossiveis->proxCaminho->vetCaminho, map->caminhosPossiveis->proxCaminho->tamanho);
                    break;
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
            
        }
    }

    else{
        printf("Indiana Jones nao consegue abrir o bau :(\n");
        printw("Indiana Jones nao consegue abrir o bau :(\n");
    }

    refresh();
    
    // swtich case
    // 1 mostrar o menor caminho movimentacaoShow()
    // 2 mostrar todos os caminhos mostragemCaminho()
    // 3 mostrar por meio de tuplas mostrarSequencia()
    // 0 sair



    // if (*caminhosJaVistos) { //passar algo como parâmetro
    //     printf("Indiana Jones consegue abrir o bau de %d formas diferente deseja mostrar todas?\n", *caminhosJaVistos);
    //     printw("Indiana Jones consegue abrir o bau de %d formas diferente deseja mostrar todas?\n", *caminhosJaVistos);
    //     ncPausar();
    //     refresh();
    //     // mostragemCaminho(map, map->caminhosPossiveis->proxCaminho, &rotaN);
    //     printw("tam = %d\n", map->caminhosPossiveis->proxCaminho->tamanho);
    //     mostrarSequencia(map->caminhosPossiveis->proxCaminho->vetCaminho, map->caminhosPossiveis->proxCaminho->tamanho);
            
    // } 

    // else {
    //     printf("Indiana Jones nao consegue abrir o bau :(\n");
    //     printw("Indiana Jones nao consegue abrir o bau :(\n");
    // }
    // refresh();
}
