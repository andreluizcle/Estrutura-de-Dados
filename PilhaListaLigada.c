#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int valor;
    struct No* prox;
} No;

typedef struct Pilha{
    No* top;
} Pilha;

No* newNo(int valor){
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;

    return no;
}

Pilha* newPilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->top = NULL;

    return p;
}

void push(Pilha* p, int x){
    No* no = newNo(x);
    no->prox = p->top;
    p->top = no;
}

int estaVazia(Pilha *p){
    return p->top == NULL;
}

int pop(Pilha* p){
    if(estaVazia(p)){
        printf("Pilha Vazia!");
        exit(1);
    }
    int valor = p->top->valor;
    No* aux = p->top;
    p->top = p->top->prox;
    free(aux);

    return valor;
}

int sizePilha(Pilha* p){
    int size = 0;
    for(No* aux = p->top; aux != NULL; aux = aux->prox)
        size++;
    return size;
}

void printPilha(Pilha* p){
    printf("\n[");
    for(No* aux = p->top; aux != NULL; aux = aux->prox){
        printf(" %d ", aux->valor);
        if(aux->prox != NULL)
            printf("<-");
    }
    printf("]");

    printf(" (%d)\n", sizePilha(p));
}

void printPilhaRecursiva(No* n){
    if(n == NULL)
        return;

    printf(" %d ", n->valor);
    printPilhaRecursiva(n->prox);
}

void desalocarMemoria(Pilha* p){
    No* aux;
    while(p->top != NULL){
        aux = p->top;
        p->top = p->top->prox;
        free(aux);
    }
    free(p);
}

int balanceamento(char* texto){
    int size = strlen(texto);
    Pilha* p = newPilha();
    for(int i = 0; i < size; i++){
        if(texto[i] == '['){
            push(p,1);
        }else if(texto[i] == '{'){
            push(p,2);
        }else if(texto[i] == '('){
            push(p,3);
        }
        if(texto[i] == ']' &&  (estaVazia(p) || pop(p) != 1)){
            desalocarMemoria(p);
            return 0;
        }
        if(texto[i] == '}' && (estaVazia(p) || pop(p) != 2)){
            desalocarMemoria(p);
            return 0;
        }
        if(texto[i] == ')' && (estaVazia(p) || pop(p) != 3)){
            desalocarMemoria(p);
            return 0;
        }
    }

    int balanceado = estaVazia(p);
    desalocarMemoria(p);
    return balanceado;
}

int main(){
    Pilha* p = newPilha();
    push(p, 3);
    push(p, 5);
    push(p, 7);

    printPilha(p);
    printf("pop: %d\n", pop(p));
    printf("pop: %d\n", pop(p));
    printf("pop: %d\n", pop(p));
    
    printf("balanceado: %d\n", balanceamento("[](){}"));
    printf("balanceado: %d\n", balanceamento("[(){}"));
    printf("balanceado: %d\n", balanceamento("[(])"));
    return 0;
}