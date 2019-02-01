#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/player.h>
#include <include/interface.h>
#include <include/bomberman.h>
#include <include/bomb.h>

player_t *init_player(interface_t *interface)
{
	player_t *player = NULL;

	player = malloc(sizeof(player_t));

	if (player == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	player->id = 0;
	player->score = 0;
	player->playerPositionRect.x = interface->screenSize.x / 2;
	player->playerPositionRect.y = interface->screenSize.y / 2;
	player->playerPositionRect.w = 50;
	player->playerPositionRect.h = 60;


	// load player texture
	SDL_Surface *playerSurface = IMG_Load("images/bomberman_front.png");

	if (!playerSurface) {
		fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
		destroy_game(interface, player);
		return NULL;	
	} else {
		player->TexPlayer = SDL_CreateTextureFromSurface(interface->Renderer, playerSurface);

		if (!player->TexPlayer) {
			fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
			destroy_game(interface, player);
			return NULL;
		}

		SDL_FreeSurface(playerSurface);
	}

	return player;
}

void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction)
{
	if (direction == SDLK_UP){
		if (player->playerPositionRect.y > 0) {
			player->playerPositionRect.y -= 10;
		}
	} else if (direction == SDLK_DOWN) {
		if (player->playerPositionRect.y < (interface->screenSize.y - player->playerPositionRect.h)) {
			player->playerPositionRect.y += 10;
		}
	} else if (direction == SDLK_LEFT) {
		if (player->playerPositionRect.x > 0) {
			player->playerPositionRect.x -= 10;
		}
	} else if (direction == SDLK_RIGHT) {
		if (player->playerPositionRect.x < (interface->screenSize.x - player->playerPositionRect.w)) {
			player->playerPositionRect.x += 10;
		}
	} else {
		fprintf(stderr, "unknown direction\n");
	}
}

bomb_t *dropBomb(player_t *player, bomb_t *bomb)
{
	if (bomb->exist == 0) {
		placeBomb(bomb, player);
	}

	return bomb;
}


void destroy_player(player_t *player)
{
	if (player) {
		if (player->TexPlayer) {
			SDL_DestroyTexture(player->TexPlayer);
		}

		free(player);
	}
}
