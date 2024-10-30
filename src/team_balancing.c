#include "../main.h"

// temporairement ici, créer un fichier specialement pr la fonction ?? impossible a mettre ds main.h ...
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height_team(Team* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

Team* right_rotate_team(Team* y) {
    Team* x = y->left;
    Team* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height_team(y->left), height_team(y->right)) + 1;
    x->height = max(height_team(x->left), height_team(x->right)) + 1;

    return x;
}

Team* left_rotate_team(Team* x) {
    Team* y = x->right;
    Team* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height_team(x->left), height_team(x->right)) + 1;
    y->height = max(height_team(y->left), height_team(y->right)) + 1;

    return y;
}

int get_balance_team(Team* n) {
    if (n == NULL)
        return 0;
    return height_team(n->left) - height_team(n->right);
}
