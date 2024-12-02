#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[TABLE_SIZE];
} HashTable;

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void insert(HashTable* table, int key) {
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    printf("Chave %d inserida no indice %d.\n", key, index);
}

void delete(HashTable* table, int key) {
    int index = hashFunction(key);
    Node* current = table->buckets[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                table->buckets[index] = current->next;   
            } else {
                prev->next = current->next; 
            }
            free(current);
            printf("Chave %d removida do indice %d.\n", key, index);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Chave %d nao encontrada no indice %d.\n", key, index);
}

void displayHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Índice %d:", i);
        Node* current = table->buckets[i];
        while (current != NULL) {
            printf(" %d ->", current->key);
            current = current->next;
        }
        printf(" NULL\n");
    }
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table);
}

int main() {
    HashTable* table = createHashTable();

    insert(table, 15);
    insert(table, 25);
    insert(table, 35);
    insert(table, 20);
    insert(table, 30);

    printf("\nTabela Hash apos insercoes:\n");
    displayHashTable(table);

    delete(table, 25);
    delete(table, 35);
    delete(table, 40); 

    printf("\nTabela Hash apos remocoes:\n");
    displayHashTable(table);

    freeHashTable(table);

    return 0;
}
