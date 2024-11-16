/*
 * File name     : menu_player.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program that displays the main menu for players management.
 */

#include "../main.h"

void menu_player(Team** root, Player* rootPlayer, const char* championshipName) {
    int8_t option;

    do {        
        printf("\n\n========== Players interface ==========\n");
        printf(" 1. See the existing players\n");
        printf(" 2. Show a player\n");
        printf(" 3. Add a player\n");
        printf(" 4. Edit a player\n");
        printf(" 5. Delete a player\n");
        printf(" 6. Return to teams interface to save\n");
        printf("=======================================\n\n\n");

        printf("Please choose an option: ");
        
        if (scanf("%hhd", &option) != 1) {
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1:
                display_player_tree(rootPlayer, 0);
                break;
            case 2:
                show_player(&rootPlayer);
                break;
            case 3:
                add_player(&rootPlayer, *root);
                break;
            case 4:
                edit_player(&rootPlayer, *root);
                break;
            case 5:
                delete_player(&rootPlayer);
                break;
            case 6:
                main_menu(root , rootPlayer, championshipName);
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != 6);
}
