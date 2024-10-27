#include "../main.h"

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

    Team* root = NULL;
    Player* rootPlayer = NULL;

    create_json_file(championshipName);
    main_menu(&root , rootPlayer, championshipName);
}
