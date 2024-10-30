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

typedef struct Championship {
    char name[20];
} Championship;

typedef struct Player {
    int id;
    char name[20];
    char team[30];
    int age;
    int goals;
    int assists;
    char position[10];
    struct Player* left;
    struct Player* right;
    int height;
} Player;

typedef struct Team {
    int id;
    char name[30];
    int trophies;
    int win;
    int equality;
    int defeat;
    struct Team* left;
    struct Team* right;
    int height;
} Team;

int max(int a, int b);
extern int team_count;
extern int player_count;

// championship
void create_championship(const char *championshipName);
void show_championships();
void delete_championship(const char *championshipName);
void main_menu(Team** root, Player* rootPlayer, const char* championship_file);
int file_exist(const char *filepath);

// team
int height_team(Team* n);
Team* create_new_team();
Team* insert_team(Team* node, Team* new_team);
void add_team(Team** root);
Team* right_rotate_team(Team* y);
Team* left_rotate_team(Team* x);
int get_balance_team(Team* n);
void displayTeamTree(Team* root, int space);
Team* search_team(Team* root, const char* query);
void delete_team(Team** root);
void edit_team(Team** root);
void show_team(Team** root);
Team* insert_team(Team* node, Team* new_team);

// player
void menu_player(Team** root, Player* rootPlayer, const char* championship_file);
void add_player(Player** root, Team* rootTeam);
int height_player(Player* n);
Player* right_rotate_player(Player* y);
Player* left_rotate_player(Player* x);
int get_balance_player(Player* n);
Player* search_player(Player* root, const char* query);
void show_player(Player** root);
void delete_player(Player** root);
void edit_player(Player** root, Team* rootTeam);
void displayPlayerTree(Player* root, int space);
Player* insert_player(Player* node, Player* new_player);




// save & load
void save_teams_and_players(Team* root, Player* all_players, const char* championship_file);
void load_file(Team** root_team, Player** root_player, const char* filename, const char* password);


#endif
