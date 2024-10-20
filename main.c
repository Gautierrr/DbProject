#include "main.h"

int main(int argc, char *args[]) {
    int option;

    do {
        printf("\n\n\n======== Home Page ==========\n\n");
        printf("1. See existing championships\n");
        printf("2. Select a championship\n");
        printf("3. Create a championship\n");
        printf("4. Exit\n");
        printf("\n==============================\n\n\n");

        printf("Please choose an option : ");
        
        if (scanf("%d", &option) != 1) { // verif si un char est saisi au lieu d'un int
            while (getchar() != '\n');
            option = 0;
        } else {
            getchar();
        }

        switch (option) {
            case 1:
                printf("1");
                // Implémenter une fonction qui permet de recup tt les fichiers de bdd, les parser en enlevant l'extension puis afficher une liste avec le nom des fichiers dans l'extension
                // pour que cela fonctionne bien, lors de lenregistrement du binary tree dans le fichier bdd il faut absolument mettre le nom du championnat en tant que nom de fichier ex : 'ligue1'.'db'
                break;
            case 2:
                printf("2");
                // Appeler la fonction créé précédemment qui permet de recup tt les fichiers de bdd pour vérifier si le nom de championnat entré est valide
                // Si oui alors renvoyer vers la page pour entrer le mot de passe du championnat chargé
                // Si le nom du championnat entré existe pas alors réafficher le menu principal
                break;
            case 3:
                // Appeler la fonction permettant de créer un championnat, en premier fonction qui demande le nom du championnat a créer
                // main_menu();
                insert_exemple();
                break;
            case 4:
                printf("Bye bye ...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option < 1 || option > 4);

    return EXIT_SUCCESS;
}
