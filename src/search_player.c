#include "../main.h"

Player* search_player_by_id(Player* node, const char* id) {
    if (node == NULL || strcmp(node->id, id) == 0) {
        return node;
    }

    if (strcmp(id, node->id) < 0) {
        return search_player_by_id(node->left, id);
    } else {
        return search_player_by_id(node->right, id);
    }
}

Player* search_player_by_name(Player* node, const char* name) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(node->name, name) == 0) {
        return node;
    }

    Player* result = search_player_by_name(node->left, name);
    if (result != NULL) {
        return result;
    }

    return search_player_by_name(node->right, name);
}

Player* search_player(Player* root, const char* query) {
    Player* player = search_player_by_id(root, query);
    if (player != NULL) {
        return player;
    }

    return search_player_by_name(root, query);
}

