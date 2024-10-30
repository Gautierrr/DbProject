#include "../main.h"

void show_championships() {
    DIR *dir = opendir("db");
    struct dirent *entry;
    printf("\nExisting championships:\n\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".json.enc") != NULL ) {
            printf("  - %.*s\n", (int)(strlen(entry->d_name) - 9), entry->d_name);
        }
    }

    closedir(dir);
    printf("\n");
}
