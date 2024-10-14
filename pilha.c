#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


t_stack* create_stack(int n) {
    t_stack *stack = (t_stack*)malloc(sizeof(t_stack));
    if (!stack) {
        return NULL;
    }
    stack->data = (t_elem*)malloc(n * sizeof(t_elem));
    if (!stack->data) {
        free(stack); 
        return NULL;
    }
    stack->top = -1;      
    stack->capacity = n;  
    return stack;
}

void destroy(t_stack *p) {
    if (p) {
        free(p->data); 
        free(p);       
    }
}

int is_full(t_stack *p) {
    return p->top == p->capacity - 1;
}

int is_empty(t_stack *p) {
    return p->top == -1;
}

int push(t_stack *p, t_elem x) {
    if (is_full(p)) {
        return 0;
    }
    p->data[++(p->top)] = x; // ++(p->top) incrementa antes pq top é -1
    return 1; 
}

int pop(t_stack* p, t_elem* x) {
    if (is_empty(p)) {
        return 0; 
    }
    *x = p->data[(p->top)--]; 
    return *x; 
}

int top_index(t_stack *p, t_elem *x) {
    if (is_empty(p)) {
        return 0; 
    }
    *x = p->data[p->top]; 
    return *x; 
}

void clear(t_stack *p) {
    while (!is_empty(p)) {
        pop(p, NULL);
    }
    p->top = -1;
}

void print(t_stack *p) {
    if (is_empty(p)) {
        printf("Pilha vazia.\n");
        return;
    }
    for (int i = p->top; i >= 0; i--) {
        printf("%d ", p->data[i]);
    }
    printf("\n");
}



int main() {
    int capacity = 5; 
    t_stack *myStack = create_stack(capacity); 
    if (myStack == NULL) {
        printf("Falha ao criar a pilha.\n");
        return 1; 
    }

    printf("Pilha vazia? %s\n", is_empty(myStack) ? "Sim" : "Nao");

    for (int i = 1; i <= capacity; i++) {
        if (push(myStack, i)) {
            printf("Empilhado: %d\n", i);
        } 
        else {
            printf("Pilha cheia, nao foi possivel empilhar: %d\n", i);
        }
    }

    if (!push(myStack, 6)) {
        printf("Tentativa de empilhar 6 falhou, a pilha esta cheia.\n");
    }

    printf("Pilha: ");
    print(myStack);

    t_elem topElement;
    if (top_index(myStack, &topElement)) {
        printf("Elemento no topo: %d\n", topElement);
    } 
    else {
        printf("A pilha esta vazia, nao ha elemento no topo.\n");
    }

    for (int i = 0; i < capacity ; i++) {
        if (pop(myStack, &topElement)) {
            printf("Desempilhado: %d\n", topElement);
        } 
        else {
            printf("Tentativa de desempilhar falhou, a pilha esta vazia.\n");
        }
    }

    clear(myStack);
    printf("Pilha limpa.\n");

    printf("Pilha vazia? %s\n", is_empty(myStack) ? "Sim" : "Nao");

    destroy(myStack);
    printf("Pilha destruida.\n");

    return 0;
}