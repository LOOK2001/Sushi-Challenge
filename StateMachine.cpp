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
	//std::cout << "patrol" << std::endl;

	float vel_x, vel_y;
	enemy->GetVel(vel_x, vel_y);
	enemy->translate(vel_x, vel_y);

	if (distanceDecision(enemy->GetRange()))
	{
		SetCurrentState(EnemyState::Chase);
	}
	else
	{
		SetCurrentState(EnemyState::Patrol);
	}
}

void EnemyStateMachine::chase()
{
	//std::cout << "chase" << std::endl;

	Player* player = Global::GetMainPlayer();
	SDL_FPoint enemy_pos = enemy->GetGlobalPosition();
	SDL_FPoint player_pos = player->GetGlobalPosition();

	SDL_FPoint dir{ player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
	dir = Vector2D::Normal(dir);
	float vel_x = dir.x * 3.0;
	float vel_y = dir.y * 3.0;
	enemy->SetVel(vel_x, vel_y);
	enemy->translate(vel_x, vel_y);

	if (distanceDecision(50.0))
	{
		SetCurrentState(EnemyState::Attack);
	}
	else
	{
		if (distanceDecision(enemy->GetRange() + 100))
		{
			SetCurrentState(EnemyState::Chase);
		}
		else
		{
			float vel_x, vel_y;
			enemy->GetInitVel(vel_x, vel_y);
			enemy->SetVel(vel_x, vel_y);
			SetCurrentState(EnemyState::Patrol);
		}
			
	}
}

void EnemyStateMachine::attack()
{
	//std::cout << "attack" << std::endl;

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
