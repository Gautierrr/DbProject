#include "../main.h"

void saveTreeToFile(Team* node, FILE* file) {
    if (node == NULL)
        return;

    fprintf(file, "%d,%s,%d,%d,%d,%d,%d\n", node->id, node->name, node->trophies, node->win, node->equality, node->defeat);
    saveTreeToFile(node->left, file);  // left subtree save
    saveTreeToFile(node->right, file); // right subtree save
}

void freeTree(Team* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void main_menu_exemple(Team* root) {
    int choice;
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Afficher l'arbre\n");
        printf("2. Sauvegarder l'arbre dans un fichier\n");
        printf("3. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAffichage de l'arbre:\n");
                displayTree(root, 0);
                break;
            case 2: {
                FILE* file = fopen("tree_data.txt", "w");
                if (file == NULL) {
                    printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
                    break;
                }
                saveTreeToFile(root, file);
                fclose(file);
                printf("Arbre sauvegardé dans 'tree_data.txt'.\n");
                break;
            }
            case 3:
                printf("Sortie du programme.\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choice != 3);
}