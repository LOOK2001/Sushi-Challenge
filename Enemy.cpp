#include "include/Enemy.h"
#include "include/Utils.h"


void Enemy::init()
{
	Character::init();

	SetObjectType(ObjectType::ENEMY);

	player = Global::GetMainPlayer();

	health = 100;

	// Random position for coins
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<float> uniform_pos(-1, 1);
	init_velocity_x = uniform_pos(e1);
	init_velocity_y = uniform_pos(e1);
	velocity_x = init_velocity_x;
	velocity_y = init_velocity_y;

	stateMachine = new EnemyStateMachine();
	static_cast<EnemyStateMachine*>(stateMachine)->SetEnemy(this);
	stateMachine->SetCurrentState(EnemyStateMachine::EnemyState::Patrol);
	stateMachine->init();
}

void Enemy::update()
{
	stateMachine->update();

	Character::update();
}

void Enemy::render(SDL_Renderer* ren)
{
	Character::render(ren);

	Decay(ren);
}

void Enemy::SetHitColor(const float& r, const float& g, const float& b, const float& a)
{
	hit_color[0] = r;
	hit_color[1] = g;
	hit_color[2] = b;
	hit_color[3] = a;
}

void Enemy::CollisionResponse(GameObject* other)
{
	if (!active)
		return;

	if (other->GetObjectType() == ObjectType::BULLET)
	{
		if (health <= 0)
		{
			DeleteObject(this);
		}

		SetHitColor(255, 255, 255, 255);

		health -= 100;
		DeleteObject(other);
	}

	if (other->GetObjectType() == ObjectType::WALL || other->GetObjectType() == ObjectType::DOOR)
	{
		SetVel(-velocity_x, -velocity_y);
		Translate(velocity_x, velocity_y);
	}
}

void Enemy::Decay(SDL_Renderer* ren)
{
	if (hit_color[0] == 0.0)
	{
		SwitchState("idle");
		return;
	}

	// If getting hurt
	SwitchState("hurt");

	hit_color[0] *= decayrate;
	hit_color[1] *= decayrate;
	hit_color[2] *= decayrate;
	hit_color[3] *= decayrate;

	if (hit_color[0] < 1.0f)
		hit_color[0] = hit_color[1] = hit_color[2] = hit_color[3] = 0.0f;

	Camera* camera = Global::GetMainCamera();
	SDL_FPoint pos = camera->GetPos();

	SDL_FRect bb = this->GetBoxCollider();

	float x = bb.x - pos.x;
	float y = bb.y - pos.y;

	// Draw hit color
	SDL_SetRenderDrawColor(ren, hit_color[0], hit_color[1], hit_color[2], hit_color[3]);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	SDL_FRect box;
	box = { x, y, rect.w, rect.h };
	SDL_RenderFillRectF(ren, &box);
}


void SushiBoss::update()
{
	// Check if the player close enough
	if (player)
	{
		float distance = Vector2D::Distance(player->GetGlobalPosition(), GetGlobalPosition());
		if (distance < range)
		{
			// Attack the player
			SDL_FPoint self_pos = GetGlobalPosition();
			SDL_FPoint player_pos = player->GetGlobalPosition();

			SDL_FPoint dir{ player_pos.x - self_pos.x, player_pos.y - self_pos.y };
			dir = Vector2D::Normal(dir);

			start_time = SDL_GetTicks();
			if (start_time >= (last_time + 2000)) {
				last_time = start_time;

				Bomb* bullet = new Bomb("./images/bomb1.png", self_pos.x, self_pos.y);
				bullet->init();
				bullet->SetDirection(dir);
				bullet->SetSpeed(2.0f);
				bullet->SetObjectType(ObjectType::ENEMY_BULLET);
				AddInstance(bullet);
			}
		}
	}
}

void SushiBoss::CollisionResponse(GameObject* other)
{
	if (!active)
		return;

	if (other->GetObjectType() == ObjectType::BULLET)
	{
		SetHitColor(255, 255, 255, 255);

		health -= 10;
		DeleteObject(other);

		if (health <= 0)
		{
			// Create portal
			SDL_FPoint pos = GetGlobalPosition();
			Portal* portal = new Portal(pos.x + 100, pos.y, "./images/Portal.png");
			portal->init();
			portal->SetObjectType(ObjectType::PORTAL);
			AddInstance(portal);

			DeleteObject(this);
		}
	}
}

void SushiBoss::Decay(SDL_Renderer* ren)
{
	if (hit_color[0] == 0.0)
	{
		SwitchState("idle");
		return;
	}

	// If getting hurt
	SwitchState("hurt");

	hit_color[0] *= decayrate;
	hit_color[1] *= decayrate;
	hit_color[2] *= decayrate;
	hit_color[3] *= decayrate;

	if (hit_color[0] < 1.0f)
		hit_color[0] = hit_color[1] = hit_color[2] = hit_color[3] = 0.0f;

	Camera* camera = Global::GetMainCamera();
	SDL_FPoint pos = camera->GetPos();

	SDL_FRect bb = this->GetBoxCollider();

	float x = bb.x - pos.x;
	float y = bb.y - pos.y;

	// Draw hit color
	SDL_SetRenderDrawColor(ren, hit_color[0], hit_color[1], hit_color[2], hit_color[3]);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	SDL_FRect box;
	box = { x, y, rect.w, rect.h };
	SDL_RenderFillRectF(ren, &box);
}
