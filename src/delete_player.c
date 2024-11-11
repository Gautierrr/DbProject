#include "../main.h"

Player* find_player_min(Player* node) {
    if (node == NULL) {
        return NULL;
    }
    
    while (node->left != NULL) {
        node = node->left;
    }
    
    return node;
}

Player* delete_player_balancing(Player* root, Player* nodeToDelete) {
    if (root == NULL) {
        return root;
    }

    if (nodeToDelete->id < root->id) {
        root->left = delete_player_balancing(root->left, nodeToDelete);
    } else if (nodeToDelete->id > root->id) {
        root->right = delete_player_balancing(root->right, nodeToDelete);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Player* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Player* temp = find_player_min(root->right);
            root->id = temp->id;
            strcpy(root->name, temp->name);
            strcpy(root->team, temp->team);
            root->age = temp->age;
            root->goals = temp->goals;
            root->assists = temp->assists;
            strcpy(root->position, temp->position);

            root->right = delete_player_balancing(root->right, temp);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height_player(root->left), height_player(root->right));

    int balance = get_balance_player(root);

    if (balance > 1 && get_balance_player(root->left) >= 0) {
        return right_rotate_player(root);
    }

    if (balance > 1 && get_balance_player(root->left) < 0) {
        root->left = left_rotate_player(root->left);
        return right_rotate_player(root);
    }

    if (balance < -1 && get_balance_player(root->right) <= 0) {
        return left_rotate_player(root);
    }

    if (balance < -1 && get_balance_player(root->right) > 0) {
        root->right = right_rotate_player(root->right);
        return left_rotate_player(root);
    }

    return root;
}

void delete_player(Player** root) {
    getchar();
    char query[50];

    printf("Enter the ID or name of the player to delete: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    Player* nodeToDelete = search_player(*root, query);
    
    if (nodeToDelete != NULL) {
        *root = delete_player_balancing(*root, nodeToDelete);
        printf("Player deleted successfully!\n");
    } else {
        printf("Player not found.\n");
    }
}
