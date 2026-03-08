/**
 * bitboard.h
 */

#pragma once

#include <types.h>

#define BB(sq) (1ULL << (U64)(sq))

#define SET_BIT(bb, sq) ((bb) |= BB(sq))
#define GET_BIT(bb, sq) (((bb) >> (U64)(sq)) & 1ULL)
#define POP_BIT(bb, sq) ((bb) &= ~BB(sq))

#define INDEX(x, y) ((U8)((U8)(y) * 8u + (U8)(x)))
#define ROW(sq)     ((U8)((sq) / 8u))
#define COL(sq)     ((U8)((sq) % 8u))
