#include <board.h>
#include <bitboard.h>
#include <movegen.h>
#include <types.h>
#include <move.h>
#include <montecarlo.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    Board board = {
        .color = RED,
        .red_bitboard = 0ULL,
        .yellow_bitboard = 0ULL
    };

    Node *root = create_node(NULL, &board, 255);
    if (!root) return 1;

    for (;;) {
        U8 move = 255;

        if (board.color == RED) {
            unsigned int input = 0;

            U8 count;
            gen_moves(&board, NULL, &count);

            do {
                printf("Move [1-7] > ");
                if (scanf("%u", &input) != 1) {
                    free_node(root);
                    return 1;
                }

                if (input >= 1 && input <= 7)
                    move = (U8)(input - 1);
                else
                    move = 255;

            } while (move == 255 || !is_legal(&board, move));
        } else {
            mcts_train(root, 10000);

            move = mcts_best_move(root);
            if (move == 255)
                break;
        }

        make_move(&board, move);
        print_board(&board);

        if (is_win(&board))
            break;

        root = mcts_advance_root(root, move);
        if (!root)
            break;

        switch_color(&board);
    }

    free_node(root);
    return 0;
}