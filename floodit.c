#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "sma.h"
#include <time.h>

int main() {

    int m, n, numColors, numMoves = 0;
    scanf("%d %d %d", &m, &n, &numColors);
    printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);


    while (!is_board_colored(board, m, n)) {
        // int color;
        // //imprime as opções de cores coloridas   
        // printf("Escolha uma cor:\n");
        // for (int i = 0; i < numColors; i++) {
        //     print_slot(i);
        //     printf(" %d ", i); 
        // }
        printf("\n\n");
        print_board(board, m, n);
        // scanf("%d", &color);
        numMoves++;
        //color = HEURISTICA
        flood_fill(board, m, n, color);
    }
    destroy_board(board, m, n);
    return 0;

}