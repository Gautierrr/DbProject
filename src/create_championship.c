#include "../main.h"

char* championship_name() {
    char *name = malloc(20 * sizeof(char));
    if (name == NULL) {
        printf("Memory allocation error.\n");
        return NULL;
    }

    size_t len;

    do {
        printf("Please enter the name of the championship : ");
        fgets(name, 20, stdin);

        len = strlen(name);

        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        if (strlen(name) == 0) {
            printf("\nYou have not entered a name. Please try again.\n");
        }

    } while (strlen(name) == 0);

    return name;
}

int file_exist(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;  // file already exist
    }
    return 0;
}

void create_json_file(char **name_ptr) {
    const char *directory = "db";
    char filepath[30];

    // db/name.json
    snprintf(filepath, sizeof(filepath), "%s/%s.json", directory, *name_ptr);

    while (file_exist(filepath)) {
        printf("File '%s' already exists. Please choose a different name.\n", filepath);
        
        free(*name_ptr);
        *name_ptr = championship_name();
        
        snprintf(filepath, sizeof(filepath), "%s/%s.json", directory, *name_ptr);
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error creating file '%s'.\n", filepath);
        return;
    }

    fprintf(file, "{\n\t\"championship\": \"%s\"\n}\n", *name_ptr);

    fclose(file);

    printf("File '%s' created successfully.\n", filepath);
}

int create_championship() {
    char *name = championship_name();
    Team* root = NULL;
    
    if (name != NULL) {
        create_json_file(&name);

        free(name);

        main_menu(&root);
    }

    return 0;
}
