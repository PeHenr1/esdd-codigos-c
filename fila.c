#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

t_queue* create_queue(int n) {
    t_queue *q = (t_queue*)malloc(sizeof(t_queue));
    if (!q) {
        printf("Erro ao alocar memória para a fila.\n");
        return NULL;
    }
    q->data = (t_elem*)malloc(n * sizeof(t_elem));
    if (!q->data) {
        printf("Erro ao alocar memória para os elementos da fila.\n");
        free(q);
        return NULL;
    }
    q->capacity = n;
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    return q;
}

void destroy(t_queue *q) {
    if (q) {
        free(q->data); 
        free(q);     
    }
}

int is_empty(t_queue *q) {
    return (q->count == 0);
}

int is_full(t_queue *q) {
    return (q->count == q->capacity);
}

int size(t_queue *q) {
    return q->count;
}

int in(t_queue *q, t_elem x) {
    if (is_full(q)) {
        printf("A fila está cheia.");
        return -1;
    }
    q->data[q->rear] = x; 
    q->rear = (q->rear + 1) % q->capacity; 
    q->count++; 
    return 0;
}

int out(t_queue *q, t_elem *x) {
    if (is_empty(q)) {
        printf("A fila está vazia. Não é possível remover um elemento.\n");
        return -1; 
    }
    *x = q->data[q->front]; 
    q->front = (q->front + 1) % q->capacity;
    q->count--; 
    return *x; 
}

void clear(t_queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0; 
}

void print(t_queue *q) {
    if (is_empty(q)) {
        printf("A fila está vazia.\n");
        return;
    }
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->data[(q->front + i) % q->capacity]); // Acessa os elementos considerando o índice circular
    }
    printf("\n");
}


int main() {
    int capacity = 5; // Capacidade da fila
    t_queue *queue = create_queue(capacity); // Cria uma nova fila

    printf("Inserindo elementos na fila:\n");
    for (int i = 1; i <= capacity; i++) {
        if (in(queue, i) == 0) {
            printf("Elemento %d inserido.\n", i);
        } else {
            printf("Falha ao inserir elemento %d: fila cheia.\n", i);
        }
    }

    print(queue);
    printf("Tamanho da fila: %d\n", size(queue));

    printf("\nRemovendo elementos da fila:\n");
    for (int i = 0; i < capacity + 1; i++) { // Tenta remover mais elementos do que existem
        int x;
        if (out(queue, &x) == -1) {
            printf("Não foi possível remover elemento: fila vazia.\n");
        } else {
            printf("Elemento removido: %d\n", x);
        }
    }

    print(queue);
    printf("Tamanho da fila: %d\n", size(queue));

    printf("\nInserindo mais alguns elementos:\n");
    in(queue, 6);
    in(queue, 7);
    print(queue);

    printf("\nLimpando a fila...\n");
    clear(queue);
    print(queue); // Deve estar vazia
    printf("Tamanho da fila após limpar: %d\n", size(queue));

    destroy(queue);
    printf("Fila destruída.\n");

    return 0;
}