#include "../main.h"

/*
int verify_password() {
    char password[20];
    printf("Enter password: ");
    scanf("%19s", password);

    if (strcmp(password, "password") == 0) {
        printf("Password correct. Loading championship...\n");
        return 1;
    } else {
        printf("Incorrect password.\n");
        return 0;
    }
}
*/

int file_exist(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void create_json_file(const char *name) {
    const char *directory = "db";
    char filepath[30];

    // db/name.json
    snprintf(filepath, sizeof(filepath), "%s/%s.json", directory, name);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error creating file '%s'.\n", filepath);
        return;
    }

    fprintf(file, "{\n\t\"championship\": \"%s\"\n}\n", name);

    fclose(file);

    printf("File '%s' created successfully.\n", filepath);
}


void create_championship(const char *championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championshipName);

    if (file_exist(filepath)) {
        printf("Championship '%s' already exists.\n", championshipName);
        /*if (verify_password()) {
            // Charger les données du championnat
            printf("Championship '%s' loaded successfully.\n", championshipName);
        } else {
            printf("Failed to load championship '%s'.\n", championshipName);
        }*/
    } else {
        Team* root = NULL;

        printf("Creating new championship '%s'.\n", championshipName);
        create_json_file(championshipName);
        main_menu(&root, championshipName);
    }
}
