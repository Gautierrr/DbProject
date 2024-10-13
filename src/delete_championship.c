#include "../main.h"

void delete_championship(MYSQL *conn) {
    char delete_champ[50];

    printf("\nEntrez le type de championnat a supprimer: ");
    scanf("%s", delete_champ);

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM test WHERE championship_type = '%s'", delete_champ); // MODIFIER TABLE TEST !!!!!

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur lors de la suppression du championnat: %s\n", mysql_error(conn));
    } else {
        if (mysql_affected_rows(conn) > 0) {
            printf("\nLe type de championnat a ete supprime avec succes.\n");
        } else {
            printf("\nAucun championnat n'existe avec ce nom.\n");
        }

        printf("\nAppuyez sur entree pour revenir au menu principal...");
        getchar();
        getchar();
        display_main_menu(conn);
    }
}
