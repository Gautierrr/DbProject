/*
 * File name     : delete_championship.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program to delete an existing championship.
 */

#include "../main.h"

// checks if the championship really exists otherwise returns an error
int file_exist(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void delete_championship(const char *championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json.enc", championshipName);

    if (!file_exist(filepath)) {
        printf("Championship '%s' does not exist.\n", championshipName);
        return;
    }

    // use the remove function from stdio.h to delete a file
    if (remove(filepath) == 0) {
        printf("Championship '%s' deleted successfully!\n", championshipName);
    } else {
        printf("Error deleting championship '%s'.\n", championshipName);
    }
}
