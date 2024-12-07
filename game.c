// 1. Jogo de Adivinhação

// Estrutura usada: Árvore Binária.

// Um clássico jogo em que o computador tenta adivinhar o que você está pensando. 
// A árvore é usada para armazenar perguntas e respostas. 
// O jogador responde com "sim" ou "não" até chegar a uma folha.

// Cada nó contém uma pergunta.
// As folhas contêm as respostas possíveis.

// Como Jogar:
// O jogo faz perguntas que devem ser respondidas com "sim" ou "não".
// Se errar a resposta, você ensina ao jogo uma nova pergunta e resposta.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char question[100];        
    struct Node *yes;           
    struct Node *no;           
} Node;

Node* createNode(const char* text) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->question, text);
    node->yes = NULL;
    node->no = NULL;
    return node;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->yes);
    freeTree(root->no);
    free(root);
}

void playGame(Node* root) {
    Node* current = root;
    Node* parent = NULL;
    char answer[10];

    // Enquanto não for uma folha
    while (current->yes != NULL && current->no != NULL) {  
        printf("%s (sim/nao): ", current->question);
        scanf("%s", answer);

        if (strcmp(answer, "sim") == 0) {
            parent = current;
            current = current->yes;
        }
        else if (strcmp(answer, "nao") == 0) {
            parent = current;
            current = current->no;
        } 
        else {
            printf("Por favor, responda com 'sim' ou 'nao'.\n");
        }
    }

    // Estamos em uma folha (resposta final)
    printf("Eu acho que é: %s. Acertei? (sim/nao): ", current->question);
    scanf("%s", answer);

    if (strcmp(answer, "sim") == 0) {
        printf("Oba! Eu sou ótimo nisso!\n");
    } 
    else {
        // Aprender uma nova resposta
        printf("Qual é a resposta correta? ");
        char newAnswer[100];
        scanf(" %[^\n]s", newAnswer);

        printf("Faça uma pergunta que distingue '%s' de '%s'.\n", newAnswer, current->question);
        char newQuestion[100];
        scanf(" %[^\n]s", newQuestion);

        // Criar novos nós para a nova pergunta e resposta
        Node* newYesNode = createNode(newAnswer);
        Node* newNoNode = createNode(current->question);

        // Atualizar o nó atual com a nova pergunta
        strcpy(current->question, newQuestion);
        current->yes = newYesNode;
        current->no = newNoNode;

        printf("Obrigado! Aprendi algo novo!\n");
    }
}

// Função principal
int main() {
    // A árvore é construída de forma lógica para incluir exemplos variados de categorias como animais, plantas, objetos e conceitos abstratos.
    Node* root = createNode("É um ser vivo?");

    root->yes = createNode("É um animal?");
    root->yes->yes = createNode("É um animal doméstico?");
    root->yes->yes->yes = createNode("Cachorro");
    root->yes->yes->no = createNode("Leão");
    root->yes->no = createNode("É uma planta?");
    root->yes->no->yes = createNode("Árvore");
    root->yes->no->no = createNode("Cogumelo");

    root->no = createNode("É um objeto?");
    root->no->yes = createNode("É eletrônico?");
    root->no->yes->yes = createNode("Celular");
    root->no->yes->no = createNode("Livro");
    root->no->no = createNode("É algo abstrato?");
    root->no->no->yes = createNode("Amor");
    root->no->no->no = createNode("Montanha");

    printf("Bem-vindo ao jogo de 20 perguntas!\n");
    char playAgain[10];

    do {
        playGame(root);
        printf("Deseja jogar novamente? (sim/nao): ");
        scanf("%s", playAgain);
    } while (strcmp(playAgain, "sim") == 0);


    freeTree(root);
    printf("Obrigado por jogar! Até a próxima.\n");
    return 0;
}

/*

Bem-vindo ao jogo de 20 perguntas!

É um ser vivo? (sim/nao): sim
É um animal? (sim/nao): nao
É uma planta? (sim/nao): sim
Eu acho que é: Árvore. Acertei? (sim/nao): nao
Qual é a resposta correta? Girassol
Faça uma pergunta que distingue 'Girassol' de 'Árvore'.
É uma flor?
Obrigado! Aprendi algo novo!

Deseja jogar novamente? (sim/nao): sim

É um ser vivo? (sim/nao): sim
É um animal? (sim/nao): nao
É uma planta? (sim/nao): sim
É uma flor? (sim/nao): sim
Eu acho que é: Girassol. Acertei? (sim/nao): nao
Qual é a resposta correta? Rosa    
Faça uma pergunta que distingue 'Rosa' de 'Girassol'.
É uma flor 'romantica'?            
Obrigado! Aprendi algo novo!

Deseja jogar novamente? (sim/nao): sim

É um ser vivo? (sim/nao): sim
É um animal? (sim/nao): nao
É uma planta? (sim/nao): sim
É uma flor? (sim/nao): sim
É uma flor 'romantica'? (sim/nao): nao
Eu acho que é: Girassol. Acertei? (sim/nao): sim
Oba! Eu sou ótimo nisso!
Deseja jogar novamente? (sim/nao): nao
Obrigado por jogar! Até a próxima.

 */