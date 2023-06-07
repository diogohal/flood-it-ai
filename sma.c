#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "sma.h"


// ---------- CREATE FUNCTIONS ----------
// Create a node of the search tree
node_t *create_node(int numColors) {

    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;

    new_node->weight = 0;
    new_node->corner = 0;
    new_node->color = 0;
    new_node->next = NULL;
    new_node->children = malloc(sizeof(node_t*)*4*numColors);
    for(int i=0; i<numColors*4; i++)
        new_node->children[i] = NULL;

    return new_node;

}

// Create the root of the search tree
root_t* create_root(int m, int n, int numColors) {

    root_t *new_root = malloc(sizeof(root_t));
    if(!new_root)
        return NULL;

    new_root->init = create_node(numColors);
    new_root->numColored = 0;

    return new_root;

}


// ---------- SEARCH FUNCTIONS ----------
// Calculates the weight based in how much new slots will be colored
int colored_heuristic(board_t *board, int m, int n, int numColors, node_t *node) {

    // Board backup 
    slot_t copy[m][n];
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            copy[i][j].color = board->slots[i][j]->color;
            copy[i][j].colored = board->slots[i][j]->colored;
        }
    
    // Count non colored slots before and after the node move
    int before = countNonColored(board, m, n);
    flood_fill(board, m, n, node->color, node->corner);
    int after = countNonColored(board, m, n);

    // Reset board
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            board->slots[i][j]->color = copy[i][j].color;
            board->slots[i][j]->colored = copy[i][j].colored;
        }

    return before - after;

}

// Calculate the weight based in how much new slots will be accessible (colored regions with it's border)
int area_heuristic(board_t *board, int m, int n, int numColors, node_t *node) {

    int before, after, x, y = 0;

    // Board backup
    slot_t copy[m][n];
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            copy[i][j].color = board->slots[i][j]->color;
            copy[i][j].colored = board->slots[i][j]->colored;
        }

    // Set the coordinates of the corner
    if(node->corner == 0) {
        x = 0;
        y = 0;
    }
    else if(node->corner == 1) {
        x = m-1;
        y = 0;
    }
    else if(node->corner == 2) {
        x = m-1;
        y = n-1;
    }
    else if(node->corner == 3) {
        x = 0;
        y = n-1;
    }        

    // Count non access areas before and after the node move
    setToNonColored(board, m, n);
    flood_fill_aux_start(board->slots[x][y], board->slots[x][y]->color, board->slots[x][y]->color);
    before = countUnaccessedAreas(board, m, n);
    flood_fill(board, m, n, node->color, node->corner);
    after = countUnaccessedAreas(board, m, n);
    
    // Reset board
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) {
            board->slots[i][j]->color = copy[i][j].color;
            board->slots[i][j]->colored = copy[i][j].colored;
        }

    return before - after;

}

// Expand the search tree from a node with a specified corner
node_t *expand_node_corner(board_t *board, node_t *node, int m, int n, int numColors, int corner) {

    int max = 0;
    for(int i=0; i<numColors; i++) {
        node->children[i] = create_node(numColors);
        node->children[i]->color = i;
        node->children[i]->corner = corner;
        // Use area heuristic (main) if there are a lot of unaccessed
        if(countUnaccessedAreas(board, m, n) > 10)
            node->children[i]->weight = area_heuristic(board, m, n, numColors, node->children[i]);
        // Use colored heuristic (main) if there are a lot of unaccessed
        else
            node->children[i]->weight = colored_heuristic(board, m, n, numColors, node->children[i]);

        if(node->children[i]->weight > max)
            max = node->children[i]->weight;
    }

    // if(max == 0) {
    //     for(int i=0; i<numColors; i++) {
    //         node->children[i]->weight = colored_heuristic(board, m, n, numColors, node->children[i]);        }
    // }

    return node;

}

// Expand the search tree from a node with not specified corner
node_t *expand_node(board_t *board, node_t *node, int m, int n, int numColors) {
    
    int max = 0;
    // Area heuristic (main)
    for(int i=0; i<numColors; i++) {
        for(int j=0; j<4; j++) {
            node->children[i*4+j] = create_node(numColors);
            node->children[i*4+j]->color = i;
            node->children[i*4+j]->corner = j;
            node->children[i*4+j]->weight = area_heuristic(board, m, n, numColors, node->children[i*4+j]);
            if(node->children[i*4+j]->weight > max)
                max = node->children[i*4+j]->weight;
        }
    }

    // If all slots are accessed, use non colored heuristic
    if(max == 0) {
        for(int i=0; i<numColors; i++) {
            for(int j=0; j<4; j++)
                node->children[i*4+j]->weight = colored_heuristic(board, m, n, numColors, node->children[i*4+j]);
        }
    }

    return node;

}

// Choose the node with greater weight. Free the other nodes. 
node_t *decision(node_t *node, int numColors, int numCorners) {

    node_t *decision = node->children[0];
    node->next = decision;
    for(int i=1; i<numColors*numCorners; i++)
        if(node->children[i]->weight > decision->weight) {
            free(decision->children);
            free(decision);
            decision = node->children[i];
            node->next = decision;
        }
        else {
            free(node->children[i]->children);
            free(node->children[i]);
        }
    
    return decision;

}


// ---------- DESTROY FUNCTIONS ----------
// Destroy all remaining nodes
void destroy_node(node_t *node, int numColors) {

    if(!node)
        return;
    
    destroy_node(node->next, numColors);
    free(node->children);
    free(node);

}

// Destroy the root and all the remaining nodes
void destroy_root(root_t *root, int numColors) {

    if (root == NULL)
        return;

    destroy_node(root->init, numColors);
    free(root);

}


// ---------- PRINTING FUNCTIONS ----------
// Print the letter of a giving number corner
char printCorner(int corner) {

    if(corner == 0)
        return 'a';
    else if(corner == 1)
        return 'b';
    else if(corner == 2)
        return 'c';
    else
        return 'd';
}