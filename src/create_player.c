#include "../main.h"

static int player_count = 0;

Player* create_new_player(Team* team) {
    Player* new_player = (Player*)malloc(sizeof(Player));
    if (new_player == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    player_count++;
    new_player->id = player_count;

    printf("Enter player name: ");
    fgets(new_player->name, sizeof(new_player->name), stdin);
    size_t len = strlen(new_player->name);
    if (len > 0 && new_player->name[len - 1] == '\n') {
        new_player->name[len - 1] = '\0';
    }

    printf("Enter player age: ");
    while (scanf("%d", &new_player->age) != 1) {
        printf("Invalid input. Please enter a valid player age: ");
        while (getchar() != '\n');
    }

    printf("Enter number of goals: ");
    while (scanf("%d", &new_player->goals) != 1) {
        printf("Invalid input. Please enter a valid number of goals: ");
        while (getchar() != '\n');
    }

    printf("Enter number of assists: ");
    while (scanf("%d", &new_player->assists) != 1) {
        printf("Invalid input. Please enter a valid number of assists: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Enter player position: ");
    fgets(new_player->position, sizeof(new_player->position), stdin);
    len = strlen(new_player->position);
    if (len > 0 && new_player->position[len - 1] == '\n') {
        new_player->position[len - 1] = '\0';
    }

    new_player->left = new_player->right = NULL;
    new_player->height = 1;

    return new_player;
}

Player* insert_player(Player* root, Player* new_player) {
    if (root == NULL) {
        return new_player;
    }

    if (new_player->id < root->id) {
        root->left = insert_player(root->left, new_player);
    } else if (new_player->id > root->id) {
        root->right = insert_player(root->right, new_player);
    } else {
        return root;
    }

    root->height = 1 + max(height_player(root->left), height_player(root->right));

    int balance = get_balance_player(root);

    if (balance > 1 && new_player->id < root->left->id) {
        return right_rotate_player(root);
    }
    if (balance < -1 && new_player->id > root->right->id) {
        return left_rotate_player(root);
    }
    if (balance > 1 && new_player->id > root->left->id) {
        root->left = left_rotate_player(root->left);
        return right_rotate_player(root);
    }
    if (balance < -1 && new_player->id < root->right->id) {
        root->right = right_rotate_player(root->right);
        return left_rotate_player(root);
    }

    return root;
}

void add_player_to_team(Team* team) {
    Player* new_player = create_new_player(team);
    if (new_player != NULL) {
        team->playersRoot = insert_player(team->playersRoot, new_player);
        printf("Player added successfully to team %s with ID %d\n", team->name, new_player->id);
    } else {
        printf("Failed to create player.\n");
    }
}

void add_player(Team* root) {
    getchar();
    char search_query[100];

    printf("Enter the ID or name of the team the player belongs to: ");
    fgets(search_query, sizeof(search_query), stdin);
    search_query[strcspn(search_query, "\n")] = '\0';

    Team* team = search_team(root, search_query);
    if (team != NULL) {
        add_player_to_team(team);
    } else {
        printf("Team not found.\n");
    }
}
