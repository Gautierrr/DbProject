#include "../main.h"

void modify_championship(MYSQL *conn) {

    char old_type[50];
    char new_type[50];

    printf("\nEntrez le type de championnat a modifier: ");
    scanf("%s", old_type);

    printf("Entrez le nouveau type de championnat: ");
    scanf("%s", new_type);

    char query[256];
    snprintf(query, sizeof(query), "UPDATE test SET championship_type = '%s' WHERE championship_type = '%s'", new_type, old_type); // MODIFIER TABLE TEST !!!!!

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erreur lors de la modification du championnat: %s\n", mysql_error(conn));
    } else {
        if (mysql_affected_rows(conn) > 0) {
            printf("\nLe type de championnat a ete modifie avec succes.\n");
        } else {
            printf("\nAucun championnat n'existe avec ce nom.\n");
        }
        
        printf("\nAppuyez sur entree pour revenir au menu principal...");
        getchar();
        getchar();
        display_main_menu(conn);
    }
}
