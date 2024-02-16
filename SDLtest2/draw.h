#pragma once

int load_media();

SDL_Surface* get_image(const char* file_name);

SDL_Texture* load_texture(const char* texture_name);

void draw_entity(Entity* entity);

void draw();