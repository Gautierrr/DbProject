#include "../main.h"

void edit_team(Team** root) {
    getchar();
    char query[50];
    
    printf("Enter the team ID or name to modify: ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Team* team_to_modify = search_team(*root, query);

    if (team_to_modify == NULL) {
        printf("Team not found.\n");
        return;
    }

    printf("Current team details:\n");
    printf("ID: %d\n", team_to_modify->id);
    printf("Name: %s\n", team_to_modify->name);
    printf("Trophies: %d\n", team_to_modify->trophies);
    printf("Wins: %d\n", team_to_modify->win);
    printf("Equalities: %d\n", team_to_modify->equality);
    printf("Defeats: %d\n", team_to_modify->defeat);

    printf("\nEnter new team name (or press Enter to keep the current): ");
    char new_name[50];
    fgets(new_name, sizeof(new_name), stdin);
    len = strlen(new_name);
    if (len > 0 && new_name[len - 1] == '\n') {
        new_name[len - 1] = '\0';
    }
    if (strlen(new_name) > 0) {
        strcpy(team_to_modify->name, new_name);
    }

    printf("Enter new number of trophies (or press Enter to keep the current): ");
    char trophies_input[10];
    fgets(trophies_input, sizeof(trophies_input), stdin);
    if (strlen(trophies_input) > 0 && trophies_input[0] != '\n') {
        team_to_modify->trophies = atoi(trophies_input);
    }

    printf("Enter new number of wins (or press Enter to keep the current): ");
    char wins_input[10];
    fgets(wins_input, sizeof(wins_input), stdin);
    if (strlen(wins_input) > 0 && wins_input[0] != '\n') {
        team_to_modify->win = atoi(wins_input);
    }

    printf("Enter new number of equalities (or press Enter to keep the current): ");
    char equalities_input[10];
    fgets(equalities_input, sizeof(equalities_input), stdin);
    if (strlen(equalities_input) > 0 && equalities_input[0] != '\n') {
        team_to_modify->equality = atoi(equalities_input);
    }

    printf("Enter new number of defeats (or press Enter to keep the current): ");
    char defeats_input[10];
    fgets(defeats_input, sizeof(defeats_input), stdin);
    if (strlen(defeats_input) > 0 && defeats_input[0] != '\n') {
        team_to_modify->defeat = atoi(defeats_input);
    }

    printf("Team updated successfully!\n");
}
