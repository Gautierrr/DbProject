#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Championship {
    char name[20];
} Championship;

typedef struct Player {
    char id[10];
    char name[20];
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
    int playerCount;
    struct Player* playersRoot;
    struct Team* left;
    struct Team* right;
    int height;
} Team;

// typedef struct Node {
//     int type; // 1 = championship, 2 = team, 3 = player
//     union {
//         Championship championship;
//         Team team;
//         Player player;
//     };
//     struct Node* left;
//     struct Node* right;
// } Node;

int max(int a, int b);

// championship
char* championship_name();
int file_exist(const char *filepath);
void create_json_file(char **name);
int create_championship();
void main_menu(Team** root, const char* championship_file);

// team
int height_team(Team* n);
Team* create_new_team();
Team* insert_team(Team* node, Team* new_team);
void add_team(Team** root);
Team* right_rotate_team(Team* y);
Team* left_rotate_team(Team* x);
int get_balance_team(Team* n);
void displayTree(Team* root, int space);
Team* search_team(Team* root, const char* query);
void delete_team(Team** root);
void edit_team(Team** root);

// player
void menu_player(Team** root, const char* championship_file);
void add_player(Team* root);
int height_player(Player* n);
Player* right_rotate_player(Player* y);
Player* left_rotate_player(Player* x);
int get_balance_player(Player* n);




// save
void save_binary_tree(Team* root, const char* file);

#endif
