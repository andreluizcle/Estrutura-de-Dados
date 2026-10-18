#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int top = 0;
int v[MAX];

void push(int x){
    v[top] = x;
    top++;
}

int pop(){
    return v[--top];
}

int main(){
    push(3);
    push(5);
    push(4);
    push(2);
    push(1);

    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
}