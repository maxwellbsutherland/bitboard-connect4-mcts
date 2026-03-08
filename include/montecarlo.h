/**
 * montecarlo.h
 */

#pragma once

#include <board.h>

#include <math.h>

#define C 2
#define INF 1000000

typedef struct _node {
    struct _node *parent;
    struct _node *children[7];

    unsigned int n;
    double r;

    Board board;

    U8 moves[7];
    U8 move_count;
    U8 child_count;
    U8 move_from_parent;
} Node;

static inline double UCB1(const Node *n) {
    if (!n || n->n == 0) return INF;
    return (n->r / n->n) + (C * sqrt(log(n->parent->n) / n->n));
}

Node *create_node(const Node *parent, const Board *board, U8 move);
void free_node(Node *node);

void mcts_train(Node *root, int n);
Node *mcts_advance_root(Node *root, U8 move);
U8   mcts_best_move(const Node *root);
