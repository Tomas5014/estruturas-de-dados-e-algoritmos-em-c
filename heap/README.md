# Fila de Prioridades (Heaps) - Gerenciador de Tarefas

Este repositório contém a implementação de um sistema de gerenciamento de tarefas para equipes de desenvolvimento de software, utilizando a estrutura de dados **Heap** (Fila de Prioridades) em C. O sistema foi projetado para auxiliar na priorização de atividades com base em dois critérios simultâneos: alta urgência e menor tempo de conclusão.

## O Problema: Priorização Dupla

O desafio principal deste projeto foi gerenciar uma mesma coleção de tarefas sob duas óticas diferentes sem perder a consistência. O cenário simulado exige que a equipe saiba exatamente qual a tarefa mais crítica no momento e qual a tarefa mais rápida de ser concluída. Para isso, o sistema requer o uso de **duas heaps operando em conjunto**:

1. **Max-Heap (Heap Máxima):** Organiza as tarefas pela sua **urgência**, garantindo que a tarefa com maior prioridade crítica esteja sempre na raiz da árvore para ser resolvida primeiro.
2. **Min-Heap (Heap Mínima):** Organiza as tarefas pelo seu **tempo estimado de conclusão**, permitindo identificar rapidamente "quick wins" (tarefas que podem ser finalizadas mais rápido).

## Detalhes da Implementação Técnica

A solução foi construída utilizando alocação dinâmica de memória (vetores dinâmicos com `malloc` e `realloc`) para representar as árvores binárias (Heaps) implicitamente em arrays.

* **Sincronização Complexa:** A principal complexidade técnica resolvida neste projeto é a sincronização entre as duas Heaps. Quando uma tarefa é escolhida para ser realizada e removida da Max-Heap devido à sua alta urgência, o sistema busca e remove automaticamente a mesma tarefa da Min-Heap (e vice-versa), garantindo que as duas filas reflitam sempre o mesmo conjunto de tarefas ativas.
* **Atualização Dinâmica:** O sistema permite atualizar a urgência de uma tarefa em andamento. O algoritmo reposiciona a tarefa (fazendo o *sift-up* ou *sift-down*) dentro da Max-Heap sem afetar a sua posição na Min-Heap, mantendo as propriedades de ambas as árvores.
* **Estrutura de Dados Estratégica:** Utilização de structs para representar cada `Tarefa` (contendo ID único, nível de urgência e tempo em horas) e uma estrutura controladora `HEAP` que encapsula os vetores dinâmicos e contadores.

## Estrutura de Ficheiros

* `heap.c`: Código-fonte completo contendo a lógica de ambas as Heaps, as funções de manutenção do balanceamento (`subirMax`, `descerMax`, `subirMin`, `descerMin`) e o menu interativo.

## Como compilar e executar

Para compilar e testar o código localmente, certifique-se de ter o compilador GCC instalado. No terminal do seu sistema operativo, execute:

```bash
# Compilar o código-fonte
gcc heap.c -o gerenciador_tarefas

# Executar o programa
./gerenciador_tarefas