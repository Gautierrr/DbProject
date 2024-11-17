/*
 * File name     : team_balancing.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that defines the functions allowing the rebalancing of the binary tree of teams by making rotations as soon as the gap between the levels of the tree is greater than 1.
 */

#include "../main.h"

// returns the maximum between 2 parameters, used to calculate the height of a node
int max(size_t a, size_t b) {
    return (a > b) ? a : b;
}

// calculates the height of a node
int height_team(Team* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// if the tree is "leaning" to the left, that is to say that the left part of the tree is 2 floors larger than the right part, then we perform a rotation to the right to rebalance it
Team* right_rotate_team(Team* y) {
    Team* x = y->left;
    Team* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height_team(y->left), height_team(y->right)) + 1;
    x->height = max(height_team(x->left), height_team(x->right)) + 1;

    return x;
}

// same but this time the tree is too "leaning" to the right so we rotate it to the left to rebalance it
Team* left_rotate_team(Team* x) {
    Team* y = x->right;
    Team* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height_team(x->left), height_team(x->right)) + 1;
    y->height = max(height_team(y->left), height_team(y->right)) + 1;

    return y;
}

// calculate the height difference between the right and left parts of the tree
int get_balance_team(Team* n) {
    if (n == NULL)
        return 0;
    return height_team(n->left) - height_team(n->right);
}
