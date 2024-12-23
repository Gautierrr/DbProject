/*
 * File name     : edit_team.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : This program allows you to modify the attributes ​​of a team.
 */

#include "../main.h"

void edit_team(Team** root) {
    getchar();
    char query[50];
    
    printf("Enter the team ID or name to modify : ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Team* teamToModify = search_team(*root, query);

    if (teamToModify == NULL) {
        printf("Team not found.\n\n");
        return;
    }

    // displays the current attributes of the selected team
    printf("\nCurrent team details :\n");
    printf("ID: %ld\n", teamToModify->id);
    printf("Name: %s\n", teamToModify->name);
    printf("Trophies: %ld\n", teamToModify->trophies);
    printf("Wins: %ld\n", teamToModify->win);
    printf("Equalities: %ld\n", teamToModify->equality);
    printf("Defeats: %ld\n", teamToModify->defeat);

    // a modification of the team is possible for each of the attributes, except the id, if nothing is entered or the value entered is incorrect then this does not modify the attribute in question

    printf("\nEnter new team name (or press Enter to keep the current): ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    len = strlen(newName);
    if (len > 0 && newName[len - 1] == '\n') {
        newName[len - 1] = '\0';
    }
    if (strlen(newName) > 0) {
        strcpy(teamToModify->name, newName);
    }

    int16_t temp;
    char input[10];

    printf("Enter new number of trophies (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%hd", &temp) == 1 && temp >= 0) {
            teamToModify->trophies = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of trophies.\n");
        }
    }

    printf("Enter new number of wins (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%hd", &temp) == 1 && temp >= 0) {
            teamToModify->win = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of wins.\n");
        }
    }

    printf("Enter new number of equalities (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%hd", &temp) == 1 && temp >= 0) {
            teamToModify->equality = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of equalities.\n");
        }
    }

    printf("Enter new number of defeats (or press Enter to keep the current): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1 || (input[0] != '\n' && input[0] != '\0')) {
        if (sscanf(input, "%hd", &temp) == 1 && temp >= 0) {
            teamToModify->defeat = (size_t)temp;
        } else {
            printf("Invalid input. Keeping the current number of defeats.\n");
        }
    }

    printf("Team updated successfully!\n\n");
}
