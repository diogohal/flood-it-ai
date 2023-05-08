#ifndef SMA_H
#define SMA_H

typedef struct node {

    int weight;
    int color;
    int *colors;
    struct node **children;

} node_t;

typedef struct root {

    slot_t *slots[4];
    struct node *father;

} root_t;

#endif