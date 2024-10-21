#include "../main.h"

void displayInOrder(Team* node) {
    if (node != NULL) {
        displayInOrder(node->left);
        printf("Team ID: %d, Name: %s, Trophies: %d\n", node->id, node->name, node->trophies);
        displayInOrder(node->right);
    }
}

void displayTree(Team* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->id);

    displayTree(root->left, space);
}