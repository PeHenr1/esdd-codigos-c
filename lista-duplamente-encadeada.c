#include <stdio.h>
#include <stdlib.h>
#include "lista-duplamente-encadeada.h"

t_list* create_list(){
    t_list* list = (t_list*)malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int destroy_list(t_list *list){
    if(list == NULL) return 1; // lista já vazia
    t_node* current = list->head;
    t_node* aux;

    while (current != NULL){
        aux = current->next;
        free(current);
        current = aux;
    }
    
    free(list); // Libere a lista após todos os nós terem sido liberados
    return 0; // Sucesso
}

int size(t_list *list){
    return list->size;
}

int is_empty(t_list *list){
    return list->size == 0;
}

int append(t_list *list, int elem){
    t_node* node = (t_node*)malloc(sizeof(t_node)); 

    if (node == NULL) {
        return -1; // Retorna um erro se a alocação falhar
    }

    node->item = elem;
    node->next = NULL;

    if (is_empty(list)) {
        list->head = node;
        list->tail = node;
        node->prev = NULL;
    } 
    else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
    return 0;
}

int insert(t_list *list, int index, int elem){
    if (index < 0 || index > list->size) return -1;
    
    t_node* node = (t_node*)malloc(sizeof(t_node)); 
    if (node == NULL) {
        return -1; // Retorna um erro se a alocação falhar
    }

    node->item = elem;

    if (index == 0) {
        node->prev = NULL;
        if (is_empty(list)) {
            list->head = node;
            list->tail = node;
            node->next = NULL;
        }
        else{
            node->next = list->head;
            list->head->prev = node;
            list->head = node;
        }

    } 
    else if (index == list->size) {
        node->prev = list->tail; 
        node->next = NULL; 
        list->tail->next = node;
        list->tail = node;
    } 
    else {
        t_node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        node->next = current->next; 
        node->prev = current; 
        current->next->prev = node; 
        current->next = node; 
    }
    list->size++;
    return 0; // Sucesso
}

int remove_item(t_list *list, int item){
    if(is_empty(list)) return -1;

    t_node* current = list->head;
    while(current != NULL){
        if(current->item == item){
            // primeiro nó
            if(current->prev == NULL){
                list->head = current->next;
                if (list->head != NULL) {
                    list->head->prev = NULL; 
                } 
                else { 
                    list->tail = NULL;
                }
            }
            // demais nós
            else{
                current->prev->next = current->next;

                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
                else{
                    list->tail = NULL;
                }
            }  
            free(current);
            list->size--;
            return 0;
        }
        current = current->next;
    }
    return 1;
}

t_node* get_node_item(t_list *list, int item){
    if(is_empty(list)) return NULL;
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
    if(index < 0 || index >= list->size) return NULL;
    if(is_empty(list)) return NULL;
    t_node* current = list->head;
    int i = 0;

    while(i < index){
        current = current->next;
        i++;
    }
    return current;
}

void print_list(t_list *list){
    t_node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->item);
        current = current->next;
    }
    printf("\n");
}

int clear(t_list *list){
    if(is_empty(list)) return -1;
    t_node* current = list->head;
    t_node* aux;
    while(current != NULL){
        aux = current->next;
        free(current);
        current = aux;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return 0;
}

int find(t_list *list, int item){
    if(is_empty(list)) return -1;

    t_node* current = list->head;  
    
    while (current != NULL) {  
        if (current->item == item) { 
            return 0;    
        }
        current = current->next;  
    }
    return -1; 
}

int remove_at(t_list *list, int index){
    if(index < 0 || index >= list->size) return -1;
    if(is_empty(list)) return -1;

    t_node* current = list->head;

    if(index == 0){
        list->head = current->next;
        if (list->head != NULL) {
            list->head->prev = NULL; 
        } 
        else { 
            list->tail = NULL;
        }
        free(current);
    }

    else{
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        
        if (current->next != NULL) {
            current->next->prev = current->prev; 
        } 
        else {
            list->tail = current->prev; 
        }

        free(current);
    }
    list->size--;
    return 0;
}

t_node* peek_front(t_list *list){
    return list->head;
}

t_node* peek_back(t_list *list){
    return list->tail;
}

t_node* pop_front(t_list *list){
    if (is_empty(list)) return NULL; 

    t_node* head_node = list->head; 
    list->head = head_node->next;

    if (list->head != NULL){
        list->head->prev = NULL;
    }
    else{
        list->tail = NULL;
    }
    list->size--;
    return head_node;
}

t_node* pop_back(t_list *list){
    if (is_empty(list)) return NULL; 

    t_node* tail_node = list->tail;
    list->tail = tail_node->prev;

    if(list->tail != NULL) list->tail->next = NULL;
    else list->head = NULL;

    list->size--;
    return tail_node;
}

int reverse(t_list *list){
    if(is_empty(list))return -1;
    t_node* current = list->head;
    t_node* previous = NULL;
    t_node* next = NULL;

    while(current != NULL){
        next = current->next;     // Armazena o próximo nó
        current->next = previous; // Inverte o ponteiro next
        current->prev = next;     // Inverte o ponteiro prev
        previous = current;        // Avança previous para o nó atual
        current = next;           // Avança current para o próximo nó
    }
    list->head = previous;
    return 0;
}

int sort(t_list *list){
    if(is_empty(list)) return -1;
    int swapped;
    do {
        swapped = 0; 
        t_node* current = list->head;

        while (current != NULL && current->next != NULL) {
            if (current->item > current->next->item) {
                int temp = current->item; 
                current->item = current->next->item; 
                current->next->item = temp; 
                swapped = 1; 
            }
            current = current->next;
        }
    } while (swapped); 

    return 0; 
}

// apenas faz o merge e esvazia a lista dois
/*int merge(t_list* list1, t_list* list2) {
    if (is_empty(list1) || is_empty(list2)) return -1;
    
    sort(list1);
    sort(list2);

    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;
    
    list1->tail = list2->tail;
    
    list1->size += list2->size;
    
    return 0;
}*/
// cria uma nova e ordenada
t_list* merge(t_list* list1, t_list* list2) {
    sort(list1);
    sort(list2);

    if (!list1 || !list2) {
        return NULL; // Retorna NULL se houver erro
    }

    // Cria uma nova lista para armazenar a lista mesclada
    t_list *merged_list = (t_list*)malloc(sizeof(t_list));
    if (!merged_list) {
        return NULL; // Erro ao alocar memória
    }
    merged_list->head = NULL;
    merged_list->tail = NULL;
    merged_list->size = 0;

    t_node *current1 = list1->head;
    t_node *current2 = list2->head;

    while (current1 != NULL && current2 != NULL) {
        t_node *new_node = (t_node*)malloc(sizeof(t_node));
        if (!new_node) {
            free(merged_list); // Libera a memória alocada para merged_list
            return NULL; // Erro ao alocar memória
        }

        if (current1->item < current2->item) {
            new_node->item = current1->item;
            current1 = current1->next;
        } else {
            new_node->item = current2->item;
            current2 = current2->next;
        }

        new_node->next = NULL;
        new_node->prev = merged_list->tail;

        if (merged_list->tail) {
            merged_list->tail->next = new_node;
        } else {
            merged_list->head = new_node; // Primeiro elemento
        }

        merged_list->tail = new_node;
        merged_list->size++;
    }

    // Adiciona os nós restantes de list1
    while (current1 != NULL) {
        t_node *new_node = (t_node*)malloc(sizeof(t_node));
        if (!new_node) {
            free(merged_list); // Libera a memória alocada para merged_list
            return NULL; // Erro ao alocar memória
        }
        new_node->item = current1->item;
        new_node->next = NULL;
        new_node->prev = merged_list->tail;

        if (merged_list->tail) {
            merged_list->tail->next = new_node;
        } else {
            merged_list->head = new_node; // Primeiro elemento
        }

        merged_list->tail = new_node;
        merged_list->size++;
        current1 = current1->next;
    }

    // Adiciona os nós restantes de list2
    while (current2 != NULL) {
        t_node *new_node = (t_node*)malloc(sizeof(t_node));
        if (!new_node) {
            free(merged_list); // Libera a memória alocada para merged_list
            return NULL; // Erro ao alocar memória
        }
        new_node->item = current2->item;
        new_node->next = NULL;
        new_node->prev = merged_list->tail;

        if (merged_list->tail) {
            merged_list->tail->next = new_node;
        } else {
            merged_list->head = new_node; // Primeiro elemento
        }

        merged_list->tail = new_node;
        merged_list->size++;
        current2 = current2->next;
    }

    return merged_list; // Retorna a lista mesclada
}



int main() {
    t_list* list = create_list();

    append(list,1);
    append(list,2);
    append(list,3);
    print_list(list);

    insert(list,3,4);
    insert(list,5,5);
    print_list(list);

    remove_item(list,1);
    print_list(list);

    printf("Numero %d %s\n", 1, (remove_item(list,1) == 0) ? "removido com sucesso" : "nao encontrado");
    print_list(list);

    printf("Numero %d %s\n", 4, (remove_item(list,4) == 0) ? "removido com sucesso" : "nao encontrado");
    print_list(list);

    printf("Item %d %s na lista.\n", 3, (get_node_item(list, 3) != NULL) ? "encontrado" : "nao encontrado");
    printf("Item %d %s na lista.\n", 10, (get_node_item(list, 10) != NULL) ? "encontrado" : "nao encontrado");

    t_node* found_node = get_item_by_index(list, 1);
    printf("Item no indice %d: ", 1);
    if (found_node != NULL) {
        printf("%d.\n", found_node->item);
    } else {
        printf("inexistente [indice invalido].\n");
    }

    found_node = get_item_by_index(list, 2);
    if (found_node != NULL) {
        printf("Item no indice %d: %d.\n", 1, found_node->item);
    } 
    else {
        printf("Indice informado [%d] invalido.\n",2);
    }

    printf("%s\n", (clear(list) == 0) ? "Lista limpa com sucesso." : "A lista ja estava vazia ou nao foi inicializada.");
    printf("%s\n", (clear(list) == 0) ? "Lista limpa com sucesso." : "A lista ja estava vazia ou nao foi inicializada.");

    append(list,2);
    append(list,4);
    append(list,6);
    append(list,8);
    append(list,9);
    insert(list,0,1);
    print_list(list);

    printf("O item %d %s na lista.\n", 4, (find(list, 4) == 0) ? "esta presente" : "nao esta presente");
    printf("O item %d %s na lista.\n", 3, (find(list, 3) == 0) ? "esta presente" : "nao esta presente");

    printf("O item no indice [%d]: %s\n", 0,(remove_at(list, 0) == 0) ? "foi removido" : "nao existe, valor invalido ou lista vazia.");
    printf("O item no indice [%d]: %s\n", 3,(remove_at(list, 3) == 0) ? "foi removido" : "nao existe, valor invalido ou lista vazia.");
    print_list(list);

    t_node* front_node = peek_front(list);
    if (front_node != NULL) printf("Head: %d\n", front_node->item);
    else printf("Lista vazia\n");

    t_node* back_node = peek_back(list);
    if (back_node != NULL) printf("Tail: %d\n", back_node->item);
    else printf("Lista vazia\n");

    
    t_node* removed_node = pop_front(list);
    if (removed_node != NULL) {
        printf("Head removido: %d\n", removed_node->item);
        free(removed_node); 
    } 
    else {
        printf("A lista está vazia, não há nó para remover.\n");
    }

    removed_node = pop_back(list);
    if (removed_node != NULL) {
        printf("Tail removido: %d\n", removed_node->item);
        free(removed_node);
    } else {
        printf("A lista está vazia, não há nó para remover.\n");
    }

    print_list(list);

    insert(list,1,5);
    insert(list,0,27);
    print_list(list);

    reverse(list);
    print_list(list);

    sort(list);
    print_list(list);

    t_list* list2 = create_list();

    append(list2,100);
    append(list2,200);
    append(list2,300);


    printf("Lista 1: ");
    print_list(list);
    printf("Lista 2: ");
    print_list(list2);

    t_list* merged_list = merge(list, list2);
    printf("Lista Merged [1 e 2]: ");
    print_list(merged_list);



    t_list* list3 = create_list();
    append(list3,3);
    append(list3,2);
    append(list3,1);
    printf("Lista 3: ");
    print_list(list3);

    t_list* list4 = create_list();
    append(list4,11);
    append(list4,27);
    append(list4,6);
    printf("Lista 4: ");
    print_list(list4);

    t_list* merged_list2 = merge(list3, list4);
    printf("Lista Merged [3 e 4]: ");
    print_list(merged_list2);

    destroy_list(list);
    destroy_list(list2);
    destroy_list(list3);
    destroy_list(list4);
    destroy_list(merged_list);
    destroy_list(merged_list2);

    return 0;
}


