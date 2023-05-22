#ifndef CANDY_H
#define CANDY_H

typedef struct slot {

    int color;
    int colored;
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
void print_slot(int color);
void destroy_board(board_t *board, int m, int n);
void flood_fill(board_t *board, int m, int n, int color, int corner);
void flood_fill_aux_start(slot_t *slot, int oldColor, int color);
int countNonColored(board_t *board, int m, int n);
int countBiggerArea(board_t *board, int m, int n);
int is_board_colored(board_t *board, int m, int n);
void readBoard(board_t *board, FILE *file, int m, int n);
void print_board_num(board_t *board, int m, int n);
int remainingColor(board_t *board, int m, int n);

#endif