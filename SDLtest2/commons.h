#pragma once

#ifndef _INCLUDES
#define _INCLUDES

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "structs.h"
#include "enums.h"
#include "draw.h"
#include "init.h"
#include "stage.h"
#include "input.h"
#include "spawn.h"
#include "animation.h"

SDL_Window* window;
SDL_Surface* screen;

Stage stage;

SDL_Rect uni_sprite_clips[4];
SDL_Rect uni_32_sprite_clips[4];
SDL_Texture* penguin_sprite_sheet;
SDL_Texture* player_sprite_sheet;
SDL_Texture* dog_sprite_sheet;
SDL_Texture* banana_sprite_sheet;
SDL_Texture* blood_sprite_sheet;

Entity* player;

int spawnerRate;

SDL_Renderer* renderer;

SDL_Event e;

int running;
int reload;
int restart;
int dead;

int last_frame_time;

#endif
