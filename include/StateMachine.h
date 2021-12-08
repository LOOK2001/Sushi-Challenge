#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <iostream>

#include <SDL2/SDL_timer.h>



class StateMachine;
class State
{
public:
	void UpdateState(StateMachine* controller)
	{
		DoActions(controller);
		CheckTransitions(controller);
	}

	void DoActions(StateMachine* controller) {};

private:
	void CheckTransitions(StateMachine* controller) {};
};

typedef std::function<void()> stateFunction;
typedef std::unordered_map<int, std::function<void()>> stateMap;

class StateMachine
{
public:
	virtual void init() {}
	virtual void update()
	{
		//currentState->UpdateState(this);
		auto iter = states_map.find(currentState);
		if (iter == states_map.end())
		{
			// Not found
			std::cout << "Not found state" << std::endl;
			return;
		}
		(iter->second)();
	}

	virtual void SetCurrentState(const int& newState)
	{
		currentState = newState;
	}

protected:
	stateMap states_map;
	int currentState;
};


class Patrol : public State
{

};

class Enemy;
class EnemyStateMachine : public StateMachine
{
public:

	enum EnemyState 
	{
		Patrol,
		Chase,
		Attack
	};

	virtual void init()
	{
		// States
		std::function<void()> patrol_func(std::bind(&EnemyStateMachine::patrol, this));
		states_map.emplace(EnemyState::Patrol, patrol_func);
		std::function<void()> attack_func(std::bind(&EnemyStateMachine::attack, this));
		states_map.emplace(EnemyState::Attack, attack_func);
		std::function<void()> chase_func(std::bind(&EnemyStateMachine::chase, this));
		states_map.emplace(EnemyState::Chase, chase_func);
	}

	virtual void update()
	{
		StateMachine::update();
	}

	void SetEnemy(Enemy* _enemy) { enemy = _enemy; }

	// Decision
	bool distanceDecision(float threshold);

	// States
	void patrol();

	void chase();

	void attack();

private:
	Enemy* enemy;
	int start_time;
	int last_time;
};

#endif	// STATEMACHINE_H