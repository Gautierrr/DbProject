#include "../main.h"

int teamCount = 0;

Team* create_new_team() {
    Team* newTeam = (Team*)malloc(sizeof(Team));
    if (newTeam == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    teamCount++;
    newTeam->id = teamCount; // unique id

    getchar();
    printf("Enter team name: ");
    fgets(newTeam->name, sizeof(newTeam->name), stdin);
    size_t len = strlen(newTeam->name);
    if (len > 0 && newTeam->name[len - 1] == '\n') {
        newTeam->name[len - 1] = '\0';
    }

    printf("Enter number of trophies: ");
    while (scanf("%d", &newTeam->trophies) != 1) {
        printf("Invalid input. Please enter a valid number of trophies : ");
        while (getchar() != '\n');
    }

    printf("Enter number of wins: ");
    while (scanf("%d", &newTeam->win) != 1) {
        printf("Invalid input. Please enter a valid number of wins : ");
        while (getchar() != '\n');
    }

    printf("Enter number of equalities: ");
    while (scanf("%d", &newTeam->equality) != 1) {
        printf("Invalid input. Please enter a valid number of equalities : ");
        while (getchar() != '\n');
    }

    printf("Enter number of defeats: ");
    while (scanf("%d", &newTeam->defeat) != 1) {
        printf("Invalid input. Please enter a valid number of defeats : ");
        while (getchar() != '\n');
    }

    newTeam->left = newTeam->right = NULL;
    newTeam->height = 1;

    return newTeam;
}

int check_name(Team* node, const char* name) {
    if (node == NULL) {
        return 0;
    }

    if (strcmp(name, node->name) == 0) {
        return 1;  // name already exist
    } 
    
    if (check_name(node->left, name) || check_name(node->right, name)) {
        return 1;
    }

    return 0;
}

Team* insert_team(Team* node, Team* newTeam) {
    if (node == NULL) {
        return newTeam;
    }

    if (newTeam->id < node->id) {
        node->left = insert_team(node->left, newTeam);
    } else if (newTeam->id > node->id) {
        node->right = insert_team(node->right, newTeam);
    } else {
        return node;
    }

    node->height = 1 + max(height_team(node->left), height_team(node->right));

    int balance = get_balance_team(node);

    if (balance > 1 && newTeam->id < node->left->id)
        return right_rotate_team(node);

    if (balance < -1 && newTeam->id > node->right->id)
        return left_rotate_team(node);

    if (balance > 1 && newTeam->id > node->left->id) {
        node->left = left_rotate_team(node->left);
        return right_rotate_team(node);
    }

    if (balance < -1 && newTeam->id < node->right->id) {
        node->right = right_rotate_team(node->right);
        return left_rotate_team(node);
    }

    return node;
}

void add_team(Team** root) {
    Team* newTeam = create_new_team();
    if (newTeam != NULL) {
        int name = check_name(*root, newTeam->name);
        
        if (name == 0) {
            *root = insert_team(*root, newTeam);
            printf("Team added successfully!\n");
        } else {
            printf("Failed to add team: Name already exist.\n");
            free(newTeam);
        }
    } else {
        printf("Failed to create team.\n");
    }
}
