#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>

int main() {

    int m, n, numColors;
    scanf("%d %d %d", &m, &n, &numColors);
    printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);
    print_board(board, m, n);
    destroy_board(board, m, n);
    return 0;

}