/*
 * File name     : display_team_tree.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the binary tree of teams horizontally.
 */

#include "../main.h"

void display_team_tree(Team* root, size_t space) {
    if (root == NULL)
        return;

    space += 10;

    display_team_tree(root->right, space);

    printf("\n\n");
    for (size_t i = 10; i < space; i++)
        printf(" ");
    printf("ID: %d, Name: %s\n", root->id, root->name);

    display_team_tree(root->left, space);
    printf("\n");
}
