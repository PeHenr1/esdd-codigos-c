// codigo comentado em https://dontpad.com/peupeup3u/anotacoes/edd/lista-encadeada

#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int item;
    struct _node *next;
} t_node;

typedef struct
{
    t_node *head;
    t_node *tail;
    int size;
} t_list;

t_list *create_list()
{
    t_list *list;
    list = (t_list *)malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int is_empty(t_list *list)
{
    return list->size == 0;
}

void append(t_list *list, int item)
{
    t_node *node;
    node = (t_node *)malloc(sizeof(t_node));
    node->item = item;
    node->next = NULL;

    if (is_empty(list))
    {
        list->head = node;
    }
    else
    {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;
}

/* MEU CODIGO COM O GPT (search)
t_node *search(t_list *list, int item)
{
    t_node *current = list->head;

    while (current != NULL)
    {
        if (current->item == item)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
*/

t_node* search(t_list* list, int item) {
    t_node* current = list->head;  
    while (current->item != item || current != NULL) {  
        current = current->next; 
    }
    return current;
}


int remove_element(t_list *list, t_node *node_to_be_removed){
    if(node_to_be_removed == list->head){
        list->head = node_to_be_removed->next;
        free(node_to_be_removed);
        list->size--;
    }
    else{
        t_node* node_prev = list->head;
        while (node_prev->next != node_to_be_removed)
        {
            node_prev = node_prev->next;
        }
        node_prev->next = node_to_be_removed->next;
        if(list->tail == node_to_be_removed){
            list->tail = node_prev;
        }
    }
    free(node_to_be_removed);
    list->size--;
}

/* MEU CODIGO COM O GPT (remove_element)
int remove_element(t_list *list, t_node *node_to_be_removed)
{
    if (is_empty(list))
    {
        return 0;
    }

    t_node *current = list->head;
    t_node *previous = NULL;

    while (current != NULL)
    {
        if (current == node_to_be_removed)
        {
            if (previous == NULL)
            {
                list->head = current->next;
                if (list->head == NULL)
                {
                    list->tail = NULL;
                }
            }
            else
            {
                previous->next = current->next;
                if (current->next == NULL)
                {
                    list->tail = previous;
                }
            }

            free(current);
            list->size--;
            return 1;
        }
        previous = current;
        current = current->next;
    }

    return 0;
}*/

void reverse(t_list *list)
{
    t_node *current = list->head;
    t_node *previous = NULL;
    t_node *node_aux = NULL;

    while (current != NULL)
    {
        node_aux = current->next;
        current->next = previous;
        previous = current;
        current = node_aux;
    }

    list->head = previous;
}

void print_list(t_list *list)
{
    t_node *node_aux = list->head;
    while (node_aux != NULL)
    {
        printf("%d ", node_aux->item);
        node_aux = node_aux->next;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
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
