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

    Player* playerToModify = search_player(*root, query);

    if (playerToModify == NULL) {
        printf("Player not found.\n");
        return;
    }

    printf("\nCurrent player details:\n");
    printf("ID: %d\n", playerToModify->id);
    printf("Name: %s\n", playerToModify->name);
    printf("Team: %s\n", playerToModify->team);
    printf("Age: %d\n", playerToModify->age);
    printf("Goals: %d\n", playerToModify->goals);
    printf("Assists: %d\n", playerToModify->assists);
    printf("Position: %s\n", playerToModify->position);

    printf("\nEnter the ID or name of the new team the player belongs to (or press Enter to keep the current): ");
    char newTeam[50];
    fgets(newTeam, sizeof(newTeam), stdin);
    len = strlen(newTeam);
    if (len > 0 && newTeam[len - 1] == '\n') {
        newTeam[len - 1] = '\0';
    }

    if (strlen(newTeam) > 0 && search_team(rootTeam, newTeam) == NULL) {
        printf("Team does not exist. Player's team not modified.\n");
    } else if (strlen(newTeam) > 0) {
        strcpy(playerToModify->team, newTeam);
    }

    printf("Enter new player name (or press Enter to keep the current): ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    len = strlen(newName);
    if (len > 0 && newName[len - 1] == '\n') {
        newName[len - 1] = '\0';
    }
    if (strlen(newName) > 0) {
        strcpy(playerToModify->name, newName);
    }

    printf("Enter new age (or press Enter to keep the current): ");
    char ageInput[10];
    fgets(ageInput, sizeof(ageInput), stdin);
    if (strlen(ageInput) > 0 && ageInput[0] != '\n') {
        playerToModify->age = atoi(ageInput);
    }

    printf("Enter new number of goals (or press Enter to keep the current): ");
    char goalsInput[10];
    fgets(goalsInput, sizeof(goalsInput), stdin);
    if (strlen(goalsInput) > 0 && goalsInput[0] != '\n') {
        playerToModify->goals = atoi(goalsInput);
    }

    printf("Enter new number of assists (or press Enter to keep the current): ");
    char assistsInput[10];
    fgets(assistsInput, sizeof(assistsInput), stdin);
    if (strlen(assistsInput) > 0 && assistsInput[0] != '\n') {
        playerToModify->assists = atoi(assistsInput);
    }

    printf("Enter new position (or press Enter to keep the current): ");
    char new_position[50];
    fgets(new_position, sizeof(new_position), stdin);
    len = strlen(new_position);
    if (len > 0 && new_position[len - 1] == '\n') {
        new_position[len - 1] = '\0';
    }
    if (strlen(new_position) > 0) {
        strcpy(playerToModify->position, new_position);
    }

    printf("Player updated successfully!\n");
}
