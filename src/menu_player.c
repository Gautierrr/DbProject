#include "../main.h"

void menu_player(Team** root, const char* championship_file) {
    int option;

    do {        
        printf("\n\n\n====== Main menu ======\n");
        printf("1. See the existing players\n");
        printf("2. Select a player\n");
        printf("3. Add a player\n");
        printf("4. Edit a player\n");
        printf("5. Delete a player\n");
        printf("6. Save new players and return to teams interface\n");
        printf("7. Return to teams interface\n");
        printf("========================\n\n\n");

        printf("Please choose an option : ");
        
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                add_player(*root);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                // save_binary_tree(*root, championship_file); // add une option genre si a = 1 alors save team et si a = 2 alors save player
                option = 7;
                break;
            case 7:
                return;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != 7);
}
