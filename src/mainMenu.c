#include "../main.h"

void display_main_menu(MYSQL *conn) {
    int option;

    do {
        printf("\n\n\n==== Menu Principal ====\n");
        printf("1. Voir les types de championnats deja existants\n");
        printf("2. Ajouter un type de championnat\n");
        printf("3. Modifier un type de championnat\n");
        printf("4. Supprimer un type de championnat\n");
        printf("5. Selectionner un championnat\n");
        printf("6. Quitter\n");
        printf("======================\n\n\n");

        printf("Veuillez choisir une option: ");
        
        if (scanf("%d", &option) != 1) { // verif si un char est saisi au lieu d'un int
            while (getchar() != '\n');
            option = 0;
        }

        switch (option) {
            case 1:
                show_championship_types(conn);
                break;
            case 2:
                add_championship(conn);
                break;
            case 3:
                modify_championship();
                break;
            case 4:
                delete_championship();
                break;
            case 5:
                menu_select_championship();
                break;
            case 6:
                printf("Au revoir!\n");
                break;
            default:
                printf("Option invalide, veuillez reessayer.\n");
        }
    } while (option < 1 || option > 6);
}
