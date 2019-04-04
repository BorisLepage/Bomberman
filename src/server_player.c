#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server.h>
#include <include/server_player.h>
#include <include/server_bomb.h>

void player_action(t_server_game *server_game, bomb_server_t *server_bomb, int player, char command) {

    // TODO Yop : Swicth a fonctionner
    t_player_infos *the_player;
    switch (player)
    {
        case 1 :
            the_player = &server_game->player1;
            break;
        case 2 :
            the_player = &server_game->player2;
            break;
        case 3 :
            the_player = &server_game->player3;
            break;
        case 4 :
            the_player = &server_game->player4;
            break;
    }

    // If player is dead, don't take any information
    if (the_player->live != 1)
    {
        printf("IS DEAD\n");
        return;
    }

    switch (command)
    {
        case 'U' :
        case 'D' :
        case 'L' :
        case 'R' :
            player_move(server_game, player, command);

            break;
        case 'B' :
            if (the_player->bombs_left > 0)
            {
                bomb_drop(server_game, server_bomb, player);
            }
            break;
    }
}

void player_move(t_server_game *server_game, int player, char command)
{

    // TODO Yop : Swicth a fonctionner
    t_player_infos *the_player;
    switch (player)
    {
        case 1 :
            the_player = &server_game->player1;
            break;
        case 2 :
            the_player = &server_game->player2;
            break;
        case 3 :
            the_player = &server_game->player3;
            break;
        case 4 :
            the_player = &server_game->player4;
            break;
    }

    switch (command)
    {
        case 'U' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos-1)) {
                the_player->y_pos--;
            }
            break;
        case 'D' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos+1)) {
                the_player->y_pos++;
            }
            break;
        case 'L' :
            if (place_is_free(server_game, the_player->x_pos-1, the_player->y_pos)) {
                the_player->x_pos--;
            }
            break;
        case 'R' :
            if (place_is_free(server_game, the_player->x_pos+1, the_player->y_pos)) {
                the_player->x_pos++;
            }
            break;
    }
}

bool place_is_free(t_server_game *server_game, int x, int y)
{
    if (server_game->schema[y][x] == '0' || server_game->schema[y][x] == '1'|| server_game->schema[y][x] == '2')
    {
        return false;
    }

    return true;
}

void bomb_drop(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    create_new_bomb(server_game, server_bomb, player);
}