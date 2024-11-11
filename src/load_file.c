#include "../main.h"

Team* create_team_node(int id, const char* name, int trophies, int win, int equality, int defeat) {
    Team* team = (Team*)malloc(sizeof(Team));
    team->id = id;
    strncpy(team->name, name, sizeof(team->name) - 1);
    team->name[sizeof(team->name) - 1] = '\0';
    team->trophies = trophies;
    team->win = win;
    team->equality = equality;
    team->defeat = defeat;
    team->left = team->right = NULL;
    team->height = 1;
    return team;
}

Player* create_player_node(int id, const char* name, int age, int goals, int assists, const char* position, const char* team_name) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->id = id;
    strncpy(player->name, name, sizeof(player->name) - 1);
    player->name[sizeof(player->name) - 1] = '\0';
    player->age = age;
    player->goals = goals;
    player->assists = assists;
    strncpy(player->position, position, sizeof(player->position) - 1);
    player->position[sizeof(player->position) - 1] = '\0';
    strncpy(player->team, team_name, sizeof(player->team) - 1);
    player->team[sizeof(player->team) - 1] = '\0';
    player->left = player->right = NULL;
    player->height = 1;  
    return player;
}

void load_file(Team** rootTeam, Player** rootPlayer, const char* championshipName, const char* password) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json.enc", championshipName);
    char decryptedFilepath[50];
    snprintf(decryptedFilepath, sizeof(decryptedFilepath), "db/%s_decrypted.json", championshipName);

    encrypt_or_decrypt(filepath, decryptedFilepath, password, 2);

    FILE* file = fopen(decryptedFilepath, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", decryptedFilepath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* jsonData = (char*)malloc(fileSize + 1);
    fread(jsonData, 1, fileSize, file);
    fclose(file);

    jsonData[fileSize] = '\0';

    cJSON* rootJson = cJSON_Parse(jsonData);
    if (rootJson == NULL) {
        printf("Error parsing JSON\n");
        free(jsonData);
        return;
    }

    cJSON* teamsJson = cJSON_GetObjectItem(rootJson, "teams");
    if (!cJSON_IsArray(teamsJson)) {
        printf("Error: 'teams' is not a valid JSON array\n");
        cJSON_Delete(rootJson);
        free(jsonData);
        return;
    }

    int maxTeamId = 0;
    int maxPlayerId = 0;
    cJSON* teamJson;

    cJSON_ArrayForEach(teamJson, teamsJson) {
        int id = cJSON_GetObjectItem(teamJson, "id")->valueint;
        if (id > maxTeamId) {
            maxTeamId = id;
        }
        const char* name = cJSON_GetObjectItem(teamJson, "name")->valuestring;
        int trophies = cJSON_GetObjectItem(teamJson, "trophies")->valueint;
        int win = cJSON_GetObjectItem(teamJson, "win")->valueint;
        int equality = cJSON_GetObjectItem(teamJson, "equality")->valueint;
        int defeat = cJSON_GetObjectItem(teamJson, "defeat")->valueint;

        Team* team = create_team_node(id, name, trophies, win, equality, defeat);
        *rootTeam = insert_team(*rootTeam, team);

        cJSON* playersJson = cJSON_GetObjectItem(teamJson, "players");
        if (cJSON_IsArray(playersJson)) {
            cJSON* playerJson;
            cJSON_ArrayForEach(playerJson, playersJson) {
                int playerId = atoi(cJSON_GetObjectItem(playerJson, "id")->valuestring);
                const char* playerName = cJSON_GetObjectItem(playerJson, "name")->valuestring;
                int age = cJSON_GetObjectItem(playerJson, "age")->valueint;
                int goals = cJSON_GetObjectItem(playerJson, "goals")->valueint;
                int assists = cJSON_GetObjectItem(playerJson, "assists")->valueint;
                const char* position = cJSON_GetObjectItem(playerJson, "position")->valuestring;

                if (playerId > maxPlayerId) {
                    maxPlayerId = playerId;
                }

                Player* player = create_player_node(playerId, playerName, age, goals, assists, position, name);
                *rootPlayer = insert_player(*rootPlayer, player);
            }
        }
    }

    cJSON_Delete(rootJson);
    free(jsonData);
    printf("Teams and players have been successfully loaded from %s.\n", decryptedFilepath);

    teamCount = maxTeamId;
    playerCount = maxPlayerId;

    remove(decryptedFilepath);

    main_menu(rootTeam, *rootPlayer, championshipName);
}
