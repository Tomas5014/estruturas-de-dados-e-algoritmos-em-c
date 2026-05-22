# Árvore AVL

Esta pasta contém o código desenvolvido para um trabalho prático focado na estrutura de dados **Árvore AVL**. O objetivo principal foi implementar uma árvore binária de pesquisa que se mantém balanceada de forma automática após cada operação de inserção ou exclusão de nós.

## O que foi implementado

Para demonstrar a compreensão das diferentes formas de manipular a estrutura, o trabalho exigiu a criação de duas versões distintas. Ambas calculam o Fator de Balanceamento (FB) e aplicam as rotações necessárias (Simples à Esquerda/Direita e Duplas) para manter o equilíbrio estrutural.

### 1. Versão Recursiva (`avl-com-recursao.c`)
Nesta abordagem, as operações baseiam-se em chamadas recursivas, o que torna o código mais limpo e declarativo. As seguintes funcionalidades foram completamente implementadas:
* **Inserção e Exclusão:** Lógica de balanceamento automático integrada;
* **Cálculo da Altura da Árvore:** Recurso a uma função recursiva para determinar o nível máximo dos nós;
* **Busca de Elementos;**
* **Múltiplas Impressões:** Travessias estruturadas em *in-order* (em-ordem), *post-order* (pós-ordem) e *pre-order* (pré-ordem), bem como uma visualização formatada da árvore deitada;
* **Destruição da Árvore:** Função dedicada à libertação adequada da memória alocada dinamicamente.

### 2. Versão Iterativa (`avl-sem-recursao.c`)
Esta versão foca-se em evitar o empilhamento de chamadas recursivas (usando, por exemplo, a função `inserirInterativo`). 
* Para conseguir subir na árvore e recalcular os Fatores de Balanceamento (FB) e as alturas após uma inserção iterativa, a estrutura do nó (`NO`) foi adaptada para incluir um ponteiro direto para o nó `pai`.
* Inclui igualmente um menu interativo para testar inserções, remoções e a impressão da árvore atualizada.

## Estrutura de Ficheiros
* `avl-com-recursao.c`: Código-fonte da implementação recursiva.
* `avl-sem-recursao.c`: Código-fonte da implementação iterativa.

## Como compilar e executar

Certifique-se de que possui um compilador de C (como o GCC) instalado. Para testar qualquer uma das versões, abra o terminal nesta pasta e execute:

**Para a versão recursiva:**
```bash
gcc avl-com-recursao.c -o avl_recursiva
./avl_recursiva
```
**Para a versão iterativa:**
```bash
gcc avl-sem-recursao.c -o avl_iterativa
./avl_iterativa
```