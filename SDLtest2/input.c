#include "commons.h"

void process_input()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	player->dx = 0;
	player->dy = 0;

	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		player->dy -= PLAYER_SPEED;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		player->dy += PLAYER_SPEED;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		player->dx -= PLAYER_SPEED;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		player->dx += PLAYER_SPEED;
	}
	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		running = 0;
	}
	if (currentKeyStates[SDL_SCANCODE_R])
	{
		restart = 1;
	}
	if (currentKeyStates[SDL_SCANCODE_Z])
	{
		if (reload <= 0 && !dead)
		{
			spawn_bullet(GOOD, BULLET_SPEED, 0, player->x + 32, player->y + 24);
			reload = RELOAD_TIME;
		}
	}

	if (!dead)
	{
		player->x += player->dx;
		player->y += player->dy;
	}

	if (player->x < 0) player->x = 0;
	if (player->x > SCREEN_WIDTH - 64) player->x = SCREEN_WIDTH - 64;
	if (player->y < 0) player->y = 0;
	if (player->y > SCREEN_HEIGHT - 64) player->y = SCREEN_HEIGHT - 64;
}