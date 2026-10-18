#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRINT 10   // quantidade maxima de elementos exibidos
#define VALOR_MAX 10000 // valores aleatorios entre 0 e VALOR_MAX-1

typedef struct No{
    int valor;
    struct No* prox;
} No;

typedef struct Fila{
    No* ini;
    No* fim;
} Fila;

typedef struct Lista{
    No* ini;
} Lista;

typedef struct Pilha{
    No* topo;
} Pilha;

//Auxiliares - Lista Ligada (necessarias para addOrdenado compilar)
No* newNo(int valor){
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;
    return no;
}

void addLista(Lista* li, int pos, int valor){
    No* no = newNo(valor);
    if(pos == 0 || li->ini == NULL){
        no->prox = li->ini;
        li->ini = no;
        return;
    }
    No* aux = li->ini;
    for(int i = 0; i < pos-1 && aux->prox != NULL; i++)
        aux = aux->prox;
    no->prox = aux->prox;
    aux->prox = no;
}

//Insert - Lista Ligada
void addOrdenado(Lista* li, int valor){
    //ORDEM do OR IMPORTA
    if(li->ini == NULL || valor < li->ini->valor){
        addLista(li, 0, valor);
        return;
    }
    No* no = newNo(valor);
    No* aux = li->ini;
    while(aux->prox != NULL && aux->prox->valor < valor){
        aux = aux->prox;
    }
    no->prox = aux->prox; //NULL = NULL caso acabe a lista
    aux->prox = no;
}

//Insert - Vetor
void AddOrdenaInsert(int v[], int n){
    int lixo = -1;
    int chave = v[n-1];
    int i = n-2;
    //print(v,n)
    while(i>=0 && v[i]>chave){
        v[i+1] = v[i];
        v[i] = lixo;
        i--;
    }

    v[i+1] = chave;
}

void InsertSort(int v[], int n){
    int N = 2;
    while(N<=n){
        AddOrdenaInsert(v,N);
        N++;
    }
}

void InsertSortR(int v[], int n){
    if(n>1){
        InsertSortR(v, n-1);
        AddOrdenaInsert(v, n);
    }
}

//Selection - Vetor
int maximo(int v[], int n){
    int max = 0;
    for(int i = 1; i<n;i++)
        if (v[i] > v[max])
            max = i;
    return max;
}

void ordenaSelection(int v[], int n){
    while(n>1){
        int max = maximo(v,n);
        int aux = v[n-1]; //A
        v[n-1] = v[max];  //B
        v[max] = aux;     //C
        n--;
    }
}

void ordenaSelection2(int v[], int n){
    for(int N = n; N > 1; N--){
        int max = 0;
        for(int i = 1; i<N; i++)
            if (v[i] > v[max]) max = i;
        int aux = v[N-1]; //A  (corrigido: era v[n-1])
        v[N-1] = v[max];  //B
        v[max] = aux;     //C
    }
}

void ordenaSelectionR(int v[], int n){
    if(n>1){
        int max = maximo(v,n);
        int aux = v[n-1]; //A
        v[n-1] = v[max];  //B
        v[max] = aux;     //C
        ordenaSelectionR(v, n-1);
    }
}

//BubbleSort - Vetor
void BubbleR(int v[], int n){
    if(n>1){
        for(int i = 0; i<n-1; i++){
            if(v[i] > v[i+1]){
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
        BubbleR(v, n-1);
    }
}

void Bubble(int v[], int n){
    while(n>1){
        for(int i = 0; i<n-1; i++){
            if(v[i] > v[i+1]){
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
            }
        }
        n--;
    }
}

//Utilitarios - Vetor
int* gerarVetor(int n, unsigned int seed){
    int* v = malloc(n * sizeof(int));
    if(v == NULL) return NULL;
    srand(seed);
    for(int i = 0; i < n; i++)
        v[i] = rand() % VALOR_MAX;
    return v;
}

void imprimeVetor(const char* titulo, int v[], int n){
    int limite = (n > MAX_PRINT) ? MAX_PRINT : n;
    printf("%s: [", titulo);
    for(int i = 0; i < limite; i++)
        printf("%s%d", i ? ", " : "", v[i]);
    if(n > MAX_PRINT)
        printf(", ... (mostrando %d de %d)", limite, n);
    printf("]\n");
}

int estaOrdenado(int v[], int n){
    for(int i = 0; i < n-1; i++)
        if(v[i] > v[i+1]) return 0;
    return 1;
}

//Teste de tempo
typedef void (*FuncOrd)(int[], int);

typedef struct Teste{
    const char* nome;
    FuncOrd func;
} Teste;

void executaTeste(const Teste* t, int original[], int copia[], int n){
    memcpy(copia, original, n * sizeof(int)); // todas as funcoes ordenam o MESMO vetor

    printf("=== %s ===\n", t->nome);
    imprimeVetor("Antes ", copia, n);

    clock_t ini = clock();
    t->func(copia, n);
    clock_t fim = clock();

    imprimeVetor("Depois", copia, n);

    double ms = 1000.0 * (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo: %.3f ms | %s\n\n", ms,
           estaOrdenado(copia, n) ? "ordenado corretamente" : "ERRO: vetor NAO ficou ordenado");
}

int main(void){
    int n;
    printf("Tamanho do vetor (N): ");
    if(scanf("%d", &n) != 1 || n <= 0){
        printf("Valor invalido.\n");
        return 1;
    }

    unsigned int seed = (unsigned int) time(NULL); // troque por um numero fixo para repetir os testes
    int* original = gerarVetor(n, seed);
    int* copia = malloc(n * sizeof(int));
    if(original == NULL || copia == NULL){
        printf("Erro: memoria insuficiente.\n");
        free(original);
        free(copia);
        return 1;
    }

    printf("Seed usada: %u\n", seed);
    imprimeVetor("Vetor original", original, n);
    printf("\n");

    Teste testes[] = {
        {"InsertSort (iterativo)",          InsertSort},
        {"InsertSortR (recursivo)",         InsertSortR},
        {"ordenaSelection (iterativo)",     ordenaSelection},
        {"ordenaSelection2 (iterativo)",    ordenaSelection2},
        {"ordenaSelectionR (recursivo)",    ordenaSelectionR},
        {"Bubble (iterativo)",              Bubble},
        {"BubbleR (recursivo)",             BubbleR}
    };
    int qtd = sizeof(testes) / sizeof(testes[0]);

    for(int i = 0; i < qtd; i++)
        executaTeste(&testes[i], original, copia, n);

    free(original);
    free(copia);
    return 0;
}