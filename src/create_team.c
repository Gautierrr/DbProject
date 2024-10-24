#include "../main.h"

static int team_count = 0;

Team* create_new_team() {
    Team* new_team = (Team*)malloc(sizeof(Team));
    if (new_team == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    team_count++;
    new_team->id = team_count; // unique id
    new_team->playerCount = 0;
    new_team->playersRoot = NULL;

    getchar();
    printf("Enter team name: ");
    fgets(new_team->name, sizeof(new_team->name), stdin);
    size_t len = strlen(new_team->name);
    if (len > 0 && new_team->name[len - 1] == '\n') {
        new_team->name[len - 1] = '\0';
    }

    printf("Enter number of trophies: ");
    while (scanf("%d", &new_team->trophies) != 1) {
        printf("Invalid input. Please enter a valid number of trophies : ");
        while (getchar() != '\n');
    }

    printf("Enter number of wins: ");
    while (scanf("%d", &new_team->win) != 1) {
        printf("Invalid input. Please enter a valid number of wins : ");
        while (getchar() != '\n');
    }

    printf("Enter number of equalities: ");
    while (scanf("%d", &new_team->equality) != 1) {
        printf("Invalid input. Please enter a valid number of equalities : ");
        while (getchar() != '\n');
    }

    printf("Enter number of defeats: ");
    while (scanf("%d", &new_team->defeat) != 1) {
        printf("Invalid input. Please enter a valid number of defeats : ");
        while (getchar() != '\n');
    }

    new_team->left = new_team->right = NULL;
    new_team->height = 1;

    return new_team;
}

int check_id(Team* node, int id) {
    if (node == NULL) {
        return 0;
    }

    if (id == node->id) {
        return 1;  // id already exist
    } else if (id < node->id) {
        return check_id(node->left, id);
    } else {
        return check_id(node->right, id);
    }
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

Team* insert_team(Team* node, Team* new_team) {
    if (node == NULL) {
        return new_team;
    }

    if (new_team->id < node->id) {
        node->left = insert_team(node->left, new_team);
    } else if (new_team->id > node->id) {
        node->right = insert_team(node->right, new_team);
    } else {
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
        int id = check_id(*root, new_team->id);
        int name = check_name(*root, new_team->name);
        
        if (id == 0 && name == 0) {
            *root = insert_team(*root, new_team);
            printf("Team added successfully!\n");
        } else {
            if (id) {
                printf("Failed to add team: ID already exist.\n");
            }
            
            if (name) {
                printf("Failed to add team: Name already exist.\n");
            }
            free(new_team);
        }
    } else {
        printf("Failed to create team.\n");
    }
}
