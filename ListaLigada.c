#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* prox;
} No;

typedef struct Lista{
    No* ini;
} Lista;

No* newNo(int valor){
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;
    
    return no;
}

Lista* newLista(){
    Lista* li = (Lista*)malloc(sizeof(Lista));
    li->ini = NULL;

    return li;
}

int estaVazia(Lista* li){
    return li->ini == NULL;
}

int sizeLista(Lista* li){
    int size = 0;
    No* aux = li->ini;
    while(aux != NULL){
        aux = aux->prox;
        size++;
    }

    return size;
}

void printLista(Lista* li){
    printf("[");
    No* aux = li->ini;
    while(aux != NULL){
        printf(" %d ", aux->valor);
        aux = aux->prox;
    }
    printf("] (%d)", sizeLista(li));
}

void addFim(Lista* li, int x){
    No* no = newNo(x);
    No* aux = li->ini;
    if(li->ini == NULL){
        li->ini = no;
        return;
    }
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = no;
}

No* get(Lista* li, int idx){
    if(idx < 0|| idx >= sizeLista(li)){
        printf("Fora dos Limites!");
        exit(1);
    }
    No* aux = li->ini;
    for(int i = 0; i < idx; i++){
        aux = aux->prox;
    }

    return aux;
}

int remover(Lista* li, int idx){
    No* no = get(li, idx);
    int valor = no->valor;
    if(idx == 0){
        li->ini = no->prox;
    } else{
        No* anterior = get(li, idx-1);
        anterior->prox = no->prox;
    }

    free(no);
    return valor;
}

void set(Lista* li, int valor, int idx){
    No* aux = get(li, idx);
    aux->valor = valor;
}

void add(Lista* li, int valor, int idx){
    No* no = newNo(valor);
    if(idx == 0){
        no->prox = li->ini;
        li->ini = no;
        return;
    }

    No* anterior = get(li, idx-1);
    no->prox = anterior->prox;
    anterior->prox = no;
}

void freeLista(Lista* li){
    No* aux = li->ini;
    while(aux != NULL){
        No* prox = aux->prox;
        free(aux);
        aux = prox;
    }
    free(li);
}

int main(){
    Lista *li = newLista();
    addFim(li,3);
    addFim(li,4);
    addFim(li,9);
    addFim(li,1);
    addFim(li,4);
    printLista(li);
    int pos = 2;
    printf("Removeu elemento pos. %d = %d\n",pos,remover(li,pos));
    printf("Lista apos remocao:\n");
    printLista(li);
    add(li,9,pos);
    printf("Lista apos insercao:\n");
    printLista(li);
    freeLista(li);

    return 0;
}