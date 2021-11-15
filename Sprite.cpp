
#include "include/Sprite.h"

void SpriteObject::SetCount(const int count)
{
	frame_count = count;
	view.w = GetWidth() / count;
}

void SpriteObject::sprite_update()
{
	int frame_time = (int)(SDL_GetTicks() / frame_duration) % frame_count;

	if (last_frame_time != frame_time) {
		if (frame_time < 1) { // reset sprite x
			view.x = 0;
		}
		else {
			view.x += view.w;
		}
	}

	last_frame_time = frame_time;
}
