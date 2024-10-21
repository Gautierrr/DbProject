#include "../main.h"

// modifier pour si on save une 2e fois apres avoir deja save alors cela charge le fichier .json et le réorganise avec les bonnes données
// inserer dans le fichier correspondant name = championship

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

void save_binary_tree(Team* root) {
    FILE* file = fopen("db/binary_tree.json", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "{\n\"teams\": ");
    save_tree_to_file(root, file);
    fprintf(file, "\n}\n");

    fclose(file);
    printf("Tree saved to db/binary_tree.json successfully.\n");
}
