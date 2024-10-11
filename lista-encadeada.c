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

int is_empty(t_list *list){
    return list->size == 0;
}

// Libera a memória alocada para a lista
int destroy_list(t_list *list);
// Retorna o tamanho atual da lista
int size(t_list *list);
// Verifica se a lista está vazia
int append(t_list *list, int elem);
// Insere um elemento em uma posição específica da lista
int insert(t_list *list, int index, int elem);
// Remove a primeira ocorrência do elemento especificado da lista
int remove_item(t_list *list, int item);
// Retorna o nó que contém o item especificado, se encontrado na lista
t_node* get_node_item(t_list *list, int item);
// Retorna o nó na posição especificada na lista
t_node* get_item_by_index(t_list *list, int index);
// Imprime os elementos da lista
int print_list(t_list *list);
// Remove todos os elementos da lista
int clear(t_list *list);
// Retorna se encontrou determinado item na lista
int find(t_list *list, int item);
// Remove o elemento na posição especificada da lista
int remove_at(t_list *list, int index);
// Retorna o nó no início da lista
t_node* peek_front(t_list *list);
// Retorna o nó no final da lista
t_node* peek_back(t_list *list);
// Remove e retorna o nó no início da lista
t_node* pop_front(t_list *list);
// Remove e retorna o nó no final da lista
t_node* pop_back(t_list *list);
// Inverte a ordem dos elementos na lista
int reverse(t_list *list);
// Ordena os elementos na lista
int sort(t_list *list);
// Funde duas listas ordenadas em uma única lista ordenada. Assuma que list1 e list2 estão ordenadas.
int merge(t_list *list1, t_list *list2);
// Clona os elementos de uma lista para outra lista
int clone(t_list *src, t_list *dest);




int main(int argc, char const *argv[]){
    t_list *list;

    list = create_list();
    append(list, 2);
    append(list, 4);
    append(list, 1);
    append(list, 6);
    append(list, 7);

    print_list(list);

    t_node *node_to_remove = search(list, 6);
    if (node_to_remove != NULL)
    {
        printf("Item %d encontrado.\n", node_to_remove->item);
        remove_element(list, node_to_remove);
        print_list(list);
    }
    else
    {
        printf("Item não encontrado.\n");
    }

    reverse(list);
    print_list(list);

    return 0;
}
