#include "../main.h"

void edit_player(Team** root) {
    getchar();
    char query[50];
    
    printf("Enter the player ID or name to modify : ");
    fgets(query, sizeof(query), stdin);
    size_t len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') {
        query[len - 1] = '\0';
    }

    Player* player_to_modify = NULL;
    Team* team_with_player = NULL;

    Team* current_team = *root;
    while (current_team != NULL) {
        player_to_modify = search_player(current_team->playersRoot, query);
        if (player_to_modify != NULL) {
            team_with_player = current_team;
            break;
        }
        current_team = current_team->left;
    }

    if (player_to_modify == NULL) {
        printf("Player not found.\n");
        return;
    }

    printf("Current player details :\n");
    printf("ID : %d\n", player_to_modify->id);
    printf("Name : %s\n", player_to_modify->name);
    printf("Age : %d\n", player_to_modify->age);
    printf("Goals : %d\n", player_to_modify->goals);
    printf("Assists : %d\n", player_to_modify->assists);
    printf("Position : %s\n", player_to_modify->position);

    printf("\nEnter new player name (or press Enter to keep the current) : ");
    char new_name[50];
    fgets(new_name, sizeof(new_name), stdin);
    len = strlen(new_name);
    if (len > 0 && new_name[len - 1] == '\n') {
        new_name[len - 1] = '\0';
    }
    if (strlen(new_name) > 0) {
        strcpy(player_to_modify->name, new_name);
    }

    printf("Enter new player age (or press Enter to keep the current) : ");
    char age_input[10];
    fgets(age_input, sizeof(age_input), stdin);
    if (strlen(age_input) > 0 && age_input[0] != '\n') {
        player_to_modify->age = atoi(age_input);
    }

    printf("Enter new number of goals (or press Enter to keep the current) : ");
    char goals_input[10];
    fgets(goals_input, sizeof(goals_input), stdin);
    if (strlen(goals_input) > 0 && goals_input[0] != '\n') {
        player_to_modify->goals = atoi(goals_input);
    }

    printf("Enter new number of assists (or press Enter to keep the current) : ");
    char assists_input[10];
    fgets(assists_input, sizeof(assists_input), stdin);
    if (strlen(assists_input) > 0 && assists_input[0] != '\n') {
        player_to_modify->assists = atoi(assists_input);
    }

    printf("Enter new player position (or press Enter to keep the current) : ");
    char new_position[50];
    fgets(new_position, sizeof(new_position), stdin);
    len = strlen(new_position);
    if (len > 0 && new_position[len - 1] == '\n') {
        new_position[len - 1] = '\0';
    }
    if (strlen(new_position) > 0) {
        strcpy(player_to_modify->position, new_position);
    }

    printf("Do you want to change the player's team? (y/n): ");
    char change_team;
    scanf(" %c", &change_team);
    getchar();

    if (change_team == 'y' || change_team == 'Y') {
        printf("Enter the new team ID or name : ");
        char new_team_query[50];
        fgets(new_team_query, sizeof(new_team_query), stdin);
        len = strlen(new_team_query);
        if (len > 0 && new_team_query[len - 1] == '\n') {
            new_team_query[len - 1] = '\0';
        }

        Team* new_team = search_team(*root, new_team_query);
        if (new_team != NULL) {
            char id_str[20];
            snprintf(id_str, sizeof(id_str), "%d", player_to_modify->id);

            delete_player(&team_with_player, id_str);
            new_team->playersRoot = insert_player(new_team->playersRoot, player_to_modify);
            printf("Player moved to team %s successfully!\n", new_team->name);
        } else {
            printf("New team not found. Player remains in the old team.\n");
        }
    }

    printf("Player updated successfully!\n");
}
