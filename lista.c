#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int max;
    int n;
    int* items;
} t_list;

t_list* create_list(int max) {
    t_list* list;
    list = (t_list*) malloc(sizeof(t_list));
    list->max = max;
    list->n = 0;
    list->items = (int*) malloc(sizeof(int)*max);
    return list;
}

void destroy_list(t_list* list) {
    free(list->items);
    free(list);
}

int is_full(t_list* list){
    return list->n == list->max;
}

int append(t_list* list, int e){
    if(!is_full(list)){
        list->items[list->n] = e;
        list->n++;
        return 1;
    }
    return 0;
}

int insert(){}

//int update(){}



