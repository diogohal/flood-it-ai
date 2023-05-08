#include "sma.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

root_t* create_root(board_t *board, int m, int n) {

    root_t *new_root = malloc(sizeof(root_t));
    if(!new_root)
        return NULL;

    new_root->slots[0] = board->slots[0][0];
    new_root->slots[1] = board->slots[0][n-1];
    new_root->slots[2] = board->slots[m-1][0];
    new_root->slots[3] = board->slots[m-1][n-1];
    
    new_root->father = NULL;
    return new_root;

}

node_t *create_node(int numChildren, root_t *root) {

    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;
    
    new_node->weight = 0;
    new_node->color = 0;
    new_node->children = NULL;

    return new_node;

}