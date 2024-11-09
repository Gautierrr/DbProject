#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("For usage instructions, please enter:\n");
        printf("  main.exe help\n"); // update avec le nom définitif de main.exe
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "help") == 0) {
        printf("Usage:\n");
        printf("  main.exe \"nameChampionship\"            -> Create/load a championship\n"); // update le help avec le password a mettre pour load un file
        printf("  main.exe show                          -> Show existing championships\n"); // update avec le nom définitif de main.exe
        printf("  main.exe delete \"nameChampionship\"     -> Delete an existing championship\n");
    } else if (strcmp(argv[1], "show") == 0) {
        show_championships();
    } else if (strcmp(argv[1], "delete") == 0) {
        if (argc < 3) {
            printf("Please specify the championship to delete.\n");
            return EXIT_FAILURE;
        }
        delete_championship(argv[2]);
    } else {
        char filepath[50];
        snprintf(filepath, sizeof(filepath), "db/%s.json.enc", argv[1]);

        FILE *file = fopen(filepath, "r");
        if (file) {
            fclose(file);
            if (argv[2] == NULL) {
                printf("To load the championship %s you should enter a password to decrypt this.\n", argv[1]); // refaire la phrase
                return EXIT_FAILURE;
            }
            printf("\nLoading championship: %s\n", argv[1]);
            
            Team* root = NULL;
            Player* rootPlayer = NULL;

            load_file(&root , &rootPlayer, argv[1], argv[2]);
        } else {
            printf("\nCreating new championship: %s\n", argv[1]);
            create_championship(argv[1]);
        }
    }

    return EXIT_SUCCESS;
}
