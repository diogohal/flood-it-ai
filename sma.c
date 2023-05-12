#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sma.h"
#include "struct.h"

// Creates a node structure
node_t *create_node(int numColors) {

    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;
    
    new_node->weight = 0;
    new_node->color = 0;
    new_node->children = malloc(sizeof(node_t)*4*numColors);

    return new_node;

}

// Creates a root structure
root_t* create_root(board_t *board, int m, int n) {

    root_t *new_root = malloc(sizeof(root_t));
    if(!new_root)
        return NULL;

    new_root->init = create_node(board->numColors);
    new_root->numColored = 0;

    return new_root;

}

// Calculates the weight of each choice based in heuristic
int calculate_weight(node_t *node, int numChildren) {

    return rand() % 100;

}

// Expand the node for next search
node_t *expand_node(node_t *node, int numColors) {

    for(int i=0; i<numColors; i++) {
        for(int j=0; j<4; j++) {
            node->children[i] = create_node(numColors);
            node->children[i]->color = i;
            node->children[i]->corner = j;
            node->children[i]->weight = calculate_weight(node, numColors);
        }
    }

    return node;

}

// Makes the decision of the tree path
node_t *decision(node_t *node, int numColors) {

    node_t *decision = node->children[0];
    for(int i=1; i< numColors; i++)
        if(node->children[i]->weight > decision->weight)
            decision = node->children[i];
    
    return decision;

}