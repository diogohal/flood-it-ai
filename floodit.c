#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    FILE *file = fopen("30x30_example.txt", "r");

    // Creates important structures and variables
    int m, n, numColors, numMoves, color = 0;
    scanf("%d %d %d", &m, &n, &numColors);
    // fscanf(file, "%d %d %d", &m, &n, &numColors);
    printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);
    // readBoard(board, file, m, n);
    // printf("%d\n\n", teste);
    // printf("%d\n", board->slots[m-2][0]->colored);
    // print_board(board, m, n);
    root_t *root = create_root(m, n, numColors);
    node_t *node = root->init;
    srand(time(NULL));
    clock_t start, end;
    start = clock();
    numMoves = 0;

    while (!is_board_colored(board, m, n)) {
        expand_node(board, node, m, n, numColors);
        node = decision(node, numColors);
        numMoves++;
        // if(node->weight == 0) {
        //     color = remainingColor(board, m, n);
        //     flood_fill(board, m, n, color, 0);
        //     continue;
        // }
        flood_fill(board, m, n, node->color, node->corner);
        sleep(1);
        printf("\n\n");
        print_board(board, m, n);
        // printf("\e[1;1H\e[2J");        
    }

    end = clock();
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d | %f segundos\n", numMoves, ((double)(end-start))/CLOCKS_PER_SEC);
    destroy_root(root, numColors);
    destroy_board(board, m, n);
    fclose(file);
    return 0;

}