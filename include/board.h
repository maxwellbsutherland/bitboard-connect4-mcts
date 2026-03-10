/**
 * board.h
 */

#pragma once

#include <types.h>

typedef struct {
    U64 red_bitboard;
    U64 yellow_bitboard;
    U8 color;
} Board;

static inline U64 get_occupied(const Board *board) {
    return board->red_bitboard | board->yellow_bitboard;
}

static inline void switch_color(Board *board) {
    board->color = (board->color == RED) ? YELLOW : RED;
}

int is_win(const Board *board);
int is_draw(const Board *board);

void print_board(const Board *board);
