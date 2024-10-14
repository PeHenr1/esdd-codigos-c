#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef int t_elem;

typedef struct {
    t_elem *data;  // Ponteiro para os dados da pilha
    int top;       // Índice do topo da pilha
    int capacity;  // Capacidade máxima da pilha
} t_stack;

t_stack* create_stack(int n);
void destroy(t_stack *p);
int is_full(t_stack *p);
int is_empty(t_stack *p);
int push(t_stack *p, t_elem x);
int pop(t_stack *p, t_elem *x);
int top_index(t_stack *p, t_elem *x);
void clear(t_stack *p);
void print(t_stack *p);

#endif /* STACK_H */