# Estrutura de Dados I

Coletânea dos códigos desenvolvidos nas aulas de **Estrutura de Dados I**. Todas as estruturas e algoritmos foram implementados do zero em **C**, sem bibliotecas prontas de estruturas de dados.

Cada arquivo `.c` é um programa independente, com a sua própria `main` demonstrando o que foi implementado.

## Estrutura do repositório

```text
.
├── ListaLigada.c                  # lista simplesmente ligada
├── ListaLigadaEOrdenacao.c        # lista ligada com operações extras e inserção ordenada
├── PilhaVetor.c                   # pilha com vetor global
├── PilhaEstruturaVetor.c          # pilha com vetor dentro de uma struct
├── PilhaListaLigada.c             # pilha com lista ligada
├── FilaVetores.c                  # fila circular com vetor
├── FilaListaLigadaEPrioridade.c   # fila com lista ligada e fila de prioridade
├── ArvoreBinariaEBusca.c          # árvore binária de busca
├── Busca.c                        # busca binária e interseção de vetores
├── OrdenacoesN2.c                 # Insertion, Selection e Bubble Sort
├── OrdenacoesNLOGN.c              # Merge Sort e Quick Sort
├── Ordenacao.txt                  # anotações de aula sobre ordenação
└── PraticandoC.c                  # exercícios de struct, ponteiros e alocação dinâmica
```

## Conteúdo

### Listas

| Arquivo | O que implementa |
|---|---|
| [`ListaLigada.c`](ListaLigada.c) | Lista simplesmente ligada: inserir no fim (`addFim`), inserir em um índice (`add`), acessar (`get`), alterar (`set`), remover por índice (`remover`), tamanho, impressão e liberação da memória (`freeLista`). |
| [`ListaLigadaEOrdenacao.c`](ListaLigadaEOrdenacao.c) | Lista ligada com `addLista`, `setLista`, `get`, `remover`, concatenação de listas (`concatenaLista`), remoção de todas as ocorrências de um valor (`removeK`), busca sequencial (`busca`) e inserção em lista já ordenada (`addOrdenado`). |

### Pilhas

| Arquivo | O que implementa |
|---|---|
| [`PilhaVetor.c`](PilhaVetor.c) | Versão mais simples: vetor global de 100 posições e uma variável `top`, com `push` e `pop`. |
| [`PilhaEstruturaVetor.c`](PilhaEstruturaVetor.c) | Pilha com `struct` (`v`, `max`, `top`), verificação de pilha cheia/vazia e `BalanciamentoParenteses`, que confere se os parênteses de um texto estão balanceados. |
| [`PilhaListaLigada.c`](PilhaListaLigada.c) | Pilha com nós encadeados: `push`, `pop`, `sizePilha`, impressão iterativa e recursiva, liberação da memória e `balanceamento`, que verifica `()`, `[]` e `{}`. |

### Filas

| Arquivo | O que implementa |
|---|---|
| [`FilaVetores.c`](FilaVetores.c) | Fila circular com vetor: `ini` e `fim` andam em módulo `max`, e o contador `size` distingue fila cheia de fila vazia (nos dois casos `ini == fim`). |
| [`FilaListaLigadaEPrioridade.c`](FilaListaLigadaEPrioridade.c) | Fila com lista ligada e ponteiros para início e fim (inserção e remoção em O(1)), e **fila de prioridade** feita com duas filas: a fila prioritária é sempre esvaziada antes da normal. |

### Árvores

[`ArvoreBinariaEBusca.c`](ArvoreBinariaEBusca.c) implementa uma **árvore binária de busca** de inteiros. Valores menores ou iguais ao do nó vão para a subárvore esquerda e os maiores vão para a direita. Na tabela, **h** é a altura da árvore e **n** é o número de nós.

| Operação | Funções | Custo |
|---|---|---|
| Inserção | `addTree` (recursiva, usa `addNo`) e `addTreeI` (iterativa) | O(h) |
| Busca | `buscaR` (recursiva) e `buscaI` (iterativa) | O(h) |
| Máximo | `MaxBuscaR`, `MaxBuscaI` e `MaxR` | O(h) |
| Tamanho e altura | `SizeTree` e `alturaTree` (árvore vazia = -1, folha = 0) | O(n) |
| Percursos | `printPreOrdem`, `printEmOrdem`, `printPosOrdem` e `printTree` | O(n) |
| Exportação | `printTreeXML` grava a árvore em pré-ordem no arquivo `Tree.xml` | O(n) |
| Liberação | `liberaMemoria` | O(n) |

No pior caso (valores inseridos em ordem crescente ou decrescente) a árvore degenera em uma lista e h = n - 1.

A `main` monta a mesma árvore com a inserção recursiva e com a iterativa e exercita todas as funções. Saída (trecho):

```text
printTree (rec): [ 20,30,30,35,40,45,50,60,65,70,80,]
Pre-ordem : 50 30 20 30 40 35 45 70 60 65 80
Em-ordem  : 20 30 30 35 40 45 50 60 65 70 80
Pos-ordem : 30 20 35 45 40 30 65 60 80 70 50
Tamanho: 11
Altura : 3
Maximo : 80 80 80
```

### Busca

| Arquivo | O que implementa |
|---|---|
| [`Busca.c`](Busca.c) | Busca binária iterativa (`buscaBinariaI`) e recursiva (`buscaBinariaR`) em vetor ordenado, devolvendo o índice ou -1, ambas em O(log n). Também tem `interseccaoBB`, que conta quantos elementos de um vetor aparecem em outro: ordena o segundo com Merge Sort e faz uma busca binária para cada elemento do primeiro. O segundo vetor fica ordenado ao final. |

A busca sequencial está em `busca`, no arquivo [`ListaLigadaEOrdenacao.c`](ListaLigadaEOrdenacao.c), e a busca em árvore, em `buscaR` e `buscaI`, no arquivo da árvore.

### Ordenação

| Algoritmo | Arquivo | Variantes | Complexidade |
|---|---|---|---|
| Insertion Sort | `OrdenacoesN2.c` | iterativo e recursivo | O(n²) no pior caso, Θ(n) no melhor |
| Selection Sort | `OrdenacoesN2.c` | duas versões iterativas e uma recursiva | Θ(n²) |
| Bubble Sort | `OrdenacoesN2.c` | iterativo e recursivo | Θ(n²), pois não há parada antecipada |
| Merge Sort | `OrdenacoesNLOGN.c` | recursivo, com vetores auxiliares | Θ(n log n) |
| Quick Sort | `OrdenacoesNLOGN.c` | recursivo, pivô no primeiro elemento | O(n log n) em média, O(n²) no pior caso |

Como o pivô do Quick Sort é sempre o primeiro elemento, o pior caso acontece justamente com o vetor **já ordenado**.

Os dois arquivos de ordenação são programas interativos: você informa o tamanho **N** do vetor, ele é preenchido com valores aleatórios (a *seed* usada é exibida) e um menu permite escolher qual algoritmo executar, ou executar todos sobre o mesmo vetor. O programa mostra o vetor antes e depois, mede o **tempo de execução** com `clock()` e confere se o resultado ficou realmente ordenado.

[`OrdenacoesN2.c`](OrdenacoesN2.c) traz ainda `addOrdenado`, a inserção ordenada em lista ligada.

[`Ordenacao.txt`](Ordenacao.txt) reúne as anotações de aula: passo a passo de cada algoritmo e análise de complexidade.

### Prática de C

| Arquivo | O que implementa |
|---|---|
| [`PraticandoC.c`](PraticandoC.c) | Exercícios de `struct`, ponteiros e alocação dinâmica: coordenadas, segmentos e triângulos, com distância euclidiana, comprimento de segmento, inversão, translação, perímetro e **interseção de dois segmentos** (devolve `NULL` quando não há ponto de encontro). |

## Como compilar e executar

É preciso ter o `gcc` instalado. Cada arquivo `.c` tem a sua própria `main`, então eles são compilados **um de cada vez**:

```bash
gcc ListaLigada.c -o lista_ligada -Wall
./lista_ligada
```

No Windows, execute com `.\lista_ligada.exe`.

O `PraticandoC.c` usa `sqrt` e `round`, então precisa linkar a biblioteca matemática:

```bash
gcc PraticandoC.c -o praticando_c -Wall -lm
./praticando_c
```

Para compilar todos de uma vez (Linux, macOS ou Git Bash), deixando os executáveis na pasta `bin/`:

```bash
mkdir -p bin
for f in *.c; do gcc "$f" -o "bin/${f%.c}" -Wall -lm; done
./bin/ArvoreBinariaEBusca
```

Para procurar erros de memória (vazamentos, acessos inválidos) durante os estudos:

```bash
gcc -g -fsanitize=address,undefined ArvoreBinariaEBusca.c -o arvore
./arvore
```

Observações:

- `OrdenacoesN2` e `OrdenacoesNLOGN` pedem o tamanho do vetor e mostram um menu; digite `0` para sair.
- `ArvoreBinariaEBusca` cria o arquivo `Tree.xml` na pasta em que for executado.
- Em operações inválidas (remover de uma estrutura vazia, índice fora dos limites, pilha cheia) os programas imprimem uma mensagem e encerram com `exit(1)`.
- Os executáveis de `bin/` e o `Tree.xml` gerado não precisam ir para o repositório; vale adicioná-los ao `.gitignore`.

## Roadmap

- [x] Listas ligadas
- [x] Pilhas (vetor e lista ligada)
- [x] Filas (vetor, lista ligada e prioridade)
- [x] Ordenação O(n²): Bubble, Insertion e Selection
- [x] Ordenação O(n log n): Merge Sort e Quick Sort
- [x] Busca binária (iterativa e recursiva) e busca sequencial em lista ligada
- [x] Árvore binária de busca: inserção, busca, máximo, tamanho, altura e percursos
- [ ] Remoção de nós da árvore binária de busca

## Autor

Feito por [@andreluizcle](https://github.com/andreluizcle) durante a disciplina de Estrutura de Dados I.
