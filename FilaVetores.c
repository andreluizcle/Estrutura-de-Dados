//Fila Ouroboros
#include <stdlib.h>
#include <stdio.h>

typedef struct Fila{
    int* v;
    int max;
    int ini, fim;
    int size; //Nao da para verificar por função pois ini == fim é tanto vazia quanto cheia 
} Fila;

Fila* newFila(int max){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->v = (int*)malloc(sizeof(int)*max);
    f->max = max;
    f->ini = 0;
    f->fim = 0;
    f->size = 0;

    return f;
}

void add(Fila* f, int x){
    if(f->size == f->max){
        printf("Fila Cheia!");
        exit(1);
    }
    f->v[f->fim] = x;
    f->fim = (f->fim+1)%f->max;
    f->size++;
}

int remover(Fila* f){
    if(f->size == 0){
        printf("Fila Vazia!");
        exit(1);
    }
    int valor = f->v[f->ini];
    f->v[f->ini] = 0;
    f->size--;
    f->ini = (f->ini+1)%f->max;
    return valor;
}

void printFila(Fila* f){
    printf("[");
    for(int i = 0; i<f->size; i++){
        int index = (f->ini + i) % f->max;
        printf(" %d ", f->v[index]);
    }
    printf("] (%d)\n", f->size);
}

int main(){
    Fila * f = newFila(5);
    add(f,1); printFila(f);
    add(f,2); printFila(f);
    add(f,3); printFila(f);
    add(f,4); printFila(f);
    remover(f); printFila(f);
    remover(f); printFila(f);
    remover(f); printFila(f);
    add(f,5); printFila(f);
    add(f,6); printFila(f);
    add(f,7); printFila(f);
    remover(f); printFila(f);
    remover(f); printFila(f);
    remover(f); printFila(f);
}