#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    // Creates important structures and variables
    int m, n, color, numColors, numMoves = 0;
    scanf("%d %d %d", &m, &n, &numColors);
    printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);
    node_t *test = create_node();
    root_t *root = create_root(board, m, n);


    while (!is_board_colored(board, m, n)) {
        // imprime as opções de cores coloridas   
        // printf("Escolha uma cor:\n");
        // for (int i = 0; i < numColors; i++) {
        //     print_slot(i);
        //     printf(" %d ", i); 
        // }
        printf("\n\n");
        print_board(board, m, n);
        // scanf("%d", &color);
        color = calculate_weight(test, numColors);
        sleep(1);
        numMoves++;
        //color = HEURISTICA
        flood_fill(board, m, n, color);
    }
    printf("Parabéns, você completou o tabuleiro!\n");
    destroy_board(board, m, n);
    return 0;

}