#include "commons.h"

int main(void)
{
	if (init() < 0)
		exit(-1);

	if (load_media() < 0)
		exit(-1);

	printf("playing\n");

	init_stage();

	while (running)
	{
		if (restart)
		{
			destroy_all_entities();
			init_stage();
			restart = 0;
		}

		while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

		last_frame_time = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				running = 0;
		}

		if (reload > 0)
			reload--;

		process_input();

		move_monsters();
		move_bullets();
		despawn_monsters();
		monster_spawner();

		animate_all();

		player_monster_collision();
		monster_bullet_collision();

		draw();

		SDL_Delay(8);
	}

	close_all();

	return 0;
}