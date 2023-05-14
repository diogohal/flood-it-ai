#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "sma.h"


// Esta parte está errada. A verifucação não funciona quando a pintura não é convexa
void startColored(board_t *board, int m, int n) {

    int color = board->slots[0][0]->color;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if(board->slots[i][j]->color != color)
                break;
            else
                board->slots[i][j]->colored = 0;
        }
    }

    color = board->slots[m-1][0]->color;
    for (int i=m-1; i>=0; i--) {
        for (int j=0; j<n; j++) {
            if(board->slots[i][j]->color != color)
                break;
            else
                board->slots[i][j]->colored = 1;
        }
    }

    color = board->slots[m-1][n-1]->color;
    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            if(board->slots[i][j]->color != color)
                break;
            else
                board->slots[i][j]->colored = 2;
        }
    }

    color = board->slots[0][n-1]->color;
    for (int i=0; i<m; i++) {
        for (int j=n-1; j>=0; j--) {
            if(board->slots[i][j]->color != color)
                break;
            else
                board->slots[i][j]->colored = 3;
        }
    }
}

// ---------- CREATE FUNCTIONS ----------
board_t* create_board(int m, int n, int numColors) {
    // aloca memória para a estrutura board
    board_t *board = (board_t*) malloc(sizeof(board_t));
    board->numColors = numColors;

    // aloca memória para a matriz de slots
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

    // Define colored values for the corners
    // startColored(board, m, n);
    
    return board;
}


// ---------- COLORING FUNCTIONS ----------
void flood_fill_aux(slot_t *slot, int oldColor, int color) {
    // preenche o tabuleiro com a cor color
    if (slot->color == oldColor) {
        slot->color = color;
        slot->colored = 1;
        if (slot->left != NULL) flood_fill_aux(slot->left, oldColor, color);
        if (slot->right != NULL) flood_fill_aux(slot->right, oldColor, color);
        if (slot->up != NULL) flood_fill_aux(slot->up, oldColor, color);
        if (slot->down != NULL) flood_fill_aux(slot->down, oldColor, color);
    }
}

int is_board_colored(board_t *board, int m, int n) {
    // verifica se o tabuleiro está colorido
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

    if(corner == 0) {
        x = 0;
        y = 0;
    }
    if(corner == 1) {
        x = m-1;
        y = 0;
    }
    if(corner == 2) {
        x = m-1;
        y = n-1;
    }
    if(corner == 3) {
        x = 0;
        y = n-1;
    }

    oldColor = board->slots[x][y]->color;
    if (color == oldColor) return;
    flood_fill_aux(board->slots[x][y], oldColor, color);

}

// ---------- HEURISTIC FUNCTIONS ----------
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

// ---------- PRINTING FUNCTIONS ----------
void print_slot(int color) {
    
    if(color == 0)
        printf("\033[41m  \033[0m");
    else if(color == 1)
        printf("\033[42m  \033[0m");
    else if(color == 2)
        printf("\033[43m  \033[0m");
    else if(color == 3)
        printf("\033[44m  \033[0m");
    else if(color == 4)
        printf("\033[45m  \033[0m");
    else if(color == 5)
        printf("\033[46m  \033[0m");
    else if(color == 6)
        printf("\033[47m  \033[0m");
    else if(color == 7)
        printf("\033[101m  \033[0m");
    else if(color == 8)
        printf("\033[102m  \033[0m");
    else if(color == 9)
        printf("\033[103m  \033[0m");

}

void print_board(board_t *board, int m, int n) {

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) 
            print_slot(board->slots[i][j]->color);
        printf("\n");
    }

}


// ---------- DESTROY FUNCTIONS ----------
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

