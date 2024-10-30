#include "../main.h"

int file_exist(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void create_json_file(const char *championshipName) {
    const char *directory = "db";
    char filepath[30];

    // db/name.json
    snprintf(filepath, sizeof(filepath), "%s/%s.json", directory, championshipName);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error creating file '%s'.\n", filepath);
        return;
    }

    fprintf(file, "{\n\t\"championship\": \"%s\"\n}\n", championshipName);

    fclose(file);
}


void create_championship(const char *championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championshipName);

    Team* root = NULL;
    Player* rootPlayer = NULL;

    create_json_file(championshipName);
    main_menu(&root , rootPlayer, championshipName);
}
