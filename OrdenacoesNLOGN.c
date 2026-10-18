#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PRINT 10   // quantidade maxima de elementos exibidos
#define VALOR_MAX 100000 // valores aleatorios entre 0 e VALOR_MAX-1

int particao(int* v, int p, int r){
    int pivo = v[p];
    int topo = p;
    for(int i = p+1; i<=r;i++){
        if(v[i]<pivo){
            v[topo]=v[i];
            v[i]=v[topo+1];
            topo++;
        }
    }
    v[topo] = pivo;
    return topo;
}

void quickSort(int* v, int p, int r){
    if(p<r){
        int q = particao(v,p,r);
        quickSort(v,p,q-1);
        quickSort(v,q+1,r);
    }
}

void merge(int* v1, int n1, int* v2, int n2, int* v){
    int top = 0, top1 = 0, top2 = 0;
    while(top1 < n1 && top2 < n2){
        v[top++] = v1[top1] <= v2[top2]? v1[top1++]: v2[top2++];
    }

    //Caso haja elementos faltantes em v1 ou v2
    while (top1<n1 || top2 <n2) v[top++] = top1<n1? v1[top1++]: v2[top2++];
}

void mergeSort(int *v, int n){
    if(n>1){
        int n1, n2;
        n1 = n/2;
        n2 = n-n1;
        int *v1 = (int*)malloc(sizeof(int)*n1);
        int *v2 = (int*)malloc(sizeof(int)*n2);
        for(int i = 0; i<n1; i++) v1[i] = v[i];
        for(int i = 0; i<n2; i++) v2[i] = v[i+n1];
        mergeSort(v1, n1);
        mergeSort(v2, n2);
        merge(v1, n1, v2, n2, v);
        free(v1);
        free(v2);
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

//Adaptador: quickSort recebe (v, p, r), os testes usam (v, n)
void adaptaQuickSort(int v[], int n){
    quickSort(v, 0, n-1);
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
        {"quickSort ", adaptaQuickSort},
        {"mergeSort ", mergeSort}
    };
    int qtd = sizeof(testes) / sizeof(testes[0]);

    for(int i = 0; i < qtd; i++)
        executaTeste(&testes[i], original, copia, n);

    free(original);
    free(copia);
    return 0;
}