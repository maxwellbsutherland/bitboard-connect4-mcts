#include <board.h>
#include <bitboard.h>
#include <movegen.h>

#include <stdio.h>
#include <stdlib.h>

int is_win(const Board *board) {
    U64 bb = (board->color == RED)
        ? board->red_bitboard
        : board->yellow_bitboard;
    U64 m;

    m = bb & (bb >> 1);
    if (m & (m >> 2)) return 1;

    m = bb & (bb >> 8);
    if (m & (m >> 16)) return 1;

    m = bb & (bb >> 7);
    if (m & (m >> 14)) return 1;

    m = bb & (bb >> 9);
    if (m & (m >> 18)) return 1;

    return 0;
}

int is_draw(const Board *board) {
    U8 count;
    gen_moves(board, NULL, &count);
    return (count == 0);
}

void print_board(const Board *board) {
    U64 occupied = get_occupied(board);

    for (int y = 6; y > 0; --y) {
        for (int x = 0; x < 7; ++x) {
            U8 sq = INDEX(x, y);

            char c = '.';
            if (GET_BIT(occupied, sq))
                c = GET_BIT(board->red_bitboard, sq) ? 'X' : 'O';

            printf("%c ", c);
        }
        printf("\n");
    }

    printf("1 2 3 4 5 6 7\n");
}