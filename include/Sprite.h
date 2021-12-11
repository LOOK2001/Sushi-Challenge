// Class for maintaining sprite animation
#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"
#include "Image.h"
#include "Global.h"


// Base class for sprite animation object
class SpriteObject : public Image, public GameObject {
public:
	SpriteObject(unsigned count, double duration, const char* imageName = nullptr):
		Image(imageName)
	{
		frame_count = count;
		frame_duration = duration;
		last_frame_time = 0;

		view.w = GetImgWidth() / count;
		view.h = GetImagHeight();
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

	// The number of column of the sprite sheet
	void SetCount(const int count);
	int GetCount() const { return frame_count; }
	// How long for each column
	void SetDuration(const double duration) { frame_duration = duration; }
	double GetDuration() const { return frame_duration; }
	
	virtual void SetScale(const float& _scale) { scale = _scale; }
	virtual float GetScale() { return scale;}

protected:
	SDL_Rect frame_rect;
	unsigned frame = 0;
	unsigned frame_count;
	double frame_duration;
	int last_frame_time;
	float scale = 1;
};

#endif // SPRITE_H
