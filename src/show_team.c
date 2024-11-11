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
    printf("\nID: %d\n", displayTeam->id);
    printf("Name: %s\n", displayTeam->name);
    printf("Trophies: %d\n", displayTeam->trophies);
    printf("Wins: %d\n", displayTeam->win);
    printf("Equalities: %d\n", displayTeam->equality);
    printf("Defeats: %d\n\n", displayTeam->defeat);

}
