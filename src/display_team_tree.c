#include "../main.h"

void displayTeamTree(Team* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    displayTeamTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("ID: %d, Name: %s\n", root->id, root->name);

    displayTeamTree(root->left, space);
}
