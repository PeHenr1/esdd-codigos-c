#ifndef STACK_H
#define STACK_H

typedef struct t_node {
    int item;
    struct t_node* next;
    struct t_node* prev;
} t_node;

typedef struct {
    t_node* head;
    t_node* tail;
    int size;
} t_list;

t_list* create_list();
int destroy_list(t_list *list);
int size(t_list *list);
int is_empty(t_list *list);
int append(t_list *list, int elem);
int insert(t_list *list, int index, int elem);
int remove_item(t_list *list, int item);
t_node* get_node_item(t_list *list, int item);
t_node* get_item_by_index(t_list *list, int index);
void print_list(t_list *list);
int clear(t_list *list);
int find(t_list *list, int item);
int remove_at(t_list *list, int index);
t_node* peek_front(t_list *list);
t_node* peek_back(t_list *list);
t_node* pop_front(t_list *list);
t_node* pop_back(t_list *list);
int reverse(t_list *list);
int sort(t_list *list);
//int merge(t_list *list1, t_list *list2);
t_list* merge(t_list* list_1, t_list* list2);
int clone(t_list *src, t_list *dest);

#endif