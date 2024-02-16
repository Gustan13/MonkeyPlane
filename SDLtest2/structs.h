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

// Isso � um bom aprendizado de como realizar uma lista linkada com cabe�a e cauda.
// A cabe�a da lista � um peda�o de mem�ria usada apenas para indicar o pr�ximo peda�o de mem�ria.
