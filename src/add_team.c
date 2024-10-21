#include "../main.h"

// modifier pour etre sur que le user entre bien des int ect

Team* create_new_team() {
    Team* new_team = (Team*)malloc(sizeof(Team));
    if (new_team == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("Enter team ID: ");
    scanf("%d", &new_team->id);
    getchar();

    printf("Enter team name: ");
    fgets(new_team->name, sizeof(new_team->name), stdin);
    size_t len = strlen(new_team->name);
    if (len > 0 && new_team->name[len - 1] == '\n') {
        new_team->name[len - 1] = '\0';
    }

    printf("Enter number of trophies: ");
    scanf("%d", &new_team->trophies);

    printf("Enter number of wins: ");
    scanf("%d", &new_team->win);

    printf("Enter number of equalities: ");
    scanf("%d", &new_team->equality);

    printf("Enter number of defeats: ");
    scanf("%d", &new_team->defeat);

    new_team->left = new_team->right = NULL;
    new_team->height = 1;

    return new_team;
}

Team* insert_team(Team* node, Team* new_team) {
    if (node == NULL) {
        return new_team;
    }

    if (new_team->id < node->id) {
        node->left = insert_team(node->left, new_team);
    } else if (new_team->id > node->id) {
        node->right = insert_team(node->right, new_team);
    } else {
        printf("A team with ID %d already exists.\n", new_team->id);
        free(new_team);
        return node;
    }

    node->height = 1 + max(height_team(node->left), height_team(node->right));

    int balance = get_balance_team(node);

    if (balance > 1 && new_team->id < node->left->id)
        return right_rotate_team(node);

    if (balance < -1 && new_team->id > node->right->id)
        return left_rotate_team(node);

    if (balance > 1 && new_team->id > node->left->id) {
        node->left = left_rotate_team(node->left);
        return right_rotate_team(node);
    }

    if (balance < -1 && new_team->id < node->right->id) {
        node->right = right_rotate_team(node->right);
        return left_rotate_team(node);
    }

    return node;
}

void add_team(Team** root) {
    Team* new_team = create_new_team();
    if (new_team != NULL) {
        *root = insert_team(*root, new_team);
        printf("Team added successfully!\n");
    } else {
        printf("Failed to add team.\n");
    }
}
