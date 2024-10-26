#include "../main.h"

void show_championships() {
    const char *directory = "db";
    DIR *dir = opendir(directory);
    if (dir == NULL) {
        printf("Unable to open directory '%s'\n", directory);
        return;
    }

    struct dirent *entry;
    printf("Existing championships:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".json") != NULL) {
            printf("  - %.*s\n", (int)(strlen(entry->d_name) - 5), entry->d_name);
        }
    }

    closedir(dir);
}
