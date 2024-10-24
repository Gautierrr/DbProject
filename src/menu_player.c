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
        printf("6. Return to teams interface to save\n");
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
                return;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != 6);
}
