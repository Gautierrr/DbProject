#include "../main.h"

Team* find_team_min(Team* node) {
    if (node == NULL) {
        return NULL;
    }
    
    while (node->left != NULL) {
        node = node->left;
    }
    
    return node;
}

Team* delete_team_balancing(Team* root, Team* nodeToDelete) {
    if (root == NULL) {
        return root;
    }

    if (nodeToDelete->id < root->id) {
        root->left = delete_team_balancing(root->left, nodeToDelete);
    } else if (nodeToDelete->id > root->id) {
        root->right = delete_team_balancing(root->right, nodeToDelete);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Team* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Team* temp = find_team_min(root->right);
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->trophies = temp->trophies;
            root->win = temp->win;
            root->equality = temp->equality;
            root->defeat = temp->defeat;

            root->right = delete_team_balancing(root->right, temp);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height_team(root->left), height_team(root->right));

    int8_t balance = get_balance_team(root);

    if (balance > 1 && get_balance_team(root->left) >= 0) {
        return right_rotate_team(root);
    }

    if (balance > 1 && get_balance_team(root->left) < 0) {
        root->left = left_rotate_team(root->left);
        return right_rotate_team(root);
    }

    if (balance < -1 && get_balance_team(root->right) <= 0) {
        return left_rotate_team(root);
    }

    if (balance < -1 && get_balance_team(root->right) > 0) {
        root->right = right_rotate_team(root->right);
        return left_rotate_team(root);
    }

    return root;
}

void delete_team(Team** root) {
    getchar();
    char query[50];

    printf("Enter the ID or name of the team to delete: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    Team* nodeToDelete = search_team(*root, query);
    
    if (nodeToDelete != NULL) {
        *root = delete_team_balancing(*root, nodeToDelete);
        printf("Team deleted successfully!\n");
    } else {
        printf("Team not found.\n");
    }
}
