#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Pilha{
    int *v;
    int max,top;
} Pilha;

Pilha* newPilha(int max){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->v = (int*)malloc(sizeof(int)*max);
    p->max = max;
    p->top = 0;
    
    return p;
} 

int estaCheia(Pilha* p){
    return p->max == p->top;
}

int estaVazia(Pilha* p){
    return p->top == 0;
}

void push(Pilha* p, int x){
    if(estaCheia(p)){
        printf("\nPilha cheia!\n");
        exit(1);
    }
    p->v[p->top++] = x;
}

int pop(Pilha* p){
    if(estaVazia(p)){
        printf("\nPilha Vazia!\n");
        exit(1);
    }
    return p->v[--(p->top)];
}

int BalanciamentoParenteses(char* texto){
    int size = strlen(texto);
    Pilha* p = newPilha(size);
    for(int i = 0; i<size; i++){
        if(texto[i] == '('){
            push(p, 1);
        } else if (texto[i] == ')'){
            if(estaVazia(p))
                return 0;
            pop(p);
        }
    }

    return estaVazia(p);
}

void desalocarMemoria(Pilha* p){
    if(p == NULL)
        return;
    free(p->v);
    free(p);
}

void printPilha(Pilha* p){
    printf("[");
    for(int i = 0; i < p->max; i++){
        printf(" %d ", p->v[i]);
        if(!(i == p->max-1))
            printf("->");
    }
    printf("]");
}

int main(){
    Pilha* p = newPilha(3);
    char texto [100];
    strcpy(texto," ((2+2)*2)+(2+2) ");
    printf("%s balanc .=%d\n " , texto , BalanciamentoParenteses( texto ));
    strcpy(texto , " (() " );
    printf("%s balanc .=%d\n " , texto , BalanciamentoParenteses( texto ));
    strcpy(texto , " ())( " );
    printf("%s balanc .=%d\n " , texto , BalanciamentoParenteses( texto ));
 
    push(p, 5);
    push(p, 7);
    push(p, 3);

    printPilha(p);
    desalocarMemoria(p);
    return 0;
}