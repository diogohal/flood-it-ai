#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    
    if(new_node->children == NULL)
        printf("É NULL!!!!\n");

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

// Expand the node for next search
node_t *expand_node(node_t *node, int numColors) {

    for(int i=0; i<numColors; i++) {
        for(int j=0; j<4; j++) {
            node->children[i*4+j] = create_node(numColors);
            node->children[i*4+j]->color = i;
            node->children[i*4+j]->corner = j;
            node->children[i*4+j]->weight = calculate_weight(node, numColors);
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