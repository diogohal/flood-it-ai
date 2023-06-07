#ifndef SMA_H
#define SMA_H
#include "struct.h"

typedef struct node {

    int weight;
    int color;
    int corner;
    struct node **children;
    struct node *next;

} node_t;

typedef struct root {

    int numColored;
    struct node *init;

} root_t;

// Create functions
node_t *create_node(int numColors);
root_t* create_root(int m, int n, int numColors);

// Search functions
node_t *expand_node(board_t *board, node_t *node, int m, int n, int numColors);
node_t *expand_node_corner(board_t *board, node_t *node, int m, int n, int numColors, int corner);
node_t *decision(node_t *node, int numColors, int numCorners);

// Printing functions
char printCorner(int corner);

// Destroy functions
void destroy_root(root_t *root, int numColors);

#endif