#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 5 // Ordem da Árvore B (número máximo de filhos)

// Estrutura de um nó da Árvore B
typedef struct BTreeNode {
    int keys[ORDER - 1];        // Array de chaves
    struct BTreeNode* children[ORDER]; // Ponteiros para os filhos
    int numKeys;               // Número de chaves no nó
    bool isLeaf;               // Indica se o nó é uma folha
} BTreeNode;

// Cria um novo nó da Árvore B
BTreeNode* createBTreeNode(bool isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    for (int i = 0; i < ORDER; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Divide um nó cheio
void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    int mid = (ORDER - 1) / 2; // Posição da chave do meio

    // Cria um novo nó para conter os valores da direita
    BTreeNode* newChild = createBTreeNode(child->isLeaf);
    newChild->numKeys = (ORDER - 1) - mid - 1;

    // Copia as chaves da direita do nó original para o novo nó
    for (int i = 0; i < newChild->numKeys; i++) {
        newChild->keys[i] = child->keys[i + mid + 1];
    }

    // Se o nó não for folha, copie também os ponteiros de filhos
    if (!child->isLeaf) {
        for (int i = 0; i <= newChild->numKeys; i++) {
            newChild->children[i] = child->children[i + mid + 1];
        }
    }

    // Ajusta o número de chaves do nó original
    child->numKeys = mid;

    // Ajusta os ponteiros dos filhos do pai
    for (int i = parent->numKeys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    // Move a chave do meio para o nó pai
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[mid];
    parent->numKeys++;
}

// Insere uma chave em um nó não cheio
void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Insere a nova chave na posição correta
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        // Encontra o filho apropriado para a nova chave
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // Se o filho estiver cheio, divida-o
        if (node->children[i]->numKeys == ORDER - 1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

// Insere uma chave na Árvore B
BTreeNode* insertBTree(BTreeNode* root, int key) {
    if (root == NULL) {
        // Cria a raiz se a árvore estiver vazia
        root = createBTreeNode(true);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == ORDER - 1) {
            // Se a raiz estiver cheia, divida-a
            BTreeNode* newRoot = createBTreeNode(false);
            newRoot->children[0] = root;

            splitChild(newRoot, 0, root);

            int i = (key > newRoot->keys[0]) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);

            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
    return root;
}

// Função que percorre a árvore para adivinhar o número
int guessNumber(BTreeNode* root, int target) {
    BTreeNode* currentNode = root;
    while (currentNode != NULL) {
        // Pergunta ao usuário se o número é maior ou menor
        for (int i = 0; i < currentNode->numKeys; i++) {
            printf("O número que você pensou é maior ou menor que %d? (Digite 1 para maior, -1 para menor, 0 para igual): ", currentNode->keys[i]);
            int response;
            scanf("%d", &response);
            
            if (response == 0) {
                printf("Eu adivinhei! O número é %d!\n", currentNode->keys[i]);
                return 0; // Ganhou
            } else if (response == 1) {
                // Vai para o filho à direita
                currentNode = currentNode->children[i + 1];
                break;
            } else if (response == -1) {
                // Vai para o filho à esquerda
                if (i == 0) {
                    currentNode = currentNode->children[i];
                } else {
                    currentNode = currentNode->children[i - 1];
                }
                break;
            }

            // Se estiver na última chave e não tiver feito uma escolha, sai do loop
            if (i == currentNode->numKeys - 1) {
                printf("Perdi... ou então você trapaceou haha\n");
                return -1; // Perdeu
            }
        }
    }
    return -1; // Se não encontrar o número
}

int main() {
    printf("=============================================\n");
    printf("         Jogo de Adivinhação com Árvore B\n");
    printf("=============================================\n");

    // Criação da árvore de números de 1 a 100
    BTreeNode* tree = NULL;
    for (int i = 1; i <= 100; i++) {
        tree = insertBTree(tree, i);
    }

    // Inicia o jogo de adivinhação
    int result = guessNumber(tree, 0);

    if (result == 0) {
        printf("Eu adivinhei seu número!\n");
    } else {
        printf("Tente novamente! Eu não consegui adivinhar.\n");
    }

    return 0;
}
