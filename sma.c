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
    // printf("PESO = %d | CORNER = %d | COLOR = ", before - after, node->corner);
    // print_slot(node->color);
    // printf("\n");
    // print_board(board, m, n);
    // printf("\n");
    // print_board(board, m , n);

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            board->slots[i][j]->color = copy[i][j].color;
            board->slots[i][j]->colored = copy[i][j].colored;
        }

    // printf("\nDEBUG!! ANTES = %d | DEPOIS = %d | Saldo = %d\n", before, after, before-after);
    return before - after;

}

// Search for the node with the bigger area
int area_heuristic(board_t *board, int m, int n, int numColors, node_t *node) {

    int before, after = 0;

    // Board backup
    slot_t copy[m][n];
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            copy[i][j].color = board->slots[i][j]->color;
            copy[i][j].colored = board->slots[i][j]->colored;
        }
    
    // Weight calculation
    // PRECISA SETAR -1 PARA OS SLOTS DESSE CANTO PARA A CONTAGEM SER VÁLIDA
    before = countBiggerArea(board, m, n);
    flood_fill(board, m, n, node->color, node->corner);
    after = countBiggerArea(board, m, n);

    // printf("BEFORE = %d | AFTER = %d\n", before, after);

    printf("Cor: ");
    print_slot(node->color);
    printf("| Canto: %d | Peso: %d\n", node->corner, before-after);

    // Reset board
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            board->slots[i][j]->color = copy[i][j].color;
            board->slots[i][j]->colored = copy[i][j].colored;
        }

    return before - after;

}

// Expand the node for next search
node_t *expand_node(board_t *board, node_t *node, int m, int n, int numColors) {
    
    // printf("NÃO COLORIDOS = %d\n", countNonColored(board, m, n));
    for(int i=0; i<numColors; i++) {
        for(int j=0; j<4; j++) {
            node->children[i*4+j] = create_node(numColors);
            node->children[i*4+j]->color = i;
            node->children[i*4+j]->corner = j;
            // node->children[i*4+j]->weight = calculate_weight(node, numColors*4);
            node->children[i*4+j]->weight = calculate_weight2(board, m, n, numColors, node->children[i*4+j]);
            // node->children[i*4+j]->weight = area_heuristic(board, m, n, numColors, node->children[i*4+j]);
        }
    }

    // printf("MELHOR ESCOLHA = cannto = %d | cor = %d\n", node->corner, node->color);

    return node;

}

// Makes the decision of the tree path
node_t *decision(node_t *node, int numColors) {

    node_t *decision = node->children[0];
    for(int i=1; i<numColors*4; i++)
        if(node->children[i]->weight > decision->weight) {
            free(decision->children);
            free(decision);
            decision = node->children[i];
        }
        else {
            free(node->children[i]->children);
            free(node->children[i]);
        }
    
    return decision;

}


// ---------- DESTROY FUNCTIONS ----------
void destroy_node(node_t *node, int numColors) {

    if(!node)
        return;
    
    for(int i=0; i<4*numColors; i++) {
        if(node->children[i]) {
            destroy_node(node->children[i], numColors);
            printf("oii\n");
        }
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

void printNodes(root_t *root, int numColors) {

    node_t *node = root->init;

    while(node) {
        for(int i=0; i<numColors*4; i++) {
            if(node->children[i]) {
                print_slot(node->children[i]->color);
                node = node->children[i];
                break;
            }
            
        }
        printf("\n");
    }

}