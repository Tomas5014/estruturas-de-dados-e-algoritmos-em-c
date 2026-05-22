#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 2
#define TAMANHO (2*T + 1)

typedef int TIPOCHAVE;

typedef struct aux{
    int numero_De_Chaves; // numero de elementos presentes na pagina;
    TIPOCHAVE ch[TAMANHO];
    struct aux *p[TAMANHO + 1];
    bool folha; //Flag pra indicar se é folha ou não;
}NODO, *NO_PONT;
// Se fosse nescessario um ponteiro de Registros, bastaria criar outro vetor de ponteiros, paralelo ao tipo chave, pra uma struct registro.

int inserirOrdenado (NO_PONT no, TIPOCHAVE ch, bool ehFolha){

    int i = no->numero_De_Chaves - 1;

    while(i >= 0 && no->ch[i] > ch){
        no->ch[i + 1] = no->ch[i];
        if(!ehFolha){
            no->p[i + 2] = no->p[i + 1];
        }
            i--;
    }
    
    if(i >= 0 && no->ch[i] == ch)
        return -1;

    no->ch[i + 1] = ch;
    no->numero_De_Chaves++;

    return i + 1;
}

NO_PONT selecionaRamoDescidaB(NO_PONT raiz, TIPOCHAVE ch){
    int i = 0;
    while(i < raiz->numero_De_Chaves && raiz->ch[i] < ch)
        i++;

    if(i < raiz->numero_De_Chaves && raiz->ch[i] == ch)
        return NULL;

    return raiz->p[i];
}

void dividirNoB(NO_PONT raiz, NO_PONT filho){
    int i;
    TIPOCHAVE ch = filho->ch[T];

    NO_PONT novo = (NO_PONT)malloc(sizeof(NODO));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->folha = filho->folha;

    for (i = 0; i < T; i++)
        novo->ch[i] = filho->ch[i + T + 1];

    if(!filho->folha){
        for (i = 0; i <= T; i++)
            novo->p[i] = filho->p[i + T + 1];
    }

    filho->numero_De_Chaves = T;

    novo->numero_De_Chaves = T;

    int posicao = inserirOrdenado(raiz, ch, raiz->folha);

    raiz->p[posicao + 1] = novo;    
}

bool inserirArvoreBAuxiliar(NO_PONT *raiz, TIPOCHAVE ch){
    NO_PONT filho = NULL;
    
    if((*raiz)->folha){
        if(inserirOrdenado(*raiz, ch, true) == -1){
            printf("Erro! O elemento ja esta na arvore!\n");
            return false;
        }
    } else {
        // Continua descendo.
        filho = selecionaRamoDescidaB(*raiz, ch);
        if(filho == NULL){
            printf("Erro! O elemento ja esta na arvore!\n");
            return false;
        }

        if (!inserirArvoreBAuxiliar(&filho, ch)) {
            return false;
        }

        if(filho->numero_De_Chaves == TAMANHO){
            dividirNoB(*raiz, filho);
        }
    }

    return true;
}

 
bool inserirArvoreB(NO_PONT *raiz, TIPOCHAVE ch){
    if(*raiz == NULL){
        *raiz = (NO_PONT)malloc(sizeof(NODO));
        if (*raiz == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
        (*raiz)->numero_De_Chaves = 0;
        (*raiz)->folha = true;
        for (int i = 0; i <= TAMANHO; i++)
            (*raiz)->p[i] = NULL;
    }

    if(!inserirArvoreBAuxiliar(raiz, ch))
        return false;

    if((*raiz)->numero_De_Chaves == TAMANHO){
        NO_PONT novaRaiz = (NO_PONT)malloc(sizeof(NODO));
        if (novaRaiz == NULL) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
        novaRaiz->folha = false;
        novaRaiz->numero_De_Chaves = 0;
        for(int j = 0; j <= TAMANHO; j++)
            novaRaiz->p[j] = NULL;
        novaRaiz->p[0] = *raiz;
        dividirNoB(novaRaiz, *raiz);
        *raiz = novaRaiz;
    }
    return true;
}


void imprimirArvoreB(NO_PONT raiz, int nivel) {
    if (raiz != NULL) {
        int i;
        for (i = 0; i < raiz->numero_De_Chaves; i++) {
            imprimirArvoreB(raiz->p[i], nivel + 1);
            printf("%*s%d\n", nivel * 4, "", raiz->ch[i]);
        }
        imprimirArvoreB(raiz->p[i], nivel + 1);
    }
}
/***********************************************************************************************************************************/

int buscaChave (NO_PONT no, TIPOCHAVE ch){
    int i = 0;
    while(i < no->numero_De_Chaves && ch > no->ch[i])
        i++;
    if (i < no->numero_De_Chaves && ch == no->ch[i])
        return i;
    else    return -1;
}

// Função para deletar uma chave de um nó folha
void deletaFolha(NO_PONT no, int j) {
    for (int i = j; i < no->numero_De_Chaves - 1; i++) {
        no->ch[i] = no->ch[i + 1];
    }
    no->numero_De_Chaves--;
}

// Encontra o predecessor da chave
TIPOCHAVE obtemPredecessor(NO_PONT no, int i) {
    no = no->p[i];
    while (!no->folha)
        no = no->p[no->numero_De_Chaves];
    return no->ch[no->numero_De_Chaves - 1];
}

// Encontra o predecessor da chave
TIPOCHAVE obtemSucessor(NO_PONT no, int i) {
    no = no->p[i + 1];
    while(!no->folha)
        no = no->p[0];
    return no->ch[0];
}

int achaIndiceRamoDeDescidaB(NO_PONT raiz, TIPOCHAVE ch){
    int i = 0;
    while(i < raiz->numero_De_Chaves && raiz->ch[i] < ch)
        i++;

    if(i < raiz->numero_De_Chaves && raiz->ch[i] == ch)
        return -1;

    return i;
}

void fundirNos(NO_PONT no, int idx);

void ajustaNo(NO_PONT pai, NO_PONT no, TIPOCHAVE ch){
    if(no->numero_De_Chaves != (T - 1))
        return; // Verifica se precisa de ajuste, retorna se não precisa.

    int i = achaIndiceRamoDeDescidaB(pai, ch);
    NO_PONT vizinho_da_esquerda = NULL;
    NO_PONT vizinho_da_direita = NULL;
    if(i > 0)
        vizinho_da_esquerda = pai->p[i - 1];
    if(i < pai->numero_De_Chaves)
        vizinho_da_direita = pai->p[i + 1];
    if (!vizinho_da_esquerda && !vizinho_da_direita) {
        printf("Erro: não há vizinhos disponíveis para rotação ou fusão.\n");
        return;
    }
    // Rotação de chaves:
    if(vizinho_da_esquerda && vizinho_da_esquerda->numero_De_Chaves > T){
        int j = inserirOrdenado(no,pai->ch[i], no->folha);
        pai->ch[i] = vizinho_da_esquerda->ch[vizinho_da_esquerda->numero_De_Chaves - 1];
        no->p[j+1] = vizinho_da_esquerda->p[vizinho_da_esquerda->numero_De_Chaves];
        vizinho_da_esquerda->numero_De_Chaves--;
        return;
    }
    if(vizinho_da_direita && vizinho_da_direita->numero_De_Chaves > T){
        int j = inserirOrdenado(no, pai->ch[i], no->folha);
        pai->ch[i] = vizinho_da_direita->ch[0];
        no->p[j + 1] = vizinho_da_direita->p[1];
        for(int k = 0; k < vizinho_da_direita->numero_De_Chaves - 1; k++){ // Como eu pego o menor valor do viz.dir., vou precisar pegar o segundo ponteiro pracolocar na função. esse for ajeita os ponteiros e as chaves (empurrando tudo pra esquerda, com exteto o primeiro ponteiro que é preservado, e o segundo ponteiro é apagado (p1)).
            vizinho_da_direita->ch[k] = vizinho_da_direita->ch[k + 1];
            vizinho_da_direita->p[k + 1] = vizinho_da_direita->p[k + 2];
        }
        vizinho_da_direita->numero_De_Chaves--;
        return;
    }
    // Fusão de NO's. Se não tem como rotacionar as chaves (vizinhos no limite de tamanho), então vou fundir com um dos vizinhos.
    if(vizinho_da_direita)
        fundirNos(pai, i);
    else
        fundirNos(pai, i - 1);
    return;
}


void deletaB(NO_PONT *pai, NO_PONT *no, TIPOCHAVE ch) {
    NO_PONT filho;
    int i = buscaChave(*no, ch);
    
    if (i != -1) {
        if ((*no)->folha) {
            // Se é folha, deletar a chave diretamente.
            deletaFolha(*no, i);
        } else {
            // Se não é folha, procurar o predecessor ou sucessor.
            if ((*no)->p[i]->numero_De_Chaves >= T + 1) {
                TIPOCHAVE pred = obtemPredecessor(*no, i);
                (*no)->ch[i] = pred;

                deletaB(&(*no), &(*no)->p[i], pred); // Chama recursivamente para deletar o predecessor.
            } else if ((*no)->p[i + 1]->numero_De_Chaves >= T + 1) {
                TIPOCHAVE suc = obtemSucessor(*no, i);
                (*no)->ch[i] = suc;
                deletaB(&(*no), &(*no)->p[i + 1], suc); // Chama recursivamente para deletar o sucessor.
            } else {
                // Caso contrário, fundir nós e deletar.
                fundirNos(*no, i);
                deletaB(&(*no), &(*no)->p[i], ch);
            }
        }
    } else {
        if (!(*no)->folha) {
            filho = selecionaRamoDescidaB(*no, ch);
            if (filho == NULL) {
                printf("Elemento não encontrado!\n");
                return;
            }

            deletaB(&(*no), &filho, ch);  // Chamada recursiva passando o filho como ponteiro de ponteiro.
            ajustaNo(*no, filho, ch); // Ajusta o nó se necessário após a deleção.
        } else {
            printf("Elemento não encontrado!\n");
            return;
        }
    }

    // Verifica se o nó precisa ser ajustado (caso de fusão ou deleção).
    if (*pai == *no && (*no)->numero_De_Chaves == 0) {
        NO_PONT temp = *no;
        // Se o nó é a raiz e ficou vazio, a nova raiz deve ser ajustada.
        if ((*no)->folha) {
            *pai = NULL;  // A árvore fica vazia.
        } else {
            if (!(*no)->folha && (*no)->p[0] != NULL) {
                *pai = (*no)->p[0];  // Ajusta a raiz apenas se o primeiro filho existir.
            }
        }
        free(temp);
    }
}

// Função para fundir dois nós
void fundirNos(NO_PONT no, int idx) {
    NO_PONT filho = no->p[idx];
    NO_PONT irmao = no->p[idx + 1];
    int t = filho->numero_De_Chaves;

    filho->ch[t] = no->ch[idx];

    for (int i = 0; i < irmao->numero_De_Chaves; i++) {
        filho->ch[i + t + 1] = irmao->ch[i];
    }

    if (!filho->folha) {
        for (int i = 0; i <= irmao->numero_De_Chaves; i++) {
            filho->p[i + t + 1] = irmao->p[i];
        }
    }

    for (int i = idx + 1; i < no->numero_De_Chaves; i++) {
        no->ch[i - 1] = no->ch[i];
        no->p[i] = no->p[i + 1];
    }

    filho->numero_De_Chaves += irmao->numero_De_Chaves + 1;
    no->numero_De_Chaves--;

    free(irmao);
}

int main() {
    NO_PONT raiz = NULL;
    int opcao, chave;
    
    do {
        printf("\nMenu:\n");
        printf("1. Inserir chave\n");
        printf("2. Deletar chave\n");
        printf("3. Imprimir árvore\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &chave);
                if (inserirArvoreB(&raiz, chave)) {
                    printf("Chave inserida com sucesso!\n");
                } else {
                    printf("Erro ao inserir chave!\n");
                }
                printf("Árvore B:\n");
                imprimirArvoreB(raiz, 0);
                break;
                
            case 2:
                printf("Digite a chave a ser deletada: ");
                scanf("%d", &chave);
                deletaB(&raiz, &raiz, chave);
                printf("Árvore B:\n");
                imprimirArvoreB(raiz, 0);
                break;
                
            case 3:
                printf("Árvore B:\n");
                imprimirArvoreB(raiz, 0);
                break;
                
            case 4:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 4);
    
    return 0;
}