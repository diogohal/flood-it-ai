#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "struct.h"
#include "sma.h"

int calcula_maior(int *colors, int numColors) {
    int maior = 0;
    for(int i = 0; i < numColors; i++) {
        if(colors[i] > colors[maior])
            maior = i;
    }
    return maior;
}

int main() {

    // Creates important structures and variables
    int m, n, color, numColors, numMoves, numNonColored = 0;
    scanf("%d %d %d", &m, &n, &numColors);
    printf("%d %d %d\n", m, n, numColors);
    board_t *board = create_board(m, n, numColors);
    root_t *root = create_root(m, n, numColors);
    node_t* node = malloc(sizeof(node_t));


    int maior = 0;
    srand(time(NULL));

    while (!is_board_colored(board, m, n)) {
        // imprime as opções de cores coloridas   
        printf("Escolha uma cor:\n");
        for (int i = 0; i < numColors; i++) {
            print_slot(i);
            printf(" %d ", i); 
        }
        printf("\n\n");
        print_board(board, m, n);
        // scanf("%d", &color);
        // expand_node(board, node, m, n, numColors);
        // printChildren(node);
        // node = decision(node, numColors);
        calculate_weight3(board, board->slots[0][0] , 0, node);
        calculate_weight3(board, board->slots[0][0] , 1, node);
        calculate_weight3(board, board->slots[0][0] , 2, node);
        calculate_weight3(board, board->slots[0][0] , 3, node);
        calculate_weight3(board, board->slots[0][0] , 4, node);

        for (int i = 0; i < numColors; i++) {
            printf(" %d ", node->colors[i]); 
        }

        maior = calcula_maior(node->colors, numColors);
        printf("Maior = %d\n", maior);
        sleep(1);
        numMoves++;
        //color = 
    
        flood_fill(board, m, n, maior, node->corner);
        numNonColored = countNonColored(board, m, n);
        print_slot(node->color);
        printf("ESCOLHA = Cor: %d | Canto: %d | Peso: %d | Restante = %d\n", node->color, node->corner, node->weight, numNonColored);
    }
    print_board(board, m, n);
    printf("Parabéns, você completou o tabuleiro! Número de passos: %d\n", numMoves);

    destroy_root(root, numColors);
    destroy_board(board, m, n);
    return 0;

}
