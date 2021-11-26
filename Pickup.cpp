#include "include/Pickup.h"
#include "include/Scene.h"

void Pickup::init()
{
	RectObject::init();

	type = ObjectType::PICKUP;
}

void Pickup::update()
{
	if (!active)
		return;

	sprite->update();
}

void Pickup::render(SDL_Renderer* ren)
{
	if (!active)
		return;

	sprite->Draw(rect.x, rect.y, 2);

	RectObject::render(ren);
}

void Pickup::SetCount(const int count)
{
	sprite->SetCount(count);
	rect.w = sprite->GetViewWidth();
	rect.h = sprite->GetViewHeight();
}

void Pickup::CollisionResponse(GameObject* other)
{
	if (!active)
		return;

	if (other->GetType() == ObjectType::BULLET)
	{
		Scene* active_scene = Global::GetActiveScene();
		SDL_Renderer* my_renderer = Global::GetRenderer();
		if (active_scene)
		{
			pe = new ParticleEmitter();
			float center_x = rect.x + rect.w / 2.0f;
			float center_y = rect.y + rect.h / 2.0f;
			pe->init("./images/particle.png", my_renderer, center_x, center_y, 50, 50, 0);

			active_scene->AddGameObject(pe);
			pe->Start();
		}

		collidable = false;
		active = false;
	}
}
