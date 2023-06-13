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

// Create functions
board_t* create_board(int m, int n, int numColors);
void readBoard(board_t *board, int m, int n);

// Control functions
void flood_fill(board_t *board, int m, int n, int color, int corner);
void flood_fill_aux_start(slot_t *slot, int oldColor, int color);
int is_board_colored(board_t *board, int m, int n);
void setToNonColored(board_t *board, int m, int n);

// Heuristic Aux Functions
int countNonColored(board_t *board, int m, int n);
int countUnaccessedAreas(board_t *board, int m, int n);

// Printing functions
void print_slot(int color);
void print_board(board_t *board, int m, int n);
void print_board_num(board_t *board, int m, int n);

// Destroy functinos
void destroy_board(board_t *board, int m, int n);

#endif