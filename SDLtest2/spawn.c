#include "commons.h"

void spawn_penguin()
{
	Entity* penguin;
	penguin = malloc(sizeof(Entity));
	memset(penguin, 0, sizeof(Entity));
	stage.fighterTail->next = penguin;
	stage.fighterTail = penguin;

	penguin->x = SCREEN_WIDTH;
	penguin->y = (float)(((rand() % 5) + 2) * 64);
	penguin->h = 64;
	penguin->w = 64;
	penguin->dy = -PENGUIN_JUMP_SET;
	penguin->dx = -ENEMY_SPEED;
	penguin->frame = 0;
	penguin->life = 3;
	penguin->current_clip = &uni_sprite_clips[(int)(penguin->frame / 16)];
	penguin->type = 'i';

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
	dog->y = (float)((rand() % 9) * 64);
	dog->h = 64;
	dog->w = 64;
	dog->dx = -4;
	dog->life = 5;
	dog->current_clip = &uni_sprite_clips[0];
	dog->type = 'd';

	dog->texture = dog_sprite_sheet;
}

void spawn_bullet()
{
	Entity* bullet;
	bullet = malloc(sizeof(Entity));
	if (bullet == NULL)
		printf("The bullet could not be spawned.\n");
	else
		printf("Pow!.\n");

	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->dx = 6;
	bullet->x = player->x + 48;
	bullet->y = player->y + 24;
	bullet->w = 32;
	bullet->h = 32;
	bullet->current_clip = &uni_32_sprite_clips[0];
	bullet->texture = banana_sprite_sheet;
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
		if ((e->x < -e->w || e->life < 1) && e != player)
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
	if (spawnerRate <= 0)
	{
		spawnerRate = SPAWNRATE_SET;
		spawn_dog();
		spawn_penguin();
	}
}