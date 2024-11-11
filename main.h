#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "cJSON.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct Player {
    size_t id;
    char name[20];
    char team[30];
    size_t age;
    size_t goals;
    size_t assists;
    char position[10];
    struct Player* left;
    struct Player* right;
    size_t height;
} Player;

typedef struct Team {
    size_t id;
    char name[30];
    size_t trophies;
    size_t win;
    size_t equality;
    size_t defeat;
    struct Team* left;
    struct Team* right;
    size_t height;
} Team;

int max(size_t a, size_t b);
extern size_t teamCount;
extern size_t playerCount;

// championship
void create_championship(const char *championshipName);
void show_championships();
void delete_championship(const char *championshipName);
void main_menu(Team** root, Player* rootPlayer, const char* championshipName);
int file_exist(const char *filepath);

// team
int height_team(Team* n);
Team* create_new_team();
Team* insert_team(Team* node, Team* newTeam);
void add_team(Team** root);
Team* right_rotate_team(Team* y);
Team* left_rotate_team(Team* x);
int get_balance_team(Team* n);
void display_team_tree(Team* root, size_t space);
Team* search_team(Team* root, const char* query);
void delete_team(Team** root);
void edit_team(Team** root);
void show_team(Team** root);

// player
void menu_player(Team** root, Player* rootPlayer, const char* championshipName);
void add_player(Player** root, Team* rootTeam);
int height_player(Player* n);
Player* right_rotate_player(Player* y);
Player* left_rotate_player(Player* x);
int get_balance_player(Player* n);
Player* search_player(Player* root, const char* query);
void show_player(Player** root);
void delete_player(Player** root);
void edit_player(Player** root, Team* rootTeam);
void display_player_tree(Player* root, size_t space);
Player* insert_player(Player* node, Player* newPlayer);




// save & load
void encrypt_or_decrypt(const char *inputFilepath, const char *outputFilepath, const char *password, const size_t value);
void save_all(Team* root, Player* allPlayers, const char* championshipName);
void load_file(Team** rootTeam, Player** rootPlayer, const char* championshipName, const char* password);


#endif
