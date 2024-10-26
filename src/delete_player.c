#include "../main.h"

Player* find_min_player(Player* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

Player* delete_player_and_balancing(Player* root, Player* node_to_delete) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(node_to_delete->id, root->id) < 0) {
        root->left = delete_player_and_balancing(root->left, node_to_delete);
    } else if (strcmp(node_to_delete->id, root->id) > 0) {
        root->right = delete_player_and_balancing(root->right, node_to_delete);
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
            Player* temp = find_min_player(root->right);
            strcpy(root->id, temp->id);
            strcpy(root->name, temp->name);
            root->age = temp->age;
            root->goals = temp->goals;
            root->assists = temp->assists;
            strcpy(root->position, temp->position);

            root->right = delete_player_and_balancing(root->right, temp);
        }
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

void delete_player(Team** team_root, const char* player_query) {
    if (player_query == NULL) {
        getchar();
        char search_query[100];

        printf("Enter the ID or name of the player to delete: ");
        fgets(search_query, sizeof(search_query), stdin);
        search_query[strcspn(search_query, "\n")] = '\0';

        player_query = search_query;
    }

    Player* node_to_delete = search_player((*team_root)->playersRoot, player_query);
    
    if (node_to_delete != NULL) {
        (*team_root)->playersRoot = delete_player_and_balancing((*team_root)->playersRoot, node_to_delete);
        printf("Player deleted successfully!\n");
    } else {
        printf("Player not found.\n");
    }
}
