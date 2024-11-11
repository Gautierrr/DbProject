#include "../main.h"

size_t teamCount = 0;

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

    int16_t temp;

    printf("Enter number of trophies: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of trophies: ");
        while (getchar() != '\n');
    }
    newTeam->trophies = (size_t)temp;

    printf("Enter number of wins: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of wins: ");
        while (getchar() != '\n');
    }
    newTeam->win = (size_t)temp;

    printf("Enter number of equalities: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of equalities: ");
        while (getchar() != '\n');
    }
    newTeam->equality = (size_t)temp;

    printf("Enter number of defeats: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of defeats: ");
        while (getchar() != '\n');
    }
    newTeam->defeat = (size_t)temp;

    newTeam->left = newTeam->right = NULL;
    newTeam->height = 1;

    return newTeam;
}

int check_team_name(Team* node, const char* name) {
    if (node == NULL) {
        return 0;
    }

    if (strcmp(name, node->name) == 0) {
        return 1;  // name already exist
    } 
    
    if (check_team_name(node->left, name) || check_team_name(node->right, name)) {
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

    int8_t balance = get_balance_team(node);

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
        int8_t name = check_team_name(*root, newTeam->name);
        
        if (name == 0) {
            *root = insert_team(*root, newTeam);
            printf("Team added successfully!\n\n");
        } else {
            printf("Failed to add team: name already exist.\n\n");
            free(newTeam);
        }
    } else {
        printf("Failed to create team.\n\n");
    }
}
