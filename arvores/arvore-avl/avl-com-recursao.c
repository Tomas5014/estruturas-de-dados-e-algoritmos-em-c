#include <stdio.h>
#include <malloc.h>

typedef int TIPOCHAVE;

typedef struct aux
{
    TIPOCHAVE ch;
    struct aux *esq;
    struct aux *dir;
    int fb;

}NO, *PONT;

PONT novoNo (TIPOCHAVE ch){
    PONT novo = (PONT)malloc(sizeof (NO));
    if(novo){
        novo->dir = NULL;
        novo->esq = NULL;
        novo->fb = 0;
        novo->ch = ch;
        }else{
            printf("\nErro ao alocar memoria pro ponteiro.\n");
        }
    return novo;
}


int alturaDoNO (PONT p){
    if(p == NULL){
        return -1;
    }
    else{
        int esq = alturaDoNO(p->esq);
        int dir = alturaDoNO(p->dir);
        if(dir > esq)
            return dir + 1;
        else
            return esq + 1;
    }
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
    p->fb = fatorBalanciamento(p);
    u->fb = fatorBalanciamento(u);
    return u;
}

PONT rotacaoRR (PONT p){ //Rotação pra esquerda.
    PONT u = p->dir;
    p->dir = u->esq;
    u->esq = p;
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
        if(raiz->esq->fb == -1 || raiz->esq->fb == 0)
            return rotacaoLL(raiz);
        if(raiz->esq->fb == 1)
            return rotacaoLR(raiz);
    }
    if(fb == 2){
        if(raiz->dir->fb == 1 || raiz->dir->fb == 0)
            return rotacaoRR(raiz);
        if(raiz->dir->fb == -1)
            return rotacaoRL(raiz);
    }
    return raiz;
}


PONT inserir (PONT raiz, TIPOCHAVE ch){
    if(raiz == NULL)
        return novoNo(ch);
    else{
        if(ch < raiz->ch)
            raiz->esq = inserir(raiz->esq, ch);
        else{
            if(ch > raiz->ch)
                raiz->dir = inserir(raiz->dir, ch);
            else
                printf("O elemento ja pertence a estrutura.\nNao eh possivel realizar a insersao.\n");
        }
    }
    
    //Acho que deve acertar o fb de todos os nos até o novo nó.
    raiz->fb = fatorBalanciamento(raiz);

    raiz = balancear(raiz);

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
                raiz->fb = fatorBalanciamento(raiz);
                raiz = balancear(raiz);
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
                raiz->fb = fatorBalanciamento(aux);
                raiz = balancear(aux);
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

void destruirArvore (PONT raiz){
    if(raiz != NULL){
        destruirArvore(raiz->esq);
        destruirArvore(raiz->dir);
        free(raiz);
    }
}

void preOrder(PONT raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->ch);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void posOrder(PONT raiz) {
    if (raiz != NULL) {
        posOrder(raiz->esq);
        posOrder(raiz->dir);
        printf("%d ", raiz->ch);
    }
}

void inOrder(PONT raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esq);
        printf("%d ", raiz->ch);
        inOrder(raiz->dir);
    }
}

int main(){
    PONT raiz = NULL;
    int opcao, h;
    TIPOCHAVE ch;
    PONT aux;
    do{
        printf("\n\n1 - Inserir\n2 - Remover\n3 - Buscar\n4 - Imprimir deitado\n5 - Imprimir em preOreder\n6 - Imprimir em posOrder\n7 - Imprimir inOrder\n8 - Destruir arvore\n9 - altura da arvore\n10 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &ch);
                raiz = inserir(raiz, ch);
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
                preOrder(raiz);
                break;
            case 6:
                posOrder(raiz);
                break;
            case 7:
                inOrder(raiz);
                break;
            case 8:
                printf("Destruindo a arvore...\n");
                destruirArvore(raiz);
                printf("Arvore destruida com sucesso.\n");
                raiz = NULL;
                break;
            case 9:
                h = alturaDoNO(raiz);
                printf("A altura da arvore eh: %d.", h);
                break;

            case 10:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    }while(opcao != 10);
    return 0;
}