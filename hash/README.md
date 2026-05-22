# Tabelas Hash - Sistema de Catalogação de Livros

Este repositório contém implementações de um sistema de catalogação de livros utilizando a estrutura de dados **Tabela Hash** na linguagem C. O objetivo deste projeto é demonstrar o domínio sobre o funcionamento interno das funções de espalhamento (hashing) e, principalmente, sobre diferentes técnicas de resolução de colisões em memória.

O cenário prático desenvolvido consiste num catálogo onde cada livro possui um código ISBN, título, autor e ano de publicação. O sistema interativo permite realizar operações essenciais: inserir, buscar, remover e imprimir os livros armazenados.

Para fins de estudo e demonstração de flexibilidade técnica, o sistema foi construído com duas arquiteturas distintas:

## 1. Endereçamento Aberto com Duplo Hash (`hash-endereçamento-aberto.c`)
Nesta implementação, todos os registos são armazenados num vetor fixo. 
* **Chave de Espalhamento:** O índice principal na tabela é calculado utilizando o **código ISBN** numérico do livro.
* **Resolução de Colisões:** Quando ocorre uma colisão (a posição calculada inicialmente já está ocupada), o sistema utiliza a técnica de **Duplo Hash** (Double Hashing). Uma segunda função matemática entra em ação para calcular o tamanho do "salto" na tabela até encontrar um espaço vazio, garantindo uma distribuição uniforme dos dados e minimizando problemas de agrupamento primário.

## 2. Encadeamento Separado (`hash-encadeamento-separado.c`)
Nesta segunda abordagem, a tabela Hash funciona como um vetor de ponteiros para listas ligadas dinâmicas.
* **Chave de Espalhamento:** O índice é calculado com base no **título do livro**. O algoritmo converte a string do título somando os valores da tabela ASCII de todos os seus caracteres.
* **Resolução de Colisões:** Livros diferentes que resultem no mesmo índice de espalhamento (colisão) são inseridos de forma sequencial na lista ligada correspondente àquela posição. Esta estrutura lida com colisões alocando memória dinamicamente apenas quando necessário.

## Como compilar e executar

Certifique-se de que tem um compilador de C (como o GCC) instalado. Pode compilar e testar cada versão de forma independente através do terminal.

**Para a versão de Endereçamento Aberto (Duplo Hash):**
```bash
gcc hash-endereçamento-aberto.c -o hash_aberto
./hash_aberto
```
**Para a versão de Encadeamento Separado:**
```bash
gcc hash-encadeamento-separado.c -o hash_encadeado
./hash_encadeado
```