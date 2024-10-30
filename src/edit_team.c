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
        printf("Team not found.\n");
        return;
    }

    printf("\nCurrent team details :\n");
    printf("ID : %d\n", teamToModify->id);
    printf("Name : %s\n", teamToModify->name);
    printf("Trophies : %d\n", teamToModify->trophies);
    printf("Wins : %d\n", teamToModify->win);
    printf("Equalities : %d\n", teamToModify->equality);
    printf("Defeats : %d\n", teamToModify->defeat);

    printf("\nEnter new team name (or press Enter to keep the current) : ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    len = strlen(newName);
    if (len > 0 && newName[len - 1] == '\n') {
        newName[len - 1] = '\0';
    }
    if (strlen(newName) > 0) {
        strcpy(teamToModify->name, newName);
    }

    printf("Enter new number of trophies (or press Enter to keep the current) : ");
    char trophiesInput[10];
    fgets(trophiesInput, sizeof(trophiesInput), stdin);
    if (strlen(trophiesInput) > 0 && trophiesInput[0] != '\n') {
        teamToModify->trophies = atoi(trophiesInput);
    }

    printf("Enter new number of wins (or press Enter to keep the current) : ");
    char winsInput[10];
    fgets(winsInput, sizeof(winsInput), stdin);
    if (strlen(winsInput) > 0 && winsInput[0] != '\n') {
        teamToModify->win = atoi(winsInput);
    }

    printf("Enter new number of equalities (or press Enter to keep the current) : ");
    char equalitiesInput[10];
    fgets(equalitiesInput, sizeof(equalitiesInput), stdin);
    if (strlen(equalitiesInput) > 0 && equalitiesInput[0] != '\n') {
        teamToModify->equality = atoi(equalitiesInput);
    }

    printf("Enter new number of defeats (or press Enter to keep the current) : ");
    char defeatsInput[10];
    fgets(defeatsInput, sizeof(defeatsInput), stdin);
    if (strlen(defeatsInput) > 0 && defeatsInput[0] != '\n') {
        teamToModify->defeat = atoi(defeatsInput);
    }

    printf("Team updated successfully!\n");
}
