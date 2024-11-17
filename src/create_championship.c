/*
 * File name     : create_championship.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : This program creates a new json file with the name of the new championship.
 */

#include "../main.h"

// create a json save file with the championship name entered by the user
void create_json_file(const char *championshipName) {
    const char *directory = "db";
    char filepath[30];

    // file path in the form : db/"name of championship".json
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
    // initialization of the roots of the binary trees
    Team* root = NULL;
    Player* rootPlayer = NULL;

    create_json_file(championshipName);
    main_menu(&root , rootPlayer, championshipName);
}
