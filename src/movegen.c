#include <movegen.h>
#include <bitboard.h>

#include <string.h>

static inline void add_move(U8 moves[], U8 *count, U8 move) {
    if (moves) moves[(*count)] = move;
    (*count)++;
}

int gen_moves(const Board *board, U8 moves[], U8 *count) {
    if (!board || !count) return -1;

    (*count) = 0;
    U64 occupied = get_occupied(board);

    if (!GET_BIT(occupied, INDEX(0, 6))) add_move(moves, count, 0);
    if (!GET_BIT(occupied, INDEX(1, 6))) add_move(moves, count, 1);
    if (!GET_BIT(occupied, INDEX(2, 6))) add_move(moves, count, 2);
    if (!GET_BIT(occupied, INDEX(3, 6))) add_move(moves, count, 3);
    if (!GET_BIT(occupied, INDEX(4, 6))) add_move(moves, count, 4);
    if (!GET_BIT(occupied, INDEX(5, 6))) add_move(moves, count, 5);
    if (!GET_BIT(occupied, INDEX(6, 6))) add_move(moves, count, 6);

    return 0;
}
