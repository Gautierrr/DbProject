#include "main.h"

MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

void get_password(char *password, size_t size) {
    printf("Entrez le mot de passe : ");
    fgets(password, size, stdin);
    password[strcspn(password, "\n")] = 0; // supp le saut de ligne a la fin du password
}

bool connect_to_database() {
    char password[PASSWORD_SIZE];

    get_password(password, PASSWORD_SIZE);

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "Echec de la connexion a la base de donnees.\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "legaug", password, "dbproject", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Echec de la connexion a la base de donnees.\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
}

void close_database_connection() {
    if (conn != NULL) {
        mysql_close(conn);
    }
}

int main(int argc, char *args[]) {
    if (connect_to_database()) {
        display_main_menu(conn);
    } else {
        printf("Echec de la connexion a la base de donnees.\n");
    }

    close_database_connection();
    return EXIT_SUCCESS;
}
