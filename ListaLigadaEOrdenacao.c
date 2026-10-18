#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

typedef struct Lista {
    No* ini;
} Lista;

No* newNo(int valor) {
    No* no = (No*)malloc(sizeof(No));
    if (no == NULL) {
        fprintf(stderr, "Erro: falha de alocacao\n");
        exit(1);
    }
    no->valor = valor;
    no->prox = NULL;

    return no;
}

Lista* newLista() {
    Lista* li = (Lista*)malloc(sizeof(Lista));
    if (li == NULL) {
        fprintf(stderr, "Erro: falha de alocacao\n");
        exit(1);
    }
    li->ini = NULL;

    return li;
}

int sizeLista(Lista* li) {
    No* aux = li->ini;
    int size = 0;
    while (aux != NULL) {
        size++;
        aux = aux->prox;
    }

    return size;
}

void printLista(Lista* li) {
    No* aux = li->ini;
    int size = sizeLista(li);
    printf("[");
    for (int i = 0; i < size; i++) {
        printf(" %d ", aux->valor);
        aux = aux->prox;
    }
    printf("]\n");
}

int estaVazia(Lista* li) {
    return li->ini == NULL;
}

No* get(Lista* li, int idx) {
    if (idx < 0) {
        fprintf(stderr, "Erro: indice invalido (%d)\n", idx);
        exit(1);
    }

    No* aux = li->ini;
    for (int i = 0; i < idx && aux != NULL; i++) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        fprintf(stderr, "Erro: indice fora da lista (%d)\n", idx);
        exit(1);
    }
    return aux;
}

int remover(Lista* li, int idx) {
    if (estaVazia(li)) {
        fprintf(stderr, "Erro: lista vazia\n");
        exit(1);
    }

    No* no;
    if (idx == 0) {
        no = li->ini;
        li->ini = li->ini->prox;
    } else {
        No* ant = get(li, idx - 1);
        no = ant->prox;
        if (no == NULL) {
            fprintf(stderr, "Erro: indice fora da lista (%d)\n", idx);
            exit(1);
        }
        ant->prox = no->prox;
    }
    int valor = no->valor;
    free(no);

    return valor;
}

void setLista(Lista* li, int idx, int valor) {
    get(li, idx)->valor = valor;
}

void addLista(Lista* li, int idx, int valor) {
    if (idx == 0) {
        No* novo = newNo(valor);
        novo->prox = li->ini;
        li->ini = novo;
        return;
    }

    No* ant = get(li, idx - 1);
    No* novo = newNo(valor);
    novo->prox = ant->prox;
    ant->prox = novo;
}

void concatenaLista(Lista* l1, Lista* l2) {
    if (l1 == l2) {
        return;
    }

    if (l1->ini == NULL) {
        l1->ini = l2->ini;
    } else {
        No* aux = l1->ini;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = l2->ini;
    }

    // l2 deixa de ser dona dos nos, evitando double free
    l2->ini = NULL;
}

void removeK(Lista* li, int k) {
    // remove todos os k do inicio (checando NULL a cada passo)
    while (li->ini != NULL && li->ini->valor == k) {
        No* del = li->ini;
        li->ini = li->ini->prox;
        free(del);
    }

    if (li->ini == NULL) {
        return;
    }

    No* ant = li->ini;
    No* aux = li->ini->prox;

    while (aux != NULL) {
        if (aux->valor == k) {
            ant->prox = aux->prox;
            free(aux);
            aux = ant->prox;
        } else {
            ant = aux;
            aux = aux->prox;
        }
    }
}

int busca(Lista* li, int k){
    for(No* aux; aux != NULL; aux = aux->prox){
        if(aux->valor == k){
            return 1;
        }
    }

    return 0;
}

//Ordenação
//Lista ja ordenada
void addOrdenado(Lista* li, int valor){
    //ORDEM do OR IMPORTA 
    if(li->ini == NULL || valor< li->ini->valor){
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

int main() {
    Lista* l = newLista();
    addLista(l, 0, 1);
    addLista(l, 1, 3);
    addLista(l, 2, 3);
    addLista(l, 3, 4);
    addLista(l, 4, 5);
    addLista(l, 5, 3);

    printLista(l);
    removeK(l, 3);
    printLista(l);

    // libera a memoria usando apenas funcoes ja existentes
    while (!estaVazia(l)) {
        remover(l, 0);
    }
    free(l);

    return 0;
}