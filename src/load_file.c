#include "../main.h"

void decrypt_file(const char *input_filepath, const char *output_filepath, const char *password) {
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, key, iv);
    
    FILE *infile = fopen(input_filepath, "rb");
    FILE *outfile = fopen(output_filepath, "wb");
    
    if (!infile || !outfile) {
        perror("File open error");
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    
    unsigned char buffer[1024];
    unsigned char plaintext[1024 + EVP_MAX_BLOCK_LENGTH];
    int len;

    while (1) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), infile);
        if (bytes_read <= 0) break;

        EVP_DecryptUpdate(ctx, plaintext, &len, buffer, bytes_read);
        fwrite(plaintext, 1, len, outfile);
    }

    EVP_DecryptFinal_ex(ctx, plaintext, &len);
    fwrite(plaintext, 1, len, outfile);
    
    EVP_CIPHER_CTX_free(ctx);
    fclose(infile);
    fclose(outfile);
}

Team* create_team_node(int id, const char* name, int trophies, int win, int equality, int defeat) {
    Team* team = (Team*)malloc(sizeof(Team));
    team->id = id;
    strncpy(team->name, name, sizeof(team->name));
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
    strncpy(player->name, name, sizeof(player->name));
    player->age = age;
    player->goals = goals;
    player->assists = assists;
    strncpy(player->position, position, sizeof(player->position));
    strncpy(player->team, team_name, sizeof(player->team));
    player->left = player->right = NULL;
    player->height = 1;  
    return player;
}

void load_file(Team** root_team, Player** root_player, const char* filename) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json.enc", filename);
    char decrypted_filepath[50];
    snprintf(decrypted_filepath, sizeof(decrypted_filepath), "db/%s_decrypted.json", filename);

    char password[100];
    printf("Enter password to decrypt the file: ");
    scanf("%s", password);

    decrypt_file(filepath, decrypted_filepath, password);

    FILE* file = fopen(decrypted_filepath, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", decrypted_filepath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* json_data = (char*)malloc(file_size + 1);
    fread(json_data, 1, file_size, file);
    fclose(file);

    json_data[file_size] = '\0';

    cJSON* root_json = cJSON_Parse(json_data);
    if (root_json == NULL) {
        printf("Error parsing JSON\n");
        free(json_data);
        return;
    }

    cJSON* teams_json = cJSON_GetObjectItem(root_json, "teams");
    if (!cJSON_IsArray(teams_json)) {
        printf("Error: 'teams' is not a valid JSON array\n");
        cJSON_Delete(root_json);
        free(json_data);
        return;
    }

    int max_team_id = 0;
    int max_player_id = 0;
    cJSON* team_json;
    cJSON* player_json;

    cJSON_ArrayForEach(team_json, teams_json) {
        int id = cJSON_GetObjectItem(team_json, "id")->valueint;
        if (id > max_team_id) {
            max_team_id = id;
        }
        const char* name = cJSON_GetObjectItem(team_json, "name")->valuestring;
        int trophies = cJSON_GetObjectItem(team_json, "trophies")->valueint;
        int win = cJSON_GetObjectItem(team_json, "win")->valueint;
        int equality = cJSON_GetObjectItem(team_json, "equality")->valueint;
        int defeat = cJSON_GetObjectItem(team_json, "defeat")->valueint;

        Team* team = create_team_node(id, name, trophies, win, equality, defeat);
        *root_team = insert_team(*root_team, team);

        cJSON* players_json = cJSON_GetObjectItem(team_json, "players");
        if (cJSON_IsArray(players_json)) {
            cJSON* player_json;
            cJSON_ArrayForEach(player_json, players_json) {
                int player_id = atoi(cJSON_GetObjectItem(player_json, "id")->valuestring);
                const char* player_name = cJSON_GetObjectItem(player_json, "name")->valuestring;
                int age = cJSON_GetObjectItem(player_json, "age")->valueint;
                int goals = cJSON_GetObjectItem(player_json, "goals")->valueint;
                int assists = cJSON_GetObjectItem(player_json, "assists")->valueint;
                const char* position = cJSON_GetObjectItem(player_json, "position")->valuestring;

                if (player_id > max_player_id) {
                    max_player_id = player_id;
                }

                Player* player = create_player_node(player_id, player_name, age, goals, assists, position, name);
                *root_player = insert_player(*root_player, player);
            }
        }
    }

    cJSON_Delete(root_json);
    free(json_data);
    printf("Teams and players have been successfully loaded from %s.\n", decrypted_filepath);

    team_count = max_team_id;
    player_count = max_player_id;

    remove(decrypted_filepath);

    main_menu(root_team, *root_player, filename);
}
