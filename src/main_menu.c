#include "../main.h"

void main_menu(Team** root) {
    int option;

    do {        
        printf("\n\n\n====== Main menu ======\n");
        printf("1. See the existing teams\n");
        printf("2. Add a team\n");
        printf("3. Edit a team\n");
        printf("4. Delete a team\n");
        printf("5. Save the Binary Tree and exit...\n");
        printf("6. See the players interface\n");
        printf("7. Exit\n");
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
                add_team(root);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                save_binary_tree(*root);
                option = 7;
                break;
            case 6:
                break;
            case 7:
                printf("Bye bye ...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option != 7);
}
