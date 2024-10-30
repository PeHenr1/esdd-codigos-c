#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int item;
	struct _node* left;
	struct _node* right;
} t_node;

typedef struct {
	t_node* root;
	int size;
} t_tree;

t_tree* create_tree(){
	t_tree* tree = (t_tree*)malloc(sizeof(t_tree));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

int is_empty(t_tree* tree){
	return (tree->size == 0);
}

void insert(t_tree* tree, int elem){
	t_node* node = (t_node*)malloc(sizeof(node));
	node->item = elem;
	node->left = NULL;
	node->right = NULL;

	if(is_empty(tree)){
		tree->root = node;
	}
	else{
		t_node* current = tree->root;
		t_node* prev = NULL;
		while(current != NULL){
			if ( current->item > node->item  ){
				prev = current;
				current = current->left;
			}
			else if ( current->item < node->item  ){
				prev = current;
				current = current->right;
			}
		}

		if( node->item > prev->item ){
			prev->right = node;
		}
		else if( node->item < prev->item ){
			prev->left = node;
		}
	}
	tree->size++;
}

void pre_order(t_node* no){
    if(no != NULL){
        printf("%d\t",no->item);
        pre_order(no->left);
        pre_order(no->right);
    }
}

void post_order(t_node* no){
    if(no != NULL){
        post_order(no->left);
        post_order(no->right);
        printf("%d\t",no->item);
    }
}

void in_order(t_node* no){
    if(no != NULL){
        in_order(no->left);
        printf("%d\t",no->item);
        in_order(no->right);
    }
}

int main(){
	t_tree* tree;

    tree = create_tree();
    insert(tree, 7);
    insert(tree, 5);
    insert(tree, 8);
    insert(tree, 11);
    insert(tree, 1);


    in_order(tree->root);
	printf("\n");
    pre_order(tree->root);
	printf("\n");
    post_order(tree->root);

	return 0;
}


