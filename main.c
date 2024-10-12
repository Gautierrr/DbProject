#include "mysql/include/mysql.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    } 

    if (mysql_real_connect(conn, "localhost", "", "", "dbproject", 3306, NULL, 0)) {
        
        printf("T un boss");

        mysql_close(conn);
    } else {
        printf("T une merde");
    }

}
