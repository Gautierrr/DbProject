#include "../main.h"

void add_championship(MYSQL *conn) {
    
    Section new_section;
    
    printf("\nEntrez le nouveau type de championnat a ajouter: ");
    scanf("%s", new_section.type);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO test (championship_type) VALUES ('%s')", new_section.type); // MODIFIER TABLE TEST !!!!!

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur lors de l'ajout de la section: %s\n", mysql_error(conn));
    } else {
        printf("\nNouveau type de championnat ajoute avec succes.\n");

        // mettre en place : attendre que le user appuie sur entree pour réafficher le menu principal
        display_main_menu(conn);
    }
}