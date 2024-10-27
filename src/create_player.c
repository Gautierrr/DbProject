#include "../main.h"

int player_count = 0;

Player* create_new_player(Team* rootTeam) {
    Player* new_player = (Player*)malloc(sizeof(Player));
    if (new_player == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    getchar();

    printf("Enter the name of the team the player belongs to : ");
    fgets(new_player->team, sizeof(new_player->team), stdin);
    size_t len = strlen(new_player->team);
    if (len > 0 && new_player->team[len - 1] == '\n') {
        new_player->team[len - 1] = '\0';
    }

    char* endptr;
    strtol(new_player->team, &endptr, 10);
    if (*endptr == '\0' && endptr != new_player->team) {
        printf("Error: The team name cannot be a number. Please enter a valid name.\n");
        free(new_player);
        return NULL;
    }

    if (search_team(rootTeam, new_player->team) == NULL) {
        printf("Team does not exist. Player not created.\n");
        free(new_player);
        return NULL;
    }

    player_count++;
    new_player->id = player_count;

    printf("Enter player name: ");
    fgets(new_player->name, sizeof(new_player->name), stdin);
    len = strlen(new_player->name);
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

int check_player_name(Player* node, const char* name) {
    if (node == NULL) {
        return 0;
    }

    if (strcmp(name, node->name) == 0) {
        return 1;
    } 
    
    if (check_player_name(node->left, name) || check_player_name(node->right, name)) {
        return 1;
    }

    return 0;
}

Player* insert_player(Player* node, Player* new_player) {
    if (node == NULL) {
        return new_player;
    }

    if (new_player->id < node->id) {
        node->left = insert_player(node->left, new_player);
    } else if (new_player->id > node->id) {
        node->right = insert_player(node->right, new_player);
    } else {
        return node;
    }

    node->height = 1 + max(height_player(node->left), height_player(node->right));

    int balance = get_balance_player(node);

    if (balance > 1 && new_player->id < node->left->id)
        return right_rotate_player(node);

    if (balance < -1 && new_player->id > node->right->id)
        return left_rotate_player(node);

    if (balance > 1 && new_player->id > node->left->id) {
        node->left = left_rotate_player(node->left);
        return right_rotate_player(node);
    }

    if (balance < -1 && new_player->id < node->right->id) {
        node->right = right_rotate_player(node->right);
        return left_rotate_player(node);
    }

    return node;
}

void add_player(Player** root, Team* rootTeam) {
    Player* new_player = create_new_player(rootTeam);
    if (new_player != NULL) {
        int name_exists = check_player_name(*root, new_player->name);
        
        if (name_exists == 0) {
            *root = insert_player(*root, new_player);
            printf("Player added successfully!\n");
        } else {
            printf("Failed to add player: Name already exists.\n");
            player_count--;
            free(new_player);
        }
    } else {
        printf("Failed to create player.\n");
    }
}
