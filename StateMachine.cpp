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
	float vel_x, vel_y;
	enemy->GetVel(vel_x, vel_y);
	enemy->Translate(vel_x, vel_y);

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
	Player* player = Global::GetMainPlayer();
	SDL_FPoint enemy_pos = enemy->GetGlobalPosition();
	SDL_FPoint player_pos = player->GetGlobalPosition();

	// Direction from the enemy to the player
	SDL_FPoint dir{ player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
	dir = Vector2D::Normal(dir);
	float vel_x = dir.x * 3.0;
	float vel_y = dir.y * 3.0;
	enemy->SetVel(vel_x, vel_y);
	// Move the enemy toward to the player
	enemy->Translate(vel_x, vel_y);

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
			// Get the initial velocity for patrol state
			float vel_x, vel_y;
			enemy->GetInitVel(vel_x, vel_y);
			enemy->SetVel(vel_x, vel_y);
			enemy->Translate(vel_x, vel_y);
			SetCurrentState(EnemyState::Patrol);
		}
			
	}
}

void EnemyStateMachine::attack()
{
	// Attack the player
	Player* player = Global::GetMainPlayer();
	SDL_FPoint enemy_pos = enemy->GetGlobalPosition();
	SDL_FPoint player_pos = player->GetGlobalPosition();

	// Direction from the enemy to the player
	SDL_FPoint dir{ player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
	dir = Vector2D::Normal(dir);

	start_time = SDL_GetTicks();
	// Fire every 600 millisecond
	if (start_time >= (last_time + 600)) {
		last_time = start_time;

		// Init the bullet with position, speed, direction
		Bullet* bullet = new Bullet("./images/particle2.png", enemy_pos.x, enemy_pos.y);
		bullet->init();
		bullet->SetDirection(dir);
		bullet->SetSpeed(2.0f);
		bullet->SetObjectType(ObjectType::ENEMY_BULLET);
		// Let the scene know the gameObject, and render it
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
