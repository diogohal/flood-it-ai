#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "sma.h"

// ---------- CREATE FUNCTIONS ----------
// Create a board structure
board_t* create_board(int m, int n, int numColors) {
    board_t *board = (board_t*) malloc(sizeof(board_t));
    board->numColors = numColors;

    // Allocate memory for the slots matrix
    board->slots = (slot_t***) malloc(m * sizeof(slot_t**));
    for (int i = 0; i < m; i++) {
        board->slots[i] = (slot_t**) malloc(n * sizeof(slot_t*));
        for (int j = 0; j < n; j++) {
            board->slots[i][j] = (slot_t*) malloc(sizeof(slot_t));
            board->slots[i][j]->color = rand() % numColors;
            board->slots[i][j]->colored = -1;
            board->slots[i][j]->left = NULL;
            board->slots[i][j]->right = NULL;
            board->slots[i][j]->up = NULL;
            board->slots[i][j]->down = NULL;
        }
    }

    // Define left, right, up and down pointers
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) board->slots[i][j]->left = board->slots[i][j-1];
            if (j < n-1) board->slots[i][j]->right = board->slots[i][j+1];
            if (i > 0) board->slots[i][j]->up = board->slots[i-1][j];
            if (i < m-1) board->slots[i][j]->down = board->slots[i+1][j];
        }
    }
    
    return board;
}

// Read an existing board
void readBoard(board_t *board, int m, int n) {

    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++) {
            scanf("%d", &board->slots[i][j]->color);
            board->slots[i][j]->color--;
        }


}


// ---------- CONTROL FUNCTIONS ----------
// Set every slot to non colored
void setToNonColored(board_t *board, int m, int n) {
    for(int i=0; i<m; i++) 
        for(int j=0; j<n; j++)
            board->slots[i][j]->colored = -1;    
}

// Set all paiting area from a corner to colored
void flood_fill_aux_start(slot_t *slot, int oldColor, int color) {
    if (slot->color == oldColor) {
        slot->colored = 1;
        if (slot->left != NULL && slot->left->colored == -1) flood_fill_aux_start(slot->left, oldColor, color);
        if (slot->right != NULL && slot->right->colored == -1) flood_fill_aux_start(slot->right, oldColor, color);
        if (slot->up != NULL && slot->up->colored == -1) flood_fill_aux_start(slot->up, oldColor, color);
        if (slot->down != NULL && slot->down->colored == -1) flood_fill_aux_start(slot->down, oldColor, color);
    }
}

// Set all paiting area from a corner to the new color
void flood_fill_aux(slot_t *slot, int oldColor, int color) {
    if (slot->color == oldColor) {
        slot->color = color;
        if (slot->left != NULL) flood_fill_aux(slot->left, oldColor, color);
        if (slot->right != NULL) flood_fill_aux(slot->right, oldColor, color);
        if (slot->up != NULL) flood_fill_aux(slot->up, oldColor, color);
        if (slot->down != NULL) flood_fill_aux(slot->down, oldColor, color);
    }
}

// Verify if the game is complete
int is_board_colored(board_t *board, int m, int n) {

    int color = board->slots[0][0]->color;
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++)
            if (board->slots[i][j]->color != color)
                return 0;
    return 1;

}

// Fill the board with the decision obtained in tree search
void flood_fill(board_t *board, int m, int n, int color, int corner) {
    
    int oldColor, x, y = 0;

    // Set the start corner
    if(corner == 0) {
        x = 0;
        y = 0;
    }
    else if(corner == 1) {
        x = m-1;
        y = 0;
    }
    else if(corner == 2) {
        x = m-1;
        y = n-1;
    }
    else if(corner == 3) {
        x = 0;
        y = n-1;
    }
    
    // If the new color is the same, doesn't change anything
    oldColor = board->slots[x][y]->color;
    if(color == oldColor)
        return;

    // Fill the paiting area with the new color and set the new area colored
    flood_fill_aux(board->slots[x][y], oldColor, color);
    setToNonColored(board, m, n);
    flood_fill_aux_start(board->slots[x][y], board->slots[x][y]->color, oldColor);

}


// ---------- HEURISTIC AUX FUNCTIONS ----------
// Check if there are colored slots around
int verifyNeighboor(slot_t *slot) {

    int response = 0;

    if((slot->down && slot->down->colored == 1) ||
    (slot->left && slot->left->colored == 1) ||
    (slot->right && slot->right->colored == 1) ||
    (slot->up && slot->up->colored == 1))
        response = 1;
    
    return response;

}

// Count non colored slots
int countNonColored(board_t *board, int m, int n) {

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(board->slots[i][j]->colored == -1)
                count++;
        }
    }

    return count;

}

// Count unaccessed slots
int countUnaccessedAreas(board_t *board, int m, int n) {

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(board->slots[i][j]->colored == -1 && !verifyNeighboor(board->slots[i][j]))
                count++;
        }
    }

    return count;

}


// ---------- PRINTING FUNCTIONS ----------
// Print the slot with as a color
void print_slot(int color) {
    
    printf("\033[48;5;%dm  \033[0m", color);
    return;

}

// Print all board with slots as a color
void print_board(board_t *board, int m, int n) {

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) 
            // printf("%2d", board->slots[i][j]->colored);
            print_slot(board->slots[i][j]->color);
        printf("\n");
    }

}

// Print all board with slots as a number
void print_board_num(board_t *board, int m, int n) {

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) 
            printf("%2d ", board->slots[i][j]->color);
        printf("\n");
    }

}


// ---------- DESTROY FUNCTIONS ----------
// Destroy the board and it's slots
void destroy_board(board_t *board, int m, int n) {

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(board->slots[i][j]);
        }
        free(board->slots[i]);
    }
    free(board->slots);
    free(board);

}