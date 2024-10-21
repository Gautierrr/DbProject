#include "../main.h"

void save_tree_to_file(Team* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "{\n");
        fprintf(file, "\"id\": %d,\n", root->id);
        fprintf(file, "\"name\": \"%s\",\n", root->name);
        fprintf(file, "\"trophies\": %d,\n", root->trophies);
        fprintf(file, "\"win\": %d,\n", root->win);
        fprintf(file, "\"equality\": %d,\n", root->equality);
        fprintf(file, "\"defeat\": %d,\n", root->defeat);

        fprintf(file, "\"left\": ");
        save_tree_to_file(root->left, file);
        fprintf(file, ",\n\"right\": ");
        save_tree_to_file(root->right, file);
        fprintf(file, "}\n");
    } else {
        fprintf(file, "null");
    }
}

void save_binary_tree(Team* root, const char* championship_file) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championship_file);

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n\"teams\": ");
    save_tree_to_file(root, file);
    fprintf(file, "\n}\n");

    fclose(file);
    printf("Binary tree saved to %s successfully.\n", filepath);
}
