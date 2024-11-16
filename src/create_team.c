/*
 * File name     : create_team.c
 * Author        : Gautier Vauloup
 * Date          : November 16, 2024
 * Description   : Program to create a team and insert it into the binary tree while balancing it.
 */

#include "../main.h"

// checks if the team name entered by the user already exists
int check_team_name(Team* node, const char* name) {
    if (node == NULL) {
        return 0;
    }

    if (strcmp(name, node->name) == 0) {
        return 1;
    } 
    
    if (check_team_name(node->left, name) || check_team_name(node->right, name)) {
        return 1;
    }

    return 0;
}

size_t teamCount = 0;

Team* create_new_team(Team* root) {
    getchar();
    char name[50];

    printf("Enter team name: ");
    fgets(name, sizeof(name), stdin);
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    }

    if (check_team_name(root, name)) {
        printf("Failed to create team: name already exists.\n\n");
        return NULL;
    }

    // allocates the memory needed to create a team, based on the size of the Team structure
    Team* newTeam = (Team*)malloc(sizeof(Team));
    if (newTeam == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // increment a counter to keep a unique id for each team
    teamCount++;
    newTeam->id = teamCount;
    strcpy(newTeam->name, name);

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

Team* insert_team(Team* node, Team* newTeam) {
    if (node == NULL) {
        return newTeam;
    }

    // determines where to insert the new node based on the value of its id
    if (newTeam->id < node->id) {
        node->left = insert_team(node->left, newTeam);
    } else if (newTeam->id > node->id) {
        node->right = insert_team(node->right, newTeam);
    } else {
        return node;
    }

    // the rest of the function allows to rebalance the tree after adding the new node by performing single or double rotations of the nodes to the right or left

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
    Team* newTeam = create_new_team(*root);
    if (newTeam != NULL) {
        *root = insert_team(*root, newTeam);
        printf("Team added successfully!\n\n");
    } else {
        printf("Failed to add team.\n\n");
    }
}
