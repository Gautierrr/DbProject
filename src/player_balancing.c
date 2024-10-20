#include "../main.h"

int heightPlayer(Player* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

Player* rightRotatePlayer(Player* y) {
    Player* x = y->left;
    Player* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(heightPlayer(y->left), heightPlayer(y->right)) + 1;
    x->height = max(heightPlayer(x->left), heightPlayer(x->right)) + 1;

    return x;
}

Player* leftRotatePlayer(Player* x) {
    Player* y = x->right;
    Player* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(heightPlayer(x->left), heightPlayer(x->right)) + 1;
    y->height = max(heightPlayer(y->left), heightPlayer(y->right)) + 1;

    return y;
}

int getBalancePlayer(Player* n) {
    if (n == NULL)
        return 0;
    return heightPlayer(n->left) - heightPlayer(n->right);
}
