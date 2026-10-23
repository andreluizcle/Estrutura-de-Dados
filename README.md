# Estrutura de Dados I

Coletânea dos códigos desenvolvidos nas aulas de **Estrutura de Dados I**, com todas as estruturas implementadas do zero em **C**, sem bibliotecas prontas de estruturas de dados.

> 🚧 **Repositório em andamento.** Ainda estou adicionando conteúdo: faltam os **algoritmos de busca** e as **estruturas de árvore** (veja o [roadmap](#roadmap)).

## Conteúdo

### Listas

| Arquivo | Descrição |
|---|---|
| `ListaLigada.c` | Lista simplesmente ligada com as operações básicas. |
| `ListaLigadaEOrdenacao.c` | Lista ligada com inserção, remoção, acesso por índice, alteração, concatenação, remoção de todas as ocorrências de um valor (`removeK`), busca e inserção ordenada (`addOrdenado`). |

### Pilhas

| Arquivo | Descrição |
|---|---|
| `PilhaVetor.c` | Pilha implementada com vetor. |
| `PilhaEstruturaVetor.c` | Pilha com vetor encapsulado em uma `struct`. |
| `PilhaListaLigada.c` | Pilha implementada com lista ligada. |

### Filas

| Arquivo | Descrição |
|---|---|
| `FilaVetores.c` | Fila implementada com vetor. |
| `FilaListaLigadaEPrioridade.c` | Fila com lista ligada (ponteiros para início e fim) e **fila de prioridade** feita com duas filas: os elementos prioritários são sempre atendidos antes dos normais. |

### Ordenação

| Algoritmo | Arquivo | Variantes | Complexidade |
|---|---|---|---|
| Insertion Sort | `OrdenacoesN2.c` | iterativo e recursivo | O(n²) no pior caso, Θ(n) no melhor |
| Selection Sort | `OrdenacoesN2.c` | duas versões iterativas e uma recursiva | Θ(n²) |
| Bubble Sort | `OrdenacoesN2.c` | iterativo e recursivo | O(n²) |
| Merge Sort | `OrdenacoesNLOGN.c` | recursivo, com vetores auxiliares | Θ(n log n) |
| Quick Sort | `OrdenacoesNLOGN.c` | recursivo | O(n log n) em média, O(n²) no pior caso |

Os dois arquivos de ordenação são programas interativos: você informa o tamanho **N** do vetor, ele é preenchido com valores aleatórios e um menu permite escolher qual algoritmo executar (ou executar todos). O programa mostra o vetor antes e depois, mede o **tempo de execução** com `clock()` e confere se o resultado ficou realmente ordenado.

`Ordenacao.txt` reúne as anotações de aula sobre ordenação: o passo a passo de cada algoritmo e a análise de complexidade.

### Prática de C

| Arquivo | Descrição |
|---|---|
| `PraticandoC.c` | Exercícios de `struct`, ponteiros e alocação dinâmica: coordenadas, segmentos e triângulos, com distância euclidiana, comprimento de segmento, translação, perímetro e **interseção de dois segmentos**. |

## Como compilar e executar

Cada arquivo `.c` tem a sua própria função `main`, então eles são compilados **um de cada vez**. É preciso ter o `gcc` instalado.

```bash
gcc NomeDoArquivo.c -o programa -Wall
./programa
```

Exemplo com o arquivo de ordenações:

```bash
gcc OrdenacoesN2.c -o ordenacoes_n2 -Wall
./ordenacoes_n2
```

No Windows, execute com `.\programa.exe`.

O `PraticandoC.c` usa `sqrt`, então precisa linkar a biblioteca matemática:

```bash
gcc PraticandoC.c -o praticando_c -lm
./praticando_c
```

## Roadmap

- [x] Listas ligadas
- [x] Pilhas (vetor e lista ligada)
- [x] Filas (vetor, lista ligada e prioridade)
- [x] Ordenação O(n²): Bubble, Insertion e Selection
- [x] Ordenação O(n log n): Merge Sort e Quick Sort
- [ ] Algoritmos de busca (sequencial e binária)
- [ ] Árvores (árvore binária e árvore binária de busca, com percursos, inserção, busca e remoção)

## Autor

Feito por [@andreluizcle](https://github.com/andreluizcle) durante a disciplina de Estrutura de Dados I.
