#include "../main.h"

void save_team_to_file(Team* team, FILE* file) {
    if (team != NULL) {
        fprintf(file, "    {\n");
        fprintf(file, "        \"id\": %d,\n", team->id);
        fprintf(file, "        \"name\": \"%s\",\n", team->name);
        fprintf(file, "        \"trophies\": %d,\n", team->trophies);
        fprintf(file, "        \"win\": %d,\n", team->win);
        fprintf(file, "        \"equality\": %d,\n", team->equality);
        fprintf(file, "        \"defeat\": %d\n", team->defeat);
        fprintf(file, "    }");
    }
}

void save_teams_to_file(Team* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    save_teams_to_file(root->left, file);

    save_team_to_file(root, file);
    fprintf(file, ",\n");

    save_teams_to_file(root->right, file);
}

void save_binary_tree(Team* root, const char* championship_file) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championship_file);

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n  \"teams\": [\n");

    save_teams_to_file(root, file);

    fseek(file, -3, SEEK_CUR);
    fprintf(file, "\n  ]\n}\n");

    fclose(file);
    printf("Teams saved to %s successfully.\n", filepath);
}
