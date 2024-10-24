#include "../main.h"

int height_player(Player* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

Player* right_rotate_player(Player* y) {
    Player* x = y->left;
    Player* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height_player(y->left), height_player(y->right)) + 1;
    x->height = max(height_player(x->left), height_player(x->right)) + 1;

    return x;
}

Player* left_rotate_player(Player* x) {
    Player* y = x->right;
    Player* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height_player(x->left), height_player(x->right)) + 1;
    y->height = max(height_player(y->left), height_player(y->right)) + 1;

    return y;
}

int get_balance_player(Player* n) {
    if (n == NULL)
        return 0;
    return height_player(n->left) - height_player(n->right);
}
