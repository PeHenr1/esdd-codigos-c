// codigo comentado em https://dontpad.com/peupeup3u/anotacoes/edd/lista-encadeada

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int item;
    struct _node *next;
} t_node;

typedef struct{
    t_node *head;
    t_node *tail;
    int size;
} t_list;

t_list *create_list(){
    t_list *list;
    list = (t_list *)malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int sizeList(t_list *list){
    return list->size;
}

int is_empty(t_list *list){
    return list->size == 0;
}

void destroy_list(t_list *list) {
    t_node* current = list->head;
    t_node* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    free(list);
}

void append(t_list *list, int elem){
    t_node* node;
    node = (t_node*) malloc(sizeof(t_node)); 
    node->item = elem;
    node->next = NULL;

    if(is_empty(list)){
        list->head = node;
    }
    else{
        list->tail->next = node;
    }
    list->tail = node;
    list->size++;
}

int insert(t_list *list, int index, int elem){
    if (index < 0 || index > list->size) return -1;
    t_node* node;
    node = (t_node*) malloc(sizeof(t_node)); 
    node->item = elem;
    node->next = NULL;

    if (index == 0) {
        node->next = list->head;  
        list->head = node;        
        if (is_empty(list)) {    
            list->tail = node;
        }
    }
    else if (index == list->size) {
        list->tail->next = node;  
        list->tail = node;        
    }
    else{ 
        t_node* current = list->head;
        int i = 0;
        while (i < index-1){ //percorre ate antes do indice
            current = current->next;
            i++;
        }
        node->next = current->next;
        current->next = node;
    }
    list->size++;
    return 1;
}

int remove_item(t_list *list, int item){
    t_node* current = list->head;
    t_node* previous = NULL;

    while (current != NULL){ 
        if(current->item == item){
            // se estiver no primeiro nó
            if (previous == NULL) {
                list->head = current->next;
                if (current->next == NULL) {
                    list->tail = NULL;
                }
            }
            //Remover um nó no meio ou no final
            else {
                previous->next = current->next;
                // Se o nó removido for o último, atualiza o tail
                if (current->next == NULL) {
                    list->tail = previous;
                }
            }
            // Libera o nó removido
            free(current);
            list->size--;
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

t_node* get_node_item(t_list *list, int item){
    t_node* current = list->head;  
    
    while (current != NULL) {  
        if (current->item == item) { 
            return current;    
        }
        current = current->next;  
    }
    
    return NULL; 
}

t_node* get_item_by_index(t_list *list, int index){
    if (index < 0 || index > list->size) return NULL;

    t_node* current = list->head;  
    int i = 0;

    while (i < index) {  
        current = current->next; 
        i++; 
    }

    return current; 
}

void print_list(t_list *list){
    t_node* node_aux = list->head;  
    while (node_aux != NULL) {      
        printf("%d ", node_aux->item);  
        node_aux = node_aux->next;      
    }
    printf("\n");
}

void clear(t_list *list){
    t_node* current = list->head;
    t_node* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int find(t_list *list, int item){
    t_node* current = list->head;  
    
    while (current != NULL) {  
        if (current->item == item) { 
            return 1;    
        }
        current = current->next;  
    }
    return -1; 
}

int remove_at(t_list *list, int index){
    if (index < 0 || index >= list->size) return -1;

    t_node* current = list->head;
    t_node* previous = NULL;

    if (index == 0) {
        list->head = current->next;
        if (current->next == NULL) { 
            list->tail = NULL;
        }
        free(current); 
    } 
    else{
        for (int i = 0; i < index; i++) {
            previous = current; 
            current = current->next;
        }
        
        previous->next = current->next; 
        if (current->next == NULL) { 
            list->tail = previous;
        }
        free(current);
    }
    list->size--;
    return -1;
}

// Retorna o nó no início da lista
t_node* peek_front(t_list *list);
// Retorna o nó no final da lista
t_node* peek_back(t_list *list);
// Remove e retorna o nó no início da lista
t_node* pop_front(t_list *list);
// Remove e retorna o nó no final da lista
t_node* pop_back(t_list *list);

void reverse(t_list *list){
    t_node* previous = NULL;
    t_node* current = list->head;
    t_node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    list->head = previous;
}

int sort(t_list *list){
    if (is_empty(list) || list->size == 1)return 0;
    
    int swapped; 
    do {
        swapped = 0; 
        t_node *current = list->head;

        while (current != NULL && current->next != NULL) {
            if (current->item > current->next->item) {
                int temp = current->item; // Armazena o valor do nó atual
                current->item = current->next->item; // Atribui o valor do próximo nó
                current->next->item = temp; // Atribui o valor armazenado ao próximo nó
                swapped = 1; // Indica que houve troca
            }
            current = current->next; // Move para o próximo nó
        }
    } while (swapped); // Continua enquanto houver trocas

    return 1;
}

// Funde duas listas ordenadas em uma única lista ordenada. Assuma que list1 e list2 estão ordenadas.
int merge(t_list *list1, t_list *list2);
// Clona os elementos de uma lista para outra lista
int clone(t_list *src, t_list *dest);




int main(){
    t_list *list;

    list = create_list();
    append(list, 2);
    append(list, 4);
    append(list, 1);

    print_list(list);

    insert(list, 1, 1);
    print_list(list);

    insert(list, 0, 6);
    insert(list,6,111);
    insert(list, 5, 111);
    print_list(list);

    remove_item(list,1);
    print_list(list);

    t_node* g_item = get_node_item(list, 1);
    if (g_item != NULL) {
        printf("Item %d encontrado.\n", g_item->item); 
    } 
    else {
        printf("Item não encontrado.\n");
    }

    t_node* g_index = get_item_by_index(list, 1);
    if (g_index != NULL) {
        printf("Item no indice %d: %d\n", 1, g_index->item);  // Imprime 20
    } 
    else {
        printf("Indice fora dos limites.\n");
    }

    printf("Item %d %s na lista.\n", 4, find(list, 4) == 1 ? "encontrado" : "nao encontrado");
    printf("Item %d %s na lista.\n", 3, find(list, 3) == 1 ? "encontrado" : "nao encontrado");

    clear(list);

    append(list, 2);
    append(list, 4);
    append(list, 2);
    append(list, 1);
    append(list, 2);
    print_list(list);

    remove_at(list, 4);
    print_list(list);
    remove_at(list, 2);
    print_list(list);
    remove_at(list, 0);
    print_list(list);
    remove_at(list, 3);
    print_list(list);

    append(list, 3);
    append(list, 9);
    print_list(list);

    reverse(list);
    print_list(list);

    sort(list);
    print_list(list);
    
    return 0;
}
