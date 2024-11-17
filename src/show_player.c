/*
 * File name     : show_player.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the player selected by the user.
 */

#include "../main.h"

void show_player(Player** root) {
    getchar();
    char query[50];

    printf("Enter the player ID or name to display: ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Player* displayPlayer = search_player(*root, query);

    if (displayPlayer == NULL) {
        printf("Player not found.\n\n");
        return;
    }

    printf("\nCurrent player details:\n");
    printf("\nID: %ld\n", displayPlayer->id);
    printf("Name: %s\n", displayPlayer->name);
    printf("Team: %s\n", displayPlayer->team);
    printf("Age: %ld\n", displayPlayer->age);
    printf("Goals: %ld\n", displayPlayer->goals);
    printf("Assists: %ld\n", displayPlayer->assists);
    printf("Position: %s\n", displayPlayer->position);
}
