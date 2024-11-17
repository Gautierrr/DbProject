/*
 * File name     : main.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : This program displays a drawing (logo of my handball club ;) and allows you to create, load, delete or view existing championships.
 */

#include "main.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\nFor usage instructions, please enter:\n");
        printf("  dbHandball help\n\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "help") == 0) {
        // program user manual
        printf("\nUsage:\n");
        printf("  dbHandball \"name of championship\"                         -> Create a championship\n");
        printf("  dbHandball \"name of championship\" \"password\"              -> Load a championship\n");
        printf("  dbHandball show                                           -> Show existing championships\n");
        printf("  dbHandball delete \"name of championship\"                  -> Delete an existing championship\n\n");
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

        // if the championship already exists it is loaded otherwise it is created
        FILE *file = fopen(filepath, "r");
        if (file) {
            fclose(file);
            if (argv[2] == NULL) {
                printf("To load the championship %s you should enter a password to decrypt this.\n", argv[1]);
                return EXIT_FAILURE;
            }
            printf("\n\nLoading championship: %s\n", argv[1]);
            
            // initialization of the roots of the binary trees
            Team* root = NULL;
            Player* rootPlayer = NULL;

            load_file(&root , &rootPlayer, argv[1], argv[2]);
        } else {
            printf("\n\nCreating new championship: %s\n", argv[1]);
            printf(
                "                                                                                                    \n"
                "                                                                                                    \n"
                "                                                                                                    \n"
                "                                                                                                    \n"
                "                                             @@@                                                    \n"
                "                                           @@@@@@@                                                  \n"
                "                                        @@@@@@@@@@@@                                                \n"
                "              *                     @@@@@@@@@@@@@@@@@@@@                     *                       \n"
                "              @@@@@           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@           @@@@@                       \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*===+@@@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:::..::@@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:.:..::+@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:::.::.:*@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:...:..+@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@::..:=@@@@@@@@@@@@@@@@@@@@@@@@@@                      \n"
                "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+-:..:.::@@@@@@@@@@*:::-*@@@@@@@@@@@                      \n"
                "              @@@@@@@@@@@@@@@@@@@@@@@*=-:::::...:..:@@@@@@@@@:..::::-@@@@@@@@@                       \n"
                "              @@@@@@@@@@@@@@@@@@@@+==---::::..:::...:-@@@@@+:::..::::@@@@@@@@@                       \n"
                "              @@@@@@@@@@@@@@@@@@+====---:::::.:::..::.:@@+::.....:::=@@@@@@@@@                       \n"
                "               @@@@@@@@@@@@@@@++++===---:::::..::...........+@@*::-@@@@@@@@@@@                       \n"
                "               @@@@@@@@@@@@@@*++++++=----::::..::..:.....:@@@@@@@@@@@@@@@@@@@                        \n"
                "               @@@@@@@@@@@@@*+++@@@@@@@@@::::..::.::...:@@@@@@@@@@@@@@@@@@@@@                        \n"
                "                @@@@@@@@@@@++*@@@@@@@@@@@-:::.:::......:@@@@@@@@@@@@@@@@@@@@                         \n"
                "                @@@@@@@@**+++@@@@@@@@@@@@+:::.:::..:...:*@@@@@@@@@@@@@@@@@@@                         \n"
                "                 @@@@@@**@@**@@@@@@@@@@@@@:::.:::......:*@@@@@@@@@@@@@@@@@@                          \n"
                "                 @@@@@@****@@@@@@@@@@@@@@@:::.:::..:....:@@@@@@@@@@@@@@@@@                           \n"
                "                  @@@@@@@@@@@@@@@@@@@@@@@@*::.:::..:......:*@@@@@@@@@@@@@@                           \n"
                "                   @@@@@@@@@@@@@@@@@@@@@@@@-:.:::........:::-@@@@@@@@@@@@                            \n"
                "                    @@@@@@@@@@@@@@@@@@@@@@@@:::::..:.....::..:@@@@@@@@@@                             \n"
                "                     @@@@@@@@@@@@@@@@@@@@@@@:.:::..:..........:@@@@@@@@@                             \n"
                "                      @@@@@@@@@@@@@@@@@@@@@@:.:::..:..........::@@@@@@                               \n"
                "                       @@@@@@@@@@@@@@@@@@@@@:.:::..:........:::.:*@@@@                               \n"
                "                        @@@@@@@@@@@@@@@@@@@@-::::......:::..:::..::::--                              \n"
                "                         @@@@@@@@@@@@@@@@@@@*::::..:..:*@@@=-:..::::::---                            \n"
                "                          @@@@@@@@@@@@@@@@@@@::::....:*@@@@@@@@:::::::---==                          \n"
                "                            @@@@@@@@@@@@@@@@@+:::....:@@@@@@@@@@=:::::----====                       \n"
                "                             @@@@@@@@@@@@@@@@@:::....-@@@+:*@@@        -======++++++                 \n"
                "                               @@@@@@@@@@@@@@@+.....::*=:.::@               ==+++++++*+              \n"
                "                                 @@@@@@@@@@@@@@-....:.....::.                  ++++++**              \n"
                "                                   @@@@@@@@@@@@@:::.....::.:::                   +++++               \n"
                "                                     @@@@@@@@@@@@:..:::   :...                                       \n"
                "                                       @@@@@@@@@@@+::     :...                                       \n"
                "                                          @@@@@@@@                                                   \n"
                "                                                                                                    \n"
                "                                                                                                    \n"
                "                                                                                                    \n"
                "                                                                                                    \n"
            );
            create_championship(argv[1]);
        }
    }

    return EXIT_SUCCESS;
}
