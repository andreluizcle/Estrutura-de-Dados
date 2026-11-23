#include <stdlib.h>
#include <stdio.h>

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

// int buscaBinariaI
int buscaBinariaI(int* v, int n, int chave){
    int ini = 0; int fim = n-1;
    while(ini <= fim){
        int meio = ini + (fim-ini)/2;
        if(v[meio] == chave)   
            return meio;
        if(v[meio] < chave)
            ini = meio+1;
        if(v[meio] > chave)
            fim = meio-1;
    }
    return -1;   
}

// int buscaBinariaR
int buscaBinariaR(int* v, int ini, int fim, int chave){
    if(ini <= fim){
        int meio = ini + (fim-ini)/2;
        if(v[meio] == chave)
            return meio;
        if(v[meio] < chave)
            return buscaBinariaR(v, meio+1, fim, chave);
        if(v[meio] > chave)
            return buscaBinariaR(v, ini, meio-1, chave);
    }
    return -1;   
}

// int interseccaoBB
int interseccaoBB(int* v1, int n1, int* v2, int n2){
    mergeSort(v2, n2);
    int size = 0;
    for(int i = 0; i < n1; i++){
        int chave = v1[i];
        
        if(buscaBinariaR(v2, 0, n2-1, chave) != -1){
            size++;
        }
    }
    return size;
}

int main(){
    int v[] = {5, 2, 9, 1, 7};
    int n = 5;

    mergeSort(v, n);
    printf("Ordenado: ");
    for(int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");

    printf("buscaBinariaI(7) = %d\n", buscaBinariaI(v, n, 7));
    printf("buscaBinariaR(7) = %d\n", buscaBinariaR(v, 0, n-1, 7));

    int a[] = {1, 2, 3, 4};
    int b[] = {6, 4, 5, 3};
    printf("interseccaoBB = %d\n", interseccaoBB(a, 4, b, 4));

    return 0;
}