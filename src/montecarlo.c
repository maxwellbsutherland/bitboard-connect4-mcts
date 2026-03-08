#include <montecarlo.h>
#include <movegen.h>
#include <move.h>

#include <stdlib.h>

Node *create_node(const Node *parent, const Board *board, U8 move) {
    Node *node = calloc(1, sizeof(*node));
    if (!node) return NULL;

    node->board = *board;
    node->parent = (Node *)parent;
    node->move_from_parent = move;
    node->n = 0;
    node->r = 0.0;
    node->child_count = 0;

    gen_moves(&node->board, node->moves, &node->move_count);

    for (U8 i = 0; i < 7; i++)
        node->children[i] = NULL;

    return node;
}

void free_node(Node *node) {
    if (!node) return;

    for (U8 i = 0; i < node->child_count; i++)
        free_node(node->children[i]);

    free(node);
}

static inline Node *get_highest_UCB1(Node *node) {
    U8 best = 0;

    for (U8 i = 1; i < node->child_count; i++) {
        if (UCB1(node->children[i]) > UCB1(node->children[best])) {
            best = i;
        }
    }

    return node->children[best];
}

static inline int is_terminal_node(const Node *node) {
    if (!node) return 1;
    if (is_win(&node->board)) return 1;
    if (node->move_count == 0) return 1;
    return 0;
}

static Node *select(Node *node) {
    if (!node) return NULL;

    if (is_terminal_node(node))
        return node;

    if (node->child_count < node->move_count)
        return node;

    return select(get_highest_UCB1(node));
}

static Node *expand(Node *node) {
    if (!node) return NULL;
    if (is_terminal_node(node)) return node;
    if (node->child_count >= node->move_count) return node;

    U8 move = node->moves[node->child_count];

    Board next = node->board;
    make_move(&next, move);
    switch_color(&next);

    Node *child = create_node(node, &next, move);
    if (!child) return node;

    node->children[node->child_count++] = child;
    return child;
}

static double rollout(Board board) {
    if (is_win(&board))
        return -1.0;

    U8 count;
    U8 moves[7];
    gen_moves(&board, moves, &count);

    if (count == 0)
        return 0.0;   // draw

    U8 move = moves[rand() % count];
    make_move(&board, move);
    switch_color(&board);

    return -rollout(board);
}

static void backprop(Node *node, double reward) {
    if (!node) return;

    node->n++;
    node->r += reward;
    backprop(node->parent, -reward);
}

void mcts_train(Node *root, int n) {
    if (!root) return;

    for (int i = 0; i < n; i++) {
        Node *leaf = select(root);
        if (!leaf)
            return;

        if (!is_terminal_node(leaf))
            leaf = expand(leaf);

        double reward = rollout(leaf->board);
        backprop(leaf, reward);
    }
}

Node *mcts_advance_root(Node *root, U8 move) {
    if (!root) return NULL;

    for (U8 i = 0; i < root->child_count; i++) {
        Node *child = root->children[i];
        if (child && child->move_from_parent == move) {
            child->parent = NULL;

            for (U8 j = 0; j < root->child_count; j++) {
                if (root->children[j] && root->children[j] != child)
                    free_node(root->children[j]);
            }

            free(root);
            return child;
        }
    }

    Board next = root->board;
    make_move(&next, move);
    switch_color(&next);

    Node *child = create_node(NULL, &next, move);
    free_node(root);
    return child;
}

U8 mcts_best_move(const Node *root) {
    if (!root)
        return 255;

    if (root->child_count == 0) {
        if (root->move_count == 0)
            return 255;

        return root->moves[rand() % root->move_count];
    }

    U8 best_index = 0;
    for (U8 i = 1; i < root->child_count; i++) {
        if (root->children[i]->n > root->children[best_index]->n)
            best_index = i;
    }

    return root->children[best_index]->move_from_parent;
}