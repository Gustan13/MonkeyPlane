#include "commons.h"

void spawn_penguin()
{
	Entity* penguin;
	penguin = malloc(sizeof(Entity));
	memset(penguin, 0, sizeof(Entity));
	stage.fighterTail->next = penguin;
	stage.fighterTail = penguin;

	penguin->x = SCREEN_WIDTH;
	penguin->y = (float)((rand() % ((SCREEN_HEIGHT / 64) - 2) + 1) * 64);
	penguin->h = 64;
	penguin->w = 64;
	penguin->dy = -PENGUIN_JUMP_SET;
	penguin->dx = -ENEMY_SPEED;
	penguin->life = 3;
	penguin->side = BAD;
	penguin->current_clip = &uni_sprite_clips[0];
	penguin->type = PENGUIN;

	penguin->texture = penguin_sprite_sheet;
}

void spawn_dog()
{
	Entity* dog;
	dog = malloc(sizeof(Entity));
	memset(dog, 0, sizeof(Entity));
	stage.fighterTail->next = dog;
	stage.fighterTail = dog;

	dog->x = SCREEN_WIDTH;
	dog->y = (float)((rand() % ((SCREEN_HEIGHT / 64) - 1)) * 64);
	dog->h = 64;
	dog->w = 64;
	dog->dx = -4;
	dog->life = 4;
	dog->side = BAD;
	dog->current_clip = &uni_sprite_clips[0];
	dog->type = DOG;

	dog->texture = dog_sprite_sheet;
}

void spawn_duck()
{
	Entity* duck;
	duck = malloc(sizeof(Entity));
	memset(duck, 0, sizeof(Entity));
	stage.fighterTail->next = duck;
	stage.fighterTail = duck;

	duck->x = SCREEN_WIDTH;
	duck->y = (float)((rand() % ((SCREEN_HEIGHT/64) - 1)) * 64);
	duck->w = 64;
	duck->h = 64;
	duck->dx = -4;
	duck->life = 2;
	duck->side = BAD;
	duck->current_clip = &uni_sprite_clips[0];
	duck->type = DUCK;

	duck->texture = duck_sprite_sheet;
}

void spawn_elephant()
{
	Entity* elephant;
	elephant = malloc(sizeof(Entity));
	memset(elephant, 0, sizeof(Entity));
	stage.fighterTail->next = elephant;
	stage.fighterTail = elephant;

	elephant->x = SCREEN_WIDTH;
	elephant->y = SCREEN_HEIGHT - 64;
	elephant->w = 64;
	elephant->h = 64;
	elephant->dx = -2;
	elephant->life = 5;
	elephant->side = BAD;
	elephant->current_clip = &uni_sprite_clips[0];
	elephant->type = ELEPHANT;

	elephant->texture = elephant_sprite_sheet;
}

void spawn_koala()
{
	Entity* koala;
	koala = malloc(sizeof(Entity));
	memset(koala, 0, sizeof(Entity));
	stage.fighterTail->next = koala;
	stage.fighterTail = koala;

	koala->x = (rand() % ((SCREEN_WIDTH / 64) - 1)) * 64;
	koala->y = -64;
	koala->w = 64;
	koala->h = 64;
	koala->dy = 4;
	koala->life = 1;
	koala->side = BAD;
	koala->current_clip = &uni_sprite_clips[0];
	koala->type = KOALA;

	koala->texture = koala_sprite_sheet;
}

void spawn_bullet(int side, float dx, float dy, float x, float y)
{
	Entity* bullet;
	bullet = malloc(sizeof(Entity));

	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->dx = dx;
	bullet->dy = dy;
	bullet->x = x;
	bullet->y = y;
	bullet->w = 32;
	bullet->h = 32;
	bullet->side = side;
	bullet->current_clip = &uni_32_sprite_clips[0];

	if (side == GOOD)
		bullet->texture = banana_sprite_sheet;
	else
		bullet->texture = apple_sprite_sheet;
}

void spawn_blood(float x, float y)
{
	Entity* blood;
	blood = malloc(sizeof(Entity));

	memset(blood, 0, sizeof(Entity));
	stage.particleTail->next = blood;
	stage.particleTail = blood;

	blood->x = x;
	blood->y = y;
	blood->w = 64;
	blood->h = 64;
	blood->current_clip = &uni_sprite_clips[0];
	blood->texture = blood_sprite_sheet;
}

void despawn_monsters()
{
	Entity* e, * prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if ((e->x < -e->w || e->life < 1 || e->y > SCREEN_HEIGHT) && e != player)
		{
			if (stage.fighterTail == e)
				stage.fighterTail = prev;

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

void monster_spawner()
{
	spawnerRate--;
	int i;
	if (spawnerRate <= 0)
	{
		spawnerRate = SPAWNRATE_SET;
		
		i = rand() % 7;

		switch (i)
		{
		case PENGUIN:
			spawn_penguin();
			break;

		case DOG:
			spawn_dog();
			break;

		case DUCK:
			spawn_duck();
			break;

		case ELEPHANT:
			spawn_elephant();
			break;

		case KOALA:
			spawn_koala();
			break;

		default:
			break;
		}
	}
}