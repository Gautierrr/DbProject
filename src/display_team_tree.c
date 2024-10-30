#include "../main.h"

void display_team_tree(Team* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    display_team_tree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("ID: %d, Name: %s\n", root->id, root->name);

    display_team_tree(root->left, space);
}
