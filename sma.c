#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sma.h"
#include "struct.h"

// Creates a root structure
root_t* create_root(board_t *board, int m, int n) {

    root_t *new_root = malloc(sizeof(root_t));
    if(!new_root)
        return NULL;

    new_root->init = NULL;
    new_root->numColored = 0;

    return new_root;

}

// Creates a node structure
node_t *create_node() {

    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;
    
    new_node->weight = 0;
    new_node->color = 0;
    new_node->children = NULL;

    return new_node;

}

// Calculates the weight of each choice based in heuristic
int calculate_weight(node_t *node, int numChildren) {

    srand(time(NULL));
    return rand() % numChildren;

}

// Expand the node for next search
node_t *expand_node(node_t *node, int numChildren) {

    for(int i=0; i<numChildren; i++) {
        for(int j=0; j<4; j++) {
            node->children[i] = create_node();
            node->children[i]->color = i;
            node->children[i]->weight = calculate_weight(node, numChildren);
            node->children[i]->corner = j;
        }
    }

}

// Makes the decision of the tree path
node_t *decision(node_t *node, int numChildren) {

    node_t *decision = node->children[0];
    for(int i=1; i< numChildren; i++)
        if(node->children[i]->weight > decision->weight)
            decision = node->children[i];
    
    return decision;

}