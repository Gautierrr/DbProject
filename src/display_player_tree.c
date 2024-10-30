#include "../main.h"

void display_player_tree(Player* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    display_player_tree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("ID: %d, Name: %s\n", root->id, root->name);

    display_player_tree(root->left, space);
}
