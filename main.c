#include "main.h"

int main(int argc, char *argv[]) {
    // ne pas oublier de modif le main.exe dans les aides avec le vrai nom du programme
    if (argc < 2) {
        printf("For usage instructions, please enter:\n");
        printf("  main.exe help\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "help") == 0) {
        printf("Usage:\n");
        printf("  main.exe \"nameChampionship\"            -> Create/load a championship\n");
        printf("  main.exe show                          -> Show existing championships\n");
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
        create_championship(argv[1]);
    }

    return EXIT_SUCCESS;
}
