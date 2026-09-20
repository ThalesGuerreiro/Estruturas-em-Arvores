# Estruturas de Árvores Avançadas

Implementação e análise comparativa de cinco estruturas de dados em árvore para a disciplina **Algoritmos e Estruturas de Dados II**:

* **Trie**
* **Árvore Patricia**
* **Árvore Splay**
* **Treap**
* **KD-Tree**

O projeto combina implementação em C++, análise de complexidade, exemplos de funcionamento, visualizações das estruturas e experimentos de desempenho.

## Objetivo

O objetivo é estudar diferentes estratégias de organização, busca e atualização de dados em estruturas hierárquicas, relacionando suas propriedades teóricas com o comportamento observado em experimentos computacionais.

São analisadas diferenças entre estruturas especializadas para:

* chaves textuais e prefixos;
* indexação compactada;
* árvores de busca autoajustáveis;
* árvores de busca com balanceamento probabilístico;
* dados multidimensionais.

## Estruturas implementadas

### Trie

Árvore de prefixos destinada principalmente à organização de strings. A implementação utiliza nós com filhos correspondentes aos caracteres do alfabeto suportado.

Operações analisadas:

* inserção;
* busca;
* remoção.

### Patricia

Estrutura de radix tree compactada que utiliza os pontos de divergência entre as chaves para reduzir caminhos desnecessários.

Operações analisadas:

* inserção;
* busca;
* remoção.

### Splay

Árvore binária de busca autoajustável. Após os acessos, a estrutura utiliza operações de *splay* para levar o elemento acessado em direção à raiz.

Operações analisadas:

* inserção;
* busca;
* remoção.

### Treap

Estrutura híbrida que combina as propriedades de uma árvore binária de busca com as propriedades de um heap por meio de prioridades.

Operações analisadas:

* inserção;
* busca;
* remoção.

### KD-Tree

Estrutura destinada à organização de pontos em espaços multidimensionais. Nos experimentos deste projeto, foram utilizados pontos bidimensionais.

Operações analisadas:

* inserção;
* busca;
* remoção.

## Organização do projeto

```text
Trabalho_Arvores/
├── estruturas/
│   ├── trie/
│   ├── patricia/
│   ├── splay/
│   ├── treap/
│   └── kdtree/
│
├── benchmark/
│   ├── main.cpp
│   └── benchmark.cpp
│
├── resultados/
│   └── resultados.csv
│
├── figuras/
│   ├── insercao_vs_n.png
│   ├── busca_vs_n.png
│   └── remocao_vs_n.png
│
├── Trabalho_Arvores_final.tex
├── Trabalho_Arvores_final.pdf
└── README.md
```

## Requisitos

Para compilar o projeto é necessário possuir um compilador C++ com suporte ao padrão C++17.

Exemplo utilizando `g++`:

```bash
g++ --version
```

O relatório utiliza LaTeX. Para gerar o PDF, é necessário possuir uma distribuição LaTeX, como TeX Live ou MiKTeX.

## Compilação do benchmark

Entre no diretório do benchmark e execute:

```bash
g++ -std=c++17 -O2 main.cpp benchmark.cpp ../estruturas/trie/trie.cpp ../estruturas/patricia/patricia.cpp ../estruturas/splay/splay.cpp ../estruturas/treap/treap.cpp ../estruturas/kdtree/kdtree.cpp -o benchmark
```

Depois execute:

```bash
./benchmark
```

No Windows, dependendo do ambiente utilizado:

```powershell
.\benchmark.exe
```

## Experimentos

Foram utilizados quatro tamanhos de entrada:

```text
100
1.000
10.000
100.000
```

Para cada tamanho foram avaliados três cenários:

* **aleatório** — chaves embaralhadas utilizando uma semente fixa;
* **ordenado** — chaves inseridas em ordem crescente;
* **invertido** — chaves inseridas em ordem decrescente.

Foram avaliadas cinco estruturas:

```text
Trie
Patricia
Splay
Treap
KD-Tree
```

Para cada combinação foram medidas:

* tempo de inserção;
* tempo de busca de elementos existentes;
* tempo de busca de elementos inexistentes;
* tempo de remoção.

Os resultados são armazenados em:

```text
resultados/resultados.csv
```

O arquivo possui as seguintes colunas:

```text
estrutura,n,cenario,insercao_ms,busca_existente_ms,busca_inexistente_ms,remocao_ms
```

## Resultados

Os resultados são apresentados no relatório técnico por meio de tabelas e gráficos.

Os principais gráficos relacionam o tamanho da entrada ao tempo médio observado nos três cenários:

* `figuras/insercao_vs_n.png`
* `figuras/busca_vs_n.png`
* `figuras/remocao_vs_n.png`

Os gráficos devem ser interpretados juntamente com as tabelas e com a discussão presente no relatório, pois os tempos dependem da implementação, do ambiente de execução e da distribuição dos dados.

## Observação sobre o experimento de 1.000.000 de elementos

Um experimento adicional com 1.000.000 de elementos foi considerado durante o desenvolvimento.

Entretanto, o cenário ordenado da Splay apresentou tempo de execução elevado e não foi concluído dentro do período disponível para os testes. Por esse motivo, o conjunto final de resultados foi limitado a 100.000 elementos, mantendo as medições comparáveis entre as cinco estruturas.

## Limitações

Os tempos apresentados correspondem a uma execução do benchmark e, portanto, pequenas diferenças devem ser interpretadas com cautela.

Não foi realizada uma medição direta do consumo de memória durante os experimentos. Os custos espaciais são discutidos teoricamente no relatório.

Além disso, as estruturas não trabalham exatamente com o mesmo tipo de dado: Trie utiliza strings, Splay e Treap utilizam chaves inteiras, Patricia utiliza a representação definida em sua implementação e KD-Tree utiliza pontos bidimensionais. Dessa forma, os resultados devem ser interpretados como uma comparação experimental das implementações desenvolvidas e não como uma classificação universal das estruturas.

## Relatório

O relatório técnico contém:

1. Introdução e fundamentação teórica;
2. Projeto e implementação das estruturas;
3. Exemplos e representações visuais;
4. Análise de complexidade;
5. Metodologia experimental;
6. Resultados e gráficos;
7. Aplicações e análise crítica;
8. Conclusão;
9. Referências.

## Disciplina

**Algoritmos e Estruturas de Dados II**

**Professor:** Michel Pires

**Curso:** Engenharia da Computação

**Campus V — CEFET-MG / Unidade Divinópolis**

## Autor

**Thales Guerreiro Lima Gomes de Castro**
