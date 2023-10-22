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

            if (i < tam - 1)
                printf(",");
                printw(",");
                refresh();
        }
    printf("\n");
    printw("\n");
}

bool checkingRoute(TipoMap *map, int i, int j) {

    if(i >= 0 && i < map->tamI && j >= 0 && j < map->tamJ && map->MatrixMovimento[i][j] != '1' && map->MatrixMovimento[i][j] != 'p'){
            //         showMap(map, true);
            // ncPausar();
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
        map->MatrixMovimento[atualI][atualJ] = 'P';
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

    // mostrarSequencia(map->caminhosPossiveis->proxCaminho->vetCaminho, map->caminhosPossiveis->proxCaminho->tamanho);
    // printf("\ntam = %d", tam);
    // printf("\n");
    // mostrarSequencia(routes, tam);
    // showMap(map, true);
    // ncPausar();
           
}

bool findShortestPath(int x, int y, int keys_collected, TipoMap* map, int** routes, int tam, int* cont) {
    
    movimentacao(map, x, y);

    routes[(tam)][0] = x; 
    routes[(tam)][1] = y; // salva a posiçao sendo verificada agora
    (tam)++;

    if (x == map->chestI && y == map->chestJ && keys_collected == map->keys) {
        // onde eu coloco o caminho percorrido
        irProxCaminho(map->caminhosPossiveis, tam, map, routes);
        (*cont)++;
        
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


            if (findShortestPath(newX, newY, keys_collected, map, routes, tam, cont)) {
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
}//deve 

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
        movimentacaoShow(map, caminho->vetCaminho[i][0], caminho->vetCaminho[i][1], &keys);     
        refresh(); 
        ncPausar();
    }

    printw("Indiana Jones conseguiu abrir o bau :)\n");
    printf("Indiana Jones conseguiu abrir o bau :)\n");
    mostragemCaminho(map, caminho->proxCaminho, rotaN);

}

void procurarCaminho(TipoMap* map){

    int** routes = (int**) malloc(sizeof(int*) * (map->tamI * map->tamJ));
    for (int i = 0; i < map->tamI * map->tamJ; i++) {
        routes[i] = (int*) malloc(sizeof(int) * 2);
    }


    int tam = 0;
    int cont = 0;
    int rotaN = 0;


    copyMap(map);
    if (map->caminhosPossiveis->proxCaminho == NULL)
        findShortestPath(0, 0, 0, map, routes, tam, &cont);

    if (cont) { //passar algo como parâmetro
        printf("Indiana Jones consegue abrir o bau de %d formas diferente deseja mostrar todas?\n", cont);
        ncPausar();
        refresh();
        mostragemCaminho(map, map->caminhosPossiveis->proxCaminho, &rotaN);
            
    } 

    else {
        printf("Indiana Jones nao consegue abrir o bau :(\n");
        printw("Indiana Jones nao consegue abrir o bau :(\n");
    }
    refresh();
}
