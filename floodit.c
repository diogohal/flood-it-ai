#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    // Create important structures and variables
    srand(time(NULL));
    FILE *file = fopen("30x30_example.txt", "r");
    FILE *out = fopen("solution.txt", "w");
    int m = 0, n = 0, numColors = 0, numMoves = 0, corner = 0;
    
    // Testing
    m = rand() % 100 + 1;
    n = rand() % 100 + 1;
    numColors = rand() % 20 + 1;
    
    m = 100; n = 100; numColors = 20;
    
    printf("Instance: m = %d, n = %d, numColors = %d\n", m, n, numColors);


    clock_t start, end;

    // Create board instance and search tree
    // scanf("%d %d %d", &m, &n, &numColors);
    // fscanf(file, "%d %d %d", &m, &n, &numColors);
    board_t *board = create_board(m, n, numColors);
    // readBoard(board, file, m, n);
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
        // sleep(1);
        // printf("\n\n");
        // print_board(board, m, n);
    }
    rewind(out);
    fprintf(out, "%d", numMoves);

    // Close timer
    end = clock();

    // Print result
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d | %f segundos\n", numMoves, ((double)(end-start))/CLOCKS_PER_SEC);

    destroy_root(root, numColors);
    destroy_board(board, m, n);
    fclose(file);
    fclose(out);
    return 0;

}