#ifndef SMA_H
#define SMA_H

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

int calculate_weight(node_t *node, int numChildren);
node_t *create_node();
root_t* create_root(board_t *board, int m, int n);

#endif