#include "../main.h"

void show_championship_types(MYSQL *conn) {

    const char *query = "SELECT championship_type FROM test"; // MODIFIER TABLE TEST !!!!!

    mysql_query(conn, query);

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\nTypes de championnats existants :\n");
    while ((row = mysql_fetch_row(result))) {
        printf("- %s\n", row[0]);
    }

    mysql_free_result(result);

    // mettre en place : attendre que le user appuie sur entree pour réafficher le menu principal
    display_main_menu(conn);
}