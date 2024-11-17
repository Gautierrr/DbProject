/*
 * File name     : show_team.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the team selected by the user.
 */

#include "../main.h"

void show_team(Team** root) {
    getchar();
    char query[50];

    printf("Enter the team ID or name to display: ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Team* displayTeam = search_team(*root, query);

    if (displayTeam == NULL) {
        printf("Team not found.\n\n");
        return;
    }

    printf("\nCurrent team details:\n");
    printf("\nID: %ld\n", displayTeam->id);
    printf("Name: %s\n", displayTeam->name);
    printf("Trophies: %ld\n", displayTeam->trophies);
    printf("Wins: %ld\n", displayTeam->win);
    printf("Equalities: %ld\n", displayTeam->equality);
    printf("Defeats: %ld\n\n", displayTeam->defeat);

}
