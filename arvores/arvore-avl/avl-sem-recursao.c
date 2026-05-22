#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct aux
{
    TIPOCHAVE ch;
    struct aux *esq;
    struct aux *dir;
    struct aux *pai;
    int fb;
    int h;

}NO, *PONT;

PONT novoNo (TIPOCHAVE ch){
    PONT novo = (PONT)malloc(sizeof (NO));
    if(novo){
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = NULL;
        novo->fb = 0;
        novo->ch = ch;
        novo->h = 0;
        }else{
            printf("\nErro ao alocar memoria pro ponteiro.\n");
        }
    return novo;
}


int alturaDoNO (PONT p){
    if(p->esq == NULL && p->dir == NULL)
        return 0;
    if(p->esq != NULL && p->dir != NULL){
        if(p->esq->h > p->dir->h)
            return p->esq->h + 1;
        else 
            return p->dir->h + 1;
    }
    else{
        if(p->esq)
            return p->esq->h + 1;
        else 
            return p->dir->h + 1;
    }
}


int maior(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanciamento (PONT p){
    if(p)
        return (alturaDoNO(p->dir) - alturaDoNO(p->esq));
    else
        return 0;
}

PONT rotacaoLL (PONT p){ //Rotação pra direita.
    PONT u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    u->pai = p->pai;
    p->pai = u;
    p->h = maior(alturaDoNO(p->esq), alturaDoNO(p->dir)) + 1;
    u->h = maior(alturaDoNO(u->esq), alturaDoNO(u->dir)) + 1;
    p->fb = fatorBalanciamento(p);
    u->fb = fatorBalanciamento(u);
    return u;
}

PONT rotacaoRR (PONT p){ //Rotação pra esquerda.
    PONT u = p->dir;
    p->dir = u->esq;
    u->esq = p;
    u->pai = p->pai;
    p->pai = u;
    p->h = maior(alturaDoNO(p->esq), alturaDoNO(p->dir)) + 1;
    u->h = maior(alturaDoNO(u->esq), alturaDoNO(u->dir)) + 1;
    p->fb = fatorBalanciamento(p);
    u->fb = fatorBalanciamento(u);
    return u;
}

PONT rotacaoRL (PONT p) { // Rotação direita esquerda.
    p->dir = rotacaoLL(p->dir);
    return rotacaoRR (p);
}

PONT rotacaoLR (PONT p){ // Rotação esquerda direita.
    p->esq = rotacaoRR (p->esq);
    return rotacaoLL (p);
}

PONT balancear (PONT raiz){
    int fb = raiz->fb;
    if(fb == -2){
        if(raiz->esq->fb == -1)
            return rotacaoLL(raiz);
        if(raiz->esq->fb == 1)
            return rotacaoLR(raiz);
    }
    if(fb == 2){
        if(raiz->dir->fb == 1)
            return rotacaoRR(raiz);
        if(raiz->dir->fb == -1)
            return rotacaoRL(raiz);
    }
    return raiz;
}

PONT inserirInterativo (PONT raiz, TIPOCHAVE ch){
    PONT novo = novoNo(ch);
    if(raiz ==  NULL){
        raiz = novo;
        return raiz;
    }
    PONT pai, atual = raiz;
    while (atual != NULL){
        pai = atual;
        if(atual->ch > ch)
                atual = atual->esq;
        else{
            if(atual->ch < ch)
                atual = atual->dir;
            else{
                printf("O elemento ja esta na estrutura.\n");
                return raiz;
            }
        }
    }
    if(pai->ch > ch){
        pai->esq = novo;
        novo->pai = pai;
    }else{
        pai->dir = novo;
        novo->pai = pai;
    }
    //Acertar altura e fb:
    atual = pai;
    while(atual != NULL){
        atual->h = alturaDoNO(atual);
        atual->fb = fatorBalanciamento(atual);
        atual = atual->pai;
    }
    return raiz; 
}

PONT remover (PONT raiz, TIPOCHAVE ch){
    if(raiz == NULL){
        printf("Elemento nao encontrado.\n");
        return NULL;
    }
    else{
        if(ch == raiz->ch){
            // O nó a ser removido não tem filhos (Folha):
            if(raiz->dir == NULL && raiz->esq == NULL){
                free(raiz);
                printf("No removido com sucesso.\n");
                return NULL;
            }
            else{
            // O nó a ser removido tem dois filhos:
                if(raiz->dir != NULL && raiz->esq != NULL){
                PONT aux = raiz->esq;
                while(aux->dir != NULL)
                    aux = aux->dir;
                raiz->ch = aux->ch;
                aux->ch = ch;
                printf("Elemento trocado.\n");
                raiz->esq = remover(raiz->esq, ch);
                return raiz;
                }
                else{
                //O nó a ser removido só tem um filho.
                PONT aux;
                if(raiz->esq != NULL)
                    aux = raiz->esq;
                else
                    aux = raiz->dir;
                free(raiz);
                printf("Elemento com um filho removido.\n");
                return aux;
                }
            }
        }else{
            if(ch < raiz->ch)
                raiz->esq = remover(raiz->esq, ch);
            else
                raiz->dir = remover(raiz->dir, ch);
        }
        raiz->fb = fatorBalanciamento(raiz);
        raiz = balancear(raiz);
        return raiz;
    }
}

PONT busca (PONT raiz, TIPOCHAVE ch){
    while(raiz != NULL){
        if(raiz->ch == ch)
            return raiz;
        else{
            if(ch < raiz->ch)
                raiz = raiz->esq;
            else
                raiz = raiz->dir;
        }
    }
    return NULL;
}

void imprimir (PONT raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->dir, nivel + 1);
        printf("\n\n");
        for (i = 0; i < nivel; i++)
            printf("\t");
        printf("%d", raiz->ch);
        imprimir(raiz->esq, nivel + 1);
    }
}

 

int main(){
    PONT raiz = NULL;
    int opcao;
    TIPOCHAVE ch;
    PONT aux;
    do{
        printf("\n\n1 - Inserir\n2 - Remover\n3 - Buscar\n4 - Imprimir\n5 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &ch);
                raiz = inserirInterativo(raiz, ch);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &ch);
                raiz = remover(raiz, ch);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &ch);
                aux = busca(raiz, ch);
                if(aux)
                    printf("Elemento encontrado.\n");
                else
                    printf("Elemento nao encontrado.\n");
                break;
            case 4:
                imprimir(raiz, 1);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }while(opcao != 5);
    return 0;
}


