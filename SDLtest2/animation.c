#include "commons.h"

void animate_all()
{
	Entity* e, * prev;
	int b;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e == player)
		{
			e->frame++;
			if (e->frame > 3)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[e->frame];
			continue;
		}

		switch (e->type)
		{
		case PENGUIN:
			e->frame++;
			if (e->frame > 63)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[(e->frame / 8) / 4];
			break;
		case DOG:
			e->frame++;
			if (e->frame > 8)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[e->frame / 3];
			break;
		case DUCK:
			e->frame++;
			if (e->frame > 31)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[e->frame/8];
			break;
		case ELEPHANT:

			if (e->x > (player->x + 192))
			{
				e->current_clip = &uni_sprite_clips[0];
				b = -8;
			}
			else if (e->x < (player->x - 128))
			{
				e->current_clip = &uni_sprite_clips[2];
				b = 32;
			}
			else
			{
				e->current_clip = &uni_sprite_clips[1];
				b = 16;
			}

			e->frame++;
			if (e->frame > 79)
				e->frame = 0;

			if (e->frame % 80 == 0)
			{
				float x = player->x - e->x;
				float y = player->y - e->y;

				float dist = sqrtf(powf(x, 2) + powf(y, 2));

				float cos = x / dist;
				float sin = y / dist;

				spawn_bullet(BAD, cos * ENEMY_BULLET_SPEED, sin * ENEMY_BULLET_SPEED, e->x + b, e->y - 16);
			}
			break;

		case KOALA:
			e->angle += 5;
			if (e->angle > 359)
				e->angle = 0;
			break;
		}
	}

	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		if (e->side == GOOD)
		{
			/*e->frame++;
			if (e->frame > 15)
				e->frame = 0;

			e->current_clip = &uni_32_sprite_clips[e->frame / 4];*/
			e->angle += 20;
			if (e->angle > 359)
				e->angle = 0;
		}
		else {
			/*e->frame++;
			if (e->frame > 31)
				e->frame = 0;

			e->current_clip = &uni_32_sprite_clips[e->frame / 8];*/
			e->angle += 5;
			if (e->angle > 359)
				e->angle = 0;
		}
	}

	prev = &stage.particleHead;

	for (e = stage.particleHead.next; e != NULL; e = e->next)
	{
		e->frame++;
		if (e->frame > 15)
		{
			if (stage.particleTail == e)
				stage.particleTail = prev;

			prev->next = e->next;
			free(e);
			e = prev;
			continue;
		}

		prev = e;
		e->current_clip = &uni_sprite_clips[e->frame / 4];
	}
}