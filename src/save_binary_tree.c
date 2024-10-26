#include "../main.h"

void save_player_to_file(Player* player, FILE* file) {
    if (player != NULL) {
        fprintf(file, "            {\n");
        fprintf(file, "                \"id\": \"%s\",\n", player->id);
        fprintf(file, "                \"name\": \"%s\",\n", player->name);
        fprintf(file, "                \"age\": %d,\n", player->age);
        fprintf(file, "                \"goals\": %d,\n", player->goals);
        fprintf(file, "                \"assists\": %d,\n", player->assists);
        fprintf(file, "                \"position\": \"%s\"\n", player->position);
        fprintf(file, "            }");
    }
}

int count_players(Player* player) {
    if (player == NULL) return 0;
    return 1 + count_players(player->left) + count_players(player->right);
}

void save_players_to_file(Player* player, FILE* file, int* players_saved, int total_players) {
    if (player == NULL) return;

    save_players_to_file(player->left, file, players_saved, total_players);

    save_player_to_file(player, file);
    (*players_saved)++;

    if (*players_saved < total_players) {
        fprintf(file, ",\n");
    }

    save_players_to_file(player->right, file, players_saved, total_players);
}

void save_team_to_file(Team* team, FILE* file) {
    if (team != NULL) {
        fprintf(file, "    {\n");
        fprintf(file, "        \"id\": %d,\n", team->id);
        fprintf(file, "        \"name\": \"%s\",\n", team->name);
        fprintf(file, "        \"trophies\": %d,\n", team->trophies);
        fprintf(file, "        \"win\": %d,\n", team->win);
        fprintf(file, "        \"equality\": %d,\n", team->equality);
        fprintf(file, "        \"defeat\": %d,\n", team->defeat);

        if (team->playersRoot != NULL) {
            int total_players = count_players(team->playersRoot);
            int players_saved = 0;

            fprintf(file, "        \"players\": [\n");
            save_players_to_file(team->playersRoot, file, &players_saved, total_players);
            fprintf(file, "\n        ]\n");
        } else {
            fprintf(file, "        \"players\": []\n");
        }

        fprintf(file, "    }");
    }
}

void save_teams_to_file(Team* root, FILE* file, int* first_team) {
    if (root == NULL) return;

    save_teams_to_file(root->left, file, first_team);

    if (!*first_team) {
        fprintf(file, ",\n");
    } else {
        *first_team = 0;
    }

    save_team_to_file(root, file);

    save_teams_to_file(root->right, file, first_team);
}

void save_teams_and_players(Team* root, const char* championship_file) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championship_file);

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n  \"teams\": [\n");

    int first_team = 1;
    save_teams_to_file(root, file, &first_team);

    fprintf(file, "\n  ]\n}\n");

    fclose(file);
    printf("Teams and players saved to %s successfully.\n", filepath);
}
