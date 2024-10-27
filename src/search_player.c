#include "../main.h"

Player* search_player_by_id(Team* root, int id) {
    if (root == NULL) {
        return NULL;
    }
    
    Player* player = search_player_by_id(root->playersRoot, id);
    if (player != NULL) {
        return player;
    }

    player = search_player_by_id(root->left, id);
    if (player != NULL) {
        return player;
    }
    return search_player_by_id(root->right, id);
}

Player* search_player_by_name(Team* root, const char* name) {
    if (root == NULL) {
        return NULL;
    }
    
    Player* player = search_player_by_name(root->playersRoot, name);
    if (player != NULL) {
        return player;
    }

    player = search_player_by_name(root->left, name);
    if (player != NULL) {
        return player;
    }
    return search_player_by_name(root->right, name);
}

Player* search_player(Team* root, const char* query) {
    int id;
    if (sscanf(query, "%d", &id) == 1) {
        return search_player_by_id(root, id);
    } else {
        return search_player_by_name(root, query);
    }
}
