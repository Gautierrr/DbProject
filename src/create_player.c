#include "../main.h"

size_t playerCount = 0;

Player* create_new_player(Team* rootTeam) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    getchar();

    printf("Enter the name of the team the player belongs to: ");
    fgets(newPlayer->team, sizeof(newPlayer->team), stdin);
    size_t len = strlen(newPlayer->team);
    if (len > 0 && newPlayer->team[len - 1] == '\n') {
        newPlayer->team[len - 1] = '\0';
    }

    char* notNb;
    strtol(newPlayer->team, &notNb, 10);
    if (*notNb == '\0' && notNb != newPlayer->team) {
        printf("Error: the team name cannot be a number. Please enter a valid name.\n");
        free(newPlayer);
        return NULL;
    }

    if (search_team(rootTeam, newPlayer->team) == NULL) {
        printf("Team does not exist. Player not created.\n");
        free(newPlayer);
        return NULL;
    }

    playerCount++;
    newPlayer->id = playerCount;

    printf("Enter player name: ");
    fgets(newPlayer->name, sizeof(newPlayer->name), stdin);
    len = strlen(newPlayer->name);
    if (len > 0 && newPlayer->name[len - 1] == '\n') {
        newPlayer->name[len - 1] = '\0';
    }

    int16_t temp;

    printf("Enter player age: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative player age: ");
        while (getchar() != '\n');
    }
    newPlayer->age = (size_t)temp;

    printf("Enter number of goals: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of goals: ");
        while (getchar() != '\n');
    }
    newPlayer->goals = (size_t)temp;

    printf("Enter number of assists: ");
    while (scanf("%d", &temp) != 1 || temp < 0) {
        printf("Invalid input. Please enter a valid non-negative number of assists: ");
        while (getchar() != '\n');
    }
    newPlayer->assists = (size_t)temp;
    getchar();

    printf("Enter player position: ");
    fgets(newPlayer->position, sizeof(newPlayer->position), stdin);
    len = strlen(newPlayer->position);
    if (len > 0 && newPlayer->position[len - 1] == '\n') {
        newPlayer->position[len - 1] = '\0';
    }

    newPlayer->left = newPlayer->right = NULL;
    newPlayer->height = 1;

    return newPlayer;
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

Player* insert_player(Player* node, Player* newPlayer) {
    if (node == NULL) {
        return newPlayer;
    }

    if (newPlayer->id < node->id) {
        node->left = insert_player(node->left, newPlayer);
    } else if (newPlayer->id > node->id) {
        node->right = insert_player(node->right, newPlayer);
    } else {
        return node;
    }

    node->height = 1 + max(height_player(node->left), height_player(node->right));

    int8_t balance = get_balance_player(node);

    if (balance > 1 && newPlayer->id < node->left->id)
        return right_rotate_player(node);

    if (balance < -1 && newPlayer->id > node->right->id)
        return left_rotate_player(node);

    if (balance > 1 && newPlayer->id > node->left->id) {
        node->left = left_rotate_player(node->left);
        return right_rotate_player(node);
    }

    if (balance < -1 && newPlayer->id < node->right->id) {
        node->right = right_rotate_player(node->right);
        return left_rotate_player(node);
    }

    return node;
}

void add_player(Player** root, Team* rootTeam) {
    Player* newPlayer = create_new_player(rootTeam);
    if (newPlayer != NULL) {
        int8_t nameExist = check_player_name(*root, newPlayer->name);
        
        if (nameExist == 0) {
            *root = insert_player(*root, newPlayer);
            printf("Player added successfully!\n\n");
        } else {
            printf("Failed to add player: name already exists.\n\n");
            playerCount--;
            free(newPlayer);
        }
    } else {
        printf("Failed to create player.\n\n");
    }
}
