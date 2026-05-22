#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct adjacencia {
    char *vertice;
    struct adjacencia *prox;
}ADJACENCIA, *ADJ_PONT;

typedef struct {
    /*DADOS ARMAZENADOS*/
    ADJ_PONT cab;
}VERTICE, *VERT_PONT;

typedef struct {
    int max_vertices;
    int arestas;
    int quantidade_vertices;
    VERT_PONT adj;
}GRAFO, *GRAF_PONT;

GRAF_PONT criarGrafo (int numero_vertices) {
    GRAF_PONT g = (GRAF_PONT)malloc(sizeof(GRAFO));
    g->max_vertices = numero_vertices;
    g->arestas = 0;
    g->quantidade_vertices = 0;
    g->adj = (VERT_PONT)malloc(numero_vertices * sizeof(VERTICE));
    for(int i = 0; i < numero_vertices; i++){
        g->adj[i].cab = NULL;
    }
    return g;
}

ADJ_PONT criarAdjacencia (char *vertice) {
    ADJ_PONT temp = (ADJ_PONT)malloc(sizeof(ADJACENCIA));
    temp->vertice = (char*)malloc(strlen(vertice) + 1);
    strcpy(temp->vertice, vertice);
    temp->prox = NULL;

    return temp;
}

bool criarAresta (GRAF_PONT g, int indice_vert1, int indice_vert2) {
    if(!g)
        return false;
    if(indice_vert1 >= g->max_vertices || indice_vert2 >= g->max_vertices)
        return false;
    if(indice_vert1 < 0 || indice_vert2 < 0)
        return false;

    // Cria a adjacência de vertice1 para vertice2
    ADJ_PONT novo1 = criarAdjacencia(g->adj[indice_vert2].cab->vertice);
    ADJ_PONT aux = g->adj[indice_vert1].cab;
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo1;

    // Cria a adjacência de vertice2 para vertice1
    ADJ_PONT novo2 = criarAdjacencia(g->adj[indice_vert1].cab->vertice);
    aux = g->adj[indice_vert2].cab;
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo2;

    g->arestas++;
    return(true);
}

// Daqui pra frente, as funcões tem condicões aplicadas exclusivamente para as necessidades do problema proposto.

int criarVertice (GRAF_PONT g, char *nome){
    if(g->quantidade_vertices >= g->max_vertices)
        return -1;
    int indice = -1;
    ADJ_PONT novo = (ADJ_PONT)malloc(sizeof(ADJACENCIA));
    novo->vertice = (char*)malloc(strlen(nome) + 1);
    strcpy(novo->vertice, nome);
    novo->prox = NULL;
    g->adj[g->quantidade_vertices].cab = novo;
    indice = g->quantidade_vertices;
    g->quantidade_vertices++;

    return indice;    
}

int encontrarIndice(GRAF_PONT g, char *nome){
    for(int i = 0; i < g->quantidade_vertices; i++){
        if(g->adj[i].cab != NULL && !strcmp(nome, g->adj[i].cab->vertice))
            return i;
    }
    return -1;
}

bool inserirAresta (GRAF_PONT g, char *vertice1, char *vertice2) {
    if(!g)
        return false;

    int indice1 = encontrarIndice(g, vertice1);
    int indice2 = encontrarIndice(g, vertice2);
    if(indice1 == -1 || indice2 == -1){
        // Se um dos vertices nao esta no grafo e nao cabe mais vertices, returna NULL:
        if(g->quantidade_vertices == g->max_vertices)
            return false;
        if((indice1 == -1 && indice2 == -1) && g->quantidade_vertices + 1 == g->max_vertices)
            return false;
        if(indice1 == -1){
            indice1 = criarVertice(g, vertice1);
        }
        if(indice2 == -1){
            indice2 = criarVertice(g, vertice2);
        }
    }
    if(indice1 == -1 || indice2 == -1) 
        return false; // Falha ao criar vertice

    bool b;
    b = criarAresta(g, indice1, indice2);
    
    if(!b)
        return false;
    return true;
}

void printarGrafo(GRAF_PONT g) {
    if (!g) {
        printf("Grafo nao existe.\n");
        return;
    }

    printf("Numero de vertices: %d\n", g->quantidade_vertices);
    printf("Numero de arestas: %d\n", g->arestas);

    for (int i = 0; i < g->quantidade_vertices; i++) {
        ADJ_PONT adj = g->adj[i].cab;
        printf("Vertice %s: ", adj->vertice);
        adj = adj->prox;
        while (adj != NULL) {
            printf("%s ", adj->vertice);
            adj = adj->prox;
        }
        printf("\n");
    }
}
void visitaP(GRAF_PONT g, int u, char *busca, int *cor, int *tamanho, bool *flag) {
    cor[u] = AMARELO;
    (*tamanho)++;
    //printf("%s\n",g->adj[u].cab->vertice);
    if (!strcmp(busca, g->adj[u].cab->vertice)) {
        *flag = true;
        return;
    }

    ADJ_PONT v = g->adj[u].cab->prox; // Começa após o vertice inicial
    while (v) {
        int indicev = encontrarIndice(g, v->vertice);
        if (indicev != -1 && cor[indicev] == BRANCO) {
            visitaP(g, indicev, busca, cor, tamanho, flag);
            if (*flag) {
                return; // Se o vertice foi encontrado, retorna imediatamente
            }
        }
        v = v->prox;
    }
    cor[u] = VERMELHO;
}

int profundidade(GRAF_PONT g, int partida, char *busca) {
    int *cor = (int *)malloc(g->quantidade_vertices * sizeof(int));
    for (int u = 0; u < g->quantidade_vertices; u++) {
        cor[u] = BRANCO;
    }
    int tamanho = 0; // Começa a contar do zero
    bool flag = false;
    
    if (partida >= 0 && partida < g->quantidade_vertices) {
        visitaP(g, partida, busca, cor, &tamanho, &flag);
    }

    free(cor);

    return flag ? tamanho : -1;
}

void destruirGrafo(GRAF_PONT g) {
    if (g) {
        for (int i = 0; i < g->quantidade_vertices; i++) {
            ADJ_PONT adj = g->adj[i].cab;
            while (adj) {
                ADJ_PONT temp = adj;
                adj = adj->prox;
                free(temp->vertice);
                free(temp);
            }
        }
        free(g->adj);
        free(g);
    }
}

int main() {
    int num_vertices, num_arestas;
    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &num_vertices);
    printf("Digite o numero de arestas do grafo: ");
    scanf("%d", &num_arestas);

    GRAF_PONT grafo = criarGrafo(num_vertices);

    for (int i = 0; i < num_arestas; i++) {
        char vertice1[100], vertice2[100];
        printf("Digite o vertice de origem da aresta %d: ", i+1);
        scanf("%s", vertice1);
        printf("Digite o vertice de destino da aresta %d: ", i+1);
        scanf("%s", vertice2);
        inserirAresta(grafo, vertice1, vertice2);
    }
    printarGrafo(grafo);
    
    char entrada[100], saida[100];
    printf("Digite o vertice de entrada: ");
    scanf("%s", entrada);
    printf("Digite o vertice de saida: ");
    scanf("%s", saida);

    int tamanho_entrada = profundidade(grafo, encontrarIndice(grafo, entrada), "*");
    int tamanho_saida = profundidade(grafo, encontrarIndice(grafo, "*"), saida);

    printf("Tamanho do caminho de entrada ate *: %d\n", tamanho_entrada);
    printf("Tamanho do caminho de * ate saida: %d\n", tamanho_saida);
    printf("Tamanho do caminho total : %d\n", tamanho_saida + tamanho_entrada);

    destruirGrafo(grafo);
    
    return 0;
}