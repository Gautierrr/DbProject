#include "../main.h"

void delete_championship(const char *championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json.enc", championshipName);

    if (!file_exist(filepath)) {
        printf("Championship '%s' does not exist.\n", championshipName);
        return;
    }

    if (remove(filepath) == 0) {
        printf("Championship '%s' deleted successfully.\n", championshipName);
    } else {
        printf("Error deleting championship '%s'.\n", championshipName);
    }
}
