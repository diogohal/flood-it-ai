#ifndef SMA_H
#define SMA_H

#include "struct.h"

typedef struct node {

    int weight;
    int color;
    int corner;
    struct node **children;

} node_t;

typedef struct root {

    int numColored;
    struct node *init;

} root_t;

int calculate_weight(node_t *node, int numColors);
node_t *create_node();
root_t* create_root(board_t *board, int m, int n);
node_t *expand_node(node_t *node, int numColors);
node_t *decision(node_t *node, int numColors);

#endif