#include "../main.h"

int insert_exemple() {
    Team* root = NULL;

    root = insertTeam(root, 30, "Team A", 5, 10, 2, 3);
    root = insertTeam(root, 20, "Team B", 3, 8, 5, 2);
    root = insertTeam(root, 40, "Team C", 10, 12, 6, 2);
    root = insertTeam(root, 10, "Team D", 1, 4, 2, 5);
    root = insertTeam(root, 25, "Team E", 4, 6, 1, 3);
    root = insertTeam(root, 35, "Team F", 7, 9, 3, 3);
    root = insertTeam(root, 50, "Team G", 12, 15, 5, 2);

    main_menu_exemple(root);

    freeTree(root);

    return 0;
}