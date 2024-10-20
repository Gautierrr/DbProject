#include "../main.h"

// temporairement ici, créer un fichier specialement pr la fonction ?? impossible a mettre ds main.h ...
int max(int a, int b) {
    return (a > b) ? a : b;
}







int heightTeam(Team* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

Team* rightRotateTeam(Team* y) {
    Team* x = y->left;
    Team* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(heightTeam(y->left), heightTeam(y->right)) + 1;
    x->height = max(heightTeam(x->left), heightTeam(x->right)) + 1;

    return x;
}

Team* leftRotateTeam(Team* x) {
    Team* y = x->right;
    Team* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(heightTeam(x->left), heightTeam(x->right)) + 1;
    y->height = max(heightTeam(y->left), heightTeam(y->right)) + 1;

    return y;
}

int getBalanceTeam(Team* n) {
    if (n == NULL)
        return 0;
    return heightTeam(n->left) - heightTeam(n->right);
}
