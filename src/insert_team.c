#include "../main.h"

Team* insertTeam(Team* node, int id, char name[], int trophies, int win, int equality, int defeat) {
    if (node == NULL) {
        Team* newNode = (Team*)malloc(sizeof(Team));
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->trophies = trophies;
        newNode->win = win;
        newNode->equality = equality;
        newNode->defeat = defeat;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (id < node->id)
        node->left = insertTeam(node->left, id, name, trophies, win, equality, defeat);
    else if (id > node->id)
        node->right = insertTeam(node->right, id, name, trophies, win, equality, defeat);
    else
        return node;

    node->height = 1 + max(heightTeam(node->left), heightTeam(node->right));

    int balance = getBalanceTeam(node);

    // left left
    if (balance > 1 && id < node->left->id)
        return rightRotateTeam(node);

    // right right
    if (balance < -1 && id > node->right->id)
        return leftRotateTeam(node);

    // left right
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotateTeam(node->left);
        return rightRotateTeam(node);
    }

    // right left
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotateTeam(node->right);
        return leftRotateTeam(node);
    }

    return node;
}












