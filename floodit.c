#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    // Create important structures and variables
    srand(time(NULL));
    FILE *out = fopen("solution.txt", "w");
    int m = 0, n = 0, numColors = 0, numMoves = 0, corner = 0;
    clock_t start, end;
    

    // Create board instance and search tree
    scanf("%d %d %d", &n, &m, &numColors);
    board_t *board = create_board(m, n, numColors);
    readBoard(board, m, n);
    root_t *root = create_root(m, n, numColors);
    node_t *node = root->init;
    fprintf (out, "         \n");

    // Start timer
    start = clock();

    // First execution without setting the corner
    expand_node(board, node, m, n, numColors);
    node = decision(node, numColors, 4);
    flood_fill(board, m, n, node->color, node->corner);
    corner = node->corner;
    numMoves++;
    fprintf(out, "%c ", printCorner(node->corner));
    fprintf(out, "%d ", node->color+1);

    // The next executions has the corner fixed
    while (!is_board_colored(board, m, n)) {
        expand_node_corner(board, node, m, n, numColors, corner);
        node = decision(node, numColors, 1);
        flood_fill(board, m, n, node->color, node->corner);
        numMoves++;
        fprintf(out, "%c ", printCorner(node->corner));
        fprintf(out, "%d ", node->color+1);
    }
    rewind(out);
    fprintf(out, "%d", numMoves);

    // Close timer
    end = clock();

    // Print result
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d | %f segundos\n", numMoves, ((double)(end-start))/CLOCKS_PER_SEC);

    destroy_root(root, numColors);
    destroy_board(board, m, n);
    fclose(out);
    return 0;

}