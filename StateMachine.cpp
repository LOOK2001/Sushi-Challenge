#include "include/StateMachine.h"
#include "include/Utils.h"
#include "include/Player.h"

bool EnemyStateMachine::distanceDecision(float threshold)
{
	// Check if the player close enough
	Player* player = Global::GetMainPlayer();

	if (player && enemy)
	{
		float distance = Vector2D::Distance(player->GetGlobalPosition(), enemy->GetGlobalPosition());
		if (distance < threshold)
		{
			return true;
		}
	}
	return false;
}

void EnemyStateMachine::patrol()
{
	std::cout << "patrol" << std::endl;

	float velocity_x, velocity_y;
	enemy->GetVel(velocity_x, velocity_y);
	enemy->translate(velocity_x, velocity_y);

	if (distanceDecision(enemy->GetRange()))
	{
		SetCurrentState(EnemyState::Attack);
	}
	else
	{
		SetCurrentState(EnemyState::Patrol);
	}
}

void EnemyStateMachine::chase()
{
	std::cout << "chase" << std::endl;

	Player* player = Global::GetMainPlayer();
	SDL_FPoint enemy_pos = enemy->GetGlobalPosition();
	SDL_FPoint player_pos = player->GetGlobalPosition();

	SDL_FPoint dir{ player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
	dir = Vector2D::Normal(dir);
	enemy->translate(dir.x * 3.0, dir.y * 3.0);

	if (distanceDecision(enemy->GetRange()))
	{
		SetCurrentState(EnemyState::Attack);
	}
	else
	{
		if (distanceDecision(enemy->GetRange() + 200))
			SetCurrentState(EnemyState::Chase);
		else
			SetCurrentState(EnemyState::Patrol);
	}
}

void EnemyStateMachine::attack()
{
	// Attack the player
	Player* player = Global::GetMainPlayer();
	SDL_FPoint enemy_pos = enemy->GetGlobalPosition();
	SDL_FPoint player_pos = player->GetGlobalPosition();

	SDL_FPoint dir{ player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
	dir = Vector2D::Normal(dir);

	start_time = SDL_GetTicks();
	if (start_time >= (last_time + 600)) {
		last_time = start_time;

		Bullet* bullet = new Bullet("./images/particle2.png", enemy_pos.x, enemy_pos.y);
		bullet->init();
		bullet->SetDirection(dir);
		bullet->SetSpeed(2.0f);
		bullet->SetObjectType(ObjectType::ENEMY_BULLET);
		AddInstance(bullet);
	}

	if (distanceDecision(enemy->GetRange()))
	{
		SetCurrentState(EnemyState::Attack);
	}
	else
	{
		SetCurrentState(EnemyState::Chase);
	}
}
