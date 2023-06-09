#ifndef CANDY_H
#define CANDY_H

typedef struct slot {

    int color;
    struct slot *left;
    struct slot *right;
    struct slot *up;
    struct slot *down;    

} slot_t;


typedef struct board {

    int numColors;
    slot_t ***slots;

} board_t;

board_t* create_board(int m, int n, int numColors);
void print_board(board_t *board, int m, int n);
void destroy_board(board_t *board, int m, int n);

#endif