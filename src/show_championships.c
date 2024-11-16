/*
 * File name     : show_championships.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : This program browses the db folder to display the already existing championships.
 */

#include "../main.h"

void show_championships() {
    DIR *dir = opendir("db");
    struct dirent *entry;
    printf("\nExisting championships:\n\n");
    
    // browse the db folder and display only the files in .json.enc
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".json.enc") != NULL ) {
            printf("  - %.*s\n", (int)(strlen(entry->d_name) - 9), entry->d_name);
        }
    }

    closedir(dir);
    printf("\n");
}
