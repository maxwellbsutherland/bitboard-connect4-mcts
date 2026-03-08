/**
 * move.h
 */

#pragma once

#include <types.h>
#include <board.h>

int is_legal(const Board *board, U8 move);
void make_move(Board *board, U8 move);
