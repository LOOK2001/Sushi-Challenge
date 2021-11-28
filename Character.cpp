
#include "include/Character.h"
#include "include/Camera.h"
#include "include/Utils.h"

void Player::init()
{
	RectObject::init();

	type = ObjectType::PLAYER;

	if (state.size() > 0)
	{
		rect.w = state[current_state]->GetViewWidth();
		rect.h = state[current_state]->GetViewHeight();
	}
	draw_skin = false;
	skin_color = { 0, 0, 0, 0 };

	// Weapon setup
	weapon = new Weapon("./images/gun.png", 50, 100);
	weapon->init();
	float weapon_center_x = weapon->GetImgWidth() / 2.0f;
	float weapon_center_y = weapon->GetImgHeight() / 2.0f;
	weapon->SetMuzzlePosition({ (float)weapon->GetImgWidth()-20.0f, weapon_center_y-5.0f });
	weapon->SetCenter({ weapon_center_x, weapon_center_y });
	weapon->SetSpeed(8.0f);
	AddChild(weapon);

	// Camera effect setup
	Camera* camera = Global::GetMainCamera();
	camera->SetOcillationDuration(0.2f);
	camera->SetOcillationAmplitude(1.0f);
}

void Player::update()
{
	state[current_state]->update();
}

void Player::render(SDL_Renderer* ren)
{
	state[current_state]->Draw(rect.x, rect.y, 0.0, NULL, flip_sprite, 1);

	if (draw_skin)
	{
		Camera* camera = Global::GetMainCamera();
		SDL_FPoint pos = camera->GetPos();

		float x = rect.x - pos.x;
		float y = rect.y - pos.y;

		SDL_SetRenderDrawColor(ren, skin_color.r, skin_color.g, skin_color.b, skin_color.a);
		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

		SDL_FRect box;
		box = { x, y, rect.w, rect.h };
		SDL_RenderFillRectF(ren, &box);
	}

	RectObject::render(ren);
}

void Player::handle_events(SDL_Event& ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		key_pressed = true;
		switch (ev.key.keysym.sym)
		{
		case SDLK_a:
			translate(-10, 0);
			flip_sprite = SDL_FLIP_HORIZONTAL;
			SwitchState("walk");
			break;
		case SDLK_d:
			flip_sprite = SDL_FLIP_NONE;
			SwitchState("walk");
			translate(10, 0);
			break;
		case SDLK_w:
			translate(0, -10);
			SwitchState("walk");
			break;
		case SDLK_s:
			translate(0, 10);
			SwitchState("walk");
			break;
		}
	}
	else if (ev.type == SDL_KEYUP)
	{
		key_pressed = false;
		SwitchState("idle");
	}
	else if (ev.type == SDL_MOUSEMOTION || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (ev.type == SDL_MOUSEMOTION)
		{
			SDL_FPoint dir = GetDirectionToMouse(x, y);

			float radian = Vector2D::Angle(dir);
			if (radian > PI * 0.5 || radian < -PI * 0.5)
				weapon->SetFlip(SDL_RendererFlip::SDL_FLIP_VERTICAL);
			else
				weapon->SetFlip(SDL_RendererFlip::SDL_FLIP_NONE);
			weapon->SetAngle(radian * 180 / PI);
		}
		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_FPoint dir = GetDirectionToMouse(x, y);
			weapon->Fire(dir);
			Global::GetMainCamera()->PlayCameraShake();
		}
	}

	RectObject::handle_events(ev);
}

void Player::AddState(SpriteObject* sprite_anim, std::string _state)
{
	// The state already added into the current character
	if (state.find(_state) != state.end())
		return;

	state.insert({ _state, sprite_anim });
}

void Player::SwitchState(std::string _state)
{
	if (current_state == _state)
		return;

	if (state.find(_state) == state.end())
		return;

	current_state = _state;
	state[current_state]->ResetViewCol();
}

void Player::SetDefaultState(std::string _state)
{
	current_state = _state;
}

SDL_FPoint Player::GetDirectionToMouse(const int x, const int y) const
{
	// Direction to the mouse position from player
	SDL_FPoint player_pos = GetGlobalPosition();
	float center_x = Global::GetMainCamera()->GetWidth() / 2.0f;
	float center_y = Global::GetMainCamera()->GetHeight() / 2.0f;
	SDL_FPoint dir{ x - center_x, y - center_y };

	// Normalize the direction
	dir = Vector2D::normal(dir);
	return dir;
}

void Player::CollisionResponse(GameObject* other)
{
	if (other->GetType() == ObjectType::PICKUP)
	{
		draw_skin = true;
		srand((int)skin_color.r);
		Uint8 r = (rand() % 255);
		Uint8 g = (rand() % 255);
		Uint8 b = (rand() % 255);
		skin_color = { r, g, b, 128 };
	}
}