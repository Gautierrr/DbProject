#include "../main.h"

void show_player(Player** root) {
    getchar();
    char query[50];

    printf("Enter the player ID or name to display : ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Player* displayPlayer = search_player(*root, query);

    if (displayPlayer == NULL) {
        printf("Player not found.\n");
        return;
    }

    printf("Current player details:\n");
    printf("ID: %d\n", displayPlayer->id);
    printf("Name: %s\n", displayPlayer->name);
    printf("Team: %s\n", displayPlayer->team);
    printf("Age: %d\n", displayPlayer->age);
    printf("Goals: %d\n", displayPlayer->goals);
    printf("Assists: %d\n", displayPlayer->assists);
    printf("Position: %s\n", displayPlayer->position);
}
