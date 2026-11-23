#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* esq, *dir;
} No;

typedef struct Tree{
    No* raiz;
} Tree;

No* newNo(int valor){
   No* no = (No*)malloc(sizeof(No));
   no->esq = NULL;
   no->dir = NULL;
   no->valor = valor;
   
   return no;
}

Tree* newTree(){
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->raiz = NULL;
    return t;
}

void addNo(No* raiz, int valor){ //O(h)
    if(valor <= raiz->valor){
        if(raiz->esq == NULL){
            raiz->esq = newNo(valor);
        } else{
            addNo(raiz->esq, valor);
        }
    } else{
       if(raiz->dir == NULL){
            raiz->dir = newNo(valor);
        } else{
            addNo(raiz->dir, valor);
        } 
    }
}

void addTree(Tree* arv, int valor){
    if(arv->raiz == NULL){
        arv->raiz = newNo(valor);
    } else{
        addNo(arv->raiz, valor);
    }
}

void addTreeI(Tree* t, int valor){
    if(t->raiz == NULL){
        t->raiz = newNo(valor);
        return;
    }
    No* aux = t->raiz;
    int inseriu = 0;

    while(!inseriu){
        if(valor <= aux->valor){
            if(aux->esq == NULL){
                aux->esq = newNo(valor);
                inseriu = 1;
            } else{
                aux = aux->esq;
            }
        } else if(valor > aux->valor){
            if(aux->dir == NULL){
                aux->dir = newNo(valor);
                inseriu = 1;
            } else{
                aux = aux->dir;
            }
        }       
    }
}

int MaxBuscaR(No* no){
    if(no == NULL){
        printf("Erro");
        exit(1);
    }

    if(no->dir == NULL){
        return no->valor;
    } else{
        return MaxBuscaR(no->dir);
    }
}

int MaxBuscaI(No* no){
    if(no == NULL) exit(1);
    while (no->dir)
    {
        no = no->dir;
    }
    return no->valor;
}

int MaxR(No* no){
    if(no->dir == NULL)
        return no->valor;
    return MaxR(no->dir);
}

void liberaMemoria(No* raiz){
    if(raiz == NULL) return;
    liberaMemoria(raiz->esq);
    liberaMemoria(raiz->dir);
    free(raiz);
}

int SizeTree(No* raiz){
    if(raiz == NULL){
        return 0;
    } else{
        return 1+SizeTree(raiz->esq)+SizeTree(raiz->dir);
    }
}

int alturaTree(No* raiz){
    if(raiz==NULL) return -1;
    int he = alturaTree(raiz->esq);
    int hd = alturaTree(raiz->dir);
    return he > hd ? he + 1: hd + 1;
}

//Print Arvore - Recursivo Em-Ordem 
void printNo(No* no){
    if(no == NULL)
        return;
    printNo(no->esq);
    printf("%d,", no->valor);
    printNo(no->dir);
}

void printTree(Tree* t){
    printf("[ ");
    if(t->raiz != NULL)
        printNo(t->raiz);
    printf("]\n");
}

//Print Arvore - XML Pré-Ordem
void printNoXML(No* no, FILE* f){
    fprintf(f, "%d\n", no->valor);
    if(no->esq != NULL){
        fprintf(f, "<esq>\n");
        printNoXML(no->esq,f);
        fprintf(f, "</esq>\n");
    }
    if(no->dir != NULL){
        fprintf(f, "<dir>\n");
        printNoXML(no->dir,f);
        fprintf(f, "</dir>\n");
    }
}

void printTreeXML(Tree* t){
    FILE* f = fopen("Tree.xml", "w+");
    fprintf(f,"<tree>\n");
    if(t->raiz != NULL)
        printNoXML(t->raiz, f);
    fprintf(f,"</tree>\n");
    fclose(f);
}

//Prints Gerais
void printPreOrdem(No* no){
    if(no != NULL){
        printf(" %d", no->valor);
        printPreOrdem(no->esq);
        printPreOrdem(no->dir);
    }
}

void printEmOrdem(No* no){
    if(no != NULL){
        printEmOrdem(no->esq);
        printf(" %d", no->valor);
        printEmOrdem(no->dir);
    }
}

void printPosOrdem(No* no){
    if(no != NULL){
        printPosOrdem(no->esq);
        printPosOrdem(no->dir);
        printf(" %d", no->valor);
    }
}

//Busca - O(h)
No* buscaR(No* no, int valor){ 
    if(no == NULL)
        return NULL;
    else if(no->valor == valor)
        return no;
    else if(valor < no->valor)
        return buscaR(no->esq, valor);
    else
        return buscaR(no->dir, valor);
}

No* buscaI(No* no, int valor){
    No* aux = no;
    while(aux != NULL){
        if(aux->valor == valor)
            return aux;
        else if(valor < aux->valor)
            aux = aux->esq;
        else if(valor > aux->valor)
            aux = aux->dir;
    }
    return NULL;
}

int main(){
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 30};
    int n = sizeof(valores) / sizeof(valores[0]);

    Tree* t  = newTree();   // montada com addTree  (recursivo, usa addNo)
    Tree* ti = newTree();   // montada com addTreeI (iterativo)
    for(int i = 0; i < n; i++){
        addTree(t, valores[i]);
        addTreeI(ti, valores[i]);
    }

    printf("printTree (rec): "); printTree(t);
    printf("printTree (it) : "); printTree(ti);

    printf("Pre-ordem :"); printPreOrdem(t->raiz);  printf("\n");
    printf("Em-ordem  :"); printEmOrdem(t->raiz);   printf("\n");
    printf("Pos-ordem :"); printPosOrdem(t->raiz);  printf("\n");

    printTreeXML(t);
    printf("XML gravado em Tree.xml\n");

    printf("Tamanho: %d\n", SizeTree(t->raiz));
    printf("Altura : %d\n", alturaTree(t->raiz));
    printf("Maximo : %d %d %d\n", MaxBuscaR(t->raiz), MaxBuscaI(t->raiz), MaxR(t->raiz));

    printf("buscaR(45): %s\n", buscaR(t->raiz, 45) ? "achou" : "nao achou");
    printf("buscaI(45): %s\n", buscaI(t->raiz, 45) ? "achou" : "nao achou");
    printf("buscaR(99): %s\n", buscaR(t->raiz, 99) ? "achou" : "nao achou");
    printf("buscaI(99): %s\n", buscaI(t->raiz, 99) ? "achou" : "nao achou");

    liberaMemoria(t->raiz);  free(t);
    liberaMemoria(ti->raiz); free(ti);
    return 0;
}