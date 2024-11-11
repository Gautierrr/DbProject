CC = gcc

CFLAGS = -g -Wall

EXEC = database

SRC = main.c \
      src/show_championships.c \
      src/delete_championship.c \
      src/create_championship.c \
      src/main_menu.c \
      src/create_team.c \
      src/team_balancing.c \
      src/display_team_tree.c \
      src/search_team.c \
      src/delete_team.c \
      src/edit_team.c \
      src/show_team.c \
      src/menu_player.c \
      src/player_balancing.c \
      src/create_player.c \
      src/show_player.c \
      src/search_player.c \
      src/edit_player.c \
      src/delete_player.c \
      src/display_player_tree.c \
      src/encrypt_or_decrypt.c \
      src/save_to_file.c \
      src/load_file.c \
      cJSON.c

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) -lssl -lcrypto

run:
	./$(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes ./$(EXEC) champion3 2> bonus/valgrind/valgrind_output.txt

clean:
	rm -f $(EXEC)
