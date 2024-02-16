#pragma once

typedef struct entity_t {
	float x, y, w, h, dx, dy;
	char type;
	int frame, life;
	SDL_Rect* current_clip;
	SDL_Texture* texture;
	struct entity_t* next;
} Entity;

typedef struct {
	Entity fighterHead, * fighterTail;
	Entity bulletHead, * bulletTail;
	Entity particleHead, * particleTail;
} Stage;

// Isso é um bom aprendizado de como realizar uma lista linkada com cabeça e cauda.
// A cabeça da lista é um pedaço de memória usada apenas para indicar o próximo pedaço de memória.
