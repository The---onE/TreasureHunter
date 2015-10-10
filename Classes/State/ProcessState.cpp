#include "StateList.h"

bool ProcessState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	if (time > PROCESS_TIME)
		CHANGE_TO_STATE(WaitActionState);

	return false;
}

bool ProcessState::entryState()
{
	return true;
}

void ProcessState::onUpdate(float dt)
{
	time += dt;
}

bool ProcessState::exitState()
{
	return true;
}