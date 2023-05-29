#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    srand(time(NULL));
    // Creates important structures and variables
    FILE *file = fopen("30x30_example.txt", "r");
    FILE *out = fopen("solution.txt", "w");
    int m, n, numColors, numMoves, color = 0;
    clock_t start, end;
    scanf("%d %d %d", &m, &n, &numColors);
    // fscanf(file, "%d %d %d", &m, &n, &numColors);
    board_t *board = create_board(m, n, numColors);
    // readBoard(board, file, m, n);
    root_t *root = create_root(m, n, numColors);
    node_t *node = root->init;
    start = clock();
    fprintf (out, "         \n");
    numMoves = 0;
    // print_board(board, m, n);
    while (!is_board_colored(board, m, n)) {
        expand_node(board, node, m, n, numColors);
        node = decision(node, numColors);
        fprintf(out, "%c ", printCorner(node->corner));
        fprintf(out, "%d ", node->color+1);
        numMoves++;
        flood_fill(board, m, n, node->color, node->corner);
        // sleep(1);
        printf("\n\n");
        print_board(board, m, n);
        // printf("COLOR = %d", node->color);
        // print_slot(node->color);
        // printf("| CORNER = %c\n", printCorner(node->corner));
    }
    rewind(out);
    fprintf(out, "%d", numMoves);

    end = clock();
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d | %f segundos\n", numMoves, ((double)(end-start))/CLOCKS_PER_SEC);

    destroy_root(root, numColors);
    destroy_board(board, m, n);
    fclose(file);
    fclose(out);
    return 0;

}