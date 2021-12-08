#include "include/Player.h"
#include "include/Camera.h"
#include "include/Utils.h"


void Player::init()
{
	Character::init();

	health = full_health = 100;

	type = ObjectType::PLAYER;

	if (state.size() > 0)
	{
		rect.w = state[current_state]->GetViewWidth();
		rect.h = state[current_state]->GetViewHeight();
	}

	// Weapon setup
	weapon = new Weapon("./images/gun.png", 50, 100);
	weapon->init();
	float weapon_center_x = weapon->GetImgWidth() / 2.0f;
	float weapon_center_y = weapon->GetImgHeight() / 2.0f;
	weapon->SetMuzzlePosition({ (float)weapon->GetImgWidth() - 20.0f, weapon_center_y - 5.0f });
	weapon->SetCenter({ weapon_center_x, weapon_center_y });
	weapon->SetSpeed(8.0f);
	AddChild(weapon);

	// Camera effect setup
	Camera* camera = Global::GetMainCamera();
	camera->SetOcillationDuration(0.2f);
	camera->SetOcillationAmplitude(3.5f);

	health_bar = new HealthBar(0, 0, GetWidth(), 20);
	AddChild(health_bar);
	health_bar->init();
}

void Player::update()
{
	if (current_state.compare("none") == 0)
		return;

	state[current_state]->update();
}

void Player::render(SDL_Renderer* ren)
{
	if (current_state.compare("none") == 0)
		return;

	state[current_state]->Draw(rect.x, rect.y, 0.0, NULL, flip_sprite, 1);

	Character::render(ren);
}

void Player::handle_events(SDL_Event& ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		key_pressed = true;
		switch (ev.key.keysym.sym)
		{
		case SDLK_a:
			translate(-speed, 0);
			flip_sprite = SDL_FLIP_HORIZONTAL;
			SwitchState("walk");
			break;
		case SDLK_d:
			flip_sprite = SDL_FLIP_NONE;
			SwitchState("walk");
			translate(speed, 0);
			break;
		case SDLK_w:
			translate(0, -speed);
			SwitchState("walk");
			break;
		case SDLK_s:
			translate(0, speed);
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

	Character::handle_events(ev);
}

SDL_FPoint Player::GetDirectionToMouse(const int x, const int y) const
{
	// Direction to the mouse position from player
	float center_x = Global::GetMainCamera()->GetWidth() / 2.0f;
	float center_y = Global::GetMainCamera()->GetHeight() / 2.0f;
	SDL_FPoint dir{ x - center_x, y - center_y };

	// Normalize the direction
	dir = Vector2D::Normal(dir);
	return dir;
}

void Player::UpdateHealthBar(int _health)
{
	float curr = (float)_health / (float)full_health;
	health_bar->SetPrecentage(curr);
}

void Player::CollisionResponse(GameObject* other)
{
	if (other->GetType() == ObjectType::ENEMY_BULLET || other->GetType() == ObjectType::BLAST)
	{

		if (health <= 0)
		{
			UpdateHealthBar(0);
			Died();
		}
		else
		{
			if (other->GetType() == ObjectType::ENEMY_BULLET)
			{
				health -= 20;
				if (health <= 0)
				{
					UpdateHealthBar(0);
					Died();
				}
				UpdateHealthBar(health);
				other->SetCollidable(false);
				DeleteObject(other);
			}
			else if (other->GetType() == ObjectType::BLAST)
			{
				health -= 40;
				if (health <= 0)
				{
					UpdateHealthBar(0);
					Died();
				}
				other->SetCollidable(false);
				UpdateHealthBar(health);
			}
		}
	}
}

void Player::Died()
{
	is_dead = true;
}
