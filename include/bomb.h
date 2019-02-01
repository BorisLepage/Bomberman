#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <include/interface.h>

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

typedef struct bomb_s bomb_t;

struct bomb_s
{
    // bomb texture
    SDL_Texture *TexBomb;

    // position of bomb
    SDL_Rect bombPositionRect;
};

bomb_t *init_bomb(interface_t *interface);
void moveBomb(bomb_t *bomb, interface_t *interface, SDL_Keycode direction);
void destroy_bomb(bomb_t *bomb);

#endif //BOMBERMAN_BOMB_H
