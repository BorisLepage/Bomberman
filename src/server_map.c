#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server_bomb.h>
#include <include/server_explosion.h>
#include <include/server.h>
#include <include/server_map.h>

void implement_map(t_server_game *server_game, bomb_server_t *server_bomb, explosion_server_t *server_explosion)
{
    // Clean map and bombs from players
    for (int y = 0; y < 13; y++) {
        for (int x = 0; x < 15; x++) {
            switch (server_game->schema[y][x])
            {
                case '6' :
                case '7' :
                case '8' :
                case '9' :
                case 'A' :
                case 'G' :
                case 'H' :
                case 'I' :
                    server_game->schema[y][x] = '3';
                    break;
            }
        }
    }

    // Drop Players on the map
    //
    // if alive Drop Players alive on top
    //  else    Drop Players dead on top
    if (server_game->player1.live == 1)
    {
        server_game->schema[server_game->player1.y_pos][server_game->player1.x_pos] = '6';
        server_game->schema[0][4] = 'S';
    }else{
        server_game->schema[0][4] = 'W';
    }
    if (server_game->player2.live == 1)
    {
        server_game->schema[server_game->player2.y_pos][server_game->player2.x_pos] = '7';
        server_game->schema[0][6] = 'T';
    }else{
        server_game->schema[0][6] = 'X';
    }
    if (server_game->player3.live == 1)
    {
        server_game->schema[server_game->player3.y_pos][server_game->player3.x_pos] = '8';
        server_game->schema[0][8] = 'U';
    }else{
        server_game->schema[0][8] = 'Y';
    }
    if (server_game->player4.live == 1)
    {
        server_game->schema[server_game->player4.y_pos][server_game->player4.x_pos] = '9';
        server_game->schema[0][10] = 'V';
    }else{
        server_game->schema[0][10] = 'Z';
    }

    // Drop the bombs ont the map
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;
    while (!last_bomb)
    {
        if (the_bomb->player != 0)
        {
            server_game->schema[the_bomb->y][the_bomb->x] = 'A';
        }

        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            last_bomb = true;
        }
    }

    // Drop the explosions ont the map
    bool last_explosion = false;
    explosion_server_t *the_explosion = server_explosion;
    while (!last_explosion)
    {
        //printf("EXPLOS ___ %p BOOL%d\n", server_explosion->next, the_explosion->first);
        // TODO printf("explosion Player %d\n", the_explosion->player);
        if (the_explosion->first != 1)
        {
            printf("EXPLOSIONS ___ %p %d %d\n\n", server_explosion->next, the_explosion->y, the_explosion->x);

            server_game->schema[the_explosion->y][the_explosion->x] = 'G';

            for (int i=1; i < (the_explosion->size + 1); i++ )
            {
                if ( i < (the_explosion->size_up + 1))
                {
                    server_game->schema[(the_explosion->y - i)][the_explosion->x] = 'H';
                }
                if ( i < (the_explosion->size_right + 1)) {
                    server_game->schema[the_explosion->y][(the_explosion->x + i)] = 'I';
                }
                if ( i < (the_explosion->size_down + 1)) {
                    server_game->schema[(the_explosion->y + i)][the_explosion->x] = 'H';
                }
                if ( i < (the_explosion->size_left+ 1)) {
                    server_game->schema[the_explosion->y][(the_explosion->x - i)] = 'I';
                }
            }
        }

        if (the_explosion->next != NULL)
        {
            printf("NEXT PAS NUL \n");
            the_explosion = the_explosion->next;
        }else{
            last_explosion = true;
        }
    }

}