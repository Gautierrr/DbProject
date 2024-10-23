#include "../main.h"

Team* search_team_by_id(Team* node, int id) {
    if (node == NULL || node->id == id) {
        return node;
    }

    if (id < node->id) {
        return search_team_by_id(node->left, id);
    } else {
        return search_team_by_id(node->right, id);
    }
}

Team* search_team_by_name(Team* node, const char* name) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(node->name, name) == 0) {
        return node;
    }

    Team* result = search_team_by_name(node->left, name);
    if (result != NULL) {
        return result;
    }

    return search_team_by_name(node->right, name);
}

Team* search_team(Team* root, const char* query) {
    char* endptr;
    int id = strtol(query, &endptr, 10);

    if (*endptr == '\0') {
        return search_team_by_id(root, id);
    } else {
        return search_team_by_name(root, query);
    }
}
