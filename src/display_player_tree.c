/*
 * File name     : display_player_tree.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the binary tree of players horizontally.
 */

#include "../main.h"

void display_player_tree(Player* root, size_t space) {
    if (root == NULL)
        return;

    space += 10;

    display_player_tree(root->right, space);

    printf("\n\n");
    for (size_t i = 10; i < space; i++)
        printf(" ");
    printf("ID: %ld, Name: %s\n", root->id, root->name);

    display_player_tree(root->left, space);
    printf("\n");
}
