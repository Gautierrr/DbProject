#include "../main.h"

void main_menu() {
    int option;

    do {        
        printf("\n\n\n====== Main menu ======\n");
        printf("1. See the existing teams\n");
        printf("2. Add a team\n");
        printf("3. Edit a team\n");
        printf("4. Delete a team\n");
        printf("5. See the players interface\n");
        printf("6. Exit\n");
        printf("========================\n\n\n");

        printf("Please choose an option : ");
        
        if (scanf("%d", &option) != 1) { // verif si un char est saisi au lieu d'un int
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1:
                break;
            case 2:
                insert_exemple();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                printf("Bye bye ...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option < 1 || option > 6);
}
