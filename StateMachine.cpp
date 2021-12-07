#include "include/StateMachine.h"

void State::CheckTransitions(StateController* controller)
{
	for (auto i = 0; i < transitions.size(); i++)
	{
		bool decisionSuccessed = transitions[i]->decision->Decide(controller);

		if (decisionSuccessed) {
			controller->TransitionToState(transitions[i]->trueState);
		}
		else {
			controller->TransitionToState(transitions[i]->falseState);
		}
	}
}
