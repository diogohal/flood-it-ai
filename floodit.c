#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int main() {

    // Creates important structures and variables
    int m, n, color, numColors, numMoves, numNonColored = 0;
    scanf("%d %d %d", &m, &n, &numColors);
    // printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);
    int teste = countNonColored(board, m, n);
    // printf("%d\n\n", teste);
    // printf("%d\n", board->slots[m-2][0]->colored);
    // print_board(board, m, n);
    root_t *root = create_root(m, n, numColors);
    node_t *node = root->init;
    srand(time(NULL));

    while (!is_board_colored(board, m, n)) {
        // imprime as opções de cores coloridas   
        // printf("Escolha uma cor:\n");
        // for (int i = 0; i < numColors; i++) {
        //     print_slot(i);
        //     printf(" %d ", i); 
        // }
        // printf("\n\n");
        // print_board(board, m, n);
        // scanf("%d", &color);
        expand_node(board, node, m, n, numColors);
        // printChildren(node);
        node = decision(node, numColors);
        // color = calculate_weight(node, numColors);
        // sleep(1);
        numMoves++;
        //color = HEURISTICA
        flood_fill(board, m, n, node->color, node->corner);
        numNonColored = countNonColored(board, m, n);
        // print_slot(node->color);
        // printf("ESCOLHA = Cor: %d | Canto: %d | Peso: %d | Restante = %d\n", node->color, node->corner, node->weight, numNonColored);
    }
    // print_board(board, m, n);
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d\n", numMoves);

    destroy_root(root, numColors);
    destroy_board(board, m, n);
    return 0;

}