#include <move.h>
#include <bitboard.h>
#include <movegen.h>

int is_legal(const Board *board, U8 move) {
    if (!board) return 1;

    U8 count;
    U8 moves[7];
    gen_moves(board, moves, &count);
    for (U8 i = 0; i < count; i++) {
        if (moves[i] == move)
            return 1;
    }

    return 0;
}

void make_move(Board *board, U8 move) {
    U64 occupied = get_occupied(board);

    U8 y = 1; 
    while (GET_BIT(occupied, INDEX(move, y))) {
        y++;
    }

    U64 *bb = (board->color == RED) 
        ? &board->red_bitboard 
        : &board->yellow_bitboard;
    
    U8 sq = INDEX(move, y);
    SET_BIT(*bb, sq);
}
