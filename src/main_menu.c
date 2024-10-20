#include "../main.h"

char* championship_name() {
    char *name = malloc(20 * sizeof(char));
    if (name == NULL) {
        printf("Memory allocation error.\n");
        return NULL;
    }

    size_t len;

    do {
        printf("Please enter the name of the championship : ");
        fgets(name, 20, stdin);

        len = strlen(name);

        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        if (strlen(name) == 0) {
            printf("\nYou have not entered a name. Please try again.\n");
        }

    } while (strlen(name) == 0);

    return name;
}

void main_menu() {
    int option;
    char *championshipName;

    do {
        championshipName = championship_name();
        
        printf("\n\n\n==== Main menu of %s ====\n", championshipName);
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

    free(championshipName);
}
