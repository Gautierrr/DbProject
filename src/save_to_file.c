#include "../main.h"

void encrypt_file(const char *inputFilepath, const char *outputFilepath, const char *password) {
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, key, iv);
    
    FILE *infile = fopen(inputFilepath, "rb");
    FILE *outfile = fopen(outputFilepath, "wb");
    
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
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), infile);
        if (bytesRead <= 0) break;

        EVP_EncryptUpdate(ctx, ciphertext, &len, buffer, bytesRead);
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

void save_players_for_team(Player* player, const char* teamName, FILE* file, int* firstPlayer) {
    if (player == NULL) return;

    save_players_for_team(player->left, teamName, file, firstPlayer);

    if (strcmp(player->team, teamName) == 0) {
        if (!*firstPlayer) {
            fprintf(file, ",\n");
        }
        save_player_to_file(player, file);
        *firstPlayer = 0;
    }

    save_players_for_team(player->right, teamName, file, firstPlayer);
}

void save_team_to_file(Team* team, Player* allPlayers, FILE* file) {
    if (team != NULL) {
        fprintf(file, "    {\n");
        fprintf(file, "        \"id\": %d,\n", team->id);
        fprintf(file, "        \"name\": \"%s\",\n", team->name);
        fprintf(file, "        \"trophies\": %d,\n", team->trophies);
        fprintf(file, "        \"win\": %d,\n", team->win);
        fprintf(file, "        \"equality\": %d,\n", team->equality);
        fprintf(file, "        \"defeat\": %d,\n", team->defeat);

        fprintf(file, "        \"players\": [\n");
        int firstPlayer = 1;
        save_players_for_team(allPlayers, team->name, file, &firstPlayer);
        fprintf(file, "\n        ]\n");

        fprintf(file, "    }");
    }
}

void save_teams_to_file(Team* root, Player* allPlayers, FILE* file, int* firstTeam) {
    if (root == NULL) return;

    save_teams_to_file(root->left, allPlayers, file, firstTeam);

    if (!*firstTeam) {
        fprintf(file, ",\n");
    } else {
        *firstTeam = 0;
    }

    save_team_to_file(root, allPlayers, file);

    save_teams_to_file(root->right, allPlayers, file, firstTeam);
}

void save_teams_and_players(Team* root, Player* allPlayers, const char* championshipName) {
    char filepath[50];
    snprintf(filepath, sizeof(filepath), "db/%s.json", championshipName);
    char encryptedFilepath[50];
    snprintf(encryptedFilepath, sizeof(encryptedFilepath), "db/%s.json.enc", championshipName);
    
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filepath);
        return;
    }

    fprintf(file, "{\n  \"teams\": [\n");

    int firstTeam = 1;
    save_teams_to_file(root, allPlayers, file, &firstTeam);

    fprintf(file, "\n  ]\n}\n");

    fclose(file);
    printf("\nTeams and players saved to %s successfully.\n", filepath);

    char password[20];
    printf("Enter a password to encrypt the file: ");
    scanf("%s", password);

    encrypt_file(filepath, encryptedFilepath, password);
    
    remove(filepath);
    printf("File encrypted and saved as '%s'.\n", encryptedFilepath);
}
