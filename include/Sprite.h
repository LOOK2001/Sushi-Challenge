// Class for maintaining sprite animation
#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"
#include "Image.h"
#include "Global.h"


class SpriteObject : public Image, public GameObject {
public:
	SpriteObject(unsigned count, double duration, const char* imageName = nullptr):
		Image(imageName)
	{
		frame_count = count;
		frame_duration = duration;
		last_frame_time = 0;

		view.w = GetWidth() / count;
		view.h = GetHeight();
		view.x = 0;
		view.y = 0;
	};
	~SpriteObject() {};

	void cleanup() {};

	void update()
	{
		sprite_update();
	}

	void sprite_update();

	void ResetViewCol() { view.x = 0; }

	// Update width and height
	void SetCount(const int count);
	int GetCount() const { return frame_count; }
	void SetDuration(const double duration) { frame_duration = duration; }
	double GetDuration() const { return frame_duration; }

protected:
	SDL_Rect frame_rect;
	unsigned frame = 0;
	unsigned frame_count;
	double frame_duration;
	int last_frame_time;
};

#endif // SPRITE_H