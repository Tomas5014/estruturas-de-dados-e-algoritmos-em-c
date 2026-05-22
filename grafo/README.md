# Busca em Grafos - O Problema do Labirinto (Rato IBO)

Este repositório contém a implementação em C de um sistema baseado em **Grafos** para modelar e resolver o problema de navegação em um labirinto. O projeto explora conceitos fundamentais de teoria dos grafos, como listas de adjacência e algoritmos de travessia, aplicados a um cenário prático.

## O Problema: O Ratinho Brilhante

Baseado num estudo real de 1942 sobre a proficiência de ratos em labirintos, o problema apresenta o ratinho IBO, descendente de uma linhagem "brilhante". O objetivo de IBO é navegar por um labirinto, partindo do ponto de `Entrada`, encontrar e pegar o queijo (representado pelo caractere `*`) e, em seguida, encontrar o caminho até a `Saida`.

O labirinto é composto por pontos estratégicos marcados por letras ou palavras, e corredores que ligam esses pontos. O programa deve calcular a quantidade de pontos pelos quais o ratinho precisa passar para completar a sua missão com sucesso (do início ao queijo, e do queijo ao fim).

## Detalhes da Implementação Técnica

A solução modela o labirinto como um **Grafo Não Direcionado**, onde as interseções ou pontos estratégicos são os vértices e os caminhos entre eles são as arestas.

* **Estrutura de Dados:** O grafo foi implementado utilizando **Listas de Adjacência**. Esta abordagem otimiza o uso da memória, alocando espaço apenas para as conexões que realmente existem no labirinto.
* **Mapeamento de Vértices Dinâmico:** Os vértices são identificados por `strings` (nomes como "Entrada", "A", "*", "Saida"). O código possui uma lógica interna para registar novos vértices dinamicamente durante a inserção das arestas e mapeá-los para índices numéricos na estrutura.
* **Algoritmo de Busca:** Foi implementado um algoritmo de **Busca em Profundidade (DFS - Depth-First Search)**, utilizando um sistema de coloração de vértices (`BRANCO` para não visitado, `AMARELO` para em processamento, `VERMELHO` para finalizado) para rastrear os caminhos, evitar ciclos e calcular o tamanho da rota.
* **Rota Particionada:** O problema é resolvido em duas etapas de busca:
  1. A distância da `Entrada` até o alvo `*`.
  2. A distância do alvo `*` até a `Saida`.

## Estrutura de Ficheiros

* `busca-grafo.c`: Código-fonte da implementação do grafo e do algoritmo de busca.
* `busca-grafo-enunciado.txt`: Descrição textual completa do problema e das regras do labirinto.
* `busca-grafo-entrada-saida.png`: Exemplos dos dados de entrada e saída esperados.
* `busca-grafo-labirinto.png`: Representação visual do labirinto utilizado como caso de teste.

## Como compilar e executar

Para compilar e testar o código na sua máquina, utilize um compilador de C (como o GCC). Abra o terminal no diretório do projeto e execute:

```bash
# Compilar o código-fonte
gcc busca-grafo.c -o busca_grafo

# Executar o programa
./busca_grafo