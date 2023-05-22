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
node_t *create_node(int numColors);
root_t* create_root(int m, int n, int numColors);
node_t *expand_node(board_t *board, node_t *node, int m, int n, int numColors);
node_t *decision(node_t *node, int numColors);
void printChildren(node_t *node);
void destroy_root(root_t *root, int numColors);
void printNodes(root_t *root, int numColors);

#endif