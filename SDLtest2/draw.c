#include "commons.h"

SDL_Texture* load_texture(const char* texture_name)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loaded_surface = IMG_Load(texture_name);
	if (loaded_surface == NULL)
		printf("Could not load texture of name %s: %s", texture_name, SDL_GetError());
	else {
		texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		SDL_FreeSurface(loaded_surface);
	}

	return texture;
}

SDL_Surface* get_image(const char* file_name)
{
	SDL_Surface* optimized_surface = NULL;

	SDL_Surface* loaded_surface = SDL_LoadBMP(file_name);
	if (loaded_surface == NULL)
		printf("Could not load surface.\n");
	else {
		optimized_surface = SDL_ConvertSurface(loaded_surface, screen->format, 0);
		SDL_FreeSurface(loaded_surface);
	}

	return optimized_surface;
}

int load_media()
{
	player_sprite_sheet = load_texture("fly_monkey.png");
	penguin_sprite_sheet = load_texture("penguin.png");
	dog_sprite_sheet = load_texture("dog.png");
	banana_sprite_sheet = load_texture("banana.png");
	blood_sprite_sheet = load_texture("explosion.png");
	duck_sprite_sheet = load_texture("duck.png");
	elephant_sprite_sheet = load_texture("elephant.png");
	apple_sprite_sheet = load_texture("apple.png");
	koala_sprite_sheet = load_texture("koala.png");

	for (int i = 0; i < 4; i++)
	{
		uni_sprite_clips[i].x = 0;
		uni_sprite_clips[i].y = 64 * i;
		uni_sprite_clips[i].h = 64;
		uni_sprite_clips[i].w = 64;

		uni_32_sprite_clips[i].x = 0;
		uni_32_sprite_clips[i].y = 32 * i;
		uni_32_sprite_clips[i].h = 32;
		uni_32_sprite_clips[i].w = 32;
	}

	return 0;
}

void draw_entity(Entity* entity)
{
	SDL_Rect rect = {
		(int)entity->x,
		(int)entity->y,
		(int)entity->w,
		(int)entity->h
	};
	SDL_Point point = {entity->x + entity->w / 2, entity->y + entity->h / 2};
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	//SDL_RenderCopy(renderer, entity->texture, entity->current_clip, &rect);
	SDL_RenderCopyEx(renderer, entity->texture, entity->current_clip, &rect, entity->angle, NULL, flip);
}

void draw()
{
	Entity* e;

	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 1);
	SDL_RenderClear(renderer);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xff, 0xff));

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e != player || !dead)
		{
			draw_entity(e);
		}
	}

	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		draw_entity(e);
	}

	for (e = stage.particleHead.next; e != NULL; e = e->next)
	{
		draw_entity(e);
	}

	SDL_RenderPresent(renderer);
}