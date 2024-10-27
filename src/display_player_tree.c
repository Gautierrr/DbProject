#include "../main.h"

void displayPlayerTree(Player* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    displayPlayerTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("ID: %d, Name: %s\n", root->id, root->name);

    displayPlayerTree(root->left, space);
}
