/*
 * File name     : player_balancing.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that defines the functions allowing the rebalancing of the binary tree of players by making rotations as soon as the gap between the levels of the tree is greater than 1.
 */

#include "../main.h"

// calculates the height of a node
int height_player(Player* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// if the tree is "leaning" to the left, that is to say that the left part of the tree is 2 floors larger than the right part, then we perform a rotation to the right to rebalance it
Player* right_rotate_player(Player* y) {
    Player* x = y->left;
    Player* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height_player(y->left), height_player(y->right)) + 1;
    x->height = max(height_player(x->left), height_player(x->right)) + 1;

    return x;
}

// same but this time the tree is too "leaning" to the right so we rotate it to the left to rebalance it
Player* left_rotate_player(Player* x) {
    Player* y = x->right;
    Player* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height_player(x->left), height_player(x->right)) + 1;
    y->height = max(height_player(y->left), height_player(y->right)) + 1;

    return y;
}

// calculate the height difference between the right and left parts of the tree
int get_balance_player(Player* n) {
    if (n == NULL)
        return 0;
    return height_player(n->left) - height_player(n->right);
}
