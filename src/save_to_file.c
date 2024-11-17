/*
 * File name     : save_to_file.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program to save the 2 binary trees in an encrypted json file.
 */


#include "../main.h"

// write all attributes of a player with json formatting
void save_player_to_file(Player* player, FILE* file) {
    if (player != NULL) {
        fprintf(file, "            {\n");
        fprintf(file, "                \"id\": \"%ld\",\n", player->id);
        fprintf(file, "                \"name\": \"%s\",\n", player->name);
        fprintf(file, "                \"age\": %ld,\n", player->age);
        fprintf(file, "                \"goals\": %ld,\n", player->goals);
        fprintf(file, "                \"assists\": %ld,\n", player->assists);
        fprintf(file, "                \"position\": \"%s\"\n", player->position);
        fprintf(file, "            }");
    }
}

// recursively traverse all players in the binary tree
void save_players_to_team(Player* player, const char* teamName, FILE* file, size_t* firstPlayer) {
    if (player == NULL) return;

    save_players_to_team(player->left, teamName, file, firstPlayer);

    if (strcmp(player->team, teamName) == 0) {
        if (!*firstPlayer) {
            fprintf(file, ",\n");
        }
        save_player_to_file(player, file);
        *firstPlayer = 0;
    }

    save_players_to_team(player->right, teamName, file, firstPlayer);
}

// write all attributes of a team with json formatting and including the players who are part of the team
void save_team_to_file(Team* team, Player* allPlayers, FILE* file) {
    if (team != NULL) {
        fprintf(file, "    {\n");
        fprintf(file, "        \"id\": %ld,\n", team->id);
        fprintf(file, "        \"name\": \"%s\",\n", team->name);
        fprintf(file, "        \"trophies\": %ld,\n", team->trophies);
        fprintf(file, "        \"win\": %ld,\n", team->win);
        fprintf(file, "        \"equality\": %ld,\n", team->equality);
        fprintf(file, "        \"defeat\": %ld,\n", team->defeat);

        fprintf(file, "        \"players\": [\n");
        size_t firstPlayer = 1;
        save_players_to_team(allPlayers, team->name, file, &firstPlayer);
        fprintf(file, "\n        ]\n");

        fprintf(file, "    }");
    }
}

// recursively traverses all teams in the binary tree
void save_teams_to_file(Team* root, Player* allPlayers, FILE* file, size_t* firstTeam) {
    if (root == NULL) return;

    save_teams_to_file(root->left, allPlayers, file, firstTeam);

    if (!*firstTeam) {
        fprintf(file, ",\n");
    } else {
        *firstTeam = 0;
    }

    save_team_to_file(root, allPlayers, file);

    save_teams_to_file(root->right, allPlayers, file, firstTeam);
}

// write the teams and players to a json file then encrypt it into a new file by calling the encrypt_or_decrypt function and finally delete the uncrypted json file
void save_all(Team* root, Player* allPlayers, const char* championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championshipName);
    char encryptedFilepath[50];
    snprintf(encryptedFilepath, sizeof(encryptedFilepath), "db/%s.json.enc", championshipName);
    
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n  \"teams\": [\n");

    size_t firstTeam = 1;
    save_teams_to_file(root, allPlayers, file, &firstTeam);

    fprintf(file, "\n  ]\n}\n");

    fclose(file);
    printf("\nTeams and players saved to %s successfully!\n", filepath);

    char password[20];
    printf("Enter a password to encrypt the file: ");
    scanf("%s", password);

    encrypt_or_decrypt(filepath, encryptedFilepath, password, 1);
    
    remove(filepath);
    printf("File encrypted and saved as '%s'.\n", encryptedFilepath);
}
