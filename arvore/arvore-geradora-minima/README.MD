# Árvore Geradora Mínima (Kruskal) - Problema de Otimização Espacial

Este repositório contém a solução para um problema de otimização espacial modelado através da estrutura de dados de Grafos. O objetivo principal do projeto é aplicar o conceito de **Árvore Geradora Mínima (Minimum Spanning Tree - MST)** para conectar múltiplos pontos num plano cartesiano com o menor custo total possível.

## O Problema: Resgate com Teias

O algoritmo foi desenvolvido para resolver um cenário fictício e lúdico: um grupo de pessoas está em queda livre no mesmo plano paralelo ao solo. Para salvá-las, o Homem-Aranha precisa conectar todas as pessoas utilizando cabos de teia entre elas. Como o tempo é curto, a missão exige que se gaste o mínimo possível de teia para garantir que ninguém fique desconectado do grupo.

A entrada do sistema fornece as coordenadas (x, y) de cada pessoa em centímetros. O programa deve processar essas localizações e imprimir o comprimento mínimo necessário de teia em metros, formatado com duas casas decimais.

## Detalhes da Implementação Técnica

A solução foi inteiramente desenvolvida em **C**, demonstrando o uso avançado de alocação dinâmica de memória, manipulação de ponteiros e estruturas de dados complexas.

* **Modelagem do Grafo:** O cenário foi abstraído para um grafo não direcionado. Cada pessoa (coordenada) representa um vértice na estrutura.
* **Cálculo de Pesos:** O programa calcula a Distância Euclidiana (usando o Teorema de Pitágoras) entre todos os pares de vértices possíveis. Essa distância matemática torna-se o peso de cada aresta.
* **Algoritmo de Kruskal:** Para encontrar a Árvore Geradora Mínima, foi implementado o Algoritmo de Kruskal. A lógica avalia as arestas iterativamente em busca dos menores pesos, unindo as diferentes árvores (ou componentes) até que todos os vértices estejam conectados sem formar ciclos.
* **Estruturas Utilizadas:** Listas de adjacência para a representação eficiente do grafo na memória.

## Estrutura do Repositório

* `arvore-geradora-minima.c`: Código-fonte principal contendo a implementação do grafo, o cálculo das distâncias e o Algoritmo de Kruskal.
* `exemplo-entrada-saida.png`: Um exemplo de como deve ser inserida a entrada e a sua saída esperada.

## Como compilar e executar

Para testar a implementação localmente, certifique-se de ter um compilador de C (como o GCC) instalado. 

**Atenção:** Como o código utiliza funções da biblioteca matemática `<math.h>` (como `sqrt` e `pow`), é estritamente necessário incluir a flag `-lm` durante a compilação no Linux.

Abra o terminal na pasta do projeto e execute os seguintes comandos:

```bash
# Compilar o código-fonte linkando a biblioteca matemática
gcc arvore-geradora-minima.c -o arvore_minima -lm

# Executar o programa
./arvore_minima