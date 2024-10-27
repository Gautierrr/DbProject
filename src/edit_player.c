#include "../main.h"

void edit_player(Player** root, Team* rootTeam) {
    getchar();
    char query[50];
    
    printf("Enter the player ID or name to modify: ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Player* player_to_modify = search_player(*root, query);

    if (player_to_modify == NULL) {
        printf("Player not found.\n");
        return;
    }

    printf("\nCurrent player details:\n");
    printf("ID: %d\n", player_to_modify->id);
    printf("Name: %s\n", player_to_modify->name);
    printf("Team: %s\n", player_to_modify->team);
    printf("Age: %d\n", player_to_modify->age);
    printf("Goals: %d\n", player_to_modify->goals);
    printf("Assists: %d\n", player_to_modify->assists);
    printf("Position: %s\n", player_to_modify->position);

    printf("\nEnter the ID or name of the new team the player belongs to (or press Enter to keep the current): ");
    char new_team[50];
    fgets(new_team, sizeof(new_team), stdin);
    len = strlen(new_team);
    if (len > 0 && new_team[len - 1] == '\n') {
        new_team[len - 1] = '\0';
    }

    if (strlen(new_team) > 0 && search_team(rootTeam, new_team) == NULL) {
        printf("Team does not exist. Player's team not modified.\n");
    } else if (strlen(new_team) > 0) {
        strcpy(player_to_modify->team, new_team);
    }

    printf("Enter new player name (or press Enter to keep the current): ");
    char new_name[50];
    fgets(new_name, sizeof(new_name), stdin);
    len = strlen(new_name);
    if (len > 0 && new_name[len - 1] == '\n') {
        new_name[len - 1] = '\0';
    }
    if (strlen(new_name) > 0) {
        strcpy(player_to_modify->name, new_name);
    }

    printf("Enter new age (or press Enter to keep the current): ");
    char age_input[10];
    fgets(age_input, sizeof(age_input), stdin);
    if (strlen(age_input) > 0 && age_input[0] != '\n') {
        player_to_modify->age = atoi(age_input);
    }

    printf("Enter new number of goals (or press Enter to keep the current): ");
    char goals_input[10];
    fgets(goals_input, sizeof(goals_input), stdin);
    if (strlen(goals_input) > 0 && goals_input[0] != '\n') {
        player_to_modify->goals = atoi(goals_input);
    }

    printf("Enter new number of assists (or press Enter to keep the current): ");
    char assists_input[10];
    fgets(assists_input, sizeof(assists_input), stdin);
    if (strlen(assists_input) > 0 && assists_input[0] != '\n') {
        player_to_modify->assists = atoi(assists_input);
    }

    printf("Enter new position (or press Enter to keep the current): ");
    char new_position[50];
    fgets(new_position, sizeof(new_position), stdin);
    len = strlen(new_position);
    if (len > 0 && new_position[len - 1] == '\n') {
        new_position[len - 1] = '\0';
    }
    if (strlen(new_position) > 0) {
        strcpy(player_to_modify->position, new_position);
    }

    printf("Player updated successfully!\n");
}
