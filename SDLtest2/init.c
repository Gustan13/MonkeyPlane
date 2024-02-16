#include "commons.h"

int init()
{
	printf("Initializing SDL...\n");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	window = SDL_CreateWindow(
		"Monkey Plane",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_SWSURFACE);
	if (window == NULL)
		return -1;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("%s\n", SDL_GetError());
		return -1;
	}

	IMG_Init(IMG_INIT_PNG);

	screen = SDL_GetWindowSurface(window);
	if (screen == NULL)
		return -1;

	printf("SDL initialized.\n");

	return 0;
}

void destroy_all_entities()
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	player = NULL;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		prev->next = e->next;
		free(e);
		e = prev;
	}

	prev = &stage.bulletHead;

	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		prev->next = e->next;
		free(e);
		e = prev;
	}
}

int close_all()
{
	printf("Closing SDL...\n");

	destroy_all_entities();
	SDL_DestroyTexture(dog_sprite_sheet);
	SDL_DestroyTexture(player_sprite_sheet);
	SDL_DestroyTexture(penguin_sprite_sheet);
	SDL_DestroyTexture(banana_sprite_sheet);
	SDL_DestroyTexture(blood_sprite_sheet);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	printf("SDL closed.\n");
	printf("Quitting...\n");

	exit(0);
}