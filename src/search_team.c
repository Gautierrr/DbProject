/*
 * File name     : search_team.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that allows you to search for a team based on its id or name.
 */

#include "../main.h"

Team* search_team_by_id(Team* node, size_t id) {
    if (node == NULL || node->id == id) {
        return node;
    }

    // ordered in ascending order so search based on whether the id is greater or not
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

    // not ordered by name so searches the entire binary tree
    Team* result = search_team_by_name(node->left, name);
    if (result != NULL) {
        return result;
    }

    return search_team_by_name(node->right, name);
}

Team* search_team(Team* root, const char* query) {
    char* nb;
    size_t id = strtol(query, &nb, 10);

    if (*nb == '\0') {
        return search_team_by_id(root, id);
    } else {
        return search_team_by_name(root, query);
    }
}
