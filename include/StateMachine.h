#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <iostream>

#include <SDL2/SDL_timer.h>



class StateController;
class Action
{
public:
	virtual void Act(StateController* controller) {};
};

class Transition;
class StateController;
class State
{
public:
	void UpdateState(StateController* controller)
	{
		DoActions(controller);
		CheckTransitions(controller);
	}

	void DoActions(StateController* controller)
	{
		for (auto i = 0; i < actions.size(); i++)
		{
			actions[i]->Act(controller);
		}
	}

private:
	void CheckTransitions(StateController* controller);

public:
	std::vector<Action*> actions;
	std::vector<Transition*> transitions;
};


class StateController
{
public:

	void Update()
	{
		if (!isActive)
			return;
		currentState->UpdateState(this);
	}

	void TransitionToState(State* nextState)
	{
		if (nextState != remainState)
		{
			currentState = nextState;
			OnExitState();
		}
	}

	bool CheckIfCountDownElapsed(float duration)
	{
		stateTimeElapsed = SDL_GetTicks() - startTime;
		return (stateTimeElapsed >= duration);
	}

private:
	void OnStartState()
	{
		startTime = SDL_GetTicks();
	}

	void OnExitState()
	{
		startTime = 0;
		stateTimeElapsed = 0;
	}

public:
	State* currentState;
	State* remainState;
	float stateTimeElapsed;
	float startTime;

private:
	bool isActive;
};


class Decision
{
public:
	virtual bool Decide(StateController* controller) {};
};


class Transition
{
public:
	Decision* decision;
	State* trueState;
	State* falseState;
};

class PatrolAction : public Action
{
private:
	void Patrol(StateController* controller)
	{
		std::cout << "Patrol" << std::endl;
	}
};

#endif	// STATEMACHINE_H