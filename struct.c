#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>

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
            board->slots[i][j]->left = NULL;
            board->slots[i][j]->right = NULL;
            board->slots[i][j]->up = NULL;
            board->slots[i][j]->down = NULL;
        }
    }

    // define os ponteiros left, right, up e down
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

void print_slot(slot_t *slot) {
    
    if(slot->color == 0)
        printf("\033[41m  \033[0m");
    else if(slot->color == 1)
        printf("\033[42m  \033[0m");
    else if(slot->color == 2)
        printf("\033[43m  \033[0m");
    else if(slot->color == 3)
        printf("\033[44m  \033[0m");
    else if(slot->color == 4)
        printf("\033[45m  \033[0m");
    else if(slot->color == 5)
        printf("\033[46m  \033[0m");
    else if(slot->color == 6)
        printf("\033[47m  \033[0m");
    else if(slot->color == 7)
        printf("\033[101m  \033[0m");
    else if(slot->color == 8)
        printf("\033[102m  \033[0m");
    else if(slot->color == 9)
        printf("\033[103m  \033[0m");

}

void print_board(board_t *board, int m, int n) {

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            print_slot(board->slots[i][j]);
        printf("\n");
    }

}

void destroy_board(board_t *board, int m, int n) {
    // libera a memória alocada para os slots
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(board->slots[i][j]);
        }
        free(board->slots[i]);
    }
    free(board->slots);

    // libera a memória alocada para a estrutura board
    free(board);
}