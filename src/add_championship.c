#include "../main.h"

void add_championship(MYSQL *conn) {

    Section new_section;

    printf("\nEntrez le nouveau type de championnat a ajouter: ");
    scanf("%s", new_section.type);

    // verifie sur ce type de championnat existe deja
    char check_query[256];
    snprintf(check_query, sizeof(check_query), "SELECT championship_type FROM test WHERE championship_type = '%s'", new_section.type);
    mysql_query(conn, check_query);

    MYSQL_RES *result = mysql_store_result(conn);

    if (mysql_num_rows(result) > 0) {
        printf("\nCe type de championnat existe deja.\n");
    } else {
        char query[256];
        snprintf(query, sizeof(query), "INSERT INTO test (championship_type) VALUES ('%s')", new_section.type);

        if (mysql_query(conn, query)) {
            printf("Erreur lors de l'ajout du championnat: %s\n", mysql_error(conn));
        } else {
            printf("\nNouveau type de championnat ajouté avec succes.\n");
        }
    }

    mysql_free_result(result);

    printf("\nAppuyez sur entree pour revenir au menu principal...");
    getchar();
    getchar();
    display_main_menu(conn);
}
