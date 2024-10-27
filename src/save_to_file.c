#include "../main.h"

void encrypt_file(const char *input_filepath, const char *output_filepath, const char *password) {
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, key, iv);
    
    FILE *infile = fopen(input_filepath, "rb");
    FILE *outfile = fopen(output_filepath, "wb");
    
    if (!infile || !outfile) {
        perror("File open error");
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    
    unsigned char buffer[1024];
    unsigned char ciphertext[1024 + EVP_MAX_BLOCK_LENGTH];
    int len;

    while (1) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), infile);
        if (bytes_read <= 0) break;

        EVP_EncryptUpdate(ctx, ciphertext, &len, buffer, bytes_read);
        fwrite(ciphertext, 1, len, outfile);
    }

    EVP_EncryptFinal_ex(ctx, ciphertext, &len);
    fwrite(ciphertext, 1, len, outfile);
    
    EVP_CIPHER_CTX_free(ctx);
    fclose(infile);
    fclose(outfile);
}

void save_player_to_file(Player* player, FILE* file) {
    if (player != NULL) {
        fprintf(file, "            {\n");
        fprintf(file, "                \"id\": \"%d\",\n", player->id);
        fprintf(file, "                \"name\": \"%s\",\n", player->name);
        fprintf(file, "                \"age\": %d,\n", player->age);
        fprintf(file, "                \"goals\": %d,\n", player->goals);
        fprintf(file, "                \"assists\": %d,\n", player->assists);
        fprintf(file, "                \"position\": \"%s\"\n", player->position);
        fprintf(file, "            }");
    }
}

void save_players_for_team(Player* player, const char* team_name, FILE* file, int* is_first_player) {
    if (player == NULL) return;

    save_players_for_team(player->left, team_name, file, is_first_player);

    if (strcmp(player->team, team_name) == 0) {
        if (!*is_first_player) {
            fprintf(file, ",\n");
        }
        save_player_to_file(player, file);
        *is_first_player = 0;
    }

    save_players_for_team(player->right, team_name, file, is_first_player);
}

void save_team_to_file(Team* team, Player* all_players, FILE* file) {
    if (team != NULL) {
        fprintf(file, "    {\n");
        fprintf(file, "        \"id\": %d,\n", team->id);
        fprintf(file, "        \"name\": \"%s\",\n", team->name);
        fprintf(file, "        \"trophies\": %d,\n", team->trophies);
        fprintf(file, "        \"win\": %d,\n", team->win);
        fprintf(file, "        \"equality\": %d,\n", team->equality);
        fprintf(file, "        \"defeat\": %d,\n", team->defeat);

        fprintf(file, "        \"players\": [\n");
        int is_first_player = 1;
        save_players_for_team(all_players, team->name, file, &is_first_player);
        fprintf(file, "\n        ]\n");

        fprintf(file, "    }");
    }
}

void save_teams_to_file(Team* root, Player* all_players, FILE* file, int* first_team) {
    if (root == NULL) return;

    save_teams_to_file(root->left, all_players, file, first_team);

    if (!*first_team) {
        fprintf(file, ",\n");
    } else {
        *first_team = 0;
    }

    save_team_to_file(root, all_players, file);

    save_teams_to_file(root->right, all_players, file, first_team);
}

void save_teams_and_players(Team* root, Player* all_players, const char* championship_file) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championship_file);
    char encrypted_filepath[50];
    snprintf(encrypted_filepath, sizeof(encrypted_filepath), "db/%s.json.enc", championship_file);
    
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n  \"teams\": [\n");

    int first_team = 1;
    save_teams_to_file(root, all_players, file, &first_team);

    fprintf(file, "\n  ]\n}\n");

    fclose(file);
    printf("\nTeams and players saved to %s successfully.\n", filepath);

    char password[100];
    printf("Enter a password to encrypt the file: ");
    scanf("%s", password);

    encrypt_file(filepath, encrypted_filepath, password);
    
    remove(filepath);
    printf("File encrypted and saved as '%s'.\n", encrypted_filepath);
}
