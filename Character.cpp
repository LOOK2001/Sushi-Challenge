
#include "include/Character.h"
#include "include/Camera.h"
#include "include/Utils.h"


void HealthBar::init()
{
	RectFillObject::init();

	float width = rect.w;
	float height = rect.h;

	back = new RectFillObject({ 220, 220, 220, 255 }, rect.x, rect.y - 10.0f, width, height);
	front = new RectFillObject({ 220, 0, 0, 255 }, rect.x, rect.y - 10.0f, width, height);
}

void HealthBar::render(SDL_Renderer* ren)
{
	if (!active)
		return;

	Camera* camera = Global::GetMainCamera();
	SDL_FPoint camera_pos = camera->GetPos();
	SDL_FPoint pos = GetGlobalPosition();

	float x = pos.x - camera_pos.x;
	float y = pos.y - camera_pos.y;

	SDL_Color back_color = back->getColor();
	SDL_FRect back_rect = back->GetSize();
	back_rect.x += x, back_rect.y += y;
	SDL_SetRenderDrawColor(ren, back_color.r, back_color.g, back_color.b, 255);
	SDL_RenderFillRectF(ren, &back_rect);

	SDL_Color front_color = front->getColor();
	SDL_FRect front_rect = front->GetSize();
	front_rect.x += x, front_rect.y += y;
	SDL_SetRenderDrawColor(ren, front_color.r, front_color.g, front_color.b, 255);
	SDL_RenderFillRectF(ren, &front_rect);
}

void HealthBar::SetPrecentage(const float& _p)
{
	precentage = _p;
	float width = GetWidth() * precentage;
	front->SetWidth(width);
}


void Character::init()
{
	if (current_state.compare("none") == 0)
		return;

	if (state.size() > 0)
	{
		rect.w = state[current_state]->GetViewWidth();
		rect.h = state[current_state]->GetViewHeight();
	}

	RectObject::init();
	type = ObjectType::PLAYER;
}

void Character::update()
{
	RectObject::update();

	if (!current_state.compare("none") == 0)
	{
		state[current_state]->update();
	}
}

void Character::render(SDL_Renderer* ren)
{
	if (current_state.compare("none") == 0)
		return;

	state[current_state]->Draw(rect.x, rect.y, 0.0, NULL, flip_sprite, 1);

	RectObject::render(ren);
}

void Character::handle_events(SDL_Event& ev)
{
	RectObject::handle_events(ev);
}

void Character::AddState(SpriteObject* sprite_anim, std::string _state)
{
	// The state already added into the current character
	if (state.find(_state) != state.end())
		return;

	state.insert({ _state, sprite_anim });
}

void Character::SwitchState(std::string _state)
{
	if (current_state == _state)
		return;

	if (state.find(_state) == state.end())
		return;

	current_state = _state;
	state[current_state]->ResetViewCol();
}

void Character::SetDefaultState(std::string _state)
{
	current_state = _state;
}
