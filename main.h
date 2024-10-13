#ifndef MAIN_H
#define MAIN_H
#define PASSWORD_SIZE 50

#include "mysql/include/mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// extern MYSQL *conn;
// extern MYSQL_RES *result;
// extern MYSQL_ROW row;

void get_password(char *password, size_t size);
bool connect_to_database();
void close_database_connection();
void display_main_menu(MYSQL *conn);
void show_championship_types(MYSQL *conn);
void add_championship(MYSQL *conn);
void modify_championship(MYSQL *conn);
void delete_championship(MYSQL *conn);
void menu_select_championship();

typedef struct Player {
    char name[50];
    int goals;
    int assists;
    // autres stats
} Player;

typedef struct Team {
    char name[50];
    Player* players;
    int player_count;
} Team;

typedef struct Championship {
    boolean gender; // Vrai : Masculin ou faux : Féminin
    int category; // 1 : Enfants, 2 : Adolescents, 3 : Séniors
    int ranking; // Div 1, 2, 3 etc ...
    char region[50];
    int department; // code postal
    Team* teams;
    int team_count;
} Championship;

typedef struct Section {
    char type[50]; // National, Régional, Départemental
    Championship* championships;
} Section;

#endif
