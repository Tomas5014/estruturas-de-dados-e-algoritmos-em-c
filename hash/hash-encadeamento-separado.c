#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define Tamanho_Da_Hash 11

// Livro:
typedef struct{
    char titulo[50];
    int cod_ISBN;
    char autor[50];
    int ano;

}REGISTRO;

// Lista ligada:
typedef struct aux{
    REGISTRO reg;
    struct aux *prox;

}NODE, *PONT;

typedef struct{
    PONT inicio;
    int quantidade_De_Elementos;
}LISTA;

//Hash:
typedef struct{
    LISTA hash[Tamanho_Da_Hash];
}HASH;

/*  Para calcular a posicao, o criterio que eu escolhi é somar o valor da tabela aScII de todos os carateres, do nome do livro, % tamanho.  */
int calcular_Posicao (char *titulo){
    int posicao = 0;
    // a funcao toupper() converte a letra pra maiúsculo, caso ela seja minúscula.
    for(int i = 0; titulo[i] != '\0'; i++)
        posicao += toupper((int)titulo[i]);
    posicao %= Tamanho_Da_Hash;
    return posicao;
}

void inicializar_Hash (HASH *h){
    for(int i = 0; i < Tamanho_Da_Hash; i++){
        h->hash[i].inicio = NULL;
        h->hash[i].quantidade_De_Elementos = 0;
    }
}

PONT busca_Sequencial_Lista (LISTA *l, char *titulo){
    PONT pos = l->inicio;
    while(pos != NULL){
        // a funcao strcasecmp() verifica se as duas strings sao iguais, sem diferenciar maiúsculas e minúsculas. Retorna 0 se elas forem iguais.
        if (strcasecmp(titulo, pos->reg.titulo) == 0) {
            return pos;
        }
        pos = pos->prox;
    }
    return NULL;
}

void inserir_Lista(REGISTRO reg, LISTA *l){
    PONT pos = l->inicio;
    PONT novo = (PONT)malloc(sizeof(NODE));
    novo->reg = reg;
    novo->prox = NULL;
    if(pos == NULL)
        l->inicio = novo;
    else{
        while(pos->prox != NULL)
            pos = pos->prox;
        pos->prox = novo;
    }
    l->quantidade_De_Elementos++;        
}

void inserir_Na_Hash(REGISTRO reg, HASH *h){
    int posicao = calcular_Posicao(reg.titulo);
    inserir_Lista(reg, &(h->hash[posicao])); // Possivel erro na forma como eu to mandando a lista!
}

void remover_Hash(char *titulo, HASH *h){
    int posicao = calcular_Posicao(titulo);
    // inicio da lista onde o livro pode estar:
    LISTA *l = &(h->hash[posicao]);
    PONT pos = l->inicio;
    PONT ant = NULL;
    // flag pra saber se algum elemento foi removido, ja que essa hash vai aceitar elementos repetidos.
    int flag = 0;
    while(pos != NULL){
        // a funcao strcasecmp() verifica se as duas strings sao iguais, sem diferenciar maiúsculas e minúsculas. Retorna 0 se elas forem iguais.
        if (strcasecmp(titulo, pos->reg.titulo) == 0) {
            flag = 1;
            if(ant == NULL){
                l->inicio = pos->prox;
                free(pos);
                pos = l->inicio;
            }else{
                ant->prox = pos->prox;
                free(pos);
                pos = ant->prox;
            }
            printf("Livro removido!\n");
        }else{
            ant = pos;
            pos = pos->prox;
        }
    }
    if(!flag)
        printf("Livro nao encontrado!\n");
}

void imprimir_Livro(REGISTRO reg) {
    printf("Titulo: %s\n", reg.titulo);
    printf("codigo ISBN: %d\n", reg.cod_ISBN);
    printf("autor: %s\n", reg.autor);
    printf("ano: %d\n", reg.ano);
}

void imprimir_Posicao(char *titulo) {
    int posicao = calcular_Posicao(titulo);
    printf("Posicao na tabela: %d\n", posicao);
}

void imprimir_Livros_Posicao(HASH *h, int posicao) {
    LISTA *l = &(h->hash[posicao]);
    PONT pos = l->inicio;
    while (pos != NULL) {
        imprimir_Livro(pos->reg);
        pos = pos->prox;
    }
}

void destruirEstrutura (HASH *h){
    for(int i = 0; i < Tamanho_Da_Hash; i++){
        PONT pos;
        pos = h->hash[i].inicio;
        while(pos != NULL){
            PONT var = pos;
            pos = pos->prox;
            free(var);
        }
    }
}

int main() {
    HASH hash;
    inicializar_Hash(&hash);
    
    int opcao;
    do {
        printf("\n----- MENU -----\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Buscar livro\n");
        printf("4. Imprimir livros em uma posicao\n");
        printf("5. imprimir posicao pelo nome.\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                REGISTRO livro;
                printf("\n----- INSERIR LIVRO -----\n");
                printf("Titulo: ");
                scanf(" %[^\n]s", livro.titulo);
                printf("codigo ISBN: ");
                scanf("%d", &livro.cod_ISBN);
                printf("autor: ");
                scanf(" %[^\n]s", livro.autor);
                printf("ano: ");
                scanf("%d", &livro.ano);
                inserir_Na_Hash(livro, &hash);
                printf("Livro inserido com sucesso!\n");
                imprimir_Posicao(livro.titulo);

                break;
            }
            case 2: {
                char titulo[50];
                printf("\n----- REMOVER LIVRO -----\n");
                printf("Titulo: ");
                scanf(" %[^\n]s", titulo);
                
                remover_Hash(titulo, &hash);
                break;
            }
            case 3: {
                char titulo[50];
                printf("\n----- BUSCAR LIVRO -----\n");
                printf("Titulo: ");
                scanf(" %[^\n]s", titulo);
                
                int posicao = calcular_Posicao(titulo);
                PONT livro = busca_Sequencial_Lista(&(hash.hash[posicao]), titulo);
                if (livro != NULL) {
                    printf("Livro encontrado!\n");
                    imprimir_Livro(livro->reg);
                } else {
                    printf("Livro nao encontrado!\n");
                }
                break;
            }
            case 4: {
                int posicao;
                printf("\n----- IMPRIMIR LIVROS EM UMA POSICAO -----\n");
                printf("Posicao: ");
                scanf("%d", &posicao);
                
                imprimir_Livros_Posicao(&hash, posicao);
                break;
            }
            case 5: {
                char titulo[50];
                printf("Titulo: ");
                scanf(" %[^\n]s", titulo);
                imprimir_Posicao(titulo);
                break;
            }
            case 6:
                destruirEstrutura(&hash);
                printf("Estrutura destruida.\n");
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
    
    return 0;
}