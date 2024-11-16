/*
 * File name     : main_menu.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the main menu for teams management and for saving binary trees.
 */

#include "../main.h"

// functions to free the memory of the 2 binary trees
void free_player_tree(Player* player) {
    if (player == NULL) return;

    free_player_tree(player->left);
    free_player_tree(player->right);

    free(player);
}

void free_team_tree(Team* team) {
    if (team == NULL) return;

    free_team_tree(team->left);
    free_team_tree(team->right);

    free(team);
}

void main_menu(Team** root, Player* rootPlayer, const char* championshipName) {
    int8_t option;

    do {        
        printf("\n============= Main menu =============\n");
        printf(" 1. See the existing teams\n");
        printf(" 2. Show a team\n");
        printf(" 3. Add a team\n");
        printf(" 4. Edit a team\n");
        printf(" 5. Delete a team\n");
        printf(" 6. See the players interface\n");
        printf(" 7. Save the Binary Tree and exit...\n");
        printf(" 8. Exit\n");
        printf("=====================================\n\n\n");

        printf("Please choose an option: ");
        
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1:
                display_team_tree(*root, 0);
                break;
            case 2:
                show_team(root);
                break;
            case 3:
                add_team(root);
                break;
            case 4:
                edit_team(root);
                break;
            case 5:
                delete_team(root);
                break;
            case 6:
                menu_player(root, rootPlayer, championshipName);
                break;
            case 7:
                // call the save function then go to option 8 to properly exit the program
                save_all(*root, rootPlayer, championshipName);
            case 8:
                printf("Bye bye ...\n");
                free_team_tree(*root);
                free_player_tree(rootPlayer);
                *root = NULL;
                rootPlayer = NULL;
                exit(0);
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != 8);
}
