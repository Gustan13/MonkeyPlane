#include "commons.h"

int collided(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return (x1 + w1 > x2 && x1 < x2 + w2) && (y1 + h1 > y2 && y1 < y2 + h2);
}

void move_monsters()
{
	Entity* e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e == player)
			continue;

		if (e->type == 'i')
		{
			e->dy += (float)0.51;

			if (e->frame % 32 == 0)
			{
				e->dy = -PENGUIN_JUMP_SET;
			}
		}
		else if (e->type == 'd')
		{
			if (!dead)
			{
				float exp = (player->y - e->y) / 80;
				exp < 0 ? (exp *= -1) : (exp *= 1);

				e->y < player->y ? (e->dy = (float)(1.5 * exp)) : (e->dy = (float)(- 1.5 * exp));
			}
			else
				e->dy = 0;
		}

		e->x += e->dx;
		e->y += e->dy;
	}
}

void move_bullets()
{
	Entity *e, *prev;

	prev = &stage.bulletHead;

	if (stage.bulletTail == &stage.bulletHead)
		return;

	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;

		if (e->x > SCREEN_WIDTH)
		{
			if (stage.bulletTail == e)
				stage.bulletTail = prev;

			prev->next = e->next;
			free(e);
			e = prev;
		}
		prev = e;
	}
}

void player_monster_collision()
{
	Entity *e;

	if (dead)
		return;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e == player)
			continue;

		if (collided(
			player->x,
			player->y,
			player->w,
			player->h,
			e->x,
			e->y,
			e->w,
			e->h))
		{
			dead++;
			spawn_blood(player->x, player->y);
			break;
		}
	}
}

void monster_bullet_collision()
{
	Entity *a, *b, *prev, *prev2;

	prev = &stage.bulletHead;
	prev2 = &stage.fighterHead;

	for (a = stage.bulletHead.next; a != NULL; a = a->next)
	{
		for (b = stage.fighterHead.next; b != NULL; b = b->next)
		{
			if (b == player)
			{
				prev2 = b;
				continue;
			}

			if (collided(
				a->x,
				a->y,
				a->w,
				a->h,
				b->x,
				b->y,
				b->w,
				b->h
			))
			{
				spawn_blood(a->x, a->y);

				if (stage.bulletTail == a)
					stage.bulletTail = prev;

				prev->next = a->next;
				free(a);
				a = prev;

				b->life--;
				break;
			}

			prev2 = b;
		}

		prev = a;
	}
}

void init_player()
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 0;
	player->y = 320;
	player->w = 64;
	player->h = 64;
	player->dx = 0;
	player->dy = 0;
	player->type = 'p';

	player->texture = player_sprite_sheet;
	player->current_clip = &uni_sprite_clips[0];
}

void init_stage()
{
	spawnerRate = SPAWNRATE_SET;
	running = 1;
	restart = 0;
	dead = 0;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.particleTail = &stage.particleHead;

	init_player();
}