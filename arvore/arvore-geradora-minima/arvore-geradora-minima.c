#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct{
    int x;
    int y;
    int indice;
}CONTEUDO, *CONT_PONT;

typedef struct adjacencia{
    CONT_PONT conteudo; 
    double peso; 
    struct adjacencia *prox;
}ADJACENCIA, *ADJ_PONT;

typedef struct {
    CONT_PONT conteudo; 
    ADJ_PONT cab; 
}VERTICE, *VERT_PONT;

typedef struct{
    int max_vertices; 
    int arestas; 
    int quantidade_de_vertices; 
    VERT_PONT vertice; 
}GRAFO, *GRAF_PONT;

// Funçao para criar um grafo com um número específico de vértices
GRAF_PONT criaGrafo (int numero_vertices){
    GRAF_PONT g = (GRAF_PONT)malloc(sizeof(GRAFO)); 
    if(!g) 
        return NULL;
    
    g->max_vertices = numero_vertices; // Define o número máximo de vértices
    g->arestas = 0; // Inicializa o contador de arestas como zero
    g->quantidade_de_vertices = 0; // Inicializa a quantidade de vértices como zero

    // Aloca memória para o vetor de vértices e inicializa cada vértice
    g->vertice = (VERT_PONT)malloc(numero_vertices * sizeof(VERTICE));
    for(int i = 0; i < numero_vertices; i++){
        g->vertice[i].cab = NULL; 
        g->vertice[i].conteudo = NULL; 
    }
    return (g); 
}

// Funçao para criar uma nova aresta
ADJ_PONT criarAdjacencia (CONT_PONT conteudo, double peso){
    ADJ_PONT adj = (ADJ_PONT)malloc(sizeof(ADJACENCIA)); 
    adj->conteudo = conteudo; 
    adj->peso = peso; 
    adj->prox = NULL; 
    return (adj);
}

// Funçao para criar uma aresta bidirecional entre dois vértices
bool criarAresta (GRAF_PONT g, int inicial_vertice, int final_vertice, double peso){
    if(!g) 
        return false;
    // Verifica se os vértices sao válidos:
    if(final_vertice < 0 || final_vertice >= g->max_vertices)
        return false;
    if(inicial_vertice < 0 || inicial_vertice >= g->max_vertices) 
        return false;

    // Cria a aresta do vértice inicial para o vértice final
    CONT_PONT cont_novo2 = g->vertice[final_vertice].conteudo;
    ADJ_PONT novo2 = criarAdjacencia (cont_novo2, peso);
    novo2->prox = g->vertice[inicial_vertice].cab; 
    g->vertice[inicial_vertice].cab = novo2;

    // Cria a aresta do vértice final para o vértice inicial 
    CONT_PONT cont_novo1 = g->vertice[inicial_vertice].conteudo;
    ADJ_PONT novo1 = criarAdjacencia (cont_novo1, peso);
    novo1->prox = g->vertice[final_vertice].cab; 
    g->vertice[final_vertice].cab = novo1;

    g->arestas++; // Incrementa o contador de arestas do grafo
    return true; 
}

// Funçao para imprimir o grafo e suas adjacências
void printarGrafo(GRAF_PONT g) {
    if (!g) { 
        printf("Grafo nao existe.\n");
        return;
    }

    printf("Numero de vertices: %d\n", g->quantidade_de_vertices);
    printf("Numero de arestas: %d\n", g->arestas);

    for (int i = 0; i < g->max_vertices; i++) {
        printf("Vertice %d: ", i);

        if (g->vertice[i].conteudo) {
            printf("(%d, %d) -> ", g->vertice[i].conteudo->x, g->vertice[i].conteudo->y);
        } else {
            printf("Vazio -> ");
        }

        ADJ_PONT adj = g->vertice[i].cab;
        while (adj) {
            if (adj->conteudo) {
                printf("(%d, %d, %.2f) -> ", adj->conteudo->x, adj->conteudo->y, adj->peso);
            } else {
                printf("Vazio -> ");
            }
            adj = adj->prox;
        }

        printf("NULL\n");
    }
}

double calcularPeso (GRAF_PONT g, int indice_vertice1, int indice_vertice2){
    double peso;
    // Obtém as coordenadas dos vértices
    int x1 = g->vertice[indice_vertice1].conteudo->x;
    int x2 = g->vertice[indice_vertice2].conteudo->x;
    int y1 = g->vertice[indice_vertice1].conteudo->y;
    int y2 = g->vertice[indice_vertice2].conteudo->y;
    // Calcula a distância entre os vértices
    peso = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    return peso;    
}

// Funçao para liberar a memória alocada para o grafo
void destruirGrafo(GRAF_PONT g) {
    if (!g) { 
        return;
    }

    // Percorre cada vértice e libera suas listas de adjacência
    for (int i = 0; i < g->max_vertices; i++) {
        ADJ_PONT adj = g->vertice[i].cab;
        while (adj) {
            ADJ_PONT prox = adj->prox;
            free(adj); 
            adj = prox;
        }
        free(g->vertice[i].conteudo); 
    }

    free(g->vertice); 
    free(g); 
}

// Implementaçao do Algoritmo de Kruskal para encontrar a Árvore Geradora Mínima
void algKruskal(GRAF_PONT g, int orig, int *pai, double *somaPesos){
    if (!g) { 
        return;
    }

    int i, dest, NV = g->quantidade_de_vertices;
    *somaPesos = 0; 

    // Aloca e inicializa o vetor de componentes da árvore
    int *arv = (int*)malloc(NV * sizeof(int));
    for(i = 0; i < NV; i++){
        arv[i] = i; // Cada vértice começa em seu próprio componente
        pai[i] = -1; 
    }
    pai[orig] = orig; // Define o vértice de origem como seu próprio pai

    while(1){
        double menor_peso = INFINITY; // Inicializa o menor peso com infinito
        orig = -1;
        dest = -1;

        // Percorre todos os vértices do grafo
        for(i = 0; i < NV; i++){ 
            ADJ_PONT aux = g->vertice[i].cab;
            while(aux){
                // Verifica se a aresta nao conecta dois vértices do mesmo componente, ou seja, se sao arvores diferentes
                if(arv[i] != arv[aux->conteudo->indice]){
                    if(menor_peso > aux->peso){ // Se encontrou um peso menor, atualiza
                        menor_peso = aux->peso;
                        orig = i;
                        dest = aux->conteudo->indice;
                    }
                }
                aux = aux->prox;
            }
        }

        if(orig == -1 || dest == -1) break; // Se nao encontrou aresta válida, termina o loop
        *somaPesos += menor_peso; // Adiciona o menor peso à soma total

        if(pai[orig] == -1) pai[orig] = dest;
        else pai[dest] = orig;

        // Atualiza o vetor de componentes de árvore (atualiza as arvores que se uniram)
        for(i = 0; i < NV; i++){
            if(arv[i] == arv[dest])
                arv[i] = arv[orig];
        }
    }

    free(arv);
}

// Funçao para inserir um novo vértice no grafo
bool inserirVertice (GRAF_PONT g, int x, int y){
    if(g->quantidade_de_vertices == g->max_vertices) // Verifica se o grafo já está cheio
        return false;
    // Verifica se o vértice já existe no grafo
    for(int i = 0; i < g->quantidade_de_vertices; i++)  
        if(g->vertice[i].conteudo->x == x && g->vertice[i].conteudo->y == y)
            return false;

    // Aloca e inicializa o conteúdo do novo vértice
    CONT_PONT novo = (CONT_PONT)malloc(sizeof(CONTEUDO));
    novo->x = x;
    novo->y = y;
    novo->indice = g->quantidade_de_vertices;
    g->vertice[g->quantidade_de_vertices].conteudo = novo;
    g->quantidade_de_vertices++;
    return true; 
}


int main() {
    int numero_vertices;
    double soma;
    int C, x, y;
    
    printf("Quantos casos testes serao inseridos? ");
    scanf("%d", &C);
    
    for(int i = 0; i < C; i++){
        printf("Quantos vértices serao inseridos? ");
        scanf("%d", &numero_vertices);

        GRAF_PONT g = criaGrafo(numero_vertices);
        if (g == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para o grafo.\n");
            return 0;
        }

        // Solicita e insere os vértices no grafo
        printf("Insira os vertices: \"x y\"\n");
        for(int j = 0; j < numero_vertices; j++){
            scanf("%d %d", &x, &y);
            if(!inserirVertice(g, x, y)){
                printf("Falha ao inserir vertice!\n");
                j--;
            }
        }

        // Cria arestas entre todos os pares de vértices
        for(int i = 0; i < g->quantidade_de_vertices; i++){
            for(int j = i + 1; j < g->quantidade_de_vertices; j++){
                criarAresta(g, i, j, calcularPeso(g, i, j));
            }
        }

        int *pai = (int*)malloc(numero_vertices * sizeof(int));
        
        algKruskal(g, 0, pai, &soma);
        
        printf("\nA soma dos pesos eh: %.2f\n", soma/100);
        
        destruirGrafo(g);
        free(pai);
    }
    
    return 0;
}
