#include "commons.h"

void animate_all()
{
	Entity* e, * prev;

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
		case 'i':
			e->frame++;
			if (e->frame > 63)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[(e->frame / 8) / 4];
			break;
		case 'd':
			e->frame++;
			if (e->frame > 8)
				e->frame = 0;

			e->current_clip = &uni_sprite_clips[e->frame / 3];
			break;
		}
	}

	for (e = stage.bulletHead.next; e != NULL; e = e->next)
	{
		e->frame++;
		if (e->frame > 15)
			e->frame = 0;

		e->current_clip = &uni_32_sprite_clips[e->frame / 4];
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