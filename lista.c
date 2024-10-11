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

void print_list(t_list* list) {
    for (int i = 0; i < list->n; i++) {
        printf("%d ", list->items[i]);
    }
    printf("\n");
}

void destroy_list(t_list* list) {
    free(list->items);
    free(list);
}

int size(t_list* list){
    return list->n;
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

int insert(t_list* list, int e, int index){
    if(index >= list->n) return 0;
    if(!is_full(list)){
        list->n++;
        for (int i = size(list); i > index ; i--){
            list->items[i] = list->items[i - 1];
        }
        list->items[index] = e;
        return 1;
    }
    return 0;
}

int update(t_list* list, int e, int index){
    if(index >= list->n) return 0;
    if(!is_full(list)){
        for (int i = 0; i < size(list) ; i++){
            if(i == index){
                list->items[index] = e;
                return 1;
            }
        }
    }
    return 0;
}

int removeByIndex(t_list* list, int index){
    if(index >= list->n || index >= list->max) return 0;
    for (int i = 0; i < size(list); i++){
        if(i == index){
            for(int j = i; j < size(list)-1; j++){
                list->items[j] = list->items[j+1];
            }
            list->n--;
            return 1;
        }
    }
    return 0;
}

int removeByElement(t_list* list, int e){
    for (int i = 0; i < size(list); i++){
        if(list->items[i] == e){
            for(int j = i; j < size(list)-1; j++){
                list->items[j] = list->items[j+1];
            }
            list->n--;
            return 1;
        }
    }
    return 0;
}

int index_of(t_list* list, int e){
    for (int i = 0; i < size(list); i++){
        if(list->items[i] == e){
            return i;
        }
    }
    return 0;
}

/*
int getElement(t_list* list, int index){
    if (index >= 0 && index < size(list)) { 
        return list->items[index]; 
    }
    return 0;
}
*/

int countElement(t_list* list, int e){
    int cont = 0;
    for (int i = 0; i < size(list); i++){
        if(list->items[i] == e){
            cont++;
        }
    }
    return cont;
}

int main() {
    t_list* list;

    list = create_list(10);
    append(list, 5);
    append(list, 10);
    append(list, 8);
    append(list, 5);

    print_list(list);

    printf("%d\n",index_of(list,5));
    printf("%d\n",countElement(list,5));

    insert(list,1,0);
    print_list(list);

    insert(list,222,5); 
    print_list(list);   // print igual ao de cima pq nao rola, indice dado é invalido

    insert(list,666,3);
    print_list(list);

    update(list,0,3);
    print_list(list);

    removeByIndex(list,3);
    print_list(list);

    removeByElement(list,5);
    print_list(list);

    printf("%d\n",countElement(list,5));

    destroy_list(list);
    return 0;
}