#include <stdlib.h>
#include <stdio.h>

typedef struct No{
    int valor;
    struct No* prox;
} No;

typedef struct Fila{
    No* ini;
    No* fim;
} Fila;

typedef struct FilaPrioridade{
    Fila* prioridade;
    Fila* normal;
} FilaPrioridade;

No* newNo(int valor){
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;

    return no;
}

Fila* newFila(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;

    return f;
}

FilaPrioridade* newFilaPrioridade(){
    FilaPrioridade* f = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    f->prioridade = newFila();
    f->normal = newFila();
    
    return f;
}

int estaVazia(Fila* f){
    return f->ini == NULL;
}

void add(Fila* f, int valor){
    No* no = newNo(valor);

    if(estaVazia(f)){
        f->ini = no;
        f->fim = no;
        return;
    }

    f->fim->prox = no;
    f->fim = no;
}

int remover(Fila* f){
    if(estaVazia(f)){
        printf("Pilha Vazia!");
        exit(1);
    }
    int valor = f->ini->valor;
    No* no = f->ini;
    
    if(f->ini == f->fim){
        f->ini = NULL;
        f->fim = NULL;
    } else {
        f->ini = f->ini->prox;
    }

    free(no);
    return(valor);
}

int sizeFila(Fila* f){
    int size = 0;
    No* aux = f->ini;
    while (aux != NULL)
    {
        size++;
        aux = aux->prox;
    }
    

    return size;
}

void printFila(Fila* f){
    No* aux = f->ini;
    printf("[");
    while (aux != NULL)
    {
        printf(" %d ", aux->valor);
        aux = aux->prox;
    }
    printf("] (%d)", sizeFila(f));
}

void addPri(FilaPrioridade* f, int x, int prioridade){
    if(prioridade){
        add(f->prioridade, x);
    } else{
        add(f->normal, x);
    }
}

int removePri(FilaPrioridade* f){
    if(!estaVazia(f->prioridade)){
        return remover(f->prioridade);
    } else{
        return remover(f->normal);
    }
}

void printFilaPri(FilaPrioridade* f){
    printf("Prioridade:\n ");
    printFila(f->prioridade);
    printf("\nNormal:\n ");
    printFila(f->normal);
}

int estaVaziaPri(FilaPrioridade* f){
    return estaVazia(f->prioridade) && estaVazia(f->normal);
}

int main(){
    Fila* f = newFila();

    add(f, 10);
    add(f, 20);
    add(f, 30);

    printFila(f);
    printf("\n");

    printf("Tamanho: %d\n", sizeFila(f));
    printf("Vazia: %d\n", estaVazia(f));

    printf("Removido: %d\n", remover(f));
    printFila(f);
    printf("\n");

    printf("Removido: %d\n", remover(f));
    printf("Removido: %d\n", remover(f));

    printf("Vazia: %d\n", estaVazia(f));
    printFila(f);
    printf("\n");

    free(f);

    //======== Fila Prioridade =========
    FilaPrioridade * fila = newFilaPrioridade();

    int prioritario = 0;
    int valor =3;
    addPri(fila,valor,prioritario);
    valor = 4;
    addPri(fila,valor,prioritario);
    prioritario = 1;
    valor = 7;
    addPri(fila,valor,prioritario);
    prioritario = 0;
    valor = 6;
    addPri(fila,valor,prioritario);
    prioritario = 1;
    valor = 10;
    addPri(fila,valor,prioritario);
    printFilaPri(fila);
    printf("\n");
    while(!estaVaziaPri(fila)){
        printf("Removeu %d\n",removePri(fila));
    }

    free(fila);
    return 0;
}