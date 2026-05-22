# Árvore B - Estrutura de Dados Balanceada

Este repositório contém uma implementação robusta de uma Árvore B desenvolvida em C. A Árvore B é uma estrutura de dados de busca auto-balanceada que generaliza a árvore binária de busca, permitindo que os nós tenham mais de dois filhos. Esta característica torna a estrutura altamente otimizada para sistemas que leem e escrevem grandes blocos de dados, reduzindo significativamente a altura da árvore e, consequentemente, o tempo de acesso.

O código implementa uma árvore com grau mínimo definido como T = 2. Isso significa que cada nó interno (exceto a raiz) deve conter pelo menos uma chave e pode armazenar um máximo de quatro chaves, com até cinco ponteiros para nós filhos. Todo o controlo de balanceamento foi implementado de forma nativa, garantindo que a árvore permanece perfeitamente equilibrada após qualquer alteração.

Durante o processo de inserção, o algoritmo lida proativamente com o excesso de chaves ("overflow") dividindo os nós cheios e promovendo a chave mediana para o nó pai. Para a operação de remoção, que é substancialmente mais complexa, o código contempla todos os cenários possíveis: remoção diretamente em nós folha, substituição por predecessores ou sucessores em nós internos e resolução de "underflow" através do empréstimo de chaves de nós irmãos adjacentes ou, quando isso não é possível, através da fusão ("merge") de nós. 

Foi também incluída uma função de impressão hierárquica que permite visualizar a estrutura da árvore no terminal, facilitando o acompanhamento das rotações e divisões em tempo real. Como material de apoio e referência para a construção da lógica de balanceamento, foi utilizado o material didático disponível em https://www.youtube.com/watch?v=zkVGGbmjTH4&t=1681s.

Para compilar e executar o código na sua máquina, certifique-se de ter o compilador GCC instalado e utilize os seguintes comandos no seu terminal:

```bash
# Compilar o código-fonte
gcc arvore-b.c -o arvore_b

# Executar o programa interativo
./arvore_b