#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef int t_elem;

typedef struct {
    t_elem *data;   // Array para armazenar os elementos
    int front;      // Índice do elemento frontal
    int rear;       // Índice do próximo elemento a ser inserido
    int capacity;   // Capacidade máxima da fila
    int count;      // Número atual de elementos na fila
} t_queue;

t_queue* create_queue(int n);
void destroy(t_queue *q);
int is_empty(t_queue *q);
int is_full(t_queue *q);
int size(t_queue *q);
int in(t_queue *q, t_elem x);
int out(t_queue *q, t_elem *x);
void clear(t_queue *q);
void print(t_queue *q);

#endif /* QUEUE_H*/