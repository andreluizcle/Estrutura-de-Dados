#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Coordenada {
    int x,y;
} Coordenada;

Coordenada* newCoordenada(int x, int y){
    Coordenada* aux = (Coordenada*)malloc(sizeof(Coordenada));
    aux->x = x;
    aux->y = y;
    return aux;
}

void printCoordenada(Coordenada *c){
    printf("(%d, %d)", c->x, c->y);
}

//Distancia euclidiana entre duas coordenadas
double euclideanDist(Coordenada * c1, Coordenada * c2){
    double dx = (c1->x)-(c2->x);
    double dy = (c1->y)-(c2->y);
    double raiz = sqrt(dx*dx+dy*dy);
    return raiz;
}

//Segmento de reta composto de duas coordenadas, uma de inicio e outra de fim.
typedef struct Segmento{
    Coordenada *ini, *fim;
}Segmento;

Segmento * newSegmento(Coordenada *ini, Coordenada *fim){
    Segmento * aux = (Segmento *)malloc(sizeof(Segmento));
    aux->ini = ini;
    aux->fim =fim;
    return aux;
}

void printSegmento(Segmento * s){
    printf("[");
    printCoordenada(s->ini);
    printCoordenada(s->fim);
    printf("]");
}

double comprimentoSegmento(Segmento * s){
    return euclideanDist(s->ini,s->fim);
}

Segmento* inverteSegmento (Segmento* seg){
    Coordenada* aux = seg->ini;
    seg->ini = seg->fim;
    seg->fim = aux;
    return seg;
}

void translacaoCoord(Coordenada*c, int dx, int dy){
    c->x += dx;
    c->y += dy;
}

void translacaoSeg(Segmento* seg, int dx, int dy){
    seg->ini->x += dx;
    seg->fim->x += dx;
    seg->ini->y += dy;
    seg->fim->y += dy;
}

typedef struct Triangulo{
    Coordenada *c1, *c2, *c3;
}Triangulo;

Triangulo* newTriangulo(Coordenada* c1, Coordenada* c2, Coordenada* c3){
    Triangulo* t = (Triangulo*)malloc(sizeof(Triangulo));
    t->c1 = c1;
    t->c2 = c2;
    t->c3 = c3;

    return t;
}

double calculaPerimetro(Triangulo* t){
    Segmento* s1 = newSegmento(t->c1, t->c2);
    Segmento* s2 = newSegmento(t->c1, t->c3);
    Segmento* s3 = newSegmento(t->c2, t->c3);

    return comprimentoSegmento(s1)+comprimentoSegmento(s2)+comprimentoSegmento(s3);
}

void printTriangulo(Triangulo* t){
    printf("\nTriangulo\n");
    printf("Coordenada 1: "); printCoordenada(t->c1);printf("\n");
    printf("Coordenada 2: "); printCoordenada(t->c2);printf("\n");
    printf("Coordenada 3: "); printCoordenada(t->c3);printf("\n");
}

//Calcule a intersecao (cruzamento) entre dois segmentos.
//Se a intersecao for vazia, devolva NULL
//
//Forma parametrica:
//  segmento a: P(t) = a->ini + t * r,  com r = a->fim - a->ini,  0 <= t <= 1
//  segmento b: Q(u) = b->ini + u * s,  com s = b->fim - b->ini,  0 <= u <= 1
//Igualando P(t) = Q(u) temos um sistema linear 2x2 em t e u (regra de Cramer).
Coordenada * intersecao(Segmento *a, Segmento *b){
    Coordenada * inter = NULL;
 
    // vetores direcao de cada segmento (em double para evitar divisao inteira)
    double rx = a->fim->x - a->ini->x;
    double ry = a->fim->y - a->ini->y;
    double sx = b->fim->x - b->ini->x;
    double sy = b->fim->y - b->ini->y;
 
    // determinante do sistema (produto vetorial r x s)
    double det = rx * sy - ry * sx;
 
    // det == 0 -> segmentos paralelos ou colineares: sem ponto unico
    if (det == 0)
        return NULL;
 
    // vetor que vai do inicio de a ate o inicio de b
    double qx = b->ini->x - a->ini->x;
    double qy = b->ini->y - a->ini->y;
 
    // solucao do sistema
    double t = (qx * sy - qy * sx) / det;
    double u = (qx * ry - qy * rx) / det;
 
    // o ponto so pertence aos DOIS segmentos se t e u estiverem em [0, 1]
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1){
        double x = a->ini->x + t * rx;
        double y = a->ini->y + t * ry;
        // Coordenada usa int, entao arredondamos
        inter = newCoordenada((int)round(x), (int)round(y));
    }
 
    return inter;
}
 
// Auxiliar para os testes
void testaIntersecao(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2){
    Segmento *a = newSegmento(newCoordenada(ax1, ay1), newCoordenada(ax2, ay2));
    Segmento *b = newSegmento(newCoordenada(bx1, by1), newCoordenada(bx2, by2));
 
    printSegmento(a); printf(" x "); printSegmento(b); printf(" -> ");
    Coordenada *inter = intersecao(a, b);
    if (inter == NULL) printf("NULL\n");
    else { printCoordenada(inter); printf("\n"); free(inter); }
 
    free(a->ini); free(a->fim); free(a);
    free(b->ini); free(b->fim); free(b);
}

int main(void){
    Coordenada *c1 = newCoordenada(1,0);
    Coordenada *c2 = newCoordenada(0,1);
    Coordenada *c3 = newCoordenada(0,0);
    printCoordenada(c1);printf("\n");
    printCoordenada(c2);printf("\n");
    printf("Distancia %.2lf\n",euclideanDist(c1,c2));
    Segmento * s = newSegmento(c1,c2);
    printSegmento(s);printf("\n");
    printf("Comprimento:%.2lf\n",comprimentoSegmento(s));
    printSegmento(inverteSegmento(s));

    Triangulo* t = newTriangulo(c1,c2,c3);
    printf("\nPerimetro do Triangulo: %.2f\n", calculaPerimetro(t));
    printTriangulo(t);

    printf("\n--- Testes de intersecao ---\n");
    testaIntersecao(0,0, 10,10,   0,10, 10,0);   // exemplo do enunciado: (5, 5)
    testaIntersecao(0,0, 2,2,     0,10, 10,0);   // retas se cruzam, segmentos nao: NULL
    testaIntersecao(0,0, 10,0,    0,5, 10,5);    // paralelos: NULL
    testaIntersecao(0,0, 10,0,    5,0, 15,0);    // colineares: NULL
    testaIntersecao(3,-5, 3,5,    0,0, 10,0);    // segmento vertical: (3, 0)
    testaIntersecao(0,0, 4,4,     4,4, 8,0);     // tocam na ponta: (4, 4)

    free(s); free(t); free(c1); free(c2); free(c3);
    return 0;
}