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
        printf("Team does not exist. Player's team not modified.\n\n");
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

    int16_t temp;
    char input[10];

    printf("Enter new age (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%d", &temp) == 1 && temp >= 0) {
            playerToModify->age = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current age.\n");
        }
    }

    printf("Enter new number of goals (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%d", &temp) == 1 && temp >= 0) {
            playerToModify->goals = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of goals.\n");
        }
    }

    printf("Enter new number of assists (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%d", &temp) == 1 && temp >= 0) {
            playerToModify->assists = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of assists.\n");
        }
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
