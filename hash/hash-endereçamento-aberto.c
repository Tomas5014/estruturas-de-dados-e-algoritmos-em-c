/**********************************************************************************************************************************************************************************************************************************************
Faça um sistema de catalogação de livros que utilize a Tabela Hash. O sistema deve permitir a inserção, remoção e busca de livros. Cada livro é identificado por um código ISBN e contém informações como título, autor e ano de publicação.
Parte 1:Endereçamento aberto
Implemente uma tabela hash usando a técnica de endereçamento aberto para resolver colisões. Utilize o método de duplo hash para isso.
A função hash deve utilizar o código ISBN dos livros para calcular o índice na tabela.
A tabela deve permitir inserção, busca e remoção de livros.
Implemente funções para imprimir todos os livros em uma determinada posição da tabela. 
**********************************************************************************************************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 13           // número primo

#define N 11            // número primo

// h(x,k) = ((x % 13) + k((x % 11) + 1)) % 13;

// h(cod,k) = ((cod % MAX) + k((cod % N) + 1)) % MAX;

typedef struct {
    int cod_ISBN;
    char titulo[50];
    char autor[50];
    int ano;
}Livro;

typedef struct{
    Livro *l[MAX];
    int *ocupado;
}Hash, *PONT;

Livro entradaDeDados (){
    Livro novo;
    printf("Insira o ISBN do livro: ");
    scanf("%d", &novo.cod_ISBN);
    printf("Insira o ano do livro: ");
    scanf("%d", &novo.ano);
    printf("Insira titulo do livro: ");
    scanf("%s", novo.titulo);
    fflush(stdin);
    printf("Insira o autor do livro: ");
    scanf("%s", novo.autor);
    fflush(stdin);
    return novo;
}

int buscaElemento (PONT p, int cod){
    int posicao;
    for(int k = 0; k < MAX; k++){
        posicao = ( (cod % MAX) + ( k * ( (cod % N) + 1 ) ) ) % MAX;
        if(p->ocupado[posicao] == 0){
            return -1; //elemento não encontrado.
        }
        if(p->l[posicao]->cod_ISBN == cod){
            return posicao;
        }
    }
    return -1;    
}


int buscaInsersao (PONT p, int cod){
    int posicao;
    for(int k = 0; k < MAX; k++){
        posicao = ( (cod % MAX) + ( k * ( (cod % N) + 1 ) ) ) % MAX;
        if(p->ocupado[posicao] == 0){
            return posicao; //posição a ser inserida, encontrada. Retorna.
        }
        // Caso não queira aceitar elementos repitidos:

        // if(p->l[posicao]->cod_ISBN == cod){
        //     return -1; // retorna -1 se o elemento já está na hash.
        // }
    }
    return -2;  // retorna -2 se a tabela está cheia.
}

int buscaRemocao (PONT p, int cod){
    int posicao;
    for(int k = 0; k < MAX; k++){
        posicao = ( (cod % MAX) + ( k * ( (cod % N) + 1 ) ) ) % MAX;
        if(p->l[posicao]->cod_ISBN == cod && p->ocupado[posicao] == 1){
            return posicao; // elemento encontrado, retorna a posição.
        }
    }
    return -1;  // Nao tá na hash.
}


bool inserir (PONT p, Livro novo){
    int posicao = buscaInsersao(p, novo.cod_ISBN);
    if(posicao == -2){
        printf("Lista cheia. nao eh possivel inserir.\n");
        return false;
    }
     if(posicao == -1){
        printf("O livro ja esta na lista.\n");
        return false;
    }
    p->l[posicao] = (Livro*)malloc(sizeof(Livro));
    *p->l[posicao] = novo;
    p->ocupado[posicao] = 1;
    return true;
}

bool remover (PONT p, int cod){
    int posicao = buscaRemocao(p, cod);
    if(posicao == -1){
        printf("O livro nao ta na hash.\n");
        return false;
    }
    p->ocupado[posicao] = 0;
    printf("Livro removido.\n");
    return true;
}

void imprimir (PONT p){
    printf("Lista de livros: \n");
    for(int i = 0; i < MAX; i++){
        if(p->ocupado[i] == 1){
            printf("ISBN: %d - Titulo: %s - Autor: %s - Ano: %d - Posicao: %d\n", p->l[i]->cod_ISBN, p->l[i]->titulo, p->l[i]->autor, p->l[i]->ano, i);
        }
    }
    printf("\n");
}

int main (){
    PONT h = (PONT)malloc(sizeof(Hash));
    h->ocupado = (int*)calloc(MAX, sizeof(int));
    int opcao, cod;
    Livro novo;
    
    do {
        printf("----- MENU -----\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Imprimir lista de livros\n");
        printf("4. Buscar elemento.\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                novo = entradaDeDados();
                inserir(h, novo);
                
                break;
            case 2:
                printf("Insira o ISBN do livro a ser removido: ");
                scanf("%d", &cod);
                remover(h, cod);
                break;
            case 3:
                imprimir(h);
                break;
            case 4:
                printf("Insira o ISBN do livro a procurado: ");
                scanf("%d", &cod);
                cod = buscaElemento(h, cod);
                if(cod == -1)
                    printf("Livro nao encontrado.\n");
                else
                    printf("O livro está na lista.\n");
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        
        printf("\n");
        
    } while(opcao != 5);
    
    free(h->ocupado);
    free(h);
    
    return 0;
}