#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "sma.h"


// ---------- CREATE FUNCTIONS ----------
node_t *create_node(int numColors) {

    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;

    new_node->weight = 0;
    new_node->corner = 0;
    new_node->color = 0;
    new_node->children = malloc(sizeof(node_t*)*4*numColors);
    for(int i=0; i<numColors*4; i++)
        new_node->children[i] = NULL;

    // Inicializa o vetor colors com 0
    for (int i = 0; i < 5; i++) {
        new_node->colors[i] = 0;
    }

    return new_node;
}



root_t* create_root(int m, int n, int numColors) {

    root_t *new_root = malloc(sizeof(root_t));
    if(!new_root)
        return NULL;

    new_root->init = create_node(numColors);
    new_root->numColored = 0;

    return new_root;

}


// ---------- SEARCH FUNCTIONS ----------
// Calculates the weight of each choice based in heuristic
int calculate_weight(node_t *node, int numChildren) {

    return rand() % 100;

}

// Calculates the weight based in how much new slots will be colored
int calculate_weight2(board_t *board, int m, int n, int numColors, node_t *node) {

    slot_t copy[m][n];
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            copy[i][j].color = board->slots[i][j]->color;
            copy[i][j].colored = board->slots[i][j]->colored;
        }
    
    int before = countNonColored(board, m, n);
    flood_fill(board, m, n, node->color, node->corner);
    int after = countNonColored(board, m, n);

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            board->slots[i][j]->color = copy[i][j].color;
            board->slots[i][j]->colored = copy[i][j].colored;
        }

    printf("CORNER = %d | COLOR = ", node->corner);
    print_slot(node->color);
    printf("\nDEBUG!! ANTES = %d | DEPOIS = %d | Saldo = %d\n\n", before, after, before-after);
    return before - after;

}


// int calcula_maior(int *colors) {
//     int maior = 0;
//     for(int i=0; i<5; i++)
//         if(colors[i] > maior)
//             maior = i;
//     return maior;
// }

// void calculate_weight3(board_t *board, slot_t *slot, int chosen, node_t *node) {
//     // preenche o tabuleiro com a cor colo
//     printf ("Escolhido: %d\n", chosen);
//     if (slot->down->color == chosen) {
//         printf ("Cor do slot %d, Escolhido: %d\n", slot->color, chosen);
//         node->colors[chosen]++;

//         if (slot->left != NULL) calculate_weight3(board, slot->left, chosen, node);
//         if (slot->right != NULL) calculate_weight3(board, slot->right, chosen, node);
//         if (slot->up != NULL) calculate_weight3(board, slot->up, chosen, node);
//         if (slot->down != NULL) calculate_weight3(board, slot->down, chosen, node);
//     }

//     return;
// }

void calculate_weight3(board_t *board, slot_t *slot, int chosen, node_t *node) {
    // preenche o tabuleiro com a cor colo
    if (slot->color == chosen) {
        if (slot->left != NULL && slot->left->color != chosen) {
            node->colors[slot->left->color]++;
        }
        if (slot->right != NULL && slot->right->color != chosen) {
            node->colors[slot->right->color]++;
        }
        if (slot->up != NULL && slot->up->color != chosen) {
            node->colors[slot->up->color]++;
        }
        if (slot->down != NULL && slot->down->color != chosen) {
            node->colors[slot->down->color]++;
        }

        if (slot->left != NULL) calculate_weight3(board, slot->left, chosen, node);
        if (slot->right != NULL) calculate_weight3(board, slot->right, chosen, node);
        if (slot->up != NULL) calculate_weight3(board, slot->up, chosen, node);
        if (slot->down != NULL) calculate_weight3(board, slot->down, chosen, node);
    }

    return;
}


// Expand the node for next search
node_t *expand_node(board_t *board, node_t *node, int m, int n, int numColors) {
    
    for(int i=0; i<numColors; i++) {
        for(int j=0; j<4; j++) {
            node->children[i*4+j] = create_node(numColors);
            node->children[i*4+j]->color = i;
            node->children[i*4+j]->corner = j;
            node->children[i*4+j]->weight = calculate_weight(node, numColors*4);
            // node->children[i*4+j]->weight = calculate_weight2(board, m, n, numColors, node->children[i*4+j]);
        }
    }

    return node;

}

// Makes the decision of the tree path
node_t *decision(node_t *node, int numColors) {

    node_t *decision = node->children[0];
    for(int i=1; i<numColors*4; i++)
        if(node->children[i]->weight > decision->weight)
            decision = node->children[i];
    
    return decision;

}


// ---------- DESTROY FUNCTIONS ----------
void destroy_node(node_t *node, int numColors) {

    if(node == NULL)
        return;
    
    if(node->children[0] != NULL) {
        for(int i=0; i<numColors*4; i++)
            destroy_node(node->children[i], numColors);
    }
    
    free(node->children);
    free(node);


}

void destroy_root(root_t *root, int numColors) {

    if (root == NULL)
        return;

    destroy_node(root->init, numColors);
    free(root);

}


// ---------- OTHERS FUNCTIONS ----------
// Print the corner, weight and color of each child of a node
void printChildren(node_t *node) {

    int i = 0;
    node_t *child = node->children[i];
    while(child) {
        printf("Canto = %d | Peso = %d | Cor = %d\n", child->corner, child->weight, child->color);
        i++;
        child = node->children[i];
    }

}
