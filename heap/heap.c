#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int urgencia;
    float tempo;
    int ID;
}Tarefa, *PONT;

typedef struct
{
    PONT tempo;
    PONT urgencia;
    int num_elem;
}HEAP, *Heap;

int pai (int i){
    return (i/2);
}

int esq (int i){
    return (i*2);
}

int dir (int i){
    return (i*2 + 1);
}

int busca (PONT t, int ID, int n){
    int i = 1;
    while(i <= n){
        if(t[i].ID == ID)
            return i;
        i++;
    }
    return -1;
}

PONT subirMax (PONT t, int i){
    int j = pai(i);
    if(j >= 1){
        if(t[j].urgencia < t[i].urgencia){
            Tarefa temp = t[i];
            t[i] = t[j];
            t[j] = temp;
            t = subirMax(t, j);
        }
    }
    return t;
}

PONT subirMin (PONT t, int i){
    int j = pai(i);
    if(j >= 1){
        if(t[j].tempo > t[i].tempo){
            Tarefa temp = t[i];
            t[i] = t[j];
            t[j] = temp;
            t = subirMin(t, j);
        }
    }
    return t;
}

void descerMax (PONT t, int i, int n){
    // Descobre qual eh o maior filho de i:
    int e = esq(i);
    int d = dir(i);
    int maior = i;
    if(e <= n && t[e].urgencia > t[i].urgencia)
        maior = e;
    if(d <= n && t[d].urgencia > t[maior].urgencia)
        maior = d;
    if(maior != i){
        // Faca a decida trocando com o maior filho:
        Tarefa temp = t[i];
            t[i] = t[maior];
            t[maior] = temp;
            descerMax(t, maior, n);
    }
}

PONT inserirMax (PONT t, Tarefa novo, int n){
    // Aumenta o tamanho do vetor.
    t = (PONT)realloc(t, sizeof(Tarefa) * (n + 2));
    n++;
    t[n] = novo;
    subirMax(t, n);
    return t;
}

Tarefa removerMin(PONT tempo, PONT urgencia, int n, int flag);

Tarefa removerMax (PONT urgencia, PONT tempo, int n, int flag){
    Tarefa elemento = urgencia[1];
    Tarefa lixo;
    if(flag){
    flag = 0;
    int i = busca(tempo, elemento.ID, n);
    tempo[i].tempo = tempo[1].tempo - 1;
    tempo = subirMin(tempo, i);
    lixo = removerMin(tempo, urgencia, n, flag);
    }
    urgencia[1] = urgencia[n];
    urgencia = (PONT)realloc(urgencia, sizeof(Tarefa) * (n));
    n--;
    descerMax(urgencia, 1, n);
    return elemento;
}

void imprimirMax (PONT t, int n){
    printf("\" ");
    for(int i = 1; i <= n; i++){
        printf("%d ", t[i].ID);
    }
    printf("\"\n");
}

void imprimirMin (PONT t, int n){
    printf("\" ");
    for(int i = 1; i <= n; i++){
        printf("%d ", t[i].ID);
    }
    printf("\"\n");
}


PONT inserirMin (PONT t, Tarefa novo, int n){
    // Aumenta o tamanho do vetor.
    t = (PONT)realloc(t, sizeof(Tarefa) * (n + 2));
    n++;
    t[n] = novo;
    t = subirMin(t, n);
    return t;
}


void descerMin (PONT t, int i, int n){
    // Descobre qual eh o maior filho de i:
    int e = esq(i);
    int d = dir(i);
    int menor = i;
    if(e <= n && t[e].tempo < t[i].tempo)
        menor = e;
    if(d <= n && t[d].tempo < t[menor].tempo)
        menor = d;
    if(menor != i){
        // Faca a decida trocando com o maior filho:
        Tarefa temp = t[i];
            t[i] = t[menor];
            t[menor] = temp;
            descerMin(t, menor, n);
    }
}

Tarefa removerMin (PONT tempo, PONT urgencia, int n, int flag){
    Tarefa elemento = tempo[1];
    if(flag){
    Tarefa lixo;
    flag = 0;
    
    int i = busca(urgencia, elemento.ID, n);
    urgencia[i].urgencia = urgencia[1].urgencia + 1;
    urgencia = subirMax(urgencia, i);
    lixo = removerMax(urgencia, tempo, n, flag);
    }
    tempo[1] = tempo[n];
    tempo = (PONT)realloc(tempo, sizeof(Tarefa) * (n));
    (n)--;
    descerMin(tempo, 1, n);
    return elemento;
}


PONT atualizacaoDeUrgencia (PONT t, int n){
    int ID, i, nova;
    printf("Qual o ID da tarefa deve ser atualizada? ");
    scanf("%d", &ID);
    i = busca(t, ID, n);
    if(i == -1){
        printf("A tarefa nao consta na lista!\n");
        return t;
    }
    printf("Tarefa encontrada. Sua urgencia eh %d. Qual sera a nova urgencia? ", t[i].urgencia);
    scanf("%d", &nova);
    if(nova < t[i].urgencia){
        t[i].urgencia = nova;
        descerMax(t, i, n);
    }
    else{
        t[i].urgencia = nova;
        t = subirMax(t, i);
    }
    printf("Urgencia atualizada!\n");
    return t;
}


void entradaDeTarefa (Heap h){
    Tarefa t;

    printf("Insira o ID: ");
    scanf("%d",&t.ID);
    printf("Insira a urgencia: ");
    scanf("%d",&t.urgencia);
    printf("Insira o tempo, em horas: ");
    scanf("%f",&t.tempo);

    h->urgencia = inserirMax(h->urgencia, t, h->num_elem);
    h->tempo = inserirMin(h->tempo, t, h->num_elem);
    h->num_elem++;
}

int main() {
    Heap h = (Heap)malloc(sizeof(HEAP));
    h->num_elem = 0;
    h->urgencia = (PONT)malloc(sizeof(Tarefa));
    h->tempo = (PONT)malloc(sizeof(Tarefa));
    int opcao;

    do {

        printf("\n----- MENU -----\n");
        printf("1. Inserir tarefa\n");
        printf("2. Remover tarefa com maior urgencia\n");
        printf("3. Remover tarefa com menor tempo\n");
        printf("4. Imprimir tarefas por urgencia\n");
        printf("5. Imprimir tarefas por tempo\n");
        printf("6. Atualizar urgencia\n");
        printf("7. Consultar tarefa mais urgente\n");
        printf("8. Consultar tarefa com menor tempo de conclusao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                entradaDeTarefa(h);
                break;
            case 2:
                if (h->num_elem > 0) {
                    int flag = 1;
                    Tarefa tarefaRemovida = removerMax(h->urgencia, h->tempo ,h->num_elem, flag);
                    printf("Tarefa removida com maior urgencia: ID %d\n", tarefaRemovida.ID);
                    h->num_elem--;
                } else {
                    printf("Nao ha tarefas para remover.\n");
                }
                break;
            case 3:
                if (h->num_elem > 0) {
                    int flag = 1;
                    Tarefa tarefaRemovida = removerMin(h->tempo, h->urgencia, h->num_elem, flag);
                    printf("Tarefa removida com menor tempo: ID %d\n", tarefaRemovida.ID);
                    h->num_elem--;
                } else {
                    printf("Nao ha tarefas para remover.\n");
                }
                break;
            case 4:
                printf("Tarefas por urgencia: ");
                imprimirMax(h->urgencia, h->num_elem);
                break;
            case 5:
                printf("Tarefas por tempo: ");
                imprimirMin(h->tempo, h->num_elem);
                break;
            case 6:
                h->urgencia = atualizacaoDeUrgencia(h->urgencia, h->num_elem);
                break;
            case 7:
                if(h->num_elem == 0){
                    printf("Nao ha tarfas na lista.\n");
                    break;
                }
                printf("A tarefa mais urgente eh a de ID %d.\n", h->urgencia[1].ID);
                break;
            case 8:
                if(h->num_elem == 0){
                    printf("Nao ha tarfas na lista.\n");
                    break;
                }
                printf("A tarefa mais rapida eh a de ID %d.\n", h->tempo[1].ID);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    free(h->urgencia);
    free(h->tempo);

    return 0;
}